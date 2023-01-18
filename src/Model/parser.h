#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <cstring>
#include <fstream>
#include <vector>

namespace my {

class Parser {
 public:
  Parser() : rows_(0), columns_(0), map_(0){};
  void ReadData(const std::string &file_path);
  std::vector<size_t> GetMazeVertical();
  std::vector<size_t> GetMazeHorizontal();
  size_t GetRows();
  size_t GetColumns();
  void CheckMaze();

 private:
  size_t rows_;
  size_t columns_;
  std::vector<size_t> map_;
};

}  // namespace my

#endif  // SRC_MODEL_PARSER_H_
