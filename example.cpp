#include <iostream>

#include "MemoryProcess.h"

std::string applicationName = "YOUR_PROGRAM_NAME.EXE"; 
int baseAddress = 0x123456;

int main()
{
    MemoryProcess* proc = new MemoryProcess(applicationName, baseAddress);

    const bool status = proc->OpenMemoryProcess();
    if (!status)
    {
        std::cout << "Can't open the memory!" << std::endl;
        exit(1);
    }

    const int offset = 0x1234;
    const size_t bytesToRead = 16;
    uint8_t buffer[bytesToRead];

    if (proc->Read(offset, buffer, bytesToRead))
    {
        std::cout << buffer << std::endl;
    }

    return 0;
}