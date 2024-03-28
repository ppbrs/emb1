"""
Integation tests checking protocol on stm32h743-zephyr-sbx project.
"""
import logging

from integration_tests.sport import SPort

_logger = logging.getLogger()


def test_empty(sport: SPort) -> None:
    """
    Check that the fimware stays sane and responsive after receiving an empty command.
    """
    sport.write_line("")
    line = sport.read_line()
    assert line is None

    sport.write_line("qwerty")
    line = sport.read_line()
    assert line.startswith("protocol: ERROR: Unknown command.")
