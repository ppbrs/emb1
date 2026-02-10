/*
The Part of the linker script for Rimini board.

The linker (rust-lld) use cortex-m-rt crate's link.x file as the linker script,
which uses this memory.x as a dependency.
*/
MEMORY

/* STM32FH743 */	
{
  /* First block of flash. */
  FLASH : ORIGIN = 0x08000000, LENGTH = 0x10000000

  /* DTCM RAM */
  RAM   : ORIGIN = 0x20000000, LENGTH = 0x20000
}
