The following methods are available:
 - Int32 AcknowledgeIRQ ()
 - Void AttachCPU (CortexM cpu)
 - Void CompleteIRQ (Int32 number)
 - Void DebugLog (String message)
 - Void ErrorLog (String message)
 - Int32 FindPendingInterrupt ()
 - IEnumerable<Int32> GetEnabledExternalInterrupts ()
 - IEnumerable<Int32> GetEnabledInternalInterrupts ()
 - Endianess GetEndianness (Endianess? defaultEndianness = null)
 - IEnumerable<Tuple<String,IGPIO>> GetGPIOs ()
 - IMachine GetMachine ()
 - String GetName ()
 - Int32 GetPeripheralInputCount ()
 - Boolean HasGPIO ()
 - Void InfoLog (String message)
 - Boolean IsHostEndian ()
 - Void Log (LogLevel type, String message)
 - Void LogUnhandledRead (Int64 offset)
 - Void LogUnhandledWrite (Int64 offset, UInt64 value)
 - Void NoisyLog (String message)
 - Void OnGPIO (Int32 number, Boolean value)
 - Byte ReadByteNotTranslated (Int64 address)
 - Byte ReadByteUsingDoubleWord (Int64 address)
 - Byte ReadByteUsingDoubleWordBigEndian (Int64 address)
 - UInt32 ReadDoubleWord (Int64 offset, Boolean isSecure)
 - UInt32 ReadDoubleWord (Int64 offset)
 - UInt32 ReadDoubleWordBigEndian (Int64 address)
 - UInt32 ReadDoubleWordNonSecureAlias (Int64 offset)
 - UInt32 ReadDoubleWordNotTranslated (Int64 address)
 - UInt64 ReadQuadWordNotTranslated (Int64 address)
 - UInt64 ReadQuadWordUsingDoubleWord (Int64 address)
 - UInt64 ReadQuadWordUsingDoubleWordBigEndian (Int64 address)
 - UInt16 ReadWordNotTranslated (Int64 address)
 - UInt16 ReadWordUsingDoubleWord (Int64 address)
 - UInt16 ReadWordUsingDoubleWordBigEndian (Int64 address)
 - Void Reset ()
 - Void SetPendingIRQ (Int32 number)
 - Void SetSevOnPendingOnAllCPUs (Boolean value)
 - Void SetSleepOnExceptionExitOnAllCPUs (Boolean value)
 - Void ShowAnalyzer (String analyzerTypeName = null, String externalName = null)
 - Void WarningLog (String message)
 - Void WriteByteNotTranslated (Int64 address, Byte value)
 - Void WriteByteUsingDoubleWord (Int64 address, Byte value)
 - Void WriteByteUsingDoubleWordBigEndian (Int64 address, Byte value)
 - Void WriteDoubleWord (Int64 offset, UInt32 value, Boolean isSecure)
 - Void WriteDoubleWord (Int64 offset, UInt32 value)
 - Void WriteDoubleWordBigEndian (Int64 address, UInt32 value)
 - Void WriteDoubleWordNonSecureAlias (Int64 offset, UInt32 value)
 - Void WriteDoubleWordNotTranslated (Int64 address, UInt32 value)
 - Void WriteQuadWordNotTranslated (Int64 address, UInt64 value)
 - Void WriteQuadWordUsingDoubleWord (Int64 address, UInt64 value)
 - Void WriteQuadWordUsingDoubleWordBigEndian (Int64 address, UInt64 value)
 - Void WriteWordNotTranslated (Int64 address, UInt16 value)
 - Void WriteWordUsingDoubleWord (Int64 address, UInt16 value)
 - Void WriteWordUsingDoubleWordBigEndian (Int64 address, UInt16 value)

Usage:
 sysbus.nvic MethodName param1 param2 ...


The following properties are available:
 - Boolean DeepSleepEnabled
     available for 'get' and 'set'
 - UInt64 Divider
     available for 'get' and 'set'
 - UInt64 Frequency
     available for 'get' and 'set'
 - Boolean HaltSystickOnDeepSleep
     available for 'get' and 'set'
 - GPIO IRQ
     available for 'get'
 - Boolean MaskedInterruptPresent
     available for 'get'
 - Boolean PauseInsteadOfReset
     available for 'get' and 'set'
 - Int64 Size
     available for 'get'

Usage:
 - get: sysbus.nvic PropertyName
 - set: sysbus.nvic PropertyName Value
