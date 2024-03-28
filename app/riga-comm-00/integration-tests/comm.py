"""
Tests for the riga-comm-00 project.

Various tests assuming a Riga board is connected to the PC via USB (both ST-link and VCP).
"""
import contextlib
import logging
import os
import pathlib
import random
import signal
import time
import subprocess as sp

import pytest
from emb_spy import ReaderStatic, Backend
from emb_spy import ReaderConfigSymbol

from integration_tests.sport import SPort

_logger = logging.getLogger(__name__)

_toolchain = "gnu"
_elf_path = pathlib.PosixPath.cwd() / "bin" / f"riga-comm-00.{_toolchain}.elf"
_openocd_cfg_path = pathlib.PosixPath.cwd() / "boards" / "riga.openocd.cfg"


@contextlib.contextmanager
def openocd():

    try:
        _ = Backend.find_openocd_telnet_port()
        oo_proc = None
        _logger.info("OpenOCD is already running.")
        yield
    except ValueError:
        _logger.info("OpenOCD is not running.")
        oo_proc = sp.Popen(args=["openocd", "-f", str(_openocd_cfg_path)], start_new_session=True, stdout=sp.DEVNULL, stderr=sp.DEVNULL)
        time.sleep(2.0)
        _logger.info(f"Started OpenOCD, PID {oo_proc.pid}.")
        # _ = Backend.find_openocd_telnet_port()
        try:
            yield
        finally:
            _logger.info(f"Terminating OpenOCD, PID {oo_proc.pid}.")
            os.kill(oo_proc.pid, signal.SIGKILL)


@pytest.mark.riga_comm_00  # type: ignore
def test_sport_receiver(sport: SPort) -> None:
    """
    Send large amounts of random bytes to the serial port and check that all bytes were received.
    """
    assert _elf_path.exists()

    # todo: Check that the binaries are identical.

    def get_rx_cnt() -> int:
        return ReaderStatic(
            config=[ReaderConfigSymbol("console::rxCnt")],
            elf_path=_elf_path,
        ).read()["console::rxCnt"].val.value

    with openocd():
        rx_cnt_0 = get_rx_cnt()
        _logger.info(f"rx_cnt={rx_cnt_0}")
        for _ in range(10):
            size = random.randint(50, 100)
            data = bytes(random.getrandbits(8) for _ in range(size))
            sport.write(data)
            rx_cnt = get_rx_cnt()
            rx_cnt_diff = rx_cnt - rx_cnt_0
            _logger.info(f"rx_cnt={rx_cnt}, rx_cnt_diff={rx_cnt_diff}")
            assert rx_cnt_diff == size
            rx_cnt_0 = rx_cnt
