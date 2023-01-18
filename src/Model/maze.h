#ifndef SRC_MODEL_MAZE_H_
#define SRC_MODEL_MAZE_H_

#include <iostream>
#include <random>
#include <vector>

namespace my {
class Maze {
 public:
  Maze() : rows_(0), columns_(0), count_unique_value_(1){};
  Maze(size_t rows, size_t cols);
  std::vector<size_t> GetVerticalBorders();
  std::vector<size_t> GetHorizontalBorders();
  void GenerateMaze();

 private:
  size_t rows_;
  size_t columns_;
  size_t count_unique_value_;
  std::vector<size_t> vertical_borders_;
  std::vector<size_t> horizontal_borders_;
  std::vector<size_t> maze_line_;
  bool Random();
  size_t CountUniqueValue(size_t set_number);
  size_t CountHorizontalBorder(size_t set_number);
  int GetVeticalBorder();
  int GetHorizontalBorder();
  void MergeValue(size_t index, size_t set_number);
  void SetUniqueValue();
  void SetVerticalBorder();
  void SetHorizontalBorder();
  void UpdateMaze();
  void SetBorder();
};

}  // namespace my

#endif  // SRC_MODEL_MAZE_H_
