::@echo off
call C:\DS\R27\win_b64\code\command\tck_init.bat
call tck_profile V5_6R2017_B27
call mkGetPreq -p c:\DS\B27
call mkCI -a
call mkrtv -c
call mkmk -ua