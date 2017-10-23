#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "include/SensorsReader.h"
#include "include/SensorsDecoder.h"
#include "include/ProjectDirModel.h"

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

  Q_SLOT void pushProjectDirButton();
  Q_SLOT void pushSensorsLogButton();

private:
  Ui::MainWindow *ui;
  ProjectDirModel m_projectDirModel;
}; // class MainWindow

#endif // MAINWINDOW_H
