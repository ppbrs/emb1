


"""
Application that can read and print the contents of multiple registers of
an STM32H743 MCU connected via OpenOCD.
"""
# Standard library imports
# Third party imports
# Local application/library imports
from emb_spy import AppStatic
from emb_spy import MmregSTM32F051

HOST, PORT = "localhost", 4444  # Default port when started manually.
# HOST, PORT = "localhost", 50002  # Port number when started by VSCode/CortexDebug.

CONFIG = {
    # "CONTROL": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "PRIMASK": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "xPSR": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "SP": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "PSP": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "MSP": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "LR": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "PC": dict(bits=True, bits_descr=False, bits_val_descr=True),

    # "SHPR2": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "SHPR3": dict(bits=True, bits_descr=False, bits_val_descr=True),

    # "RCC_CR": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "RCC_CFGR": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "RCC_AHBENR": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "RCC_APB2ENR": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "RCC_APB1ENR": dict(bits=True, bits_descr=False, bits_val_descr=True),

    # "GPIOC_MODER": dict(bits=True, bits_descr=False, bits_val_descr=True),

    # "SYST_CSR": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "SYST_RVR": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "SYST_CVR": dict(bits=True, bits_descr=False, bits_val_descr=True),
    # "SYST_CALIB": dict(bits=True, bits_descr=False, bits_val_descr=True),

    "TIM2_CNT": dict(bits=True, bits_descr=False, bits_val_descr=True),
    "TIM2_PSC": dict(bits=True, bits_descr=False, bits_val_descr=True),
    "TIM2_ARR": dict(bits=True, bits_descr=False, bits_val_descr=True),

}


if __name__ == "__main__":
    AppStatic(config=CONFIG, host=HOST, port=PORT, registers=MmregSTM32F051())()
