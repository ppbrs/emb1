The following methods are available:
 - Void AddSymbol (Range address, String name, ICPU context = null)
 - Void AddWatchpointHook (UInt64 address, SysbusAccessWidth width, Access access, String pythonScript)
 - Void ApplySVD (String path)
 - Void ChangePeripheralAccessCondition (IBusPeripheral peripheral, String newCondition, String oldCondition = null)
 - Void Clear ()
 - Void ClearPageAccessViaIo (UInt64 address)
 - Void ClearSymbols (ICPU context = null)
 - Void DebugLog (String message)
 - String DecorateWithCPUNameAndPC (String str)
 - Void DisablePeripheral (IPeripheral peripheral)
 - Void Dispose ()
 - Void EnableAllTranslations (Boolean enable = True)
 - Void EnableAllTranslations (IBusPeripheral busPeripheral, Boolean enable = True)
 - Void EnablePeripheral (IPeripheral peripheral)
 - DelayedInvalidationContext EnterDelayedInvalidationContext ()
 - Void ErrorLog (String message)
 - Object ExtractPreservedState ()
 - Void FillWithConstantByte (Byte value, Int64? size = null)
 - Void FillWithConstantDoubleWord (Int32 value, Int64? size = null)
 - Void FillWithConstantWord (Int16 value, Int64? size = null)
 - Void FillWithRepeatingData (Byte[] data, Int64? size = null)
 - IBusRegistered<MappedMemory> FindMemory (UInt64 address, ICPU context = null)
 - String FindSymbolAt (UInt64 offset, ICPU context = null)
 - Void GenerateACPITable (UInt64 address)
 - IEnumerable<IPeripheral> GetAllContextKeys ()
 - IEnumerable<UInt64> GetAllSymbolAddresses (String symbolName, ICPU context = null)
 - IReadOnlyDictionary<String,Int32> GetCommonStateBits ()
 - IEnumerable<ICPU> GetCPUs ()
 - Int32 GetCPUSlot (ICPU cpu)
 - ICPU GetCurrentCPU ()
 - Int32 GetCurrentCPUId ()
 - Endianess GetEndianness (Endianess? defaultEndianness = null)
 - BinaryFingerprint GetFingerprint (ReadFilePath fileName)
 - IEnumerable<Tuple<String,IGPIO>> GetGPIOs ()
 - IEnumerable<BinaryFingerprint> GetLoadedFingerprints ()
 - SymbolLookup GetLookup (ICPU context = null)
 - IMachine GetMachine ()
 - IEnumerable<IBusRegistered<IMapped>> GetMappedPeripherals (IPeripheral context = null)
 - String GetName ()
 - IEnumerable<IBusRegistered<IBusPeripheral>> GetRegisteredPeripherals (IPeripheral context = null)
 - IEnumerable<BusRangeRegistration> GetRegistrationPoints (IBusPeripheral peripheral, ICPU context = null)
 - IEnumerable<BusRangeRegistration> GetRegistrationPoints (IBusPeripheral peripheral)
 - IReadOnlyDictionary<String,Int32> GetStateBits (String initiatorName)
 - UInt64 GetSymbolAddress (String symbolName, Int32 index, ICPU context = null)
 - UInt64 GetSymbolAddress (String symbolName, ICPU context = null)
 - Boolean HasGPIO ()
 - Void InfoLog (String message)
 - Boolean IsAddressRangeLocked (Range range, IPeripheral context = null)
 - Boolean IsHostEndian ()
 - Boolean IsLoggingPeripheralAccessEnabled (IBusPeripheral busPeripheral)
 - Boolean IsMemory (UInt64 address, ICPU context = null, UInt64? initiatorState = null)
 - Boolean IsPeripheralEnabled (IPeripheral peripheral)
 - Void LoadAtags (String bootargs, UInt32 memorySize, UInt32 beginAddress)
 - Void LoadBinary (ReadFilePath fileName, UInt64 loadPoint, ICPU cpu = null, Int64 offset = 0, UInt64? size = null)
 - Void LoadELF (ReadFilePath fileName, Boolean useVirtualAddress = False, IPeripheral cpu = null)
 - Void LoadFdt (String file, UInt64 address, String bootargs = null, Boolean append = True, String disabledNodes = "", ICPU context = null)
 - Void LoadHEX (ReadFilePath fileName, IInitableCPU cpu = null)
 - Void LoadSRecord (ReadFilePath fileName, IInitableCPU cpu = null)
 - Void LoadSymbolsFrom (ReadFilePath fileName, Boolean useVirtualAddress = False, UInt64? textAddress = null, ICPU context = null)
 - Void LoadUImage (ReadFilePath fileName, IInitableCPU cpu = null)
 - Void Log (LogLevel type, String message)
 - Void LogAllPeripheralsAccess (Boolean enable = True, Boolean silent = False)
 - Void LogPeripheralAccess (IBusPeripheral busPeripheral, Boolean enable = True, Boolean silent = False)
 - Void LogUnhandledRead (Int64 offset)
 - Void LogUnhandledWrite (Int64 offset, UInt64 value)
 - Void NoisyLog (String message)
 - Byte ReadByte (UInt64 address, IPeripheral context = null, UInt64? cpuState = null)
 - Byte[] ReadBytes (Int64 offset, Int32 count, IPeripheral context = null)
 - Byte[] ReadBytes (UInt64 address, Int32 count, Boolean onlyMemory = False, IPeripheral context = null)
 - Void ReadBytes (UInt64 address, Int32 count, Byte[] destination, Int32 startIndex, Boolean onlyMemory = False, IPeripheral context = null)
 - UInt32 ReadDoubleWord (UInt64 address, IPeripheral context = null, UInt64? cpuState = null)
 - UInt64 ReadQuadWord (UInt64 address, IPeripheral context = null, UInt64? cpuState = null)
 - UInt16 ReadWord (UInt64 address, IPeripheral context = null, UInt64? cpuState = null)
 - Void Redirect (UInt64 from, UInt64 to, UInt64 size)
 - Void Register (IKnownSize peripheral, BusPointRegistration registrationPoint)
 - Void RemoveAllWatchpointHooks (UInt64 address)
 - Void RemoveTag (UInt64 address)
 - Void Reset ()
 - Void SetAddressRangeLocked (Range range, Boolean locked, IPeripheral context = null)
 - Void SetDelayedInvalidation (Boolean value)
 - Void SetHookAfterPeripheralRead (IBusPeripheral peripheral, String pythonScript, Range? subrange = null)
 - Void SetHookBeforePeripheralWrite (IBusPeripheral peripheral, String pythonScript, Range? subrange = null)
 - IDisposable SetLocalContext (IPeripheral context, UInt64? initiatorState = null)
 - Void SetPageAccessViaIo (UInt64 address)
 - Void SetPCOnAllCores (UInt64 pc)
 - Void SetPeripheralEnabled (IPeripheral peripheral, Boolean enabled)
 - Void ShowAnalyzer (String analyzerTypeName = null, String externalName = null)
 - Void SilenceRange (Range range)
 - Void Tag (Range range, String tag, UInt64 defaultValue = 0, Boolean pausing = False, Boolean silent = False, Boolean overridePeripheralAccesses = False)
 - Void UnmapMemory (Range range, ICPU context = null)
 - Void Unregister (ICPU cpu)
 - Void Unregister (IBusPeripheral peripheral)
 - Void Unregister (IPeripheral peripheral)
 - Void Unregister (IKnownSize peripheral)
 - Void UnregisterFromAddress (UInt64 address, ICPU context = null)
 - Void WarningLog (String message)
 - IBusRegistered<IBusPeripheral> WhatIsAt (UInt64 address, IPeripheral context = null)
 - IPeripheral WhatPeripheralIsAt (UInt64 address, IPeripheral context = null)
 - Void WriteASCIIString (UInt64 address, String stringToLoad, ICPU context = null)
 - Void WriteByte (UInt64 address, Byte value, IPeripheral context = null, UInt64? cpuState = null)
 - Void WriteBytes (Int64 offset, Byte[] array, Int32 startingIndex, Int32 count, IPeripheral context = null)
 - Void WriteBytes (Byte[] bytes, UInt64 address, Int64 count, Boolean onlyMemory = False, IPeripheral context = null)
 - Void WriteBytes (Byte[] bytes, UInt64 address, Int32 startingIndex, Int64 count, Boolean onlyMemory = False, IPeripheral context = null)
 - Void WriteBytes (Byte[] bytes, UInt64 address, Boolean onlyMemory = False, IPeripheral context = null)
 - Void WriteDoubleWord (UInt64 address, UInt32 value, IPeripheral context = null, UInt64? cpuState = null)
 - Void WriteQuadWord (UInt64 address, UInt64 value, IPeripheral context = null, UInt64? cpuState = null)
 - Void WriteWord (UInt64 address, UInt16 value, IPeripheral context = null, UInt64? cpuState = null)
 - Void ZeroRange (Range range, IPeripheral context = null)
 - Void ZeroRange (Int64 from, Int64 size, ICPU context = null)

Usage:
 sysbus MethodName param1 param2 ...


The following properties are available:
 - Endianess Endianess
     available for 'get' and 'set'
 - Boolean IsMultiCore
     available for 'get'
 - UInt64? LowestLoadedAddress
     available for 'get'
 - IMachine Machine
     available for 'get'
 - String PreservableName
     available for 'get'
 - Int32 UnexpectedReads
     available for 'get'
 - Int32 UnexpectedWrites
     available for 'get'
 - UnhandledAccessBehaviour UnhandledAccessBehaviour
     available for 'get' and 'set'

Usage:
 - get: sysbus PropertyName
 - set: sysbus PropertyName Value
