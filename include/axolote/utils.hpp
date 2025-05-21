/**
 * @file utils.hpp
 * @brief contains useful functions
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <string>

// Macro for exporting functions
#ifdef _WIN32
#ifdef AXOLOTE_EXPORTS
#define AXOLOTE_EXPORT __declspec(dllexport)
#else
#define AXOLOTE_EXPORT __declspec(dllimport)
#endif
#else
#define AXOLOTE_EXPORT
#endif

namespace axolote {

enum class DebugType { NONE, INFO, INFO2, WARNING, ERROR, FATAL };

/**
 * @brief read file entirely
 * @author João Vitor Espig (jotaespig@gmail.com)
 * @param filename name of file
 **/
std::string get_file_content(const char *filename);
#ifdef DEBUG
/**
 * @brief Debug function to print
 * @author João Vitor Espig (jotaespig@gmail.com)
 *
 * This function is a debug function to print to stdout. Works like printf.
 **/
template <typename... Args>
void debug(DebugType type, const char *format, Args &&...args) {
    std::string new_format;
    switch (type) {
    case DebugType::NONE:
        new_format = format;
        break;
    case DebugType::INFO:
        new_format = std::string("\033[0;94m[INFO]:\033[0m ") + format + "\n";
        break;
    case DebugType::INFO2:
        new_format = std::string("\033[0;92m[INFO]:\033[0m ") + format + "\n";
        break;
    case DebugType::WARNING:
        new_format
            = std::string("\033[0;33m[WARNING]:\033[0m ") + format + "\n";
        break;
    case DebugType::ERROR:
        new_format = std::string("\033[0;91m[ERROR]:\033[0m ") + format + "\n";
        break;
    case DebugType::FATAL:
        new_format = std::string("\033[4;91m[FATAL]\033[0;91m:\033[0m ") + format + "\n";
        break;
    }

    printf(new_format.c_str(), std::forward<Args>(args)...);
}
#else
/**
 * @brief Debug function to print
 * @author João Vitor Espig (jotaespig@gmail.com)
 *
 * DEBUG is not defined, so this function does nothing.
 **/
template <typename... Args>
void debug(const char *format, Args &&...args) {
}
#endif

} // namespace axolote
