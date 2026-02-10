"""AnalyzerSTM32H743."""

import logging
import pathlib

from emb_spy import AnalyzerSTM32H743


def main():
    """Run the analyzer."""

    jtag_target_name = "stm32h743.rimini.cpu0"

    board_cfg = AnalyzerSTM32H743.BoardConfig(
        jtag_target_name=jtag_target_name,
        resonator_freq=24e6,
    )
    AnalyzerSTM32H743(
        board_cfg=board_cfg,
        report_file_path=pathlib.PosixPath(__file__).with_suffix(".md"),
    ).run()


if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
    main()
