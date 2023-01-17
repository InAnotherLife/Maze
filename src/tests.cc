#include <gtest/gtest.h>

#include <vector>

#include "./Controller/controller.h"

std::string file_1 = "../examples/maze_2.txt";
std::string file_2 = "../examples/maze_4 (bad).txt";
std::string file_3 = "../examples/maze_123.txt";
my::ParseFile parser;
my::Controller controller;

using int_type = unsigned short int;

TEST(Maze, test_parse_file_1) {
  parser.ReadData(file_1);
  std::vector<size_t> maze_vert = parser.GetMazeVertical();
  std::vector<size_t> maze_horiz = parser.GetMazeHorizontal();
  int_type rows = parser.GetRows();
  int_type columns = parser.GetColumns();
  ASSERT_EQ(rows, 20);
  ASSERT_EQ(columns, 22);
  ASSERT_EQ(maze_vert.size(), rows * columns);
  ASSERT_EQ(maze_horiz.size(), rows * columns);
  ASSERT_NO_THROW(parser.CheckMaze());
}

TEST(Maze, test_parse_file_error_2) {
  parser.ReadData(file_2);
  int_type rows = parser.GetRows();
  int_type columns = parser.GetColumns();
  ASSERT_EQ(rows, 10);
  ASSERT_EQ(columns, 10);
  ASSERT_ANY_THROW(parser.CheckMaze());
}

TEST(Maze, test_open_file_error_3) {
  ASSERT_ANY_THROW(parser.ReadData(file_3));
}

int main(int argc, char **argv) {
  setlocale(LC_ALL, "en_US.UTF-8");
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}