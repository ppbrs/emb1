#!/usr/bin/python3
"""
Application that can read and print the contents of multiple registers of
an STM32H743 MCU connected via OpenOCD.
"""
# Standard library imports
import ctypes
import logging
import pathlib
# Third party imports
# Local application/library imports
from emb_spy import AppStaticReader, MmregSTM32H743

HOST, PORT = "localhost", 4444
HOST, PORT = "localhost", None

TARGET0 = "stm32h7x.cpu0"

ELF_PATH = pathlib.Path.cwd().parent / "bin" / "stm32h743-sbx.elf"

CONFIG = {
    mmreg_name: AppStaticReader.Config()
    for mmreg_name in MmregSTM32H743().get_names()
    # if mmreg_name.startswith("DEMCR")
    if (False
        # or mmreg_name.startswith("SWO_CODR")
        # or mmreg_name.startswith("SWO_SPPR")
        # or mmreg_name.startswith("SWTF_CTRL")
        # or mmreg_name.startswith("DBGMCU_IDC")
        # or mmreg_name.startswith("DBGMCU_CR")
        # or mmreg_name.startswith("ITM_TER")

        # or mmreg_name == "GPIOB_MODER"
        or mmreg_name.startswith("GPIOB")
        )
}

CONFIG = {
    # "GPIOB_MODER.MODER10": AppStaticReader.Config(),
    # "GPIOB_MODER.MODER12": AppStaticReader.Config()
    "DBGMCU_CR": AppStaticReader.Config()
}

CONFIG.update({
    # "g_fault_cnt_channel_overcurrent": AppStaticReader.Config(ctype=ctypes.c_uint32),
    # "g_fault_cnt_temperature": AppStaticReader.Config(ctype=ctypes.c_uint32),
    # "g_fault_cnt_channel_generator": AppStaticReader.Config(ctype=ctypes.c_uint32),

    # "g_measuredCurrent": AppStaticReader.Config(ctype=ctypes.c_int32),
    # "g_currentMax": AppStaticReader.Config(ctype=ctypes.c_uint32),
})


if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
    assert ELF_PATH.exists() and ELF_PATH.is_file()

    res = AppStaticReader(
        config=CONFIG,
        host=HOST, port=PORT,
        target_name=TARGET0, logger_suffix="H7",
        registers=MmregSTM32H743(),
        elf_path=ELF_PATH,
        start_if_reset=False
    )()
    print(f"{res=}")
