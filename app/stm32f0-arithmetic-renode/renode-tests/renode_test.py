"""
Run stm32f0-arithmetic-renode.gnu-arm-none-eabi-14.3.obj with Renode; check results.

This script is run from emb1 root and requires EMB1_TOOLCHAIN to be set.
"""

import asyncio
import logging
import os
import pathlib
import subprocess as sp
import sys
import time

import pytest

sys.path.append(os.path.abspath(os.getcwd()))

from integration_tests.build import build_helper
from renode import Connection, sim_check, sim_read, sim_talk

RENODE_EXEC_PATH = pathlib.PosixPath(
    "./../emb1-tools-infra/renode/renode-1.16.0+20260123gita3e74b5fa/renode"
).resolve()

EMB1_TOOLCHAINS = ["gnu-arm-none-eabi-14.3"]


@pytest.mark.pctest
@pytest.mark.parametrize("toolchain", EMB1_TOOLCHAINS)
def test_renode_simulation(toolchain: str) -> None:
    """
    Module's main function.

    :return: 0 if successful, non-zero otherwise
    """
    logger = logging.getLogger(__name__)
    logger.info("THIS IS RENODE TEST")

    build_helper(
        target="stm32f0-arithmetic-renode",
        toolchain=toolchain,
        sym_names_required=[],
        clean_up_after=False,
    )

    # list running processes
    assert RENODE_EXEC_PATH.exists()
    assert RENODE_EXEC_PATH.is_file()
    logger.info("cwd: %s", pathlib.Path.cwd())
    renode_conf_path = pathlib.PosixPath(
        f"./app/stm32f0-arithmetic-renode/stm32f0-arithmetic-renode.{toolchain}.resc"
    ).absolute()
    assert renode_conf_path.exists()
    assert renode_conf_path.is_file()

    sim = sp.Popen(
        args=[
            RENODE_EXEC_PATH,
            "-p",  # turn off colors
            "--port",
            "4444",
            renode_conf_path,
        ],
        start_new_session=True,
    )
    logger.info("pid: %d", sim.pid)
    assert sim.returncode is None  # is running

    asyncio.run(sim_check(func=_sim_check_business))

    logger.info("killing")
    sim.kill()
    logger.info("exiting")



async def _sim_check_business(connection: Connection):
    logger = logging.getLogger(__name__)

    # Flush input.
    logger.info("Flushing input")
    _ = await sim_read(connection=connection, timeout=3)

    # await sim_talk(cmd="IAC DONT ECHO", timeout=1)

    # Check state
    logger.info("Checking state")
    _ = await sim_talk(connection=connection, cmd="sysbus.cpu IsStarted", timeout=1.0)
    _ = await sim_talk(connection=connection, cmd="sysbus.cpu IsHalted")
    _ = await sim_talk(connection=connection, cmd="sysbus.cpu IsStarted")
    logger.info("=================================")
    _ = await sim_talk(connection=connection, cmd="start", timeout=2.0)
    time.sleep(2.0)
    _ = await sim_talk(connection=connection, cmd="sysbus.cpu PC")
    _ = await sim_talk(connection=connection, cmd="pause", timeout=1.0)
    logger.info("=================================")

    _ = await sim_talk(connection=connection, cmd='sysbus GetSymbolAddress "Test::suiteStarted"')

    _ = await sim_talk(
        connection=connection, cmd='sysbus ReadByte `sysbus GetSymbolAddress "Test::suiteStarted"`'
    )
    _ = await sim_talk(
        connection=connection, cmd='sysbus ReadByte `sysbus GetSymbolAddress "Test::suiteFinished"`'
    )
    _ = await sim_talk(
        connection=connection,
        cmd='sysbus ReadDoubleWord `sysbus GetSymbolAddress "Test::finishCount"`',
    )
    _ = await sim_talk(
        connection=connection, cmd='sysbus ReadDoubleWord `sysbus GetSymbolAddress "Test::okCount"`'
    )
    fail_count_res = await sim_talk(
        connection=connection,
        cmd='sysbus ReadDoubleWord `sysbus GetSymbolAddress "Test::failCount"`',
    )
    assert len(fail_count_res) == 1
    fail_count = int(fail_count_res[0], base=16)
    if fail_count == 0:
        logger.warning("✅")
    else:
        logger.error("✖️")
    _ = await sim_talk(connection=connection, cmd="sysbus.cpu PC")

    # _ = await sim_talk(cmd="quit", timeout=1.0)
    logger.info("=================================")
    logger.info("sim_check() done")
    return


if __name__ == "__main__":
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s.%(msecs)03d %(levelname).1s %(message)s",
        datefmt="%H:%M:%S",
    )
    TOOLCHAIN = os.environ["EMB1_TOOLCHAIN"]
    logging.info("EMB1_TOOLCHAIN: %s", TOOLCHAIN)
    assert TOOLCHAIN in EMB1_TOOLCHAINS
    test_renode_simulation(toolchain=TOOLCHAIN)
