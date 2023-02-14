#pragma once

#include "WebSerial.h"
#include "time.h"

#define ASSERT(x)                                                \
    if (!x) {                                                    \
        printf ("assert failure %s:%d\r\n", __FILE__, __LINE__); \
        while (true)                                             \
            ;                                                    \
    }

constexpr const char* file_name (const char* path) {
    const char* file = path;
    while (*path) {
        if (*path++ == '/') {
            file = path;
        }
    }
    return file;
}

#define CUBE_LOG_ALL(...)                                               \
    do {                                                                \
        char fileLine[100] = "";                                        \
        char ARG[100]      = "";                                        \
        printf ("[%s:%d] ", file_name (__FILE__), __LINE__);            \
        printf (__VA_ARGS__);                                           \
        printf ("\r\n");                                                \
        sprintf (fileLine, "[%s:%d] ", file_name (__FILE__), __LINE__); \
        WebSerial.print ((String)(fileLine));                           \
        sprintf (ARG, __VA_ARGS__);                                     \
        WebSerial.println ((String)(ARG));                              \
    } while (0)

#define CUBE_LOG_SERIAL(...)                             \
    printf ("[%s:%d] ", file_name (__FILE__), __LINE__); \
    printf (__VA_ARGS__);                                \
    printf ("\r\n");

#define CUBE_LOG_WEB(...)                                               \
    do {                                                                \
        char fileLine[100] = "";                                        \
        char ARG[100]      = "";                                        \
        sprintf (fileLine, "[%s:%d] ", file_name (__FILE__), __LINE__); \
        WebSerial.print ((String)(fileLine));                           \
        sprintf (ARG, __VA_ARGS__);                                     \
        WebSerial.println ((String)(ARG));                              \
    } while (0)

#include <cstdint>

uint32_t get_time_cube ();