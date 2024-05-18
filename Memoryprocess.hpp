#ifndef MEMORY_PROCESS_H_
#define MEMORY_PROCESS_H_

#include <iostream>
#include <windows.h>

class MemoryProcess 
{
public:
    MemoryProcess(std::string_view pName, int baseAddres);
    bool OpenMemoryProcess(void);
    DWORD GetError(void);
    bool Read(int offset, void* buffer, size_t bytesToRead);

private:
    DWORD GetProcId();
    uintptr_t GetModuleBaseAddress(DWORD proc);

    const int appBaseMemory;
    HANDLE hProcess;
    int memoryAddress;
    std::string processName;
};

#endif // MEMORY_PROCESS_H_
