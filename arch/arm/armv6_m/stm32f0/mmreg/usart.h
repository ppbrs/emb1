#pragma once

#include <cstdint>

namespace stm32f0 {
namespace mmreg {
namespace USART {

// USART control register 1 (USART_CR1)
struct CR1Bits {
	uint32_t UE : 1; // Bit 0 UE: USART enable
	uint32_t UESM : 1; // Bit 1 UESM: USART enable in Stop mode
	uint32_t RE : 1; // Bit 2 RE: Receiver enable
	uint32_t TE : 1; // Bit 3 TE: Transmitter enable
	uint32_t IDLEIE : 1; // Bit 4 IDLEIE: IDLE interrupt enable
	uint32_t RXNEIE : 1; // Bit 5 RXNEIE: RXNE interrupt enable
	uint32_t TCIE : 1; // Bit 6 TCIE: Transmission complete interrupt enable
	uint32_t TXEIE : 1; // Bit 7 TXEIE: interrupt enable
	uint32_t PEIE : 1; // Bit 8 PEIE: PE interrupt enable
	uint32_t PS : 1; // Bit 9 PS: Parity selection
	uint32_t PCE : 1; // Bit 10 PCE: Parity control enable
	uint32_t WAKE : 1; // Bit 11 WAKE: Receiver wake-up method
	uint32_t M0 : 1; // Bit 12 M0: Word length
	uint32_t MME : 1; // Bit 13 MME: Mute mode enable
	uint32_t CMIE : 1; // Bit 14 CMIE: Character match interrupt enable
	uint32_t OVER8 : 1; // Bit 15 OVER8: Oversampling mode
	uint32_t DEDT : 5; // Bits 20:16 DEDT[4:0]: Driver Enable de-assertion time
	uint32_t DEAT : 5; // Bits 25:21 DEAT[4:0]: Driver Enable assertion time
	uint32_t RTOIE : 1; // Bit 26 RTOIE: Receiver timeout interrupt enable
	uint32_t EOBIE : 1; // Bit 27 EOBIE: End of Block interrupt enable
	uint32_t M1 : 1; // Bit 28 M1: Word length
	uint32_t reserved0 : 3;
	static constexpr uint32_t TXEIEMask = (1 << 7);
};
union CR1Union {
	CR1Bits bits;
	uint32_t word;
};
static_assert(sizeof(CR1Union) == 4u);
// USART control register 2 (USART_CR2)
struct CR2Bits {
	uint32_t reserved0 : 4; // Bits 3:0 Reserved
	uint32_t ADDM7 : 1; // Bit 4 ADDM7:7-bit Address Detection/4-bit Address Detection
	uint32_t LBDL : 1; // Bit 5 LBDL: LIN break detection length
	uint32_t LBDIE : 1; // Bit 6 LBDIE: LIN break detection interrupt enable
	uint32_t reserved1 : 1; // Bit 7 Reserved, must be kept at reset value.
	uint32_t LBCL : 1; // Bit 8 LBCL: Last bit clock pulse
	uint32_t CPHA : 1; // Bit 9 CPHA: Clock phase
	uint32_t CPOL : 1; // Bit 10 CPOL: Clock polarity
	uint32_t CLKEN : 1; // Bit 11 CLKEN: Clock enable
	uint32_t STOP : 2; // Bits 13:12 STOP[1:0]: STOP bits
	uint32_t LINEN : 1; // Bit 14 LINEN: LIN mode enable
	uint32_t SWAP : 1; // Bit 15 SWAP: Swap TX/RX pins
	uint32_t RXINV : 1; // Bit 16 RXINV: RX pin active level inversion
	uint32_t TXINV : 1; // Bit 17 TXINV: TX pin active level inversion
	uint32_t DATAINV : 1; // Bit 18 DATAINV: Binary data inversion
	uint32_t MSBFIRST : 1; // Bit 19 MSBFIRST: Most significant bit first
	uint32_t ABREN : 1; // Bit 20 ABREN: Auto baud rate enable
	uint32_t ABRMOD : 2; // Bits 22:21 ABRMOD[1:0]: Auto baud rate mode
	uint32_t RTOEN : 1; // Bit 23 RTOEN: Receiver timeout enable
	uint32_t ADD03 : 4; // Bits 27:24 ADD[3:0]: Address of the USART node
	uint32_t ADD47 : 4; // Bits 31:28 ADD[7:4]: Address of the USART node
};
union CR2Union {
	CR2Bits bits;
	uint32_t word;
};
static_assert(sizeof(CR2Union) == 4u);
// USART control register 3 (USART_CR3)
struct CR3Bits {
	uint32_t EIE : 1; // Bit 0 EIE: Error interrupt enable
	uint32_t IREN : 1; // Bit 1 IREN: IrDA mode enable
	uint32_t IRLP : 1; // Bit 2 IRLP: IrDA low-power
	uint32_t HDSEL : 1; // Bit 3 HDSEL: Half-duplex selection
	uint32_t NACK : 1; // Bit 4 NACK: Smartcard NACK enable
	uint32_t SCEN : 1; // Bit 5 SCEN: Smartcard mode enable
	uint32_t DMAR : 1; // Bit 6 DMAR: DMA enable receiver
	uint32_t DMAT : 1; // Bit 7 DMAT: DMA enable transmitter
	uint32_t RTSE : 1; // Bit 8 RTSE: RTS enable
	uint32_t CTSE : 1; // Bit 9 CTSE: CTS enable
	uint32_t CTSIE : 1; // Bit 10 CTSIE: CTS interrupt enable
	uint32_t ONEBIT : 1; // Bit 11 ONEBIT: One sample bit method enable
	uint32_t OVRDIS : 1; // Bit 12 OVRDIS: Overrun Disable
	uint32_t DDRE : 1; // Bit 13 DDRE: DMA Disable on Reception Error
	uint32_t DEM : 1; // Bit 14 DEM: Driver enable mode
	uint32_t DEP : 1; // Bit 15 DEP: Driver enable polarity selection
	uint32_t reserved0 : 1; // Bit 16 Reserved, must be kept at reset value.
	uint32_t SCARCNT : 3; // Bits 19:17 SCARCNT[2:0]: Smartcard auto-retry count
	uint32_t WUS : 2; // Bits 21:20 WUS[1:0]: Wake-up from Stop mode interrupt flag selection
	uint32_t WUFIE : 1; // Bit 22 WUFIE: Wake-up from Stop mode interrupt enable
	uint32_t reserved1 : 9; // Bit 23 Reserved, must be kept at reset value.
};
union CR3Union {
	CR3Bits bits;
	uint32_t word;
};
static_assert(sizeof(CR3Union) == 4u);
// USART guard time and prescaler register (USART_GTPR)
struct GTPRBits {
	uint32_t PSC : 8; // Bits 7:0 PSC[7:0]: Prescaler value
	uint32_t GT : 8; // Bits 15:8 GT[7:0]: Guard time value
	uint32_t reserved : 16; // Bits 31:16 Reserved, must be kept at reset value.
};
union GTPRUnion {
	GTPRBits bits;
	uint32_t word;
};
static_assert(sizeof(GTPRUnion) == 4u);
// USART receiver timeout register (USART_RTOR)
union RTORBits {
	uint32_t RTO : 24; // Bits 23:0 RTO[23:0]: Receiver timeout value
	uint32_t BLEN : 8; // Bits 31:24 BLEN[7:0]: Block Length
};
union RTORUnion {
	RTORBits bits;
	uint32_t word;
};
static_assert(sizeof(RTORUnion) == 4u);
// USART request register (USART_RQR)
struct RQRStruct {
	uint32_t ABRRQ : 1; // Bit 0 ABRRQ: Auto baud rate request
	uint32_t SBKRQ : 1; // Bit 1 SBKRQ: Send break request
	uint32_t MMRQ : 1; // Bit 2 MMRQ: Mute mode request
	uint32_t RXFRQ : 1; // Bit 3 RXFRQ: Receive data flush request
	uint32_t TXFRQ : 1; // Bit 4 TXFRQ: Transmit data flush request
	uint32_t reserved : 27; // Bits 31:5 Reserved, must be kept at reset value.
};
union RQRUnion {
	RQRStruct bits;
	uint32_t word;
};
static_assert(sizeof(RQRUnion) == 4u);
// USART interrupt and status register (USART_ISR)
struct ISRStruct {
	uint32_t PE : 1; // Bit 0 PE: Parity error
	uint32_t FE : 1; // Bit 1 FE: Framing error
	uint32_t NF : 1; // Bit 2 NF: START bit Noise detection flag
	uint32_t ORE : 1; // Bit 3 ORE: Overrun error
	uint32_t IDLE : 1; // Bit 4 IDLE: Idle line detected
	uint32_t RXNE : 1; // Bit 5 RXNE: Read data register not empty
	uint32_t TC : 1; // Bit 6 TC: Transmission complete
	uint32_t TXE : 1; // Bit 7 TXE: Transmit data register empty
	uint32_t LBDF : 1; // Bit 8 LBDF: LIN break detection flag
	uint32_t CTSIF : 1; // Bit 9 CTSIF: CTS interrupt flag
	uint32_t CTS : 1; // Bit 10 CTS: CTS flag
	uint32_t RTOF : 1; // Bit 11 RTOF: Receiver timeout
	uint32_t EOBF : 1; // Bit 12 EOBF: End of block flag
	uint32_t reserved0 : 1;
	uint32_t ABRE : 1; // Bit 14 ABRE: Auto baud rate error
	uint32_t ABRF : 1; // Bit 15 ABRF: Auto baud rate flag
	uint32_t BUSY : 1; // Bit 16 BUSY: Busy flag
	uint32_t CMF : 1; // Bit 17 CMF: Character match flag
	uint32_t SBKF : 1; // Bit 18 SBKF: Send break flag
	uint32_t RWU : 1; // Bit 19 RWU: Receiver wake-up from Mute mode
	uint32_t WUF : 1; // Bit 20 WUF: Wake-up from Stop mode flag
	uint32_t TEACK : 1; // Bit 21 TEACK: Transmit enable acknowledge flag
	uint32_t REACK : 1; // Bit 22 REACK: Receive enable acknowledge flag
	uint32_t reserved1 : 9;
};
union ISRUnion {
	ISRStruct bits;
	uint32_t word;
};
static_assert(sizeof(ISRUnion) == 4u);
// USART interrupt flag clear register (USART_ICR)
struct ICRStruct {
	uint32_t PECF : 1; // Bit 0 PECF: Parity error clear flag
	uint32_t FECF : 1; // Bit 1 FECF: Framing error clear flag
	uint32_t NCF : 1; // Bit 2 NCF: Noise detected clear flag
	uint32_t ORECF : 1; // Bit 3 ORECF: Overrun error clear flag
	uint32_t IDLECF : 1; // Bit 4 IDLECF: Idle line detected clear flag
	uint32_t reserved0 : 1;
	uint32_t TCCF : 1; // Bit 6 TCCF: Transmission complete clear flag
	uint32_t reserved1 : 1;
	uint32_t LBDCF : 1; // Bit 8 LBDCF: LIN break detection clear flag
	uint32_t CTSCF : 1; // Bit 9 CTSCF: CTS clear flag
	uint32_t reserved2 : 1;
	uint32_t RTOCF : 1; // Bit 11 RTOCF: Receiver timeout clear flag
	uint32_t EOBCF : 1; // Bit 12 EOBCF: End of block clear flag
	uint32_t reserved3 : 4;
	uint32_t CMCF : 1; // Bit 17 CMCF: Character match clear flag
	uint32_t reserved4 : 2;
	uint32_t WUCF : 1; // Bit 20 WUCF: Wake-up from Stop mode clear flag
	uint32_t reserved5 : 11;
};
union ICRUnion {
	ICRStruct bits;
	uint32_t word;
};
static_assert(sizeof(ICRUnion) == 4u);

struct USART {
	CR1Union CR1;
	CR1Union CR2;
	CR1Union CR3;

	// USART baud rate register (USART_BRR)
	uint16_t BRR;
	uint16_t reserved0;

	GTPRUnion GTPR;
	RTORUnion RTOR;
	RQRUnion RQR;
	ISRUnion ISR;
	ICRUnion ICR;

	uint8_t RDR;
	uint8_t reserved1[3];
	uint8_t TDR;
	uint8_t reserved2[3];
};
static_assert(sizeof(USART) == 0x2Cu);
extern volatile struct USART USART1;
extern volatile struct USART USART2;
} // USART
} // mmreg
} // stm32f0
