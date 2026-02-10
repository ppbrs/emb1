#![no_main]
#![no_std]

// (https://docs.rs/cortex-m-semihosting/latest/cortex_m_semihosting/debug)
// debug::exit() is a debugging operation using a BKPT instruction
// to terminate a program and return control to the host debugger or emulator,
// passing it a success/failure code.
// The application makes a semihosting call (typically SYS_EXIT or 0x18)
// that the debugger (e.g. OpenOCD) intercepts to shut down the session.
use cortex_m_semihosting::debug;

/// Terminates the application and makes a semihosting-capable debug tool exit
/// with status code 0.
pub fn exit() -> ! {
    // semihosting::process::exit(0);
    debug::exit(debug::EXIT_SUCCESS);
    loop {} // TODO: why?
}

/// Hardfault handler.
///
/// Terminates the application and makes a semihosting-capable debug tool exit
/// with an error. This seems better than the default, which is to spin in a
/// loop.
#[cortex_m_rt::exception]
unsafe fn HardFault(_frame: &cortex_m_rt::ExceptionFrame) -> ! {
    // semihosting::process::exit(1);
    debug::exit(debug::EXIT_FAILURE);
    loop {} // TODO: why?
}
