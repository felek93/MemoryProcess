#ifndef MEMORY_PROCESS_H_
#define MEMORY_PROCESS_H_

#include <iostream>
#include <windows.h>

class MemoryProcess 
{
public:
    MemoryProcess(std::string pName, int baseAddres);
    bool OpenMemoryProcess();
    bool Read(int offset, void* buffer, size_t bytesToRead);

private:
    DWORD GetProcId();
    uintptr_t GetModuleBaseAddress(DWORD proc);

    std::string processName;
    HANDLE hProcess;
    int memoryAddress;
    const int appBaseMemory;
};

#endif // MEMORY_PROCESS_H_
