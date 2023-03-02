"""
Module for awaiting or registering callbacks on all events emitted by Dolphin.

The odd-looking Protocol classes are just a lot of syntax to essentially describe
the callback's signature. See https://www.python.org/dev/peps/pep-0544/#callback-protocols
"""
from typing import Protocol, type_check_only
from collections.abc import Callable


def on_frameadvance(callback: Callable[[], None] | None) -> None:
    """
    Registers a callback to be called every time the game has rendered a new frame.
    """


async def frameadvance() -> None:
    """
    Awaitable event that completes once the game has rendered a new frame.
    """


@type_check_only
class _MemorybreakpointCallback(Protocol):
    def __call__(self, is_write: bool, addr: int, value: int) -> None:
        """
        Example callback stub for on_memorybreakpoint.

        :param is_write: true if a value was written, false if it was read
        :param addr: address that was accessed
        :param value: new value at the given address
        """


def on_memorybreakpoint(callback: _MemorybreakpointCallback | None) -> None:
    """
    Registers a callback to be called every time a previously added memory breakpoint is hit.

    :param callback:
    :return:
    """


async def memorybreakpoint() -> tuple[bool, int, int]:
    """
    Awaitable event that completes once a previously added memory breakpoint is hit.
    """


def system_reset() -> None:
    """
    Resets the emulation.
    """
