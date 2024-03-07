#!/usr/bin/python3
"""
Application that can set bits in registers according to the script.
"""

import time

from emb_spy import Backend, MmregSTM32H743


HOST, PORT = "localhost", 4444

SCRIPT = [
    # ("GPIOD_MODER", "MODER12", 1, 0),
    # ("GPIOD_BSRR", "BR12", 1, 0.02),
    # ("GPIOD_BSRR", "BS12", 1, 0.02),
    # ("GPIOD_BSRR", "BR12", 1, 0.02),
    # ("GPIOD_BSRR", "BS12", 1, 0.02),
    # ("GPIOD_BSRR", "BR12", 1, 0.02),
    # ("GPIOD_BSRR", "BS12", 1, 0.02),
    # ("GPIOD_BSRR", "BR12", 1, 0.02),
    # ("GPIOD_BSRR", "BS12", 1, 0.02),
    # ("GPIOD_BSRR", "BR12", 1, 0.02),
    # ("GPIOD_BSRR", "BS12", 1, 0.02),
    # ("GPIOD_BSRR", "BR12", 1, 0.02),

    ("GPIOE_BSRR", "BS1", 1, 0.02),
    # ("GPIOE_BSRR", "BR1", 1, 0.02),
    # ("GPIOB_BSRR", "BS14", 1, 0.02),
    # ("GPIOB_BSRR", "BR14", 1, 0.02),

]
"""
A list of tuples (register, bit, value, sleep time)

"""


class AppModifySTM32H743:
    """
    Application that can set bits in registers according to the script.
    """

    def __init__(self, script):
        self.script = script

    def __call__(self):

        regs_dict_name = MmregSTM32H743().get_dict_name()

        with Backend(host=HOST, port=PORT) as backend:

            for step in self.script:
                reg_name = step[0]
                reg_addr = regs_dict_name[reg_name].addr
                reg_bits_all = regs_dict_name[reg_name].register_bits
                for reg_bits in reg_bits_all:
                    if reg_bits.name == step[1]:
                        reg_val = backend.read_register(reg_addr)
                        reg_val_new = reg_bits.get_reg_value(reg_value=reg_val, bits_value=step[2])
                        print(f"{step} {reg_name} {reg_addr:x} {reg_val:x} {reg_val_new:x}")
                        backend.write_register(reg_addr, reg_val_new)
                        time.sleep(step[3])
                        break
                else:
                    raise ValueError


if __name__ == "__main__":
    AppModifySTM32H743(script=SCRIPT)()
