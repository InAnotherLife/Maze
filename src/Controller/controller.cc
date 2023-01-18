#include "controller.h"

namespace my {

void Controller::OpenFile(const std::string &file_path) {
  parser_ = std::make_unique<Parser>();
  parser_->ReadData(file_path);
}

std::pair<std::vector<size_t>, std::vector<size_t>> Controller::GetMaze() {
  return std::make_pair(parser_->GetMazeVertical(),
                        parser_->GetMazeHorizontal());
}

size_t Controller::GetRows() { return parser_->GetRows(); }

size_t Controller::GetColumns() { return parser_->GetColumns(); }

std::pair<std::vector<size_t>, std::vector<size_t>> Controller::GenerateMaze(
    size_t rows, size_t columns) {
  maze_map_ = std::make_unique<Maze>(rows, columns);
  maze_map_->GenerateMaze();
  return std::make_pair(maze_map_->GetVerticalBorders(),
                        maze_map_->GetHorizontalBorders());
}

void Controller::CheckMaze() { parser_->CheckMaze(); }

}  // namespace my
