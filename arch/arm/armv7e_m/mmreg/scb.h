#pragma once

#include <cstdint>

namespace armv7e_m {
namespace mmreg {
namespace SCB {
struct CPUIDBits {
	uint32_t REVISION : 4;
	uint32_t PARTNO : 12;
	uint32_t ARCHITECTURE : 4;
	uint32_t VARIANT : 4;
	uint32_t IMPLEMENTER : 8;
};
static_assert(sizeof(CPUIDBits) == 4U);

union CPUID {
	uint32_t word;
	CPUIDBits bits;
};

struct ICSRBits {
	uint32_t VECTACTIVE : 9;
	uint32_t reserved1 : 2;
	uint32_t RETTOBASE : 1;
	uint32_t VECTPENDING : 10;
	uint32_t ISRPENDING : 1;
	uint32_t reserved2 : 2;
	uint32_t PENDSTCLR : 1;
	uint32_t PENDSTSET : 1;
	uint32_t PENDSVCLR : 1;
	uint32_t PENDSVSET : 1;
	uint32_t reserved3 : 2;
	uint32_t NMIPENDSET : 1;
};
static_assert(sizeof(ICSRBits) == 4U);

union ICSR {
	uint32_t word;
	ICSRBits bits;
};

struct AIRCRBits {
	uint32_t VECTRESET : 1;
	uint32_t VECTCLRACTIVE : 1;
	uint32_t SYSRESETREQ : 1;
	uint32_t reserved1 : 5;
	uint32_t PRIGROUP : 3;
	uint32_t reserved2 : 4;
	uint32_t ENDIANNESS : 1;
	uint32_t VECTKEY : 16;
};
static_assert(sizeof(AIRCRBits) == 4U);

union AIRCR {
	uint32_t word;
	AIRCRBits bits;
};

struct SCRBits {
	uint32_t reserved1 : 1;
	uint32_t SLEEPONEXIT : 1;
	uint32_t SLEEPDEEP : 1;
	uint32_t reserved2 : 1;
	uint32_t SEVONPEND : 1;
	uint32_t reserved3 : 27;
};
static_assert(sizeof(SCRBits) == 4U);

union SCR {
	uint32_t word;
	SCRBits bits;
};

struct CCRBits {
	uint32_t NONBASETHRDENA : 1;
	uint32_t USERSETMPEND : 1;
	uint32_t reserved1 : 1;
	uint32_t UNALIGN_TRP : 1;
	uint32_t DIV_0_TRP : 1;
	uint32_t reserved2 : 3;
	uint32_t BFHFNMIGN : 1;
	uint32_t STKALIGN : 1;
	uint32_t reserved3 : 6;
	uint32_t DC : 1;
	uint32_t IC : 1;
	uint32_t BP : 1;
	uint32_t reserved4 : 13;
};
static_assert(sizeof(CCRBits) == 4U);

union CCR {
	uint32_t word;
	CCRBits bits;
};

struct SHPR1Bits {
	uint32_t PRI_4 : 8;
	uint32_t PRI_5 : 8;
	uint32_t PRI_6 : 8;
	uint32_t reserved : 8;
};
static_assert(sizeof(SHPR1Bits) == 4U);

union SHPR1 {
	uint32_t word;
	SHPR1Bits bits;
};

struct SHPR2Bits {
	uint32_t reserved : 24;
	uint32_t PRI_11 : 8;
};
static_assert(sizeof(SHPR2Bits) == 4U);

union SHPR2 {
	uint32_t word;
	SHPR2Bits bits;
};

struct SHPR3Bits {
	uint32_t reserved : 16;
	uint32_t PRI_14 : 8;
	uint32_t PRI_15 : 8;
};
static_assert(sizeof(SHPR3Bits) == 4U);

union SHPR3 {
	uint32_t word;
	SHPR3Bits bits;
};

struct SHCSRBits {
	uint32_t MEMFAULTACT : 1;
	uint32_t BUSFAULTACT : 1;
	uint32_t reserved1 : 1;
	uint32_t USGFAULTACT : 1;
	uint32_t reserved2 : 3;
	uint32_t SVCALLACT : 1;
	uint32_t MONITORACT : 1;
	uint32_t reserved3 : 1;
	uint32_t PENDSVACT : 1;
	uint32_t SYSTICKACT : 1;
	uint32_t USGFAULTPENDED : 1;
	uint32_t MEMFAULTPENDED : 1;
	uint32_t BUSFAULTPENDED : 1;
	uint32_t SVCALLPENDED : 1;
	uint32_t MEMFAULTENA : 1;
	uint32_t BUSFAULTENA : 1;
	uint32_t USGFAULTENA : 1;
	uint32_t reserved4 : 13;
};
static_assert(sizeof(SHCSRBits) == 4U);

union SHCSR {
	uint32_t word;
	SHCSRBits bits;
};

struct CFSRBits {
	uint32_t IACCVIOL : 1;
	uint32_t DACCVIOL : 1;
	uint32_t reserved1 : 1;
	uint32_t MUNSTKERR : 1;
	uint32_t MSTKERR : 1;
	uint32_t MLSPERR : 1;
	uint32_t reserved2 : 1;
	uint32_t MMARVALID : 1;
	uint32_t IBUSERR : 1;
	uint32_t PRECISERR : 1;
	uint32_t IMPRECISERR : 1;
	uint32_t UNSTKERR : 1;
	uint32_t STKERR : 1;
	uint32_t LSPERR : 1;
	uint32_t reserved3 : 1;
	uint32_t BFARVALID : 1;
	uint32_t UNDEFINSTR : 1;
	uint32_t INVSTATE : 1;
	uint32_t INVPC : 1;
	uint32_t NOCP : 1;
	uint32_t reserved4 : 4;
	uint32_t UNALIGNED : 1;
	uint32_t DIVBYZERO : 1;
	uint32_t reserved5 : 6;
};
static_assert(sizeof(CFSRBits) == 4U);

union CFSR {
	uint32_t word;
	CFSRBits bits;
};

struct HFSRBits {
	uint32_t reserved1 : 1;
	uint32_t VECTTBL : 1;
	uint32_t reserved2 : 28;
	uint32_t FORCED : 1;
	uint32_t DEBUGEVT : 1;
};
static_assert(sizeof(HFSRBits) == 4U);

union HFSR {
	uint32_t word;
	HFSRBits bits;
};

struct DFSRBits {
	uint32_t HALTED : 1;
	uint32_t BKPT : 1;
	uint32_t DWTTRAP : 1;
	uint32_t VCATCH : 1;
	uint32_t EXTERNAL : 1;
	uint32_t reserved : 27;
};
static_assert(sizeof(DFSRBits) == 4U);

union DFSR {
	uint32_t word;
	DFSRBits bits;
};

struct PFR0Bits {
	uint32_t State0 : 4;
	uint32_t State1 : 4;
	uint32_t State2 : 4;
	uint32_t State3 : 4;
	uint32_t reserved : 16;
};
static_assert(sizeof(PFR0Bits) == 4U);

union PFR0 {
	uint32_t word;
	PFR0Bits bits;
};

struct PFR1Bits {
	uint32_t reserved1 : 8;
	uint32_t ProgrammersModel : 4;
	uint32_t reserved2 : 20;
};
static_assert(sizeof(PFR1Bits) == 4U);

union PFR1 {
	uint32_t word;
	PFR1Bits bits;
};

struct DFR0Bits {
	uint32_t reserved1 : 20;
	uint32_t DebugModel : 4;
	uint32_t reserved2 : 8;
};
static_assert(sizeof(DFR0Bits) == 4U);

union DFR0 {
	uint32_t word;
	DFR0Bits bits;
};

struct MMFR0Bits {
	uint32_t reserved1 : 4;
	uint32_t PMSASupport : 4;
	uint32_t OutermostShareability : 4;
	uint32_t ShareabilityLevels : 4;
	uint32_t TCMSupport : 4;
	uint32_t AuxiliaryRegisters : 4;
	uint32_t reserved2 : 8;
};
static_assert(sizeof(MMFR0Bits) == 4U);

union MMFR0 {
	uint32_t word;
	MMFR0Bits bits;
};

struct MMFR2Bits {
	uint32_t reserved1 : 24;
	uint32_t WFIStall : 4;
	uint32_t reserved2 : 4;
};
static_assert(sizeof(MMFR2Bits) == 4U);

union MMFR2 {
	uint32_t word;
	MMFR2Bits bits;
};

struct ISAR0Bits {
	uint32_t reserved1 : 4;
	uint32_t Bitcount_instrs : 4;
	uint32_t Bitfield_instrs : 4;
	uint32_t CmpBranch_instrs : 4;
	uint32_t Coproc_instrs : 4;
	uint32_t Debug_instrs : 4;
	uint32_t Divide_instrs : 4;
	uint32_t reserved2 : 4;
};
static_assert(sizeof(ISAR0Bits) == 4U);

union ISAR0 {
	uint32_t word;
	ISAR0Bits bits;
};

struct ISAR1Bits {
	uint32_t reserved1 : 12;
	uint32_t Extend_instrs : 4;
	uint32_t IfThen_instrs : 4;
	uint32_t Immediate_instrs : 4;
	uint32_t Interwork_instrs : 4;
	uint32_t reserved2 : 4;
};
static_assert(sizeof(ISAR1Bits) == 4U);

union ISAR1 {
	uint32_t word;
	ISAR1Bits bits;
};

struct ISAR2Bits {
	uint32_t LoadStore_instrs : 4;
	uint32_t MemHint_instrs : 4;
	uint32_t MultiAccessInt_instrs : 4;
	uint32_t Mult_instrs : 4;
	uint32_t MultS_instrs : 4;
	uint32_t MultU_instrs : 4;
	uint32_t reserved : 4;
	uint32_t Reversal_instrs : 4;
};
static_assert(sizeof(ISAR2Bits) == 4U);

union ISAR2 {
	uint32_t word;
	ISAR2Bits bits;
};

struct ISAR3Bits {
	uint32_t Saturate_instrs : 4;
	uint32_t SIMD_instrs : 4;
	uint32_t SVC_instrs : 4;
	uint32_t SynchPrim_instrs : 4;
	uint32_t TabBranch_instrs : 4;
	uint32_t ThumbCopy_instrs : 4;
	uint32_t TrueNOP_instrs : 4;
	uint32_t reserved : 4;
};
static_assert(sizeof(ISAR3Bits) == 4U);

union ISAR3 {
	uint32_t word;
	ISAR3Bits bits;
};

struct ISAR4Bits {
	uint32_t Unpriv_instrs : 4;
	uint32_t WithShifts_instrs : 4;
	uint32_t Writeback_instrs : 4;
	uint32_t reserved1 : 4;
	uint32_t Barrier_instrs : 4;
	uint32_t SynchPrim_instrs_frac : 4;
	uint32_t PSR_M_instrs : 4;
	uint32_t reserved2 : 4;
};
static_assert(sizeof(ISAR4Bits) == 4U);

union ISAR4 {
	uint32_t word;
	ISAR4Bits bits;
};

struct CLIDRBits {
	uint32_t CType1 : 3;
	uint32_t CType2 : 3;
	uint32_t CType3 : 3;
	uint32_t CType4 : 3;
	uint32_t CType5 : 3;
	uint32_t CType6 : 3;
	uint32_t CType7 : 3;
	uint32_t LoUIS : 3;
	uint32_t LoC : 3;
	uint32_t LoUU : 3;
	uint32_t reserved : 2;
};
static_assert(sizeof(CLIDRBits) == 4U);

union CLIDR {
	uint32_t word;
	CLIDRBits bits;
};

struct CTRBits {
	uint32_t IminLine : 4;
	uint32_t reserved1 : 12;
	uint32_t DminLine : 4;
	uint32_t ERG : 4;
	uint32_t CWG : 4;
	uint32_t reserved2 : 1;
	uint32_t Format : 3;
};
static_assert(sizeof(CTRBits) == 4U);

union CTR {
	uint32_t word;
	CTRBits bits;
};

struct CCSIDRBits {
	uint32_t LineSize : 3;
	uint32_t Associativity : 10;
	uint32_t NumSets : 15;
	uint32_t WA : 1;
	uint32_t RA : 1;
	uint32_t WB : 1;
	uint32_t WT : 1;
};
static_assert(sizeof(CCSIDRBits) == 4U);

union CCSIDR {
	uint32_t word;
	CCSIDRBits bits;
};

struct CSSELRBits {
	uint32_t InD : 1;
	uint32_t Level : 3;
	uint32_t reserved : 28;
};
static_assert(sizeof(CSSELRBits) == 4U);

union CSSELR {
	uint32_t word;
	CSSELRBits bits;
};

struct CPACRBits {
	uint32_t CP0 : 2;
	uint32_t CP1 : 2;
	uint32_t CP2 : 2;
	uint32_t CP3 : 2;
	uint32_t CP4 : 2;
	uint32_t CP5 : 2;
	uint32_t CP6 : 2;
	uint32_t CP7 : 2;
	uint32_t reserved1 : 4;
	uint32_t CP10 : 2;
	uint32_t CP11 : 2;
	uint32_t reserved2 : 8;
};
static_assert(sizeof(CPACRBits) == 4U);

union CPACR {
	uint32_t word;
	CPACRBits bits;
};

struct SCB {
	union CPUID CPUID;
	union ICSR ICSR;
	const void *VTOR;
	union AIRCR AIRCR;
	union SCR SCR;
	union CCR CCR;
	union SHPR1 SHPR1;
	union SHPR2 SHPR2;
	union SHPR3 SHPR3;
	union SHCSR SHCSR;
	union CFSR CFSR;
	union HFSR HFSR;
	union DFSR DFSR;
	void *MMFAR;
	void *BFAR;
	uint32_t AFSR;
	union PFR0 ID_PFR0;
	union PFR1 ID_PFR1;
	union DFR0 ID_DFR0;
	uint32_t ID_AFR0;
	union MMFR0 ID_MMFR0;
	uint32_t ID_MMFR1;
	union MMFR2 ID_MMFR2;
	uint32_t ID_MMFR3;
	union ISAR0 ID_ISAR0;
	union ISAR1 ID_ISAR1;
	union ISAR2 ID_ISAR2;
	union ISAR3 ID_ISAR3;
	union ISAR4 ID_ISAR4;
	uint32_t ID_ISAR5;
	union CLIDR CLIDR;
	union CTR CTR;
	union CCSIDR CCSIDR;
	union CSSELR CSSELR;
	union CPACR CPACR;
};
#if defined(__arm__)
static_assert(sizeof(SCB) == 0xED88U - 0xED00U + 4U);
#endif

extern volatile SCB SCB;
}
}
}
