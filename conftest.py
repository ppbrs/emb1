"""Fixtures for integrated tests."""
import sys
import time
from typing import Generator

import pytest
import serial

from integration_tests.sport import SPort

print(f"conftest.py: {sys.path=}")


@pytest.fixture  # type: ignore
def sport() -> Generator[SPort, None, None]:
    """
    Connect to the default serial port and provide a SPort object.
    """
    port = SPort.get_default_port()
    pyserial_obj = serial.Serial(
        port=port,
        baudrate=115200,
        timeout=0.3,  # read timeout
    )
    time.sleep(0.2)
    pyserial_obj.reset_input_buffer()

    yield SPort(pyserial_obj=pyserial_obj)

    time.sleep(0.2)
    pyserial_obj.reset_input_buffer()
    pyserial_obj.close()
