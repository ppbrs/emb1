#pragma once

#include <cstdint>

namespace stm32h7 {
namespace mmreg {
namespace RCC {
struct CRBits {
	uint32_t HSION : 1;
	uint32_t HSIKERON : 1;
	uint32_t HSIRDY : 1;
	uint32_t HSIDIV : 2;
	uint32_t HSIDIVF : 1;
	uint32_t reserved1 : 1;
	uint32_t CSION : 1;
	uint32_t CSIRDY : 1;
	uint32_t CSIKERON : 1;
	uint32_t reserved2 : 2;
	uint32_t HSI48ON : 1;
	uint32_t HSI48RDY : 1;
	uint32_t D1CKRDY : 1;
	uint32_t D2CKRDY : 1;
	uint32_t HSEON : 1;
	uint32_t HSERDY : 1;
	uint32_t HSEBYP : 1;
	uint32_t HSECSSON : 1;
	uint32_t reserved3 : 4;
	uint32_t PLL1ON : 1;
	uint32_t PLL1RDY : 1;
	uint32_t PLL2ON : 1;
	uint32_t PLL2RDY : 1;
	uint32_t PLL3ON : 1;
	uint32_t PLL3RDY : 1;
	uint32_t reserved4 : 2;
};
static_assert(sizeof(CRBits) == 4U);

struct CFGRBits {
	uint32_t SW : 3;
	uint32_t SWS : 3;
	uint32_t STOPWUCK : 1;
	uint32_t STOPKERWUCK : 1;
	uint32_t RTCPRE : 6;
	uint32_t HRTIMSEL : 1;
	uint32_t TIMPRE : 1;
	uint32_t reserved : 2;
	uint32_t MCO1PRE : 4;
	uint32_t MCO1 : 3;
	uint32_t MCO2PRE : 4;
	uint32_t MCO2 : 3;
};
static_assert(sizeof(CFGRBits) == 4U);

struct D1CFGRBits {
	uint32_t HPRE : 4;
	uint32_t D1PPRE : 3;
	uint32_t reserved1 : 1;
	uint32_t D1CPRE : 4;
	uint32_t reserved2 : 20;
};
static_assert(sizeof(D1CFGRBits) == 4U);

struct D2CFGRBits {
	uint32_t reserved1 : 4;
	uint32_t D2PPRE1 : 3;
	uint32_t reserved2 : 1;
	uint32_t D2PPRE2 : 3;
	uint32_t reserved3 : 21;
};
static_assert(sizeof(D2CFGRBits) == 4U);

struct D3CFGRBits {
	uint32_t reserved1 : 4;
	uint32_t D3PPRE : 3;
	uint32_t reserved2 : 25;
};
static_assert(sizeof(D3CFGRBits) == 4U);

struct PLLCKSELRBits {
	uint32_t PLLSRC : 2;
	uint32_t reserved1 : 2;
	uint32_t DIVM1 : 6;
	uint32_t reserved2 : 2;
	uint32_t DIVM2 : 6;
	uint32_t reserved3 : 2;
	uint32_t DIVM3 : 6;
	uint32_t reserved4 : 6;
};
static_assert(sizeof(PLLCKSELRBits) == 4U);

struct PLLCFGRBits {
	uint32_t PLL1FRACEN : 1;
	uint32_t PLL1VCOSEL : 1;
	uint32_t PLL1RGE : 2;
	uint32_t PLL2FRACEN : 1;
	uint32_t PLL2VCOSEL : 1;
	uint32_t PLL2RGE : 2;
	uint32_t PLL3FRACEN : 1;
	uint32_t PLL3VCOSEL : 1;
	uint32_t PLL3RGE : 2;
	uint32_t reserved1 : 4;
	uint32_t DIVP1EN : 1;
	uint32_t DIVQ1EN : 1;
	uint32_t DIVR1EN : 1;
	uint32_t DIVP2EN : 1;
	uint32_t DIVQ2EN : 1;
	uint32_t DIVR2EN : 1;
	uint32_t DIVP3EN : 1;
	uint32_t DIVQ3EN : 1;
	uint32_t DIVR3EN : 1;
	uint32_t reserved2 : 7;
};
static_assert(sizeof(PLLCFGRBits) == 4U);

struct PLLDIVRBits {
	uint32_t DIVN : 9;
	uint32_t DIVP : 7;
	uint32_t DIVQ : 7;
	uint32_t reserved1 : 1;
	uint32_t DIVR : 7;
	uint32_t reserved2 : 1;
};
static_assert(sizeof(PLLDIVRBits) == 4U);

struct PLLFRACRBits {
	uint32_t reserved1 : 3;
	uint32_t FRACN1 : 13;
	uint32_t reserved2 : 16;
};
static_assert(sizeof(PLLFRACRBits) == 4U);

struct D1CCIPRBits {
	uint32_t FMCSEL : 2;
	uint32_t reserved1 : 2;
	uint32_t QSPISEL : 2;
	uint32_t reserved2 : 10;
	uint32_t SDMMCSEL : 1;
	uint32_t reserved3 : 11;
	uint32_t CKPERSEL : 2;
	uint32_t reserved4 : 2;
};
static_assert(sizeof(D1CCIPRBits) == 4U);

struct D2CCIP1RBits {
	uint32_t SAI1SEL : 3;
	uint32_t reserved1 : 3;
	uint32_t SAI23SEL : 3;
	uint32_t reserved2 : 3;
	uint32_t SPI123SEL : 3;
	uint32_t reserved3 : 1;
	uint32_t SPI45SEL : 3;
	uint32_t reserved4 : 1;
	uint32_t SPDIFSEL : 2;
	uint32_t reserved5 : 2;
	uint32_t DFSDM1SEL : 1;
	uint32_t reserved6 : 3;
	uint32_t FDCANSEL : 2;
	uint32_t reserved7 : 1;
	uint32_t SWPSEL : 1;
};
static_assert(sizeof(D2CCIP1RBits) == 4U);

struct D2CCIP2RBits {
	uint32_t USART234578SEL : 3;
	uint32_t USART16SEL : 3;
	uint32_t reserved1 : 2;
	uint32_t RNGSEL : 2;
	uint32_t reserved2 : 2;
	uint32_t I2C123SEL : 2;
	uint32_t reserved3 : 6;
	uint32_t USBSEL : 2;
	uint32_t CECSEL : 2;
	uint32_t reserved4 : 4;
	uint32_t LPTIM1SEL : 3;
	uint32_t reserved5 : 1;
};
static_assert(sizeof(D2CCIP2RBits) == 4U);

struct D3CCIPRBits {
	uint32_t LPUART1SEL : 3;
	uint32_t reserved1 : 5;
	uint32_t I2C4SEL : 2;
	uint32_t LPTIM2SEL : 3;
	uint32_t LPTIM345SEL : 3;
	uint32_t ADCSEL : 2;
	uint32_t reserved2 : 3;
	uint32_t SAI4ASEL : 3;
	uint32_t SAI4BSEL : 3;
	uint32_t reserved3 : 1;
	uint32_t SPI6SEL : 3;
	uint32_t reserved4 : 1;
};
static_assert(sizeof(D3CCIPRBits) == 4U);

struct CIERBits {
	uint32_t LSIRDYIE : 1;
	uint32_t LSERDYIE : 1;
	uint32_t HSIRDYIE : 1;
	uint32_t HSERDYIE : 1;
	uint32_t CSIRDYIE : 1;
	uint32_t HSI48RDYIE : 1;
	uint32_t PLL1RDYIE : 1;
	uint32_t PLL2RDYIE : 1;
	uint32_t PLL3RDYIE : 1;
	uint32_t LSECSSIE : 1;
	uint32_t reserved : 22;
};
static_assert(sizeof(CIERBits) == 4U);

struct CIFRBits {
	uint32_t LSIRDYF : 1;
	uint32_t LSERDYF : 1;
	uint32_t HSIRDYF : 1;
	uint32_t HSERDYF : 1;
	uint32_t CSIRDYF : 1;
	uint32_t HSI48RDYF : 1;
	uint32_t PLL1RDYF : 1;
	uint32_t PLL2RDYF : 1;
	uint32_t PLL3RDYF : 1;
	uint32_t LSECSSF : 1;
	uint32_t HSECSSF : 1;
	uint32_t reserved : 21;
};
static_assert(sizeof(CIFRBits) == 4U);

struct CICRBits {
	uint32_t LSIRDYC : 1;
	uint32_t LSERDYC : 1;
	uint32_t HSIRDYC : 1;
	uint32_t HSERDYC : 1;
	uint32_t CSIRDYC : 1;
	uint32_t HSI48RDYC : 1;
	uint32_t PLL1RDYC : 1;
	uint32_t PLL2RDYC : 1;
	uint32_t PLL3RDYC : 1;
	uint32_t LSECSSC : 1;
	uint32_t HSECSSC : 1;
	uint32_t reserved : 21;
};
static_assert(sizeof(CICRBits) == 4U);

struct BDCRBits {
	uint32_t LSEON : 1;
	uint32_t LSERDY : 1;
	uint32_t LSEBYP : 1;
	uint32_t LSEDRV : 2;
	uint32_t LSECSSON : 1;
	uint32_t LSECSSD : 1;
	uint32_t reserved1 : 1;
	uint32_t RTCSEL : 2;
	uint32_t reserved2 : 5;
	uint32_t RTCEN : 1;
	uint32_t BDRST : 1;
	uint32_t reserved3 : 15;
};
static_assert(sizeof(BDCRBits) == 4U);

struct CSRBits {
	uint32_t LSION : 1;
	uint32_t LSIRDY : 1;
	uint32_t reserved : 30;
};
static_assert(sizeof(CSRBits) == 4U);

struct AHB3RSTRBits {
	uint32_t MDMARST : 1;
	uint32_t reserved1 : 3;
	uint32_t DMA2DRST : 1;
	uint32_t JPGDECRST : 1;
	uint32_t reserved2 : 6;
	uint32_t FMCRST : 1;
	uint32_t reserved3 : 1;
	uint32_t QSPIRST : 1;
	uint32_t reserved4 : 1;
	uint32_t SDMMC1RST : 1;
	uint32_t reserved5 : 14;
	uint32_t CPURST : 1;
};
static_assert(sizeof(AHB3RSTRBits) == 4U);

struct AHB1RSTRBits {
	uint32_t DMA1RST : 1;
	uint32_t DMA2RST : 1;
	uint32_t reserved1 : 3;
	uint32_t ADC12RST : 1;
	uint32_t reserved2 : 9;
	uint32_t ETH1MACRST : 1;
	uint32_t reserved3 : 9;
	uint32_t USB1OTGRST : 1;
	uint32_t reserved4 : 1;
	uint32_t USB2OTGRST : 1;
	uint32_t reserved5 : 4;
};
static_assert(sizeof(AHB1RSTRBits) == 4U);

struct AHB2RSTRBits {
	uint32_t DCMIRST : 1;
	uint32_t reserved1 : 3;
	uint32_t CRYPTRST : 1;
	uint32_t HASHRST : 1;
	uint32_t RNGRST : 1;
	uint32_t reserved2 : 2;
	uint32_t SDMMC2RST : 1;
	uint32_t reserved3 : 22;
};
static_assert(sizeof(AHB2RSTRBits) == 4U);

struct AHB4RSTRBits {
	uint32_t GPIOARST : 1;
	uint32_t GPIOBRST : 1;
	uint32_t GPIOCRST : 1;
	uint32_t GPIODRST : 1;
	uint32_t GPIOERST : 1;
	uint32_t GPIOFRST : 1;
	uint32_t GPIOGRST : 1;
	uint32_t GPIOHRST : 1;
	uint32_t GPIOIRST : 1;
	uint32_t GPIOJRST : 1;
	uint32_t GPIOKRST : 1;
	uint32_t reserved1 : 8;
	uint32_t CRCRST : 1;
	uint32_t reserved2 : 1;
	uint32_t BDMARST : 1;
	uint32_t reserved3 : 2;
	uint32_t ADC3RST : 1;
	uint32_t HSEMRST : 1;
	uint32_t reserved4 : 6;
};
static_assert(sizeof(AHB4RSTRBits) == 4U);

struct APB3RSTRBits {
	uint32_t reserved1 : 3;
	uint32_t LTDCRST : 1;
	uint32_t reserved2 : 28;
};
static_assert(sizeof(APB3RSTRBits) == 4U);

struct APB1LRSTRBits {
	uint32_t TIM2RST : 1;
	uint32_t TIM3RST : 1;
	uint32_t TIM4RST : 1;
	uint32_t TIM5RST : 1;
	uint32_t TIM6RST : 1;
	uint32_t TIM7RST : 1;
	uint32_t TIM12RST : 1;
	uint32_t TIM13RST : 1;
	uint32_t TIM14RST : 1;
	uint32_t LPTIM1RST : 1;
	uint32_t reserved1 : 4;
	uint32_t SPI2RST : 1;
	uint32_t SPI3RST : 1;
	uint32_t SPDIFRXRST : 1;
	uint32_t USART2RST : 1;
	uint32_t USART3RST : 1;
	uint32_t UART4RST : 1;
	uint32_t UART5RST : 1;
	uint32_t I2C1RST : 1;
	uint32_t I2C2RST : 1;
	uint32_t I2C3RST : 1;
	uint32_t reserved2 : 3;
	uint32_t HDMICECRST : 1;
	uint32_t reserved3 : 1;
	uint32_t DAC12RST : 1;
	uint32_t UART7RST : 1;
	uint32_t UART8RST : 1;
};
static_assert(sizeof(APB1LRSTRBits) == 4U);

struct APB1HRSTRBits {
	uint32_t reserved1 : 1;
	uint32_t CRSRST : 1;
	uint32_t SWPRST : 1;
	uint32_t reserved2 : 1;
	uint32_t OPAMPRST : 1;
	uint32_t MDIOSRST : 1;
	uint32_t reserved3 : 2;
	uint32_t FDCANRST : 1;
	uint32_t reserved4 : 23;
};
static_assert(sizeof(APB1HRSTRBits) == 4U);

struct APB2RSTRBits {
	uint32_t TIM1RST : 1;
	uint32_t TIM8RST : 1;
	uint32_t reserved1 : 2;
	uint32_t USART1RST : 1;
	uint32_t USART6RST : 1;
	uint32_t reserved2 : 6;
	uint32_t SPI1RST : 1;
	uint32_t SPI4RST : 1;
	uint32_t reserved3 : 2;
	uint32_t TIM15RST : 1;
	uint32_t TIM16RST : 1;
	uint32_t TIM17RST : 1;
	uint32_t reserved4 : 1;
	uint32_t SPI5RST : 1;
	uint32_t reserved5 : 1;
	uint32_t SAI1RST : 1;
	uint32_t SAI2RST : 1;
	uint32_t SAI3RST : 1;
	uint32_t reserved6 : 3;
	uint32_t DFSDM1RST : 1;
	uint32_t HRTIMRST : 1;
	uint32_t reserved7 : 2;
};
static_assert(sizeof(APB2RSTRBits) == 4U);

struct APB4RSTRBits {
	uint32_t reserved1 : 1;
	uint32_t SYSCFGRST : 1;
	uint32_t reserved2 : 1;
	uint32_t LPUART1RST : 1;
	uint32_t reserved3 : 1;
	uint32_t SPI6RST : 1;
	uint32_t reserved4 : 1;
	uint32_t I2C4RST : 1;
	uint32_t reserved5 : 1;
	uint32_t LPTIM2RST : 1;
	uint32_t LPTIM3RST : 1;
	uint32_t LPTIM4RST : 1;
	uint32_t LPTIM5RST : 1;
	uint32_t reserved6 : 1;
	uint32_t COMP12RST : 1;
	uint32_t VREFRST : 1;
	uint32_t reserved7 : 5;
	uint32_t SAI4RST : 1;
	uint32_t reserved8 : 10;
};
static_assert(sizeof(APB4RSTRBits) == 4U);

struct GCRBits {
	uint32_t WW1RSC : 1;
	uint32_t reserved : 31;
};
static_assert(sizeof(GCRBits) == 4U);

struct D3AMRBits {
	uint32_t BDMAAMEN : 1;
	uint32_t reserved1 : 2;
	uint32_t LPUART1AMEN : 1;
	uint32_t reserved2 : 1;
	uint32_t SPI6AMEN : 1;
	uint32_t reserved3 : 1;
	uint32_t I2C4AMEN : 1;
	uint32_t reserved4 : 1;
	uint32_t LPTIM2AMEN : 1;
	uint32_t LPTIM3AMEN : 1;
	uint32_t LPTIM4AMEN : 1;
	uint32_t LPTIM5AMEN : 1;
	uint32_t reserved5 : 1;
	uint32_t COMP12AMEN : 1;
	uint32_t VREFAMEN : 1;
	uint32_t RTCAMEN : 1;
	uint32_t reserved6 : 2;
	uint32_t CRCAMEN : 1;
	uint32_t reserved7 : 1;
	uint32_t SAI4AMEN : 1;
	uint32_t reserved8 : 2;
	uint32_t ADC3AMEN : 1;
	uint32_t reserved9 : 3;
	uint32_t BKPRAMAMEN : 1;
	uint32_t SRAM4AMEN : 1;
	uint32_t reserved10 : 2;
};
static_assert(sizeof(D3AMRBits) == 4U);

struct RSRBits {
	uint32_t reserved1 : 16;
	uint32_t RMVF : 1;
	uint32_t CPURSTF : 1;
	uint32_t reserved2 : 1;
	uint32_t D1RSTF : 1;
	uint32_t D2RSTF : 1;
	uint32_t BORRSTF : 1;
	uint32_t PINRSTF : 1;
	uint32_t PORRSTF : 1;
	uint32_t SFTRSTF : 1;
	uint32_t reserved3 : 1;
	uint32_t IWDG1RSTF : 1;
	uint32_t reserved4 : 1;
	uint32_t WWDG1RSTF : 1;
	uint32_t reserved5 : 1;
	uint32_t LPWRRSTF : 1;
	uint32_t reserved6 : 1;
};
static_assert(sizeof(RSRBits) == 4U);

struct AHB3ENRBits {
	uint32_t MDMAEN : 1;
	uint32_t reserved1 : 3;
	uint32_t DMA2DEN : 1;
	uint32_t JPGDECEN : 1;
	uint32_t reserved2 : 6;
	uint32_t FMCEN : 1;
	uint32_t reserved3 : 1;
	uint32_t QSPIEN : 1;
	uint32_t reserved4 : 1;
	uint32_t SDMMC1EN : 1;
	uint32_t reserved5 : 15;
};
static_assert(sizeof(AHB3ENRBits) == 4U);

struct AHB1ENRBits {
	uint32_t DMA1EN : 1;
	uint32_t DMA2EN : 1;
	uint32_t reserved1 : 3;
	uint32_t ADC12EN : 1;
	uint32_t reserved2 : 9;
	uint32_t ETH1MACEN : 1;
	uint32_t ETH1TXEN : 1;
	uint32_t ETH1RXEN : 1;
	uint32_t reserved3 : 7;
	uint32_t USB1OTGHSEN : 1;
	uint32_t USB1OTGHSULPIEN : 1;
	uint32_t USB2OTGHSEN : 1;
	uint32_t reserved4 : 4;
};
static_assert(sizeof(AHB1ENRBits) == 4U);

struct AHB2ENRBits {
	uint32_t DCMIEN : 1;
	uint32_t reserved1 : 3;
	uint32_t CRYPTEN : 1;
	uint32_t HASHEN : 1;
	uint32_t RNGEN : 1;
	uint32_t reserved2 : 2;
	uint32_t SDMMC2EN : 1;
	uint32_t reserved3 : 19;
	uint32_t SRAM1EN : 1;
	uint32_t SRAM2EN : 1;
	uint32_t SRAM3EN : 1;
};
static_assert(sizeof(AHB2ENRBits) == 4U);

struct AHB4ENRBits {
	uint32_t GPIOAEN : 1;
	uint32_t GPIOBEN : 1;
	uint32_t GPIOCEN : 1;
	uint32_t GPIODEN : 1;
	uint32_t GPIOEEN : 1;
	uint32_t GPIOFEN : 1;
	uint32_t GPIOGEN : 1;
	uint32_t GPIOHEN : 1;
	uint32_t GPIOIEN : 1;
	uint32_t GPIOJEN : 1;
	uint32_t GPIOKEN : 1;
	uint32_t reserved1 : 8;
	uint32_t CRCEN : 1;
	uint32_t reserved2 : 1;
	uint32_t BDMAEN : 1;
	uint32_t reserved3 : 2;
	uint32_t ADC3EN : 1;
	uint32_t HSEMEN : 1;
	uint32_t reserved4 : 2;
	uint32_t BKPRAMEN : 1;
	uint32_t reserved5 : 3;
};
static_assert(sizeof(AHB4ENRBits) == 4U);

struct APB3ENRBits {
	uint32_t reserved1 : 3;
	uint32_t LTDCEN : 1;
	uint32_t reserved2 : 2;
	uint32_t WWDG1EN : 1;
	uint32_t reserved3 : 25;
};
static_assert(sizeof(APB3ENRBits) == 4U);

struct APB1LENRBits {
	uint32_t TIM2EN : 1;
	uint32_t TIM3EN : 1;
	uint32_t TIM4EN : 1;
	uint32_t TIM5EN : 1;
	uint32_t TIM6EN : 1;
	uint32_t TIM7EN : 1;
	uint32_t TIM12EN : 1;
	uint32_t TIM13EN : 1;
	uint32_t TIM14EN : 1;
	uint32_t LPTIM1EN : 1;
	uint32_t reserved1 : 4;
	uint32_t SPI2EN : 1;
	uint32_t SPI3EN : 1;
	uint32_t SPDIFRXEN : 1;
	uint32_t USART2EN : 1;
	uint32_t USART3EN : 1;
	uint32_t UART4EN : 1;
	uint32_t UART5EN : 1;
	uint32_t I2C1EN : 1;
	uint32_t I2C2EN : 1;
	uint32_t I2C3EN : 1;
	uint32_t reserved2 : 3;
	uint32_t HDMICECEN : 1;
	uint32_t reserved3 : 1;
	uint32_t DAC12EN : 1;
	uint32_t UART7EN : 1;
	uint32_t UART8EN : 1;

