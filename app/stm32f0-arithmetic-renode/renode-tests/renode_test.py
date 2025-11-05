import logging
import pathlib
import time
import subprocess as sp

import asyncio
import telnetlib3
from telnetlib3.telopt import IAC, DONT, ECHO


def main() -> None:
    logger = logging.getLogger(__name__)
    logger.info("THIS IS RENODE TEST")
    # list running processes
    renode_exec_path = pathlib.PosixPath("./3party/renode_portable/renode").absolute()
    assert renode_exec_path.exists()
    assert renode_exec_path.is_file()
    logger.info("cwd: %s", pathlib.Path.cwd())
    renode_conf_path = pathlib.PosixPath(
        "./app/stm32f0-arithmetic-renode/stm32f0-arithmetic-renode.resc"
    ).absolute()
    assert renode_conf_path.exists()
    assert renode_conf_path.is_file()

    sim = sp.Popen(
        args=[
            renode_exec_path,
            "-p",  # turn off colors
            "--port",
            "4444",
            renode_conf_path,
        ],
        start_new_session=True,
    )
    logger.info("pid: %d", sim.pid)
    assert sim.returncode is None  # is running

    asyncio.run(check_sim())

    logger.info("killing")
    sim.kill()
    logger.info("exiting")


async def check_sim():
    """

    Plan:
    1. Try to connect during 5 seconds.
    2. Once connected, flush input.
    3.
    """
    logger = logging.getLogger(__name__)
    reader: telnetlib3.stream_reader.TelnetReaderUnicode | None = None
    writer: telnetlib3.stream_writer.TelnetWriterUnicode | None = None

    # Connect.
    num_attempts_max = 5
    for i in range(num_attempts_max):
        try:
            host = "localhost"
            port = 4444
            logger.info("connecting (attempt %d of %d)", i + 1, num_attempts_max)
            reader, writer = await telnetlib3.open_connection(host, port, encoding="utf8")
            logger.info("connected")
            #
            #
            break
        except OSError as err:
            logger.info("%s: %s", type(err).__name__, err)
            await asyncio.sleep(1)
    else:
        logger.info("Could not connect")
        return

    async def read(timeout: float, ignore: set[str] = set()) -> list[str]:
        res = []
        while True:
            try:
                line = await asyncio.wait_for(reader.readline(), timeout=timeout)
                if (line := line.strip()) and line not in ignore:
                    logger.info("Rx: %s", line)
                    res.append(line)
            except asyncio.TimeoutError:
                break
        return res

    async def talk(cmd: str, timeout: float = 0.25) -> str:
        logger.info("Tx: %s", cmd)
        writer.write(cmd + "\r\n")
        await writer.drain()
        return await read(timeout=timeout, ignore={cmd, "(stm32f0-arithmetic-renode)"})

    # Flush input.
    logger.info("Flushing input")
    _ = await read(timeout=3)

    # await talk(cmd="IAC DONT ECHO", timeout=1)

    # Check state
    logger.info("Checking state")
    _ = await talk(cmd="sysbus.cpu IsStarted", timeout=1.0)
    _ = await talk(cmd="sysbus.cpu IsHalted", timeout=1.0)
    _ = await talk(cmd="sysbus.cpu Start", timeout=1.0)
    _ = await talk(cmd="sysbus.cpu IsStarted", timeout=1.0)
    time.sleep(1.0)
    _ = await talk(cmd="sysbus.cpu Halt", timeout=1.0)

    _ = await talk(cmd='sysbus GetSymbolAddress "Test::suiteStarted"')

    _ = await talk(cmd='sysbus ReadDoubleWord `sysbus GetSymbolAddress "Test::suiteStarted"`')
    _ = await talk(cmd='sysbus ReadDoubleWord `sysbus GetSymbolAddress "Test::suiteFinished"`')
    _ = await talk(cmd='sysbus ReadDoubleWord `sysbus GetSymbolAddress "Test::finishCount"`')
    _ = await talk(cmd='sysbus ReadDoubleWord `sysbus GetSymbolAddress "Test::okCount"`')
    _ = await talk(cmd='sysbus ReadDoubleWord `sysbus GetSymbolAddress "Test::failCount"`')
    _ = await talk(cmd="sysbus.cpu PC")

    return


if __name__ == "__main__":
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s.%(msecs)03d %(levelname)-8s %(message)s",
        datefmt="%H:%M:%S",
    )
    main()
