The following methods are available:
 - UInt64 AcquireExternalMmuWindow (Privilege type)
 - Void ActivateNewHooks ()
 - Void AddHook (UInt64 addr, String pythonScript)
 - Void AddHookAtInterruptBegin (String pythonScript)
 - Void AddHookAtInterruptEnd (String pythonScript)
 - Void AddHookAtWfiStateChange (String pythonScript)
 - Void AddSymbolHook (String hookSymbol, String pythonScript)
 - UInt32 AssembleBlock (UInt64 addr, String instructions, UInt32 flags = 0)
 - UInt32 CheckExternalPermissions (UInt64 address)
 - Void ClearHookAtBlockBegin ()
 - Void ClearPageAccessViaIo (UInt64 address)
 - Void ClearTranslationCache ()
 - Void ContinueAndEnterStepModeAfterFinishingTimeInterval ()
 - Void CreateCPUTracer (String name)
 - Void CreateExecutionTracing (String name, String fileName, TraceFormat format, Boolean isBinary = False, Boolean compress = False, Boolean isSynchronous = False)
 - Void CreateExecutionTracingSynchronous (String name, String fileName, TraceFormat format, Boolean isBinary = False, Boolean compress = False)
 - Void DebugLog (String message)
 - Void DelayStepCommand ()
 - Void DisableExecutionTracing ()
 - Void DisableProfiler ()
 - Void DisableTimeSkip (String symbol)
 - Void DisableUbootMode ()
 - Void DisableZephyrMode ()
 - String DisassembleBlock (UInt64 addr = 18446744073709551615, UInt32 blockSize = 40, UInt32 flags = 0)
 - Void Dispose ()
 - Void EnableExternalWindowMmu (Boolean value)
 - Void EnableExternalWindowMmu (ExternalMmuPosition position)
 - Void EnableProfiler (ProfilerType type, String filename, Boolean flushInstantly = False, Boolean enableMultipleTracks = True, Int64? fileSizeLimit = null, Int32? maximumNestedContexts = null, Boolean enableFrameTracking = False)
 - Void EnableProfilerCollapsedStack (String filename, Boolean flushInstantly = False, Int64? fileSizeLimit = null, Int32? maximumNestedContexts = null, Boolean enableFrameTracking = False)
 - Void EnableProfilerPerfetto (String filename, Boolean flushInstantly = False, Boolean enableMultipleTracks = True, Int64? fileSizeLimit = null, Int32? maximumNestedContexts = null)
 - Void EnableProfiling ()
 - Void EnableReadCache (UInt64 accessAddress, UInt64 lowerAccessCount, UInt64 upperAccessCount = 0)
 - Void EnableTimeSkip (String symbol, UInt64 usPerTick = 1)
 - Void EnableUbootMode ()
 - Void EnableZephyrMode (params String[] disableIfSymbolsPresent)
 - Void ErrorLog (String message)
 - Boolean EvaluateConditionCode (UInt32 condition)
 - Object ExtractPreservedState ()
 - Void FlushProfiler ()
 - Void FlushTlb ()
 - Void FlushTlbPage (UInt64 address)
 - Void ForEach (Action<BaseCPU> action)
 - String[,] GetAllOpcodesCounters ()
 - Boolean GetArmFeature (ArmFeatures feature)
 - String GetCPUThreadName (IMachine machine)
 - UInt64 GetCurrentInstructionsCount ()
 - String GetDescription ()
 - Endianess GetEndianness (Endianess? defaultEndianness = null)
 - IEnumerator<TranslationCPU> GetEnumerator ()
 - IEnumerator<BaseCPU> GetEnumerator ()
 - UInt32 GetFaultmask (Boolean secure)
 - IEnumerable<Tuple<String,IGPIO>> GetGPIOs ()
 - IDAURegion GetIDAURegion (UInt32 regionIndex)
 - UInt32 GetItState ()
 - IMachine GetMachine ()
 - UInt64 GetMmuWindowAddend (UInt64 id)
 - UInt64 GetMmuWindowEnd (UInt64 id)
 - UInt32 GetMmuWindowPrivileges (UInt64 id)
 - UInt64 GetMmuWindowStart (UInt64 id)
 - String GetName ()
 - UInt64 GetOpcodeCounter (String name)
 - Int32 GetPeripheralInputCount ()
 - UInt32 GetPrimask (Boolean secure)
 - String GetProfilerStack ()
 - RegisterValue GetRegister (Int32 register)
 - RegisterValue GetRegister (String register)
 - IEnumerable<CPURegister> GetRegisters ()
 - String[,] GetRegistersValues ()
 - UInt64 GetRegisterUlong (Int32 register)
 - UInt64 GetRegisterUlong (String register)
 - RegisterValue GetRegisterUnsafe (Int32 register)
 - UInt64 GetSystemRegisterValue (String name)
 - Boolean HasGPIO ()
 - Void InfoLog (String message)
 - Void InitStoreTable (Boolean afterDeserialization = False)
 - Void InstallOpcodeCounterPattern (String name, String pattern)
 - Void InstallOpcodeCounterPattern (String name, UInt64 opcode, UInt64 mask)
 - Void InvalidateTranslationBlocks ()
 - Boolean IsHostEndian ()
 - Void Log (LogLevel type, String message)
 - Void LogCpuInterrupts (Boolean isEnabled)
 - Void LogFunctionNames (Boolean value, Boolean removeDuplicates = False, Boolean useFunctionSymbolsOnly = True)
 - Void LogFunctionNames (Boolean value, String spaceSeparatedPrefixes = "", Boolean removeDuplicates = False, Boolean useFunctionSymbolsOnly = True)
 - Void LogUnhandledRead (Int64 offset)
 - Void LogUnhandledWrite (Int64 offset, UInt64 value)
 - Void NativeUnwind ()
 - Void NoisyLog (String message)
 - IDisposable ObtainSinkActiveState ()
 - IDisposable ObtainSinkInactiveState ()
 - Void OnGPIO (Int32 number, Boolean value)
 - Void Pause ()
 - Void RaiseException (UInt32 exceptionId)
 - Void RegisterAccessFlags (UInt64 startAddress, UInt64 size, Boolean isIoMemory = False)
 - Void RegisterTCMRegion (IMemory memory, UInt32 interfaceIndex, UInt32 regionIndex)
 - Void RemoveAllHooks ()
 - Void RemoveHooksAt (UInt64 addr)
 - Void RequestReturn ()
 - Boolean RequestTranslationBlockRestart (Boolean quiet = False)
 - Void Reset ()
 - Void ResetAllMmuWindows ()
 - Void ResetMmuWindow (UInt64 id)
 - Void ResetMmuWindowsCoveringAddress (UInt64 address)
 - Void ResetOpcodesCounters ()
 - Void Resume ()
 - Void SaveAllOpcodesCounters (String path)
 - IEnumerable<Object> Select (Func<BaseCPU,Object> selector)
 - Void SetBroadcastDirty (Boolean enable)
 - Void SetEventFlag (Boolean value)
 - Void SetHookAtBlockBegin (String pythonScript)
 - Void SetHookAtBlockEnd (String pythonScript)
 - Void SetIDAURegion (UInt32 regionIndex, UInt32 baseAddress, UInt32 limitAddress, Boolean enabled, Boolean nonSecureCallable)
 - Void SetIDAURegion (UInt32 regionIndex, UInt32 rbar, UInt32 rlar)
 - Void SetMappedMemoryEnabled (Range range, Boolean enabled)
 - Void SetMmuWindowAddend (UInt64 id, UInt64 addend)
 - Void SetMmuWindowEnd (UInt64 id, UInt64 endAddress)
 - Void SetMmuWindowPrivileges (UInt64 id, Privilege permissions)
 - Void SetMmuWindowStart (UInt64 id, UInt64 startAddress)
 - Void SetPageAccessViaIo (UInt64 address)
 - Void SetRegister (Int32 register, RegisterValue value)
 - Void SetRegister (String register, RegisterValue value)
 - Void SetRegisterUlong (Int32 register, UInt64 value)
 - Void SetRegisterUlong (String register, UInt64 value)
 - Void SetRegisterUnsafe (Int32 register, RegisterValue value)
 - Void SetSevOnPending (Boolean value)
 - Void SetSleepOnExceptionExit (Boolean value)
 - Void SetSystemRegisterValue (String name, UInt64 value)
 - Void ShowAnalyzer (String analyzerTypeName = null, String externalName = null)
 - Void SkipTime (TimeInterval amountOfTime)
 - Void Start ()
 - UInt64 Step (Int32 count = 1)
 - Void SyncTime ()
 - String ToString ()
 - UInt64 TranslateAddress (UInt64 logicalAddress, MpuAccess accessType)
 - Boolean TryAddImplementationDefinedExemptionRegion (UInt32 startAddress, UInt32 endAddress)
 - Boolean TryRemoveImplementationDefinedExemptionRegion (UInt32 startAddress, UInt32 endAddress)
 - Void UnmapMemory (Range range)
 - Void Unregister (SemihostingUart peripheral)
 - Void Unregister (ArmPerformanceMonitoringUnit peripheral)
 - Void WarningLog (String message)
 - Boolean WillNextItInstructionExecute (UInt32 itState)

