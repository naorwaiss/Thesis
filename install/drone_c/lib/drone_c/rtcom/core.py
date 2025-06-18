from enum import Enum
from typing import TypeAlias

SocketAddress: TypeAlias = tuple[str, int]


class PacketTypes(Enum):
    CONNECTION = 0x01
    RAW = 0x02
    TYPED = 0x03


class ConnectionTypes(Enum):
    SYN = 0x01
    SYN_ACK = 0x02
    ACK = 0x03
    PING = 0x10
    PONG = 0x11
    TERMINATE = 0xFF


class RTComException(Exception):
    message: str
    code: int | None

    def __init__(self, message: str, code: int | None = None):
        self.message = message
        self.code = code
        super().__init__(self.message)

    def __str__(self):
        return f"RTComException: {self.message} (Error Code: {self.code})" if self.code else f"RTComException: {self.message}"
