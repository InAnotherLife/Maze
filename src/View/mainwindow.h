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
  QPen pen_;
  QColor color_;
  void GetStep();
  void DrawBorder();
  void DrawMaze();
  void ClearVars();
  void SceneClear();

 private slots:
  void on_maze_open_pushButton_clicked();
  void on_maze_generate_pushButton_clicked();
  void on_maze_safe_pushButton_clicked();
};

#endif  // SRC_VIEW_MAINWINDOW_H
