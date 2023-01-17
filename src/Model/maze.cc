#include "maze.h"

namespace my {

Maze::Maze(size_t rows, size_t cols)
    : rows_(rows), columns_(cols), count_unique_value_(1) {
  for (size_t i = 0; i < columns_; ++i) maze_line_.push_back(0);
}

std::vector<size_t> Maze::GetVerticalBorders() { return vertical_borders_; }

std::vector<size_t> Maze::GetHorizontalBorders() { return horizontal_borders_; }

void Maze::GenerateMaze() {
  for (size_t i = 0; i < rows_ - 1; ++i) {
    SetUniqueValue();
    SetVerticalBorder();
    SetHorizontalBorder();
    UpdateMaze();
  }
  SetBorder();
}

bool Maze::Random() {
  std::random_device rd;
  std::uniform_int_distribution<int> uniform_dist(0, 1);
  return uniform_dist(rd);
}

size_t Maze::CountUniqueValue(size_t num) {
  int count = 0;
  for (size_t i = 0; i < columns_; ++i) {
    if (maze_line_[i] == num) ++count;
  }
  return count;
}

size_t Maze::CountHorizontalBorder(size_t num) {
  int count = 0;
  for (size_t i = 0; i < columns_; ++i) {
    int index = GetHorizontalBorder() + i;
    if (maze_line_[i] == num && horizontal_borders_[index] == 1) ++count;
  }
  return count;
}

void Maze::MergeValue(size_t index, size_t num) {
  size_t next_num = maze_line_[index + 1];
  for (size_t i = 0; i < columns_; ++i) {
    if (maze_line_[i] == next_num) maze_line_[i] = num;
  }
}

int Maze::GetVeticalBorder() { return vertical_borders_.size() - columns_; }

int Maze::GetHorizontalBorder() {
  return horizontal_borders_.size() - columns_;
}

void Maze::SetUniqueValue() {
  for (size_t i = 0; i < columns_; ++i) {
    if (!maze_line_[i]) {
      maze_line_[i] = count_unique_value_;
      ++count_unique_value_;
    }
  }
}

void Maze::SetVerticalBorder() {
  for (size_t i = 0; i < columns_ - 1; ++i) {
    if (maze_line_[i] == maze_line_[i + 1] || Random()) {
      vertical_borders_.push_back(1);
    } else {
      vertical_borders_.push_back(0);
      MergeValue(i, maze_line_[i]);
    }
  }
  vertical_borders_.push_back(1);
}

void Maze::SetHorizontalBorder() {
  for (size_t i = 0; i < columns_; ++i) {
    if (CountUniqueValue(maze_line_[i]) != 1 && Random())
      horizontal_borders_.push_back(1);
    else
      horizontal_borders_.push_back(0);
  }
  for (size_t i = 0; i < columns_; ++i) {
    int index = GetHorizontalBorder() + i;
    if (CountUniqueValue(maze_line_[i]) == CountHorizontalBorder(maze_line_[i]))
      horizontal_borders_[index] = 0;
  }
}

void Maze::UpdateMaze() {
  for (size_t i = 0; i < columns_; ++i) {
    int index = GetHorizontalBorder() + i;
    if (horizontal_borders_[index] == 1) maze_line_[i] = 0;
  }
}

void Maze::SetBorder() {
  SetUniqueValue();
  SetVerticalBorder();
  size_t k = columns_;
  while (k > 0) {
    horizontal_borders_.push_back(1);
    --k;
  }
  for (size_t i = 0; i < columns_ - 1; ++i) {
    int index = GetVeticalBorder() + i;
    if (maze_line_[i] != maze_line_[i + 1] && vertical_borders_[index] == 1) {
      vertical_borders_[index] = 0;
      MergeValue(i, maze_line_[i]);
    }
  }
}

}  // namespace my
