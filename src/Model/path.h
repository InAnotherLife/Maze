#ifndef SRC_MODEL_PATH_H_
#define SRC_MODEL_PATH_H_

#include <vector>

#include "matrix.h"

namespace my {

constexpr double Start = 13.13;
constexpr double Finish = 99.99;

class FindPath {
 public:
  FindPath() {}
  FindPath(const FindPath& other) = default;
  FindPath(FindPath&& other) = default;
  FindPath& operator=(const FindPath& other) = default;
  FindPath& operator=(FindPath&& other) = default;
  ~FindPath() { delete maze_map_; }

  void SetStartPoint(std::pair<size_t, size_t> start);
  void SetFinishPoint(std::pair<size_t, size_t> finish);
  std::vector<std::pair<size_t, size_t>> GetPath(
      size_t rows, size_t columns, std::vector<size_t> vertical_borders,
      std::vector<size_t> horizontal_borders);

 private:
  Matrix* maze_map_ = nullptr;
  std::vector<std::pair<size_t, size_t>> path_;
  std::pair<size_t, size_t> start_point_;
  std::pair<size_t, size_t> finish_point_;
  std::vector<size_t> vertical_borders_;
  std::vector<size_t> horizontal_borders_;
  int count_step_ = 0;
  void WaveAlgorithm();
  std::pair<bool, bool> CheckNeighbors(size_t i, size_t j);
  bool IsFinish(size_t i, size_t j);
  bool IsEmpty(size_t i, size_t j);
  void SetWaveNumber(size_t i, size_t j, bool* reach_finish,
                     int* count_deadwall);
  void ReversePath();
  void PreviousStep(size_t i, size_t j, std::pair<size_t, size_t>* current);
};
}  // namespace my

#endif  // SRC_MODEL_PATH_H_
