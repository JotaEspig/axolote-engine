#include <axolote/utils.hpp>
#include <fstream>
#include <sstream>

std::string get_file_content(const char *filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in)
        throw (errno);

    std::string content;
    in.seekg(0, std::ios::end);
    content.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&content[0], content.size());
    in.close();
    return content;
}
