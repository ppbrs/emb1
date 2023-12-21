"""
Integation tests checking protocol on stm32h743-zephyr-sbx project.
"""
import logging

from integration_tests.serial_port import SerialPort

_logger = logging.getLogger()


def test_empty(serial_port: SerialPort) -> None:
    """
    Check that the fimware stays sane and responsive after receiving an empty command.
    """
    serial_port.write_line("")
    line = serial_port.read_line()
    assert line is None

    serial_port.write_line("qwerty")
    line = serial_port.read_line()
    assert line.startswith("protocol: ERROR: Unknown command.")
