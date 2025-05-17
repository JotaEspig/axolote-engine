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
void debug(const char *format, Args &&...args) {
    std::string new_format
        = std::string("\033[0;91mDEBUG: \033[0m") + format + "\n";
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
