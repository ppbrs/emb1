"""Fixtures for integrated tests."""
import sys
import time
from typing import Generator

import pytest
import serial

from integration_tests.serial_port import SerialPort

print(f"conftest.py: {sys.path=}")


@pytest.fixture  # type: ignore
def serial_port() -> Generator[SerialPort, None, None]:
    """Connect to the default serial port and provide a SerialPort object."""
    serial_obj = serial.Serial(
        port="/dev/ttyACM0",
        baudrate=115200,
        timeout=0.3,  # read timeout
    )
    time.sleep(0.2)
    serial_obj.reset_input_buffer()

    yield SerialPort(serial_obj=serial_obj)

    time.sleep(0.2)
    serial_obj.reset_input_buffer()
    serial_obj.close()
