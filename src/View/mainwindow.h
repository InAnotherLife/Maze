#ifndef SRC_VIEW_MAINWINDOW_H
#define SRC_VIEW_MAINWINDOW_H

#include <QColor>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLine>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPen>
#include <QTextStream>
#include <memory>
#include <utility>

#include "../Controller/controller.h"

constexpr unsigned short int Side = 500;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 protected slots:
  void mousePressEvent(QMouseEvent *event) override;

 private:
  std::unique_ptr<Ui::MainWindow> ui_;
  std::unique_ptr<QGraphicsScene> scene_;
  std::unique_ptr<my::Controller> controller_;
  QString home_path_;
  double step_x_;
  double step_y_;
  std::pair<std::vector<size_t>, std::vector<size_t>> maze_map_;
  size_t rows_;
  size_t columns_;
  std::pair<size_t, size_t> begin_point_;
  std::pair<size_t, size_t> end_point_;
  unsigned short int coords_flag_;
  QPen pen_;
  QColor color_;
  void GetStep();
  void DrawBorder();
  void DrawMaze();
  void ClearVars();
  void SceneClear();
  void FindPath();
  std::pair<size_t, size_t> GetCoords(QColor color);
  void DrawRect(size_t x, size_t y, QColor color);

 private slots:
  void on_maze_open_pushButton_clicked();
  void on_maze_generate_pushButton_clicked();
  void on_maze_safe_pushButton_clicked();
};

#endif  // SRC_VIEW_MAINWINDOW_H
