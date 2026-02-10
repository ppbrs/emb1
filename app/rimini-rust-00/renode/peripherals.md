sysbus (SystemBus)
|   
--- adc3 (STM32F0_ADC)
|       <0x58026000, 0x580263FF>
|       
--- adcM1S2 (STM32F0_ADC)
|       <0x40022000, 0x400223FF>
|       
--- axiSram (MappedMemory)
|       <0x24000000, 0x2407FFFF>
|       
--- backupSram (MappedMemory)
|       <0x38800000, 0x38800FFF>
|       
--- bdma (STM32LDMA)
|       <0x58025400, 0x580257FF>
|       
--- canMessageRAM (ArrayMemory)
|       <0x4000AC00, 0x4000D3FF>
|       
--- cpu (CortexM)
|   |   Slot: 0
|   |   
|   --- uart (SemihostingUart)
|           
--- crc (STM32_CRC)
|       <0x58024C00, 0x58024FFF>
|       
--- dma1 (STM32DMA)
|       <0x40020000, 0x400203FF>
|       
--- dma2 (STM32DMA)
|       <0x40020400, 0x400207FF>
|       
--- dma2d (STM32DMA2D)
|       <0x52001000, 0x52001BFF>
|       
--- dmamux1 (STM32_DMAMUX)
|       <0x40020800, 0x40020BFF>
|       
--- dtcm (MappedMemory)
|       <0x20000000, 0x2001FFFF>
|       
--- ethernet (SynopsysDWCEthernetQualityOfService)
|       <0x40028000, 0x40028BFF>
|       <0x40028C00, 0x40028DFF> [region: mtl]
|       <0x40029000, 0x400291FF> [region: dma]
|       
--- externalFlash (MappedMemory)
|       <0x80000000, 0x8FFFFFFF>
|       
--- exti (STM32H7_EXTI)
|       <0x58000000, 0x580003FF>
|       
--- fdcan1 (MCAN)
|       <0x4000A000, 0x4000A3FF>
|       
--- fdcan2 (MCAN)
|       <0x4000A400, 0x4000A7FF>
|       
--- flashBank1 (MappedMemory)
|       <0x08000000, 0x080FFFFF>
|       
--- flashBank2 (MappedMemory)
|       <0x08100000, 0x081FFFFF>
|       
--- flashController (STM32H7_FlashController)
|       <0x52002000, 0x52002FFF>
|       
--- gpioPortA (STM32_GPIOPort)
|       <0x58020000, 0x580203FF>
|       
--- gpioPortB (STM32_GPIOPort)
|       <0x58020400, 0x580207FF>
|       
--- gpioPortC (STM32_GPIOPort)
|       <0x58020800, 0x58020BFF>
|       
--- gpioPortD (STM32_GPIOPort)
|       <0x58020C00, 0x58020FFF>
|       
--- gpioPortE (STM32_GPIOPort)
|       <0x58021000, 0x580213FF>
|       
--- gpioPortF (STM32_GPIOPort)
|       <0x58021400, 0x580217FF>
|       
--- gpioPortG (STM32_GPIOPort)
|       <0x58021800, 0x58021BFF>
|       
--- gpioPortH (STM32_GPIOPort)
|       <0x58021C00, 0x58021FFF>
|       
--- gpioPortI (STM32_GPIOPort)
|       <0x58022000, 0x580223FF>
|       
--- gpioPortJ (STM32_GPIOPort)
|       <0x58022400, 0x580227FF>
|       
--- gpioPortK (STM32_GPIOPort)
|       <0x58022800, 0x58022BFF>
|       
--- hsem (STM32H7_HardwareSemaphore)
|       <0x58026400, 0x580267FF>
|       
--- i2c1 (STM32F7_I2C)
|       <0x40005400, 0x400057FF>
|       
--- i2c2 (STM32F7_I2C)
|       <0x40005800, 0x40005BFF>
|       
--- i2c3 (STM32F7_I2C)
|       <0x40005C00, 0x40005FFF>
|       
--- i2c4 (STM32F7_I2C)
|       <0x58001C00, 0x58001FFF>
|       
--- itcm (MappedMemory)
|       <0x00000000, 0x0000FFFF>
|       
--- lptimer1 (STM32L0_LpTimer)
|       <0x40002400, 0x400027FF>
|       
--- lptimer2 (STM32L0_LpTimer)
|       <0x58002400, 0x580027FF>
|       
--- lptimer3 (STM32L0_LpTimer)
|       <0x58002800, 0x58002BFF>
|       
--- lptimer4 (STM32L0_LpTimer)
|       <0x58002C00, 0x58002FFF>
|       
--- lptimer5 (STM32L0_LpTimer)
|       <0x58003000, 0x580033FF>
|       
--- lpuart1 (STM32F7_USART)
|       <0x58000C00, 0x58000FFF>
|       
--- ltdc (STM32LTDC)
|       <0x50001000, 0x50001BFF>
|       
--- nvic (NVIC)
|       <0xE000E000, 0xE000EFFF>
|       
--- qspi (STM32H7_QuadSPI)
|       <0x52005000, 0x52005FFF>
|       
--- rcc (STM32H7_RCC)
|       <0x58024400, 0x580247FF>
|       
--- rng (STM32F4_RNG)
|       <0x48021800, 0x48021BFF>
|       
--- rtc (STM32F4_RTC)
|       <0x58004000, 0x580043FF>
|       
--- sdmmc (STM32HSDMMC)
|       <0x52007000, 0x52008FFF>
|       
--- sdramBank1 (MappedMemory)
|       <0xC0000000, 0xCFFFFFFF>
|       
--- sdramBank2 (MappedMemory)
|       <0xD0000000, 0xDFFFFFFF>
|       
--- spi4 (STM32H7_SPI)
|       <0x40013400, 0x400137FF>
|       
--- sram1 (MappedMemory)
|       <0x30000000, 0x3001FFFF>
|       
--- sram2 (MappedMemory)
|       <0x30020000, 0x3003FFFF>
|       
--- sram3 (MappedMemory)
|       <0x30040000, 0x30047FFF>
|       
--- sram4 (MappedMemory)
|       <0x38000000, 0x3800FFFF>
|       
--- sramBank1 (MappedMemory)
|       <0x60000000, 0x6FFFFFFF>
|       
--- sramBank2 (MappedMemory)
|       <0x70000000, 0x7FFFFFFF>
|       
--- syscfg (STM32_SYSCFG)
|       <0x58000400, 0x580007FF>
|       
--- system_flash_ro (MappedMemory)
|       <0x1FF00000, 0x1FF1FFFF>
|       
--- timer1 (STM32_Timer)
|       <0x40010000, 0x400103FF>
|       
--- timer12 (STM32_Timer)
|       <0x40001800, 0x40001BFF>
|       
--- timer13 (STM32_Timer)
|       <0x40001C00, 0x40001FFF>
|       
--- timer14 (STM32_Timer)
|       <0x40002000, 0x400023FF>
|       
--- timer15 (STM32_Timer)
|       <0x40014000, 0x400143FF>
|       
--- timer16 (STM32_Timer)
|       <0x40014400, 0x400147FF>
|       
--- timer17 (STM32_Timer)
|       <0x40014800, 0x40014BFF>
|       
--- timer2 (STM32_Timer)
|       <0x40000000, 0x400003FF>
|       
--- timer3 (STM32_Timer)
|       <0x40000400, 0x400007FF>
|       
--- timer4 (STM32_Timer)
|       <0x40000800, 0x40000BFF>
|       
--- timer5 (STM32_Timer)
|       <0x40000C00, 0x40000FFF>
|       
--- timer6 (STM32_Timer)
|       <0x40001000, 0x400013FF>
|       
--- timer7 (STM32_Timer)
|       <0x40001400, 0x400017FF>
|       
--- timer8 (STM32_Timer)
|       <0x40010400, 0x400107FF>
|       
--- uart4 (STM32F7_USART)
|       <0x40004C00, 0x40004FFF>
|       
--- uart5 (STM32F7_USART)
|       <0x40005000, 0x400053FF>
|       
--- uart7 (STM32F7_USART)
|       <0x40007800, 0x40007BFF>
|       
--- uart8 (STM32F7_USART)
|       <0x40007C00, 0x40007FFF>
|       
--- usart1 (STM32F7_USART)
|       <0x40011000, 0x400113FF>
|       
--- usart2 (STM32F7_USART)
|       <0x40004400, 0x400047FF>
|       
--- usart3 (STM32F7_USART)
|       <0x40004800, 0x40004BFF>
|       
--- usart6 (STM32F7_USART)
|       <0x40011400, 0x400117FF>
|       
--- watchdog (STM32_IndependentWatchdog)
        <0x58004800, 0x58004BFF>
