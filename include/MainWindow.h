#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include/SensorsReader.h"
#include "include/SensorsDecoder.h"
#include "include/ProjectModel.h"

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  Q_SLOT void printSensorsLog();

private:
  Ui::MainWindow *ui;
  ProjectModel m_projectDirModel;
}; // class MainWindow

#endif // MAINWINDOW_H
