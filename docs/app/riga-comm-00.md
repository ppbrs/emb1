# riga-comm-00
## overview

The PC sends random ascii messages at 115200 bps.
The board sends out statistics every second about received bytes and messages.

The board can be in two modes:
* Report mode (default)
* Echo mode

When the board receives XON character (Ctrl+q, 0x11, 17), it switches to the echo mode.
When the board receives XOFF character (Ctrl+s, 0x13, 19), it switches to the report mode.

This particular application uses FreeRTOS stream buffers.

Goals:
* Test FreeRTOS stream buffers
* Test STM32F051 USART driver

***
## TODO
* Add integration tests.
* Get rid of `app::pollFromTask` and use notifications instead.
* Investigate thread safety.

***
## echo mode
```mermaid
sequenceDiagram
	participant USART_ISR

	USART_ISR->>consumeByteFromISR(): 
		consumeByteFromISR()->>StreamBuffer: xStreamBufferSendFromISR()
		activate StreamBuffer
		StreamBuffer-->>consumeByteFromISR(): 
	consumeByteFromISR()-->>USART_ISR: 

	app.pollFromTask->>StreamBuffer: xStreamBufferBytesAvailable()
	StreamBuffer-->>app.pollFromTask: yes
	app.pollFromTask->>USART_ISR: notifyDataReady()
	USART_ISR->>USART_ISR: enable TXEI

	USART_ISR->>getNextTxByte(): 
		getNextTxByte()->>StreamBuffer: xStreamBufferReceiveFromISR()
		StreamBuffer-->>getNextTxByte(): 
		deactivate StreamBuffer
	getNextTxByte()-->>USART_ISR: byte

	USART_ISR->>getNextTxByte(): 
		getNextTxByte()->>StreamBuffer: xStreamBufferReceiveFromISR()
		StreamBuffer-->>getNextTxByte(): 
	getNextTxByte()-->>USART_ISR: nullopt
	USART_ISR->>USART_ISR: disable TXEI

	opt
		app.pollFromTask->>StreamBuffer: xStreamBufferBytesAvailable()
		StreamBuffer-->>app.pollFromTask: yes
	end

```
***
## report mode
Firmware sends a report string every second.
```mermaid
sequenceDiagram
	participant USART_ISR

	loop Every second
		app.pollFrom1HzTimer()->>USART_ISR: ptrNotifyDataReady
		USART_ISR->>USART_ISR: enable TXEI

		USART_ISR->>getNextTxByte(): 
			getNextTxByte()->>reportSV: 
			reportSV-->>getNextTxByte(): byte
		getNextTxByte()-->>USART_ISR: byte

		USART_ISR->>getNextTxByte(): 
			getNextTxByte()->>reportSV: 
			reportSV-->>getNextTxByte(): empty
		getNextTxByte()-->>USART_ISR: nullopt
		USART_ISR->>USART_ISR: disable TXEI
	end
```
***