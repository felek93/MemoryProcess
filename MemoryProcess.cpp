#include "MemoryProcess.hpp"

#include <windows.h>
#include <string>
#include <TlHelp32.h>
#include <vector>

MemoryProcess::MemoryProcess(std::string_view pName, int baseAddres) : appBaseMemory{baseAddres}, hProcess{nullptr}, memoryAddress{0}
{
    processName = pName;
}

bool MemoryProcess::OpenMemoryProcess()
{
    DWORD procId = GetProcId();
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

    if (!Read(appBaseMemory, &memoryAddress, sizeof(memoryAddress)))
    {
        std::cerr << "Error: " << std::dec << GetLastError() << std::endl;
        return false;
    }
    return true;
}

bool MemoryProcess::Read(int offset, void* buffer, size_t bytesToRead)
{
    if (hProcess != nullptr)
    {
        uintptr_t memoryPointer = static_cast<uintptr_t>(memoryAddress + offset);
        return ReadProcessMemory(hProcess, (LPCVOID)memoryPointer, buffer, bytesToRead, 0) ? true : false;
    }
    return false;
}

DWORD MemoryProcess::GetProcId(void)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                if (!stricmp(procEntry.szExeFile, processName.c_str()))
                {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } 
            while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId; 
}

uintptr_t MemoryProcess::GetModuleBaseAddress(DWORD proc)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, proc);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {   // change _wcsicmp to stricmp 
                if (!stricmp(modEntry.szModule, processName.c_str()))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } 
            while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}
