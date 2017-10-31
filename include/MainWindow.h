#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

namespace Ui {
  class MainWindow;
}

class ProjectModel;
class ProjectDirModel;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
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
  std::unique_ptr<Ui::MainWindow> m_ui; //!< Форма главного окна
  std::unique_ptr<ProjectModel> m_projectModel; //!< Модель данных программы
  std::unique_ptr<ProjectDirModel> m_projectDirModel; //!< Модель данных для дерева проекта

}; // class MainWindow

#endif // MAINWINDOW_H
