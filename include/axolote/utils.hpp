/**
 * \file utils.hpp
 * \brief contains useful functions
 * \author João Vitor Espig (JotaEspig)
 **/
#pragma once

#include <string>

namespace axolote {

/**
 * \brief read file entirely
 * \author João Vitor Espig (JotaEspig)
 * \param filename - name of file
 **/
std::string get_file_content(const char *filename);

} // namespace axolote
