#include "path.h"

namespace my {

void FindPath::SetStartPoint(std::pair<size_t, size_t> start) {
  start_point_ = start;
}

void FindPath::SetFinishPoint(std::pair<size_t, size_t> finish) {
  finish_point_ = finish;
}

std::vector<std::pair<size_t, size_t>> FindPath::GetPath(
    size_t rows, size_t columns, std::vector<size_t> vertical_borders,
    std::vector<size_t> horizontal_borders) {
  maze_map_ = new Matrix(rows, columns);
  (*maze_map_)(start_point_.first, start_point_.second) = Start;
  (*maze_map_)(finish_point_.first, finish_point_.second) = Finish;
  vertical_borders_ = vertical_borders;
  horizontal_borders_ = horizontal_borders;
  auto first_check = CheckNeighbors(start_point_.first, start_point_.second);
  if (first_check.first) {
    path_.push_back(start_point_);
    path_.push_back(finish_point_);
  } else {
    WaveAlgorithm();
    ReversePath();
  }
  return path_;
}

void FindPath::WaveAlgorithm() {
  ++count_step_;
  bool stop = false;
  int count_wave = 0;
  int count_deadway = 0;
  for (size_t i = 0; i < static_cast<size_t>(maze_map_->get_rows()); ++i) {
    for (size_t j = 0; j < static_cast<size_t>(maze_map_->get_columns()); ++j) {
      if ((*maze_map_)(i, j) == count_step_) {
        ++count_wave;
        auto result = CheckNeighbors(i, j);
        stop = result.first;
        if (stop) break;
        if (result.second) ++count_deadway;
      }
    }
    if (stop) break;
  }
  if (count_wave == count_deadway) throw std::out_of_range("No maze solution!");
  if (!stop) WaveAlgorithm();
}

std::pair<bool, bool> FindPath::CheckNeighbors(size_t i, size_t j) {
  bool reach_finish = false;
  bool deadwall = false;
  int count_deadwall = 0;
  int columns = maze_map_->get_columns();
  int index_i = i * columns;
  if (!vertical_borders_[j + index_i])
    SetWaveNumber(i, j + 1, &reach_finish, &count_deadwall);
  else
    ++count_deadwall;
  if (j && !vertical_borders_[j + index_i - 1])
    SetWaveNumber(i, j - 1, &reach_finish, &count_deadwall);
  else
    ++count_deadwall;
  if (!horizontal_borders_[j + index_i])
    SetWaveNumber(i + 1, j, &reach_finish, &count_deadwall);
  else
    ++count_deadwall;
  if (i && !horizontal_borders_[j + index_i - columns])
    SetWaveNumber(i - 1, j, &reach_finish, &count_deadwall);
  else
    ++count_deadwall;
  if (count_deadwall == 4) deadwall = true;
  return std::make_pair(reach_finish, deadwall);
}

bool FindPath::IsFinish(size_t i, size_t j) {
  return ((*maze_map_)(i, j) == Finish);
}

bool FindPath::IsEmpty(size_t i, size_t j) { return !(*maze_map_)(i, j); }

void FindPath::SetWaveNumber(size_t i, size_t j, bool* reach_finish,
                             int* count_deadwall) {
  if (IsFinish(i, j))
    *reach_finish = true;
  else if (IsEmpty(i, j))
    (*maze_map_)(i, j) = count_step_ + 1;
  else
    ++(*count_deadwall);
}

void FindPath::ReversePath() {
  path_.push_back(finish_point_);
  int columns = maze_map_->get_columns();
  std::pair<size_t, size_t> current_point = finish_point_;
  while (current_point != start_point_) {
    size_t i = current_point.first;
    size_t j = current_point.second;
    int index_i = i * columns;
    if (i && !horizontal_borders_[j + index_i - columns])
      PreviousStep(i - 1, j, &current_point);
    if (!horizontal_borders_[j + index_i])
      PreviousStep(i + 1, j, &current_point);
    if (j && !vertical_borders_[j + index_i - 1])
      PreviousStep(i, j - 1, &current_point);
    if (!vertical_borders_[j + index_i]) PreviousStep(i, j + 1, &current_point);
    path_.insert(path_.begin(), current_point);
    --count_step_;
    if (!count_step_) count_step_ = static_cast<int>(Start);
  }
}

void FindPath::PreviousStep(size_t i, size_t j,
                            std::pair<size_t, size_t>* current) {
  if (i < static_cast<size_t>(maze_map_->get_rows()) &&
      j < static_cast<size_t>(maze_map_->get_columns()) &&
      static_cast<int>((*maze_map_)(i, j)) == count_step_)
    (*current) = std::make_pair(i, j);
}

}  // namespace my
