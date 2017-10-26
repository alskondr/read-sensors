#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <include/SensorsReader.h>
#include <include/SensorsDecoder.h>
#include <include/ProjectModel.h>

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
  Ui::MainWindow *m_ui; //!< Форма главного окна
  ProjectModel m_projectModel; //!< Модель данных программы

}; // class MainWindow

#endif // MAINWINDOW_H
