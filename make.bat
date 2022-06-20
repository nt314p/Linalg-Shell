@echo off
setlocal enabledelayedexpansion
for /f %%i in ('dir /B /A-D src\*.c /D') do (
    set "FILES=!FILES! src\%%i"
)
gcc !FILES! -o main -g -Wall