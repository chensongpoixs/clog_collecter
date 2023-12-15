@echo off

setlocal

set para=x64\Release

if "%1" NEQ "" set para=%1

set Dir=%~dp0%para%\

REM @ping -n 1 127.0.0.1>nul
REM start "gateway" /D %Dir% %Dir%gateway.exe ..\..\server.cfg  ..\..\log

REM   @ping -n 1 127.0.0.1>nul
REM   start "auth_server" /D %Dir% %Dir%auth.exe ..\..\server.cfg  ..\..\log


    @ping -n 1 127.0.0.1>nul
    start "dongle_auth_server" /D %Dir% %Dir%dongle_auth.exe ..\..\server.cfg  ..\..\log

REM pause
