#include "files.hpp"

#include <fstream>

void File::read_file(const std::string &filename, std::vector<u8> &data) {
  /* Open the file in binary mode */
  std::ifstream file(filename, std::ios::binary);

  if (!file) {
    throw std::runtime_error("Could not open file: " + filename);
  }

  file.seekg(0, std::ios::end);
  std::streampos fileSize = file.tellg();

  file.seekg(0, std::ios::beg);

  data.resize(fileSize);
  file.read(reinterpret_cast<char *>(data.data()), fileSize);

  if (!file) {
    throw std::runtime_error("Error reading file: " + filename);
  }

  file.close();
}
