/**
 * \file utils.hpp
 * \brief contains useful functions
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version November 07, 2023
 **/
#pragma once

#include <string>

namespace axolote
{

/**
 * \brief read file entirely
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version October 04, 2023
 * \param filename - name of file
 **/
std::string get_file_content(const char *filename);

} // namespace axolote