Usage:
 sysbus.cpu MethodName param1 param2 ...


The following properties are available:
 - String Architecture
     available for 'get'
 - RegisterValue BasePri
     available for 'get' and 'set'
 - IBusController Bus
     available for 'get'
 - Boolean ChainingEnabled
     available for 'get' and 'set'
 - IEnumerable<TranslationCPU> Clustered
     available for 'get'
 - IEnumerable<BaseCPU> Clustered
     available for 'get'
 - IEnumerable<ICluster<TranslationCPU>> Clusters
     available for 'get'
 - IEnumerable<ICluster<BaseCPU>> Clusters
     available for 'get'
 - RegisterValue Control
     available for 'get' and 'set'
 - RegisterValue CPACR
     available for 'get' and 'set'
 - RegisterValue CPACR_NS
     available for 'get' and 'set'
 - RegisterValue CPSR
     available for 'get' and 'set'
 - UInt32 CurrentBlockDisassemblyFlags
     available for 'get'
 - RegisterValue CurrentSP
     available for 'get' and 'set'
 - Decimal CyclesPerInstruction
     available for 'get' and 'set'
 - Boolean DebuggerConnected
     available for 'get' and 'set'
 - Boolean DisableInterruptsWhileStepping
     available for 'get' and 'set'
 - UInt64 ElapsedCycles
     available for 'get'
 - EmulationCPUState EmulationState
     available for 'get'
 - Boolean EnableOpcodesCounting
     available for 'set'
 - Endianess Endianness
     available for 'get'
 - UInt32 ExceptionVectorAddress
     available for 'get' and 'set'
 - UInt64 ExecutedInstructions
     available for 'get'
 - ExecutionMode ExecutionMode
     available for 'get' and 'set'
 - UInt32 ExternalMmuWindowsCount
     available for 'get'
 - RegisterValue FAULTMASK
     available for 'get' and 'set'
 - UInt32 FaultStatus
     available for 'get' and 'set'
 - UInt32 FaultStatusNonSecure
     available for 'get' and 'set'
 - RegisterValue FPCAR
     available for 'get' and 'set'
 - RegisterValue FPCAR_NS
     available for 'get' and 'set'
 - RegisterValue FPCCR
     available for 'get' and 'set'
 - RegisterValue FPCCR_NS
     available for 'get' and 'set'
 - RegisterValue FPDSCR
     available for 'get' and 'set'
 - RegisterValue FPDSCR_NS
     available for 'get' and 'set'
 - RegisterValue FPSCR
     available for 'get' and 'set'
 - RegisterValue FPSCR_NS
     available for 'get' and 'set'
 - Boolean FpuEnabled
     available for 'set'
 - String GDBArchitecture
     available for 'get'
 - Boolean IDAUEnabled
     available for 'get' and 'set'
 - Boolean ImplementsPMSA
     available for 'get'
 - Boolean ImplementsVMSA
     available for 'get'
 - UInt32 IRQ
     available for 'get'
 - Boolean IsHalted
     available for 'get' and 'set'
 - Boolean IsPaused
     available for 'get'
 - Boolean IsStarted
     available for 'get'
 - Boolean IsV8
     available for 'get'
 - String LogFile
     available for 'get' and 'set'
 - Boolean LogTranslatedBlocks
     available for 'get' and 'set'
 - Boolean LogTranslationBlockFetch
     available for 'get' and 'set'
 - RegisterValue LR
     available for 'get' and 'set'
 - Int32 MaximumBlockSize
     available for 'get' and 'set'
 - UInt32 MemoryFaultAddress
     available for 'get'
 - UInt32 MemoryFaultAddressNonSecure
     available for 'get'
 - MemorySystemArchitectureType MemorySystemArchitecture
     available for 'get'
 - String Model
     available for 'get'
 - UInt32 ModelID
     available for 'get' and 'set'
 - Boolean MPUEnabled
     available for 'get' and 'set'
 - UInt32 MPURegionAttributeAndSize
     available for 'get' and 'set'
 - UInt32 MPURegionBaseAddress
     available for 'get' and 'set'
 - UInt32 MPURegionNumber
     available for 'get' and 'set'
 - UInt32 MultiprocessingId
     available for 'get'
 - UInt32 NumberOfIDAURegions
     available for 'get' and 'set'
 - UInt32 NumberOfMPURegions
     available for 'get' and 'set'
 - UInt32 NumberOfSAURegions
     available for 'get' and 'set'
 - Boolean OnPossessedThread
     available for 'get'
 - RegisterValue OtherSP
     available for 'get' and 'set'
 - UInt32 PageSize
     available for 'get'
 - RegisterValue PC
     available for 'get' and 'set'
 - UInt32 PerformanceInMips
     available for 'get' and 'set'
 - UInt32 PmsaV8Ctrl
     available for 'get' and 'set'
 - UInt32 PmsaV8Ctrl_NS
     available for 'get' and 'set'
 - UInt32 PmsaV8Mair0
     available for 'get' and 'set'
 - UInt32 PmsaV8Mair0_NS
     available for 'get' and 'set'
 - UInt32 PmsaV8Mair1
     available for 'get' and 'set'
 - UInt32 PmsaV8Mair1_NS
     available for 'get' and 'set'
 - UInt32 PmsaV8Rbar
     available for 'get' and 'set'
 - UInt32 PmsaV8Rbar_NS
     available for 'get' and 'set'
 - UInt32 PmsaV8RbarAlias1
     available for 'get' and 'set'
 - UInt32 PmsaV8RbarAlias1_NS
     available for 'get' and 'set'
 - UInt32 PmsaV8RbarAlias2
     available for 'get' and 'set'
 - UInt32 PmsaV8RbarAlias2_NS
     available for 'get' and 'set'
 - UInt32 PmsaV8RbarAlias3
     available for 'get' and 'set'
 - UInt32 PmsaV8RbarAlias3_NS
     available for 'get' and 'set'
 - UInt32 PmsaV8Rlar
     available for 'get' and 'set'
 - UInt32 PmsaV8Rlar_NS
     available for 'get' and 'set'
 - UInt32 PmsaV8RlarAlias1
     available for 'get' and 'set'
 - UInt32 PmsaV8RlarAlias1_NS
     available for 'get' and 'set'
 - UInt32 PmsaV8RlarAlias2
     available for 'get' and 'set'
 - UInt32 PmsaV8RlarAlias2_NS
     available for 'get' and 'set'
 - UInt32 PmsaV8RlarAlias3
     available for 'get' and 'set'
 - UInt32 PmsaV8RlarAlias3_NS
     available for 'get' and 'set'
 - UInt32 PmsaV8Rnr
     available for 'get' and 'set'
 - UInt32 PmsaV8Rnr_NS
     available for 'get' and 'set'
 - String PreservableName
     available for 'get'
 - RegisterValue PRIMASK
     available for 'get' and 'set'
 - UInt32 SAUControl
     available for 'get' and 'set'
 - UInt32 SAURegionBaseAddress
     available for 'get' and 'set'
 - UInt32 SAURegionLimitAddress
     available for 'get' and 'set'
 - UInt32 SAURegionNumber
     available for 'get' and 'set'
 - UInt32 SecureFaultAddress
     available for 'get'
 - UInt32 SecureFaultStatus
     available for 'get' and 'set'
 - Boolean SecureState
     available for 'get' and 'set'
 - Boolean ShouldEnterDebugMode
     available for 'get' and 'set'
 - UInt64 SkipInstructions
     available for 'get'
 - UInt64 SkippedInstructions
     available for 'get'
 - Int32 Slot
     available for 'get'
 - RegisterValue SP
     available for 'get' and 'set'
 - Boolean SyncPCEveryInstructionDisabled
     available for 'get' and 'set'
 - Boolean TbCacheEnabled
     available for 'get' and 'set'
 - Boolean ThreadSentinelEnabled
     available for 'get' and 'set'
 - Boolean TrustZoneEnabled
     available for 'get'
 - Int32 UniqueObjectId
     available for 'get'
 - Boolean UpdateContextOnLoadAndStore
     available for 'get' and 'set'
 - RegisterValue VecBase
     available for 'get' and 'set'
 - UInt32 VectorTableOffset
     available for 'get' and 'set'
 - UInt32 VectorTableOffsetNonSecure
     available for 'get' and 'set'
 - Boolean WfeAndSevAsNop
     available for 'get' and 'set'
 - Boolean WfiAsNop
     available for 'get' and 'set'
 - UInt32 XProgramStatusRegister
     available for 'get'

Usage:
 - get: sysbus.cpu PropertyName
 - set: sysbus.cpu PropertyName Value


The following fields are available:
 - HashSet<String> FrameProfilerIgnoredSymbols
 - UInt32 IDAU_SAURegionAddressMask (read only)
 - UInt32 IDAU_SAURegionMinSize (read only)
 - Boolean UseMachineAtomicState (read only)

Usage:
 - get: sysbus.cpu fieldName
 - set: sysbus.cpu fieldName Value
