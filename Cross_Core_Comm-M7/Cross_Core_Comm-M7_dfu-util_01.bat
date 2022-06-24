@ECHO OFF
REM ***
REM Add DFU Suffix
REM ***
"C:\Users\mmarc\AppData\Local\Arduino15\packages\arduino\tools\dfu-util\0.10.0-arduino1\dfu-suffix" --add "C:\Users\mmarc\AppData\Local\Temp\arduino-sketch-18D6E906CB12455DF6C233C2B3917CDF\Cross_Core_Comm-M7.ino.bin" --vid 0x2341 --pid 0x035b 


ECHO Programming "Cross_Core_Comm-M7" to M7 <------------------------
"C:\Users\mmarc\AppData\Local\Arduino15\packages\arduino\tools\dfu-util\0.10.0-arduino1\dfu-util" --device 0x2341:0x035b -D "C:\Users\mmarc\AppData\Local\Temp\arduino-sketch-18D6E906CB12455DF6C233C2B3917CDF\Cross_Core_Comm-M7.ino.bin" --alt=0 --serial="0038002A3230510F31303431" --dfuse-address=0x08040000:leave --verbose
ECHO Programming "Cross_Core_Comm-M7" to M7 <------------------------DONE!

REM ECHO Programming "Cross_Core_Comm-M7" to M4 <------------------------
REM "C:\Users\mmarc\AppData\Local\Arduino15\packages\arduino\tools\dfu-util\0.10.0-arduino1\dfu-util" --device 0x2341:0x035b -D "C:\Users\mmarc\AppData\Local\Temp\arduino-sketch-18D6E906CB12455DF6C233C2B3917CDF\Cross_Core_Comm-M7.ino.bin" --alt=0 --serial="0038002A3230510F31303431" --dfuse-address=0x08100000:leave --verbose
REM ECHO Programming "Cross_Core_Comm-M7" to M4 <------------------------DONE!
PAUSE