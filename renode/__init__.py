import asyncio
import logging
from typing import Awaitable, Callable

import telnetlib3

Connection = tuple[
    telnetlib3.stream_reader.TelnetReaderUnicode,
    telnetlib3.stream_writer.TelnetWriterUnicode,
]


async def sim_check(func: Callable[[Connection], Awaitable[None]]):
    """

    Plan:
    1. Try to connect during 5 seconds.
    2. Once connected, flush input.
    3.
    """
    logger = logging.getLogger(__name__)

    # Connect.
    num_attempts_max = 5
    for i in range(num_attempts_max):
        try:
            host = "localhost"
            port = 4444
            logger.info("connecting (attempt %d of %d)", i + 1, num_attempts_max)
            connection = await telnetlib3.open_connection(host, port, encoding="utf8")
            logger.info("connected")
            break
        except OSError as err:
            logger.info("%s: %s", type(err).__name__, err)
            await asyncio.sleep(1)
    else:
        logger.error("Could not connect")
        return -1

    try:
        await func(connection=connection)
    except Exception:
        logger.exception("Exception")


async def sim_read(
    connection: Connection,
    timeout: float,
    ignore: set[str] = set(),
) -> list[str]:
    logger = logging.getLogger(__name__)
    reader = connection[0]
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


async def sim_talk(
    connection: Connection,
    cmd: str,
    timeout: float = 0.25,
) -> list[str]:
    logger = logging.getLogger(__name__)
    logger.info("Tx: %s", cmd)
    writer = connection[1]
    writer.write(cmd + "\r\n")
    await writer.drain()
    return await sim_read(
        connection=connection,
        timeout=timeout,
        ignore={cmd, "(stm32f0-arithmetic-renode)"},
    )
