#pragma once

#include <filesystem>


#ifdef _WIN32

    #include <windows.h>
    #include <libloaderapi.h>

#elif __linux__

    #include <climits>
    #include <unistd.h>

#endif

#define internal static


#ifdef _WIN32

internal std::filesystem::path GetExecutablePathWin()
{
    char path[MAX_PATH + 1];

    DWORD result = GetModuleFileNameA(
        nullptr,
        path,
        MAX_PATH
    );

    if(result == 0)
    {
        std::cout << "Error getting executable dir !" << std::endl;
        return {};
    }

    path[MAX_PATH + 1] = '\0'; // its not required according to docs.


    return std::filesystem::path(path).parent_path();
}

#endif

internal std::filesystem::path GetExecutablePathLinux()
{
    char path[PATH_MAX + 1];   // extra one for terminating the string.
    ssize_t length = readlink("/proc/self/exe",path,PATH_MAX);
    if(length == -1)
        return {};

    path[length] = '\0';

    std::filesystem::path p(path);
    return p.parent_path();

}


inline std::filesystem::path GetExecutablePath()
{
    #ifdef __linux__
        return GetExecutablePathLinux();
    #elif _WIN32
        return GetExecutablePathWin();
    #else
        return {};
    #endif
}

