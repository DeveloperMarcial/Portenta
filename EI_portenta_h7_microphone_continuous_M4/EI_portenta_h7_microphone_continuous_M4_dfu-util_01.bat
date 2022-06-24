@ECHO OFF
ECHO Flashing --- --- --- --- --- EI_portenta_h7_microphone_continuous_M4 to M4...
REM ***
REM Add DFU Suffix
REM ***
"C:\Users\mmarc\AppData\Local\Arduino15\packages\arduino\tools\dfu-util\0.10.0-arduino1\dfu-suffix" --add "C:\Users\mmarc\AppData\Local\Temp\arduino-sketch-6CDB4E66CE703700836072B0BA5E6942\EI_portenta_h7_microphone_continuous_M4.ino.bin" --vid 0x2341 --pid 0x035b 

REM ***
REM Flash M4
REM ***
"C:\Users\mmarc\AppData\Local\Arduino15\packages\arduino\tools\dfu-util\0.10.0-arduino1\dfu-util" --device 0x2341:0x035b -D "C:\Users\mmarc\AppData\Local\Temp\arduino-sketch-6CDB4E66CE703700836072B0BA5E6942\EI_portenta_h7_microphone_continuous_M4.ino.bin" --alt=0 --serial="0038002A3230510F31303431" --dfuse-address=0x08100000:leave --verbose

ECHO Flashing --- --- --- --- --- EI_portenta_h7_microphone_continuous_M4 to M4...DONE!

PAUSE