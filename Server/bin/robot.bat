@echo off

setlocal

set para=x64\Release

if "%1" NEQ "" set para=%1

set Dir=%~dp0%para%\

@ping -n 1 127.0.0.1>nul
start "Robot" /D %Dir% %Dir%log_collector_client.exe  192.168.1.175  8000

REM pause
