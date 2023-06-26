#!/usr/bin/python3
import logging
import pathlib

from emb_spy import AppSwo

if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)

    swo = AppSwo(
        host="localhost",
        port=None,
        logger_suffix="swo",
        out_path_base=pathlib.Path.cwd() / "app_swo",
        traceclkin_freq=64000000,
        trace_freq=2000000,
        tsformat=AppSwo.TimestampFormat.ABSOLUTE
        # tsformat=AppSwo.TimestampFormat.RELATIVE
    )

    swo.enable(restart=True)

    data = swo.collect(timeout=5)
    print(data)

    swo.disable()
