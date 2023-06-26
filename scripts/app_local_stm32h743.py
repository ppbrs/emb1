#!/usr/bin/python3
"""
Analyzing registers when disconnected.
"""

# Standard library imports
# Third party imports
# Local application/library imports
from registers.arm.armv7e_m.stm32.stm32h.registers_stm32h743 import RegistersSTM32H743


CONFIG = {
    "PSR": dict(value=0x21000000, bits=True, bits_descr=False, bits_val_descr=True),
}


class AppLocalSTM32H743:
    """ A class that contains methods of the application.
    """
    def __init__(self, config: dict[str, dict]):
        self.config = config

    def __call__(self):

        regs_dict_name = RegistersSTM32H743().get_dict_name()

        reg_addresses: list[int] = [reg.addr for reg_name, reg in regs_dict_name.items()
                                    if reg_name in self.config.keys()]
        if not reg_addresses:
            print("There is nothing to read.")
            return

        for reg_name, reg_config in self.config.items():
            if reg_config is None:
                reg_config = {}
            reg_str = regs_dict_name[reg_name].get_str(**reg_config)
            print(reg_str, "\n")


if __name__ == "__main__":
    AppLocalSTM32H743(config=CONFIG)()
