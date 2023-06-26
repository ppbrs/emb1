#pragma once


namespace stm32h743 {
namespace nvic {

enum InterruptNumber : uint8_t {

	WWDG/*_IRQn*/                   /*= 0*/,      /*!< Window WatchDog Interrupt ( wwdg1_it, wwdg2_it)                   */
	PVD_AVD/*_IRQn*/                /*= 1*/,      /*!< PVD/AVD through EXTI Line detection Interrupt                     */
	TAMP_STAMP/*_IRQn*/             /*= 2*/,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
	RTC_WKUP/*_IRQn*/               /*= 3*/,      /*!< RTC Wakeup interrupt through the EXTI line                        */
	FLASH/*_IRQn*/                  /*= 4*/,      /*!< FLASH global Interrupt                                            */
	RCC/*_IRQn*/                    /*= 5*/,      /*!< RCC global Interrupt                                              */
	EXTI0/*_IRQn*/                  /*= 6*/,      /*!< EXTI Line0 Interrupt                                              */
	EXTI1/*_IRQn*/                  /*= 7*/,      /*!< EXTI Line1 Interrupt                                              */
	EXTI2/*_IRQn*/                  /*= 8*/,      /*!< EXTI Line2 Interrupt                                              */
	EXTI3/*_IRQn*/                  /*= 9*/,      /*!< EXTI Line3 Interrupt                                              */
	EXTI4/*_IRQn*/                  /*= 10*/,     /*!< EXTI Line4 Interrupt                                              */
	DMA1_Stream0/*_IRQn*/           /*= 11*/,     /*!< DMA1 Stream 0 global Interrupt                                    */
	DMA1_Stream1/*_IRQn*/           /*= 12*/,     /*!< DMA1 Stream 1 global Interrupt                                    */
	DMA1_Stream2/*_IRQn*/           /*= 13*/,     /*!< DMA1 Stream 2 global Interrupt                                    */
	DMA1_Stream3/*_IRQn*/           /*= 14*/,     /*!< DMA1 Stream 3 global Interrupt                                    */
	DMA1_Stream4/*_IRQn*/           /*= 15*/,     /*!< DMA1 Stream 4 global Interrupt                                    */
	DMA1_Stream5/*_IRQn*/           /*= 16*/,     /*!< DMA1 Stream 5 global Interrupt                                    */
	DMA1_Stream6/*_IRQn*/           /*= 17*/,     /*!< DMA1 Stream 6 global Interrupt                                    */
	ADC/*_IRQn*/                    /*= 18*/,     /*!< ADC1 and  ADC2 global Interrupts                                  */
	FDCAN1_IT0/*_IRQn*/             /*= 19*/,     /*!< FDCAN1 Interrupt line 0                                           */
	FDCAN2_IT0/*_IRQn*/             /*= 20*/,     /*!< FDCAN2 Interrupt line 0                                           */
	FDCAN1_IT1/*_IRQn*/             /*= 21*/,     /*!< FDCAN1 Interrupt line 1                                           */
	FDCAN2_IT1/*_IRQn*/             /*= 22*/,     /*!< FDCAN2 Interrupt line 1                                           */
	EXTI9_5/*_IRQn*/                /*= 23*/,     /*!< External Line[9:5] Interrupts                                     */
	TIM1_BRK/*_IRQn*/               /*= 24*/,     /*!< TIM1 Break Interrupt                                              */
	TIM1_UP/*_IRQn*/                /*= 25*/,     /*!< TIM1 Update Interrupt                                             */
	TIM1_TRG_COM/*_IRQn*/           /*= 26*/,     /*!< TIM1 Trigger and Commutation Interrupt                            */
	TIM1_CC/*_IRQn*/                /*= 27*/,     /*!< TIM1 Capture Compare Interrupt                                    */
	TIM2/*_IRQn*/                   /*= 28*/,     /*!< TIM2 global Interrupt                                             */
	TIM3/*_IRQn*/                   /*= 29*/,     /*!< TIM3 global Interrupt                                             */
	TIM4/*_IRQn*/                   /*= 30*/,     /*!< TIM4 global Interrupt                                             */
	I2C1_EV/*_IRQn*/                /*= 31*/,     /*!< I2C1 Event Interrupt                                              */
	I2C1_ER/*_IRQn*/                /*= 32*/,     /*!< I2C1 Error Interrupt                                              */
	I2C2_EV/*_IRQn*/                /*= 33*/,     /*!< I2C2 Event Interrupt                                              */
	I2C2_ER/*_IRQn*/                /*= 34*/,     /*!< I2C2 Error Interrupt                                              */
	SPI1/*_IRQn*/                   /*= 35*/,     /*!< SPI1 global Interrupt                                             */
	SPI2/*_IRQn*/                   /*= 36*/,     /*!< SPI2 global Interrupt                                             */
	USART1/*_IRQn*/                 /*= 37*/,     /*!< USART1 global Interrupt                                           */
	USART2/*_IRQn*/                 /*= 38*/,     /*!< USART2 global Interrupt                                           */
	USART3/*_IRQn*/                 /*= 39*/,     /*!< USART3 global Interrupt                                           */
	EXTI15_10/*_IRQn*/              /*= 40*/,     /*!< External Line[15:10] Interrupts                                   */
	RTC_Alarm/*_IRQn*/              /*= 41*/,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
	TIM8_BRK_TIM12/*_IRQn*/         /*= 43*/,     /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
	TIM8_UP_TIM13/*_IRQn*/          /*= 44*/,     /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
	TIM8_TRG_COM_TIM14/*_IRQn*/     /*= 45*/,     /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
	TIM8_CC/*_IRQn*/                /*= 46*/,     /*!< TIM8 Capture Compare Interrupt                                    */
	DMA1_Stream7/*_IRQn*/           /*= 47*/,     /*!< DMA1 Stream7 Interrupt                                            */
	FMC/*_IRQn*/                    /*= 48*/,     /*!< FMC global Interrupt                                              */
	SDMMC1/*_IRQn*/                 /*= 49*/,     /*!< SDMMC1 global Interrupt                                           */
	TIM5/*_IRQn*/                   /*= 50*/,     /*!< TIM5 global Interrupt                                             */
	SPI3/*_IRQn*/                   /*= 51*/,     /*!< SPI3 global Interrupt                                             */
	UART4/*_IRQn*/                  /*= 52*/,     /*!< UART4 global Interrupt                                            */
	UART5/*_IRQn*/                  /*= 53*/,     /*!< UART5 global Interrupt                                            */
	TIM6_DAC/*_IRQn*/               /*= 54*/,     /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
	TIM7/*_IRQn*/                   /*= 55*/,     /*!< TIM7 global interrupt                                             */
	DMA2_Stream0/*_IRQn*/           /*= 56*/,     /*!<   DMA2 Stream 0 global Interrupt                                  */
	DMA2_Stream1/*_IRQn*/           /*= 57*/,     /*!<   DMA2 Stream 1 global Interrupt                                  */
	DMA2_Stream2/*_IRQn*/           /*= 58*/,     /*!<   DMA2 Stream 2 global Interrupt                                  */
	DMA2_Stream3/*_IRQn*/           /*= 59*/,     /*!<   DMA2 Stream 3 global Interrupt                                  */
	DMA2_Stream4/*_IRQn*/           /*= 60*/,     /*!<   DMA2 Stream 4 global Interrupt                                  */
	ETH/*_IRQn*/                    /*= 61*/,     /*!< Ethernet global Interrupt                                         */
	ETH_WKUP/*_IRQn*/               /*= 62*/,     /*!< Ethernet Wakeup through EXTI line Interrupt                       */
	FDCAN_CAL/*_IRQn*/              /*= 63*/,     /*!< FDCAN Calibration unit Interrupt                                  */
	DMA2_Stream5/*_IRQn*/           /*= 68*/,     /*!< DMA2 Stream 5 global interrupt                                    */
	DMA2_Stream6/*_IRQn*/           /*= 69*/,     /*!< DMA2 Stream 6 global interrupt                                    */
	DMA2_Stream7/*_IRQn*/           /*= 70*/,     /*!< DMA2 Stream 7 global interrupt                                    */
	USART6/*_IRQn*/                 /*= 71*/,     /*!< USART6 global interrupt                                           */
	I2C3_EV/*_IRQn*/                /*= 72*/,     /*!< I2C3 event interrupt                                              */
	I2C3_ER/*_IRQn*/                /*= 73*/,     /*!< I2C3 error interrupt                                              */
	OTG_HS_EP1_OUT/*_IRQn*/         /*= 74*/,     /*!< USB OTG HS End Point 1 Out global interrupt                       */
	OTG_HS_EP1_IN/*_IRQn*/          /*= 75*/,     /*!< USB OTG HS End Point 1 In global interrupt                        */
	OTG_HS_WKUP/*_IRQn*/            /*= 76*/,     /*!< USB OTG HS Wakeup through EXTI interrupt                          */
	OTG_HS/*_IRQn*/                 /*= 77*/,     /*!< USB OTG HS global interrupt                                       */
	DCMI/*_IRQn*/                   /*= 78*/,     /*!< DCMI global interrupt                                             */
	RNG/*_IRQn*/                    /*= 80*/,     /*!< RNG global interrupt                                              */
	FPU/*_IRQn*/                    /*= 81*/,     /*!< FPU global interrupt                                              */
	UART7/*_IRQn*/                  /*= 82*/,     /*!< UART7 global interrupt                                            */
	UART8/*_IRQn*/                  /*= 83*/,     /*!< UART8 global interrupt                                            */
	SPI4/*_IRQn*/                   /*= 84*/,     /*!< SPI4 global Interrupt                                             */
	SPI5/*_IRQn*/                   /*= 85*/,     /*!< SPI5 global Interrupt                                             */
	SPI6/*_IRQn*/                   /*= 86*/,     /*!< SPI6 global Interrupt                                             */
	SAI1/*_IRQn*/                   /*= 87*/,     /*!< SAI1 global Interrupt                                             */
	LTDC/*_IRQn*/                   /*= 88*/,     /*!< LTDC global Interrupt                                             */
	LTDC_ER/*_IRQn*/                /*= 89*/,     /*!< LTDC Error global Interrupt                                       */
	DMA2D/*_IRQn*/                  /*= 90*/,     /*!< DMA2D global Interrupt                                            */
	SAI2/*_IRQn*/                   /*= 91*/,     /*!< SAI2 global Interrupt                                             */
	QUADSPI/*_IRQn*/                /*= 92*/,     /*!< Quad SPI global interrupt                                         */
	LPTIM1/*_IRQn*/                 /*= 93*/,     /*!< LP TIM1 interrupt                                                 */
	CEC/*_IRQn*/                    /*= 94*/,     /*!< HDMI-CEC global Interrupt                                         */
	I2C4_EV/*_IRQn*/                /*= 95*/,     /*!< I2C4 Event Interrupt                                              */
	I2C4_ER/*_IRQn*/                /*= 96*/,     /*!< I2C4 Error Interrupt                                              */
	SPDIF_RX/*_IRQn*/               /*= 97*/,     /*!< SPDIF-RX global Interrupt                                         */
	OTG_FS_EP1_OUT/*_IRQn*/         /*= 98*/,     /*!< USB OTG HS2 global interrupt                                      */
	OTG_FS_EP1_IN/*_IRQn*/          /*= 99*/,     /*!< USB OTG HS2 End Point 1 Out global interrupt                      */
	OTG_FS_WKUP/*_IRQn*/            /*= 100*/,    /*!< USB OTG HS2 End Point 1 In global interrupt                       */
	OTG_FS/*_IRQn*/                 /*= 101*/,    /*!< USB OTG HS2 Wakeup through EXTI interrupt                         */
	DMAMUX1_OVR/*_IRQn*/            /*= 102*/,    /*!<DMAMUX1 Overrun interrupt                                          */
	HRTIM1_Master/*_IRQn*/          /*= 103*/,    /*!< HRTIM Master Timer global Interrupts                              */
	HRTIM1_TIMA/*_IRQn*/            /*= 104*/,    /*!< HRTIM Timer A global Interrupt                                    */
	HRTIM1_TIMB/*_IRQn*/            /*= 105*/,    /*!< HRTIM Timer B global Interrupt                                    */
	HRTIM1_TIMC/*_IRQn*/            /*= 106*/,    /*!< HRTIM Timer C global Interrupt                                    */
	HRTIM1_TIMD/*_IRQn*/            /*= 107*/,    /*!< HRTIM Timer D global Interrupt                                    */
	HRTIM1_TIME/*_IRQn*/            /*= 108*/,    /*!< HRTIM Timer E global Interrupt                                    */
	HRTIM1_FLT/*_IRQn*/             /*= 109*/,    /*!< HRTIM Fault global Interrupt                                      */
	DFSDM1_FLT0/*_IRQn*/            /*= 110*/,    /*!<DFSDM Filter1 Interrupt                                            */
	DFSDM1_FLT1/*_IRQn*/            /*= 111*/,    /*!<DFSDM Filter2 Interrupt                                            */
	DFSDM1_FLT2/*_IRQn*/            /*= 112*/,    /*!<DFSDM Filter3 Interrupt                                            */
	DFSDM1_FLT3/*_IRQn*/            /*= 113*/,    /*!<DFSDM Filter4 Interrupt                                            */
	SAI3/*_IRQn*/                   /*= 114*/,    /*!< SAI3 global Interrupt                                             */
	SWPMI1/*_IRQn*/                 /*= 115*/,    /*!< Serial Wire Interface 1 global interrupt                          */
	TIM15/*_IRQn*/                  /*= 116*/,    /*!< TIM15 global Interrupt                                            */
	TIM16/*_IRQn*/                  /*= 117*/,    /*!< TIM16 global Interrupt                                            */
	TIM17/*_IRQn*/                  /*= 118*/,    /*!< TIM17 global Interrupt                                            */
	MDIOS_WKUP/*_IRQn*/             /*= 119*/,    /*!< MDIOS Wakeup  Interrupt                                           */
	MDIOS/*_IRQn*/                  /*= 120*/,    /*!< MDIOS global Interrupt                                            */
	JPEG/*_IRQn*/                   /*= 121*/,    /*!< JPEG global Interrupt                                             */
	MDMA/*_IRQn*/                   /*= 122*/,    /*!< MDMA global Interrupt                                             */
	SDMMC2/*_IRQn*/                 /*= 124*/,    /*!< SDMMC2 global Interrupt                                           */
	HSEM1/*_IRQn*/                  /*= 125*/,    /*!< HSEM1 global Interrupt                                            */
	ADC3/*_IRQn*/                   /*= 127*/,    /*!< ADC3 global Interrupt                                             */
	DMAMUX2_OVR/*_IRQn*/            /*= 128*/,    /*!<DMAMUX2 Overrun interrupt                                          */
	BDMA_Channel0/*_IRQn*/          /*= 129*/,    /*!< BDMA Channel 0 global Interrupt                                   */
	BDMA_Channel1/*_IRQn*/          /*= 130*/,    /*!< BDMA Channel 1 global Interrupt                                   */
	BDMA_Channel2/*_IRQn*/          /*= 131*/,    /*!< BDMA Channel 2 global Interrupt                                   */
	BDMA_Channel3/*_IRQn*/          /*= 132*/,    /*!< BDMA Channel 3 global Interrupt                                   */
	BDMA_Channel4/*_IRQn*/          /*= 133*/,    /*!< BDMA Channel 4 global Interrupt                                   */
	BDMA_Channel5/*_IRQn*/          /*= 134*/,    /*!< BDMA Channel 5 global Interrupt                                   */
	BDMA_Channel6/*_IRQn*/          /*= 135*/,    /*!< BDMA Channel 6 global Interrupt                                   */
	BDMA_Channel7/*_IRQn*/          /*= 136*/,    /*!< BDMA Channel 7 global Interrupt                                   */
	COMP/*_IRQn*/                   /*= 137*/ ,   /*!< COMP global Interrupt                                             */
	LPTIM2/*_IRQn*/                 /*= 138*/,    /*!< LP TIM2 global interrupt                                          */
	LPTIM3/*_IRQn*/                 /*= 139*/,    /*!< LP TIM3 global interrupt                                          */
	LPTIM4/*_IRQn*/                 /*= 140*/,    /*!< LP TIM4 global interrupt                                          */
	LPTIM5/*_IRQn*/                 /*= 141*/,    /*!< LP TIM5 global interrupt                                          */
	LPUART1/*_IRQn*/                /*= 142*/,    /*!< LP UART1 interrupt                                                */
	CRS/*_IRQn*/                    /*= 144*/,    /*!< Clock Recovery Global Interrupt                                   */
	ECC/*_IRQn*/                    /*= 145*/,    /*!< ECC diagnostic Global Interrupt                                   */
	SAI4/*_IRQn*/                   /*= 146*/,    /*!< SAI4 global interrupt                                             */
	WAKEUP_PIN/*_IRQn*/             /*= 149*/,    /*!< Interrupt for all 6 wake-up pins                                  */

	NUMBER,
};
}
}