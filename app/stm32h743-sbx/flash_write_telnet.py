#!/usr/bin/python3
"""
Connect to an OpenOCD target and write the application binary to it.

Don't forget to start OpenOCD beforehand.
"""
import pathlib
from telnetlib import Telnet

ELF_PATH = pathlib.PosixPath("../../bin/stm32h743-sbx.elf").absolute()

CMD_LIST = [
    "reset halt",
    f"program {ELF_PATH} verify reset",
    "reset run",
]

HOST = "localhost"
PORT = 4444

if __name__ == "__main__":

    with Telnet(HOST, PORT) as tn:
        print("Telnet connected.", flush=True)
        # Wait until "Open On-Chip Debugger" or any other invitation:
        rd = tn.read_until(b">", timeout=10.0)
        print("OpenOCD responds.", flush=True)

        for cmd in CMD_LIST:
            print(f"> {cmd}", flush=True)
            tn.write((cmd + "\n").encode("ascii"))
            rd = tn.read_until(b">", timeout=30.0)
            rsp_lines: list[str] = rd.decode("ascii").split("\r\n")
            for rsp_line in rsp_lines:
                rsp_line = rsp_line.strip()
                if rsp_line and rsp_line != cmd and rsp_line != ">":
                    print(f"< {rsp_line}", flush=True)
