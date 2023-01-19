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

std::vector<std::pair<size_t, size_t>> Controller::GetPath(
    std::pair<size_t, size_t> start, std::pair<size_t, size_t> finish,
    size_t rows, size_t columns,
    std::pair<std::vector<size_t>, std::vector<size_t>> maze_map) {
  find_path_ = std::make_unique<FindPath>();
  find_path_->SetStartPoint(start);
  find_path_->SetFinishPoint(finish);
  auto result =
      find_path_->GetPath(rows, columns, maze_map.first, maze_map.second);
  return result;
}

}  // namespace my
