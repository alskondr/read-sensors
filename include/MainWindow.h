#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

namespace Ui {
  class MainWindow;
}

class ProjectModel;
class ProjectDirModel;
class ProjectSettings;

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

  /*!
   * \brief Поиск датчиков в проекте
   */
  Q_SLOT void buildProject();

private:
  /*!
   * \brief Вывод настроек проекта на форму
   */
  void printSettingsToForm();

  /*!
   * \brief Чтение настроек проекта с формы
   */
  void readSettingsFromForm();

  std::unique_ptr<Ui::MainWindow> m_ui; //!< Форма главного окна
  std::unique_ptr<ProjectModel> m_projectModel; //!< Модель данных программы
  std::unique_ptr<ProjectDirModel> m_projectDirModel; //!< Модель данных для дерева проекта

  std::shared_ptr<ProjectSettings> m_projectSettings; //!< Настройки проекта

  const unsigned KILO = 1024; //!< 1024

}; // class MainWindow

#endif // MAINWINDOW_H
