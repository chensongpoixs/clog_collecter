@echo off

setlocal
setlocal enabledelayedexpansion

cd /d %~dp0

mklink /d C:\wamp\www\abroad    %~dp0www


rem echo %~dp0..\cphp




pause