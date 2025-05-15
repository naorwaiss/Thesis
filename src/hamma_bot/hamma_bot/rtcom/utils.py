from typing import Iterable
import time


class RTComLog:
    PREFIX = "[RTCom.Client]"

    @staticmethod
    def print(*string: Iterable[object]):
        print(RTComLog.PREFIX, *string)


def get_epoch_time() -> float:
    return time.time()
