"""
A helper providing access to a serial port.
"""
import logging

import serial


class SPort:
    """
    A helper providing access to a serial port.
    """

    def __init__(self, pyserial_obj: serial.Serial) -> None:
        """
        Initialize all members.
        """
        self.pyserial_obj = pyserial_obj
        self.logger = logging.getLogger(pyserial_obj.port)
        self.latest_write: str | None = None

    def write_line(self, line: str) -> None:
        """
        Write a command to the serial port.
        """
        self.pyserial_obj.write((line + "\n").encode(encoding="ascii"))
        self.logger.debug("> %s", line)
        self.latest_write = line

    def write(self, data: bytes) -> None:
        """
        Write a command to the serial port.
        """
        self.pyserial_obj.write(data)
        self.logger.debug("> (%d bytes)", len(data))

    def read_all(self) -> list[str]:
        """
        Read all lines until timeout.
        """
        lines = []
        while True:
            line = self.pyserial_obj.readline().decode(encoding="ascii")
            if line.endswith("\r\n"):
                line = line[:-2]
            if line == "":
                break
            self.logger.debug("< %s", line)
            lines.append(line)
        return lines

    def read_line(self) -> str | None:
        """
        Read one line.
        """
        echo_received = False
        while True:
            line_b: bytes = self.pyserial_obj.readline()
            is_timeout = not line_b
            if is_timeout:
                self.logger.debug("< (timeout)")
                return None

            line: str = line_b.decode(encoding="ascii")
            if line.endswith("\r\n"):
                line = line[:-2]
            elif line.endswith("\n"):
                line = line[:-1]
            # if line == "":
            #     return None
            is_echo = line == self.latest_write
            if is_echo:
                if echo_received:
                    is_echo = False
                else:
                    echo_received = True
            is_debug = line.startswith("D:")
            self.logger.debug("< %s%s", line, "(echo)" if is_echo else "")
            if not is_echo and not is_debug:
                return line

    def flush(self) -> None:
        """
        Discard all received data.
        """
        self.pyserial_obj.reset_input_buffer()

    @classmethod
    def get_default_port(cls) -> str | None:
        """
        Guess and return the name of an available port.
        /dev/ttyACMx is preferred over /dev/ttyUSBx
        """
        return "/dev/ttyUSB0"
