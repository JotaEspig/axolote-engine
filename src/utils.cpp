#include <fstream>

#include "axolote/utils.hpp"

namespace axolote {

std::string get_file_content(const char *filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        axolote::debug("Failed to open file: %s", filename);
        throw(errno);
    }

    std::string content;
    in.seekg(0, std::ios::end);
    content.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&content[0], content.size());
    in.close();
    return content;
}

} // namespace axolote
