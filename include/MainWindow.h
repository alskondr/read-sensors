#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SensorsReader.h"
#include "SensorsDecoder.h"

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

  Q_SLOT printSensorsLog();

private:
  Ui::MainWindow *ui;
}; // class MainWindow

#endif // MAINWINDOW_H
