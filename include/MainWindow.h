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

  /*!
   * \brief Запись датчиков в лог
   */
  Q_SLOT void printSensorsLog();

  /*!
   * \brief Обработчик нажатия на клавишу выбора директории с проектом
   */
  Q_SLOT void pushProjectDirButton();

  /*!
   * \brief Обработчик нажатия на клавишу выбора файла с логом датчиков
   */
  Q_SLOT void pushSensorsLogButton();

private:
  Ui::MainWindow *ui; //! Форма главного окна
  ProjectDirModel m_projectDirModel; //! Модель директории с проектом
}; // class MainWindow

#endif // MAINWINDOW_H
