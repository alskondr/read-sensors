#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

namespace Ui {
  class MainWindow;
}

class SensorFinder;
class ProjectDirModel;
class ProjectSettings;
class SensorLogWriter;
class AboutWindow;
class HelpWindow;

/*!
 * \todo Добавить кнопку анализа лога датчиков
 */

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
  Q_SLOT void findSensors();

  /*!
   * \brief Отображение окна "О программе"
   */
  Q_SLOT void showAboutWindow();

  /*!
   * \brief Отображение окна "Справка"
   */
  Q_SLOT void showHelpWindow();

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
  std::unique_ptr<ProjectDirModel> m_projectDirModel; //!< Модель данных для дерева проекта
  std::unique_ptr<SensorFinder> m_sensorsFromAllFiles; //!< Сенсоры найденные во всех файлах проекта
  std::unique_ptr<SensorFinder> m_sensorsFromCheckedFiles; //!< Сенсоры найденные в отмеченных файлах проекта
  std::unique_ptr<SensorLogWriter> m_sensorLogWriter; //!< Лог датчиков

  std::shared_ptr<ProjectSettings> m_projectSettings; //!< Настройки проекта

  std::shared_ptr<AboutWindow> m_aboutWindow; //!< Окно "О программе"
  std::shared_ptr<HelpWindow> m_helpWindow; //!< Окно "Справка"

  const unsigned KILO = 1024; //!< 1024

}; // class MainWindow

#endif // MAINWINDOW_H
