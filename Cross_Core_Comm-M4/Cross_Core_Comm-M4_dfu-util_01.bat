@ECHO OFF

REM ***
REM Add DFU Suffix
REM ***

"C:\Users\mmarc\AppData\Local\Arduino15\packages\arduino\tools\dfu-util\0.10.0-arduino1\dfu-suffix" --add "C:\Users\mmarc\AppData\Local\Temp\arduino-sketch-0BEFB2F5C8FC89C90C4479D1C6674FE4\Cross_Core_Comm-M4.ino.bin" --vid 0x2341 --pid 0x035b 
ECHO ***

REM ***
REM ECHO Programming "Cross_Core_Comm-M4" to M7-M7-M7-M7-M7-M7-M7
REM ***
REM "C:\Users\mmarc\AppData\Local\Arduino15\packages\arduino\tools\dfu-util\0.10.0-arduino1\dfu-util" --device 0x2341:0x035b -D "C:\Users\mmarc\AppData\Local\Temp\arduino-sketch-0BEFB2F5C8FC89C90C4479D1C6674FE4\Cross_Core_Comm-M4.ino.bin" --alt=0 --serial="0038002A3230510F31303431" --dfuse-address=0x08040000:leave --verbose

REM ***
ECHO Programming "Cross_Core_Comm-M4" to M4-M4-M4-M4-M4-M4-M4-M4
REM ***
"C:\Users\mmarc\AppData\Local\Arduino15\packages\arduino\tools\dfu-util\0.10.0-arduino1\dfu-util" --device 0x2341:0x035b -D "C:\Users\mmarc\AppData\Local\Temp\arduino-sketch-0BEFB2F5C8FC89C90C4479D1C6674FE4\Cross_Core_Comm-M4.ino.bin" --alt=0 --serial="0038002A3230510F31303431" --dfuse-address=0x08100000:leave --verbose

PAUSE