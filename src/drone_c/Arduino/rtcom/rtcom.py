import socket
from threading import Thread
from enum import Enum
import time
from typing import Callable, Iterable

class RTCom:
    DEBUG_MODE = True
    PING_DEBUG = False
    SEND_DEBUG = False


class _PacketTypes(Enum):
    CONNECTION = 0x01
    RAW = 0x02
    TYPED = 0x03
    
    
class _ConnectionTypes(Enum):
    SYN = 0x01
    SYN_ACK = 0x02
    ACK = 0x03
    PING = 0x10
    PONG = 0x11
    TERMINATE = 0xFF

    
class RTComClient:
    MAX_INACTIVITY = 3000
    MAX_BUFFER_SIZE = 4096
    
    def __init__(self, reconnect: bool=True):
        self.reconnect = reconnect
        
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.settimeout(RTComClient.MAX_INACTIVITY / 1000)
        
        self._connect_address: tuple[str, int] | None = None
        self._connection_receiver_thread: Thread | None = None
        self._first_connection = True
        self._connected: bool = False
        self._last_sign_of_life: float = 0
        
        self._on_receive_callback: Callable[[bytes], None] | None = None
        self._on_receive_typed_registers: dict[int, Callable[[bytes], None]] = {}
        self._on_receive_typed_default: Callable[[bytes], None] | None = None
        self._on_disconnect_callback: Callable[[], None] | None = None
    
    def connect(self, address: tuple[str, int], block: bool=True) -> None:
        self._start_connection_with(address)
        while block and not self._connected:
            pass
    
    def get_last_sign_of_life(self) -> float:
        return _epoch_time() - self._last_sign_of_life
    
    def is_connected(self) -> bool:
        return self._connected

    def emit(self, data: bytes | str) -> None:
        if isinstance(data, str):
            data = data.encode()
        self._send_packet(data, _PacketTypes.RAW)
        
    def emit_typed(self, data: bytes | str, first_byte: int | str) -> None:
        if isinstance(data, str):
            data = data.encode()
        if isinstance(first_byte, str):
            first_byte = ord(first_byte)
        data = bytes([first_byte, *bytes(data)])
        self._send_packet(data, _PacketTypes.TYPED)
        
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
    
    def disconnect(self):
        self.reconnect = False
        self._handle_disconnect()
    
    def _start_connection_with(self, address: tuple[str, int]):
        assert self._connection_receiver_thread is None, "Can't connect again."
        self._connect_address = address
        self._connection_receiver_thread = Thread(target=self._receiver, args=(address,))
        self._connection_receiver_thread.start()
        self._attempt_connection()
        
        
    def _attempt_connection(self):
        self._send_con(_ConnectionTypes.SYN)
        
    
    def _receiver(self, address: tuple[str, int]):
        while self.reconnect or self._first_connection:
            try:
                data, remote_addr = self.socket.recvfrom(RTComClient.MAX_BUFFER_SIZE)
                if remote_addr == self._connect_address and len(data) > 0:
                    self._last_sign_of_life = _epoch_time()
                    self._handle_packet_receive(data)
            except TimeoutError:
                self._first_connection = False
                if self._connected:
                    self._handle_disconnect()
                else:
                    _RTComDebug.print("Connection timed out.", ("Trying to reconnect..." if self.reconnect else ""))

                if self.reconnect:
                    self._attempt_connection()
            

    def _handle_packet_receive(self, data: bytes) -> None:
        packet_type, data = data[0], data[1:]
        match packet_type:
            case _PacketTypes.CONNECTION.value:
                self._handle_connection_packet(data)
            case _PacketTypes.RAW.value:
                if self._on_receive_callback is not None:
                    self._on_receive_callback(data)
            case _PacketTypes.TYPED.value:
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
            case _ConnectionTypes.SYN_ACK.value:
                self._send_con(_ConnectionTypes.ACK)
                self._handle_connection()
            
            case _ConnectionTypes.PING.value:
                    if len(data) > 1:
                        self._handle_ping(ping_seq=data[1])
            
                
            case _ConnectionTypes.TERMINATE.value:
                self._handle_disconnect()
                
            case _:
                pass
        
    def _handle_connection(self):
        if self._connected:
            return
        _RTComDebug.print("Connected.")
        self._connected = True
        
    def _handle_disconnect(self):
        if not self._connected:
            return
        self._connected = False;
        _RTComDebug.print("Disconnected.")
        if self._on_disconnect_callback is not None:
            self._on_disconnect_callback()

        # TODO: add support for rtcom to accept terminate
        # self._send_con(_ConnectionTypes.TERMINATE)

    def _handle_ping(self, ping_seq: int):
        if RTCom.PING_DEBUG:
            _RTComDebug.print(f"Received ping: {ping_seq}, sending back PONG")
        self._send_con(_ConnectionTypes.PONG, additional_payload=bytes([ping_seq]))
            
    def _send_packet(self, data: bytes, packet_type: _PacketTypes) -> None:
        if self._connect_address is None:
            raise Exception("Trying to send before connecting.")
        
        if packet_type not in _PacketTypes:
            raise ValueError(f"Tried to send invalid packet type. {packet_type}")
        
        data = bytearray(data)
        data.insert(0, packet_type.value)
        if RTCom.SEND_DEBUG:
            _RTComDebug.print("Sending", data, "to", self._connect_address)
        self.socket.sendto(bytes(data), self._connect_address)
    
    def _send_con(self, con_type: _ConnectionTypes, additional_payload: bytes|None = None):
        payload = [con_type.value]
        if additional_payload is not None:
            payload += additional_payload
        self._send_packet(bytes(payload), _PacketTypes.CONNECTION)
        
    
class _RTComDebug:
    PREFIX = "[RTCom.Client]"
    @staticmethod
    def print(*string: Iterable[object]):
        if RTCom.DEBUG_MODE:
            print(_RTComDebug.PREFIX, *string)
            
def _epoch_time() -> float:
    return time.time() * 1000