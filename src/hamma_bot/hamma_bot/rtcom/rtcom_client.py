from .core import SocketAddress, PacketTypes, ConnectionTypes, RTComException
from .utils import RTComLog, get_epoch_time
from threading import Thread, Event
from typing import Callable
from time import sleep
import socket


class RTComClient:
    # Time (in seconds) of inactivity after which the connection is considered disconnected.
    MAX_INACTIVITY: float = 3.0

    # Maximum size (in bytes) for a single received message buffer.
    MAX_BUFFER_SIZE: int = 4096

    # Time (in seconds) to wait before retrying a connection attempt after failure.
    RETRY_CONNECTION_INTERVAL: float = 1.5

    # Time (in seconds) for socket timeout when waiting for new messages.
    SOCKET_TIMEOUT: float = 0.05

    connected: bool

    _socket: socket.socket
    _connect_address: SocketAddress | None
    _connection_receiver_thread: Thread | None
    _reconnect: bool
    _first_connection: bool
    _last_sign_of_life_timestamp: float

    _on_connect_callback: Callable[[], None] | None
    _on_receive_callback: Callable[[bytes], None] | None
    _on_receive_typed_registers: dict[int, Callable[[bytes], None]]
    _on_receive_typed_default: Callable[[bytes], None] | None
    _on_disconnect_callback: Callable[[], None] | None

    def __init__(self) -> None:
        self.connected = False

        self._socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._socket.settimeout(RTComClient.SOCKET_TIMEOUT)

        self._connect_address = None
        self._connection_receiver_thread = None
        self._reconnect = True
        self._first_connection = False
        self._last_sign_of_life_timestamp = 0.0

        self._on_connect_callback = None
        self._on_receive_callback = None
        self._on_receive_typed_registers = {}
        self._on_receive_typed_default = None
        self._on_disconnect_callback = None

        self._exit_event = Event()

    def __del__(self) -> None:
        self._socket.close()
        RTComLog.print("Closed socket.")

    def is_running(self) -> bool:
        return not self._exit_event.is_set()

    def get_last_sign_of_life(self) -> float:
        if not self.connected:
            return -1
        return get_epoch_time() - self._last_sign_of_life_timestamp

    def connect(self, address: SocketAddress, reconnect: bool = True, block: bool = True) -> None:
        assert (self._connect_address is None and self._connection_receiver_thread is None), "Can't connect again."
        self._connect_address = address
        self._reconnect = reconnect
        self._first_connection = True

        self._start_connection()
        while block and not self.connected:
            if self._exit_event.is_set():
                break
            sleep(.05)

    def emit(self, data: bytes | str) -> None:
        if isinstance(data, str):
            data = data.encode()
        self._send_packet(data, PacketTypes.RAW)

    def emit_typed(self, data: bytes | str, first_byte: int | str) -> None:
        if isinstance(data, str):
            data = data.encode()
        if isinstance(first_byte, str):
            first_byte = ord(first_byte)
        data = bytes([first_byte, *bytes(data)])
        self._send_packet(data, PacketTypes.TYPED)

    def on_connect(self, callback: Callable[[], None]) -> None:
        self._on_connect_callback = callback

    def on_receive(self, callback: Callable[[bytes], None]) -> None:
        self._on_receive_callback = callback

    def on(self, first_byte: int | str, callback: Callable[[bytes], None]) -> None:
        if isinstance(first_byte, str):
            first_byte = ord(first_byte)
        self._on_receive_typed_registers[first_byte] = callback

    def on_default(self, callback: Callable[[bytes], None]) -> None:
        self._on_receive_typed_default = callback

    def on_disconnect(self, callback: Callable[[], None]) -> None:
        self._on_disconnect_callback = callback

    def disconnect(self) -> None:
        self._reconnect = False
        self._handle_disconnect()
        self.close()

    def close(self) -> None:
        self._stop_receiver()

    def _start_connection(self) -> None:
        self._connection_receiver_thread = Thread(target=self._receiver)
        self._connection_receiver_thread.start()
        self._attempt_connection()

    def _attempt_connection(self) -> None:
        self._send_con(ConnectionTypes.SYN)

    def _receiver(self) -> None:
        connection_attempt_timestamp = get_epoch_time()

        while self._reconnect or self._first_connection:
            try:
                data, remote_addr = self._socket.recvfrom(RTComClient.MAX_BUFFER_SIZE)
                if remote_addr == self._connect_address and len(data) > 0:
                    self._update_last_sign_of_life()
                    self._handle_packet_receive(data)
            except TimeoutError:
                if self._exit_event.is_set():
                    continue

                now = get_epoch_time()

                if self.connected:
                    if self.get_last_sign_of_life() >= RTComClient.MAX_INACTIVITY:
                        self._handle_disconnect()
                        RTComLog.print("Disconnected.")
                else:
                    if now - connection_attempt_timestamp >= RTComClient.RETRY_CONNECTION_INTERVAL:
                        connection_attempt_timestamp = now
                        RTComLog.print("Connection timed out.", ("Trying to reconnect..." if self._reconnect else ""))

                        if self._reconnect:
                            self._attempt_connection()

            finally:
                if self._exit_event.is_set():
                    RTComLog.print("Stopped receiver.")
                    return

    def _handle_packet_receive(self, data: bytes) -> None:
        packet_type, data = data[0], data[1:]
        match packet_type:
            case PacketTypes.CONNECTION.value:
                self._handle_connection_packet(data)
            case PacketTypes.RAW.value:
                if self._on_receive_callback is not None:
                    self._on_receive_callback(data)
            case PacketTypes.TYPED.value:
                if len(data) > 0:
                    first_byte, data = data[0], data[1:]
                    if first_byte in self._on_receive_typed_registers:
                        self._on_receive_typed_registers[first_byte](data)
                    elif self._on_receive_typed_default is not None:
                        self._on_receive_typed_default(data)
            case _:
                pass

    def _handle_connection_packet(self, data: bytes) -> None:
        if len(data) == 0:
            return

        match data[0]:
            case ConnectionTypes.SYN_ACK.value:
                self._send_con(ConnectionTypes.ACK)
                self._handle_connection()

            case ConnectionTypes.PING.value:
                if len(data) > 1:
                    self._handle_ping(ping_seq=data[1])

            case ConnectionTypes.TERMINATE.value:
                self._handle_disconnect()
            case _:
                pass

    def _handle_connection(self) -> None:
        if self.connected:
            return
        self.connected = True
        if self._on_connect_callback is not None:
            self._on_connect_callback()

    def _handle_disconnect(self) -> None:
        if not self.connected:
            return
        self.connected = False
        self._first_connection = False

        # self._send_con(ConnectionTypes.TERMINATE)
        if self._on_disconnect_callback is not None:
            self._on_disconnect_callback()

    def _handle_ping(self, ping_seq: int) -> None:
        # RTComLog.print(f"Received ping: {ping_seq}, sending back PONG.")
        self._send_con(ConnectionTypes.PONG, additional_payload=bytes([ping_seq]))

    def _update_last_sign_of_life(self) -> None:
        self._last_sign_of_life_timestamp = get_epoch_time()

    def _send_packet(self, data: bytes, packet_type: PacketTypes) -> None:
        if self._connect_address is None:
            raise RTComException("Tried to send before connecting.", code=5)

        if packet_type not in PacketTypes:
            raise ValueError(f"Tried to send invalid packet type. {packet_type}")
        data = bytearray(data)
        data.insert(0, packet_type.value)

        try:
            self._socket.sendto(bytes(data), self._connect_address)
        except OSError as e:
            # raise RTComException(f"[RTCom] No network hardware detected.{e.strerror}", code=10)
            RTComLog.print(f"[RTCom] No network hardware detected.{e.strerror}.")

    def _send_con(self, con_type: ConnectionTypes, additional_payload: bytes | None = None) -> None:
        payload = [con_type.value]
        if additional_payload is not None:
            payload += additional_payload
        self._send_packet(bytes(payload), PacketTypes.CONNECTION)

    def _stop_receiver(self) -> None:
        RTComLog.print("Stopping receiver.")
        self._exit_event.set()
        if self._connection_receiver_thread is not None:
            self._connection_receiver_thread.join()
