#pragma once
#include <iostream>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <mach-o/dyld.h>
#elif __linux__
#include <unistd.h>
#include <limits.h>
#endif

std::filesystem::path get_executable_path()
{
#ifdef _WIN32
    char path[MAX_PATH] = {0};
    if (GetModuleFileNameA(NULL, path, MAX_PATH) > 0)
    {
        return std::filesystem::path(path).parent_path();
    }
    else
    {
        throw std::runtime_error("Failed to get executable path on Windows");
    }
#elif __APPLE__
    char path[1024];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0)
    {
        return std::filesystem::path(path).parent_path();
    }
    else
    {
        throw std::runtime_error("Failed to get executable path on macOS");
    }
#elif __linux__
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count != -1)
    {
        return std::filesystem::path(std::string(result, count)).parent_path();
    }
    else
    {
        throw std::runtime_error("Failed to get executable path on Linux");
    }
#endif
}