	static constexpr uint32_t TIM2ENMask = (1 << 0);
	static constexpr uint32_t TIM3ENMask = (1 << 1);
	static constexpr uint32_t TIM4ENMask = (1 << 2);
	static constexpr uint32_t TIM5ENMask = (1 << 3);
};
static_assert(sizeof(APB1LENRBits) == 4U);

struct APB1HENRBits {
	uint32_t reserved1 : 1;
	uint32_t CRSEN : 1;
	uint32_t SWPEN : 1;
	uint32_t reserved2 : 1;
	uint32_t OPAMPEN : 1;
	uint32_t MDIOSEN : 1;
	uint32_t reserved3 : 2;
	uint32_t FDCANEN : 1;
	uint32_t reserved4 : 23;
};
static_assert(sizeof(APB1HENRBits) == 4U);

struct APB2ENRBits {
	uint32_t TIM1EN : 1;
	uint32_t TIM8EN : 1;
	uint32_t reserved1 : 2;
	uint32_t USART1EN : 1;
	uint32_t USART6EN : 1;
	uint32_t reserved2 : 6;
	uint32_t SPI1EN : 1;
	uint32_t SPI4EN : 1;
	uint32_t reserved3 : 2;
	uint32_t TIM15EN : 1;
	uint32_t TIM16EN : 1;
	uint32_t TIM17EN : 1;
	uint32_t reserved4 : 1;
	uint32_t SPI5EN : 1;
	uint32_t reserved5 : 1;
	uint32_t SAI1EN : 1;
	uint32_t SAI2EN : 1;
	uint32_t SAI3EN : 1;
	uint32_t reserved6 : 3;
	uint32_t DFSDM1EN : 1;
	uint32_t HRTIMEN : 1;
	uint32_t reserved7 : 2;
};
static_assert(sizeof(APB2ENRBits) == 4U);

struct APB4ENRBits {
	uint32_t reserved1 : 1;
	uint32_t SYSCFGEN : 1;
	uint32_t reserved2 : 1;
	uint32_t LPUART1EN : 1;
	uint32_t reserved3 : 1;
	uint32_t SPI6EN : 1;
	uint32_t reserved4 : 1;
	uint32_t I2C4EN : 1;
	uint32_t reserved5 : 1;
	uint32_t LPTIM2EN : 1;
	uint32_t LPTIM3EN : 1;
	uint32_t LPTIM4EN : 1;
	uint32_t LPTIM5EN : 1;
	uint32_t reserved6 : 1;
	uint32_t COMP12EN : 1;
	uint32_t VREFEN : 1;
	uint32_t RTCAPBEN : 1;
	uint32_t reserved7 : 4;
	uint32_t SAI4EN : 1;
	uint32_t reserved8 : 10;
};
static_assert(sizeof(APB4ENRBits) == 4U);

struct AHB3LPENRBits {
	uint32_t MDMALPEN : 1;
	uint32_t reserved1 : 3;
	uint32_t DMA2DLPEN : 1;
	uint32_t JPGDECLPEN : 1;
	uint32_t reserved2 : 2;
	uint32_t FLASHLPEN : 1;
	uint32_t reserved3 : 3;
	uint32_t FMCLPEN : 1;
	uint32_t reserved4 : 1;
	uint32_t QSPILPEN : 1;
	uint32_t reserved5 : 1;
	uint32_t SDMMC1LPEN : 1;
	uint32_t reserved6 : 11;
	uint32_t DTCM1LPEN : 1;
	uint32_t DTCM2LPEN : 1;
	uint32_t ITCMLPEN : 1;
	uint32_t AXISRAMLPEN : 1;
};
static_assert(sizeof(AHB3LPENRBits) == 4U);

struct AHB1LPENRBits {
	uint32_t DMA1LPEN : 1;
	uint32_t DMA2LPEN : 1;
	uint32_t reserved1 : 3;
	uint32_t ADC12LPEN : 1;
	uint32_t reserved2 : 9;
	uint32_t ETH1MACLPEN : 1;
	uint32_t ETH1TXLPEN : 1;
	uint32_t ETH1RXLPEN : 1;
	uint32_t reserved3 : 7;
	uint32_t USB1OTGHSLPEN : 1;
	uint32_t USB1OTGHSULPILPEN : 1;
	uint32_t USB2OTGHSLPEN : 1;
	uint32_t USB2OTGHSULPILPEN : 1;
	uint32_t reserved4 : 3;
};
static_assert(sizeof(AHB1LPENRBits) == 4U);

struct AHB2LPENRBits {
	uint32_t DCMILPEN : 1;
	uint32_t reserved1 : 3;
	uint32_t CRYPTLPEN : 1;
	uint32_t HASHLPEN : 1;
	uint32_t RNGLPEN : 1;
	uint32_t reserved2 : 2;
	uint32_t SDMMC2LPEN : 1;
	uint32_t reserved3 : 19;
	uint32_t SRAM1LPEN : 1;
	uint32_t SRAM2LPEN : 1;
	uint32_t SRAM3LPEN : 1;
};
static_assert(sizeof(AHB2LPENRBits) == 4U);

struct AHB4LPENRBits {
	uint32_t GPIOALPEN : 1;
	uint32_t GPIOBLPEN : 1;
	uint32_t GPIOCLPEN : 1;
	uint32_t GPIODLPEN : 1;
	uint32_t GPIOELPEN : 1;
	uint32_t GPIOFLPEN : 1;
	uint32_t GPIOGLPEN : 1;
	uint32_t GPIOHLPEN : 1;
	uint32_t GPIOILPEN : 1;
	uint32_t GPIOJLPEN : 1;
	uint32_t GPIOKLPEN : 1;
	uint32_t reserved1 : 8;
	uint32_t CRCLPEN : 1;
	uint32_t reserved2 : 1;
	uint32_t BDMALPEN : 1;
	uint32_t reserved3 : 2;
	uint32_t ADC3LPEN : 1;
	uint32_t reserved4 : 3;
	uint32_t BKPRAMLPEN : 1;
	uint32_t SRAM4LPEN : 1;
	uint32_t reserved5 : 2;
};
static_assert(sizeof(AHB4LPENRBits) == 4U);

struct APB3LPENRBits {
	uint32_t reserved1 : 3;
	uint32_t LTDCLPEN : 1;
	uint32_t reserved2 : 2;
	uint32_t WWDG1LPEN : 1;
	uint32_t reserved3 : 25;
};
static_assert(sizeof(APB3LPENRBits) == 4U);

struct APB1LLPENRBits {
	uint32_t TIM2LPEN : 1;
	uint32_t TIM3LPEN : 1;
	uint32_t TIM4LPEN : 1;
	uint32_t TIM5LPEN : 1;
	uint32_t TIM6LPEN : 1;
	uint32_t TIM7LPEN : 1;
	uint32_t TIM12LPEN : 1;
	uint32_t TIM13LPEN : 1;
	uint32_t TIM14LPEN : 1;
	uint32_t LPTIM1LPEN : 1;
	uint32_t reserved1 : 4;
	uint32_t SPI2LPEN : 1;
	uint32_t SPI3LPEN : 1;
	uint32_t SPDIFRXLPEN : 1;
	uint32_t USART2LPEN : 1;
	uint32_t USART3LPEN : 1;
	uint32_t UART4LPEN : 1;
	uint32_t UART5LPEN : 1;
	uint32_t I2C1LPEN : 1;
	uint32_t I2C2LPEN : 1;
	uint32_t I2C3LPEN : 1;
	uint32_t reserved2 : 3;
	uint32_t HDMICECLPEN : 1;
	uint32_t reserved3 : 1;
	uint32_t DAC12LPEN : 1;
	uint32_t UART7LPEN : 1;
	uint32_t UART8LPEN : 1;
};
static_assert(sizeof(APB1LLPENRBits) == 4U);

struct APB1HLPENRBits {
	uint32_t reserved1 : 1;
	uint32_t CRSLPEN : 1;
	uint32_t SWPLPEN : 1;
	uint32_t reserved2 : 1;
	uint32_t OPAMPLPEN : 1;
	uint32_t MDIOSLPEN : 1;
	uint32_t reserved3 : 2;
	uint32_t FDCANLPEN : 1;
	uint32_t reserved4 : 23;
};
static_assert(sizeof(APB1HLPENRBits) == 4U);

struct APB2LPENRBits {
	uint32_t TIM1LPEN : 1;
	uint32_t TIM8LPEN : 1;
	uint32_t reserved1 : 2;
	uint32_t USART1LPEN : 1;
	uint32_t USART6LPEN : 1;
	uint32_t reserved2 : 6;
	uint32_t SPI1LPEN : 1;
	uint32_t SPI4LPEN : 1;
	uint32_t reserved3 : 2;
	uint32_t TIM15LPEN : 1;
	uint32_t TIM16LPEN : 1;
	uint32_t TIM17LPEN : 1;
	uint32_t reserved4 : 1;
	uint32_t SPI5LPEN : 1;
	uint32_t reserved5 : 1;
	uint32_t SAI1LPEN : 1;
	uint32_t SAI2LPEN : 1;
	uint32_t SAI3LPEN : 1;
	uint32_t reserved6 : 3;
	uint32_t DFSDM1LPEN : 1;
	uint32_t HRTIMLPEN : 1;
	uint32_t reserved7 : 2;
};
static_assert(sizeof(APB2LPENRBits) == 4U);

struct APB4LPENRBits {
	uint32_t reserved1 : 1;
	uint32_t SYSCFGLPEN : 1;
	uint32_t reserved2 : 1;
	uint32_t LPUART1LPEN : 1;
	uint32_t reserved3 : 1;
	uint32_t SPI6LPEN : 1;
	uint32_t reserved4 : 1;
	uint32_t I2C4LPEN : 1;
	uint32_t reserved5 : 1;
	uint32_t LPTIM2LPEN : 1;
	uint32_t LPTIM3LPEN : 1;
	uint32_t LPTIM4LPEN : 1;
	uint32_t LPTIM5LPEN : 1;
	uint32_t reserved6 : 1;
	uint32_t COMP12LPEN : 1;
	uint32_t VREFLPEN : 1;
	uint32_t RTCAPBLPEN : 1;
	uint32_t reserved7 : 4;
	uint32_t SAI4LPEN : 1;
	uint32_t reserved8 : 10;
};
static_assert(sizeof(APB4LPENRBits) == 4U);

union CR {
	uint32_t word;
	CRBits bits;
};

union CFGR {
	uint32_t word;
	CFGRBits bits;
};

union D1CFGR {
	uint32_t word;
	D1CFGRBits bits;
};

union D2CFGR {
	uint32_t word;
	D2CFGRBits bits;
};

union D3CFGR {
	uint32_t word;
	D3CFGRBits bits;
};

union PLLCKSELR {
	uint32_t word;
	PLLCKSELRBits bits;
};

union PLLCFGR {
	uint32_t word;
	PLLCFGRBits bits;
};

union PLLDIVR {
	uint32_t word;
	PLLDIVRBits bits;
};

union PLLFRACR {
	uint32_t word;
	PLLFRACRBits bits;
};

union D1CCIPR {
	uint32_t word;
	D1CCIPRBits bits;
};

union D2CCIP1R {
	uint32_t word;
	D2CCIP1RBits bits;
};

union D2CCIP2R {
	uint32_t word;
	D2CCIP2RBits bits;
};

union D3CCIPR {
	uint32_t word;
	D3CCIPRBits bits;
};

union CIER {
	uint32_t word;
	CIERBits bits;
};

union CIFR {
	uint32_t word;
	CIFRBits bits;
};

union CICR {
	uint32_t word;
	CICRBits bits;
};

union BDCR {
	uint32_t word;
	BDCRBits bits;
};

union CSR {
	uint32_t word;
	CSRBits bits;
};

union AHB3RSTR {
	uint32_t word;
	AHB3RSTRBits bits;
};

union AHB1RSTR {
	uint32_t word;
	AHB1RSTRBits bits;
};

union AHB2RSTR {
	uint32_t word;
	AHB2RSTRBits bits;
};

union AHB4RSTR {
	uint32_t word;
	AHB4RSTRBits bits;
};

union APB3RSTR {
	uint32_t word;
	APB3RSTRBits bits;
};

union APB1LRSTR {
	uint32_t word;
	APB1LRSTRBits bits;
};

union APB1HRSTR {
	uint32_t word;
	APB1HRSTRBits bits;
};

union APB2RSTR {
	uint32_t word;
	APB2RSTRBits bits;
};

union APB4RSTR {
	uint32_t word;
	APB4RSTRBits bits;
};

union GCR {
	uint32_t word;
	GCRBits bits;
};

union D3AMR {
	uint32_t word;
	D3AMRBits bits;
};

union RSR {
	uint32_t word;
	RSRBits bits;
};

union AHB3ENR {
	uint32_t word;
	AHB3ENRBits bits;
};

union AHB1ENR {
	uint32_t word;
	AHB1ENRBits bits;
};

union AHB2ENR {
	uint32_t word;
	AHB2ENRBits bits;
};

union AHB4ENR {
	uint32_t word;
	AHB4ENRBits bits;
};

union APB3ENR {
	uint32_t word;
	APB3ENRBits bits;
};

union APB1LENR {
	uint32_t word;
	APB1LENRBits bits;
};

union APB1HENR {
	uint32_t word;
	APB1HENRBits bits;
};

union APB2ENR {
	uint32_t word;
	APB2ENRBits bits;
};

union APB4ENR {
	uint32_t word;
	APB4ENRBits bits;
};

union AHB3LPENR {
	uint32_t word;
	AHB3LPENRBits bits;
};

union AHB1LPENR {
	uint32_t word;
	AHB1LPENRBits bits;
};

union AHB2LPENR {
	uint32_t word;
	AHB2LPENRBits bits;
};

union AHB4LPENR {
	uint32_t word;
	AHB4LPENRBits bits;
};

union APB3LPENR {
	uint32_t word;
	APB3LPENRBits bits;
};

union APB1LLPENR {
	uint32_t word;
	APB1LLPENRBits bits;
};

union APB1HLPENR {
	uint32_t word;
	APB1HLPENRBits bits;
};

union APB2LPENR {
	uint32_t word;
	APB2LPENRBits bits;
};

union APB4LPENR {
	uint32_t word;
	APB4LPENRBits bits;
};

struct RCC {
	union CR CR; // 0x000
	uint32_t ICSCRorHSICFGR; // 0x004
	uint32_t CRRCR; // 0x008
	uint32_t reservedOrCSICFGR; // 0x00C
	union CFGR CFGR; // 0x010
	uint32_t reserved2; // 0x014
	union D1CFGR D1CFGR; // 0x018
	union D2CFGR D2CFGR; // 0x01C
	union D3CFGR D3CFGR; // 0x020
	uint32_t reserved3; // 0x024
	union PLLCKSELR PLLCKSELR; // 0x028
	union PLLCFGR PLLCFGR; // 0x02C
	union PLLDIVR PLL1DIVR; // 0x030
	union PLLFRACR PLL1FRACR; // 0x034
	union PLLDIVR PLL2DIVR; // 0x038
	union PLLFRACR PLL2FRACR; // 0x03C
	union PLLDIVR PLL3DIVR; // 0x040
	union PLLFRACR PLL3FRACR; // 0x044
	uint32_t reserved4; // 0x048
	union D1CCIPR D1CCIPR; // 0x04C
	union D2CCIP1R D2CCIP1R; // 0x050
	union D2CCIP2R D2CCIP2R; // 0x054
	union D3CCIPR D3CCIPR; // 0x058
	uint32_t reserved5; // 0x05C
	union CIER CIER; // 0x060
	union CIFR CIFR; // 0x064
	union CICR CICR; // 0x068
	uint32_t reserved6; // 0x06C
	union BDCR BDCR; // 0x070
	union CSR CSR; // 0x074
	uint32_t reserved7; // 0x078
	union AHB3RSTR AHB3RSTR; // 0x07C
	union AHB1RSTR AHB1RSTR; // 0x080
	union AHB2RSTR AHB2RSTR; // 0x084
	union AHB4RSTR AHB4RSTR; // 0x088
	union APB3RSTR APB3RSTR; // 0x08C
	union APB1LRSTR APB1LRSTR; // 0x090
	union APB1HRSTR APB1HRSTR; // 0x094
	union APB2RSTR APB2RSTR; // 0x098
	union APB4RSTR APB4RSTR; // 0x09C
	union GCR GCR; // 0x0A0
	uint32_t reserved8; // 0x0A4
	union D3AMR D3AMR; // 0x0A8
	uint32_t reserved9[(0xD0U - 0xACU) / 4U]; // 0x0AC–0x0CC
	union RSR RSR; // 0x0D0
	union AHB3ENR AHB3ENR; // 0x0D4
	union AHB1ENR AHB1ENR; // 0x0D8
	union AHB2ENR AHB2ENR; // 0x0DC
	union AHB4ENR AHB4ENR; // 0x0E0
	union APB3ENR APB3ENR; // 0x0E4
	union APB1LENR APB1LENR; // 0x0E8
	union APB1HENR APB1HENR; // 0x0EC
	union APB2ENR APB2ENR; // 0x0F0
	union APB4ENR APB4ENR; // 0x0F4
	uint32_t reserved10; // 0x0F8
	union AHB3LPENR AHB3LPENR; // 0x0FC
	union AHB1LPENR AHB1LPENR; // 0x100
	union AHB2LPENR AHB2LPENR; // 0x104
	union AHB4LPENR AHB4LPENR; // 0x108
	union APB3LPENR APB3LPENR; // 0x10C
	union APB1LLPENR APB1LLPENR; // 0x110
	union APB1HLPENR APB1HLPENR; // 0x114
	union APB2LPENR APB2LPENR; // 0x118
	union APB4LPENR APB4LPENR; // 0x11C
	// Copies (RCC_C1_*) are intentionally excluded as they are useless.
};
static_assert(sizeof(RCC) == 0x120U);

extern volatile struct RCC RCC;
}
}
}
