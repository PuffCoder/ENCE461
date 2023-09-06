@REM @echo off
echo Launching VS Code with fixed PATH variable...

REM This is a helper script that will launch VS Code with the correct PATH
REM variable set for running on the ESL computers.

set PATH=C:/ence461/tool-chain/msys64/usr/bin;C:/ence461/tool-chain/gcc-arm-none-eabi-9-2019-q4/bin;C:/ence461/tool-chain/OpenOCD-0.10.0/bin;%PATH%

start "" code .
exit

