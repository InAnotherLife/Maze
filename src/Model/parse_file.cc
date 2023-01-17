#include "parse_file.h"

namespace my {

std::vector<size_t> ParseFile::GetMazeVertical() {
  std::vector<size_t> tmp_map(map_.begin(), map_.begin() + (map_.size() / 2));
  return tmp_map;
}

std::vector<size_t> ParseFile::GetMazeHorizontal() {
  std::vector<size_t> tmp_map(map_.begin() + (map_.size() / 2),
                              map_.begin() + map_.size());
  return tmp_map;
}

size_t ParseFile::GetRows() { return rows_; }

size_t ParseFile::GetColumns() { return columns_; }

void ParseFile::ReadData(const std::string &file_path) {
  map_.clear();
  std::ifstream file;
  file.open(file_path);
  if (!file.good()) throw std::runtime_error("No such file or directory");
  std::string str;
  getline(file, str);
  sscanf(str.c_str(), "%zu %zu", &rows_, &columns_);
  if (rows_ > 50 || columns_ > 50)
    throw std::out_of_range("Rows or columns is out of range");
  while (getline(file, str)) {
    // Примечание: strtok_r - кроссплатформенное решение, работает на
    // винде, маке и убунте. Разделение строки на токены при помощи getline
    // не работает на маке и убунте, если в конце строки нет пробела.
    char *token, *rest = nullptr;
    for (token = strtok_r(const_cast<char *>(str.c_str()), " ", &rest);
         token != nullptr; token = strtok_r(nullptr, " ", &rest)) {
      if (*token == '0')
        map_.push_back(0);
      else if (*token == '1')
        map_.push_back(1);
    }
  }
  file.close();
}

void ParseFile::CheckMaze() {
  if (map_.size() != rows_ * columns_ * 2)
    throw std::out_of_range("The file is damaged or this is not maze");
}

}  // namespace my
