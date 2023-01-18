#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include <memory>

#include "../Model/maze.h"
#include "../Model/parser.h"

namespace my {

class Controller {
 public:
  void OpenFile(const std::string &file_path);
  size_t GetRows();
  size_t GetColumns();
  std::pair<std::vector<size_t>, std::vector<size_t>> GetMaze();
  std::pair<std::vector<size_t>, std::vector<size_t>> GenerateMaze(
      size_t rows, size_t columns);
  void CheckMaze();

 private:
  std::unique_ptr<Parser> parser_;
  std::unique_ptr<Maze> maze_map_;
};

}  // namespace my

#endif  // SRC_CONTROLLER_CONTROLLER_H_
