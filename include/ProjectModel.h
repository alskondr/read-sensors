#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <include/ProjectDirModel.h>

#include <QSettings>

class ProjectModel
{
public:
  ProjectModel();

  /*!
   * \brief Сохранение настроек программы
   */
  void saveSettings();

  /*!
   * \brief Загрузка настроек программы
   */
  void loadSettings();

  // Setters and getters
  ProjectDirModel& getProjectDirModel();

  QString getSensorName() const;
  void setSensorName(const QString& sensorName);

  QString getProjectDir() const;
  void setProjectDir(const QString& projectDir);

  QString getSensorsLogFileName() const;
  void setSensorsLogFileName(const QString& sensorsLogFileName);

  unsigned getSensorsLogSize() const;
  void setSensorsLogSize(const unsigned& sensorsLogSize);

private:

  ProjectDirModel m_projectDirModel; //!< Модель директории с проектом

  QString m_sensorName; //!< Имя датчика
  QString m_projectDir; //!< Путь к директории с проектом
  QString m_sensorsLogFileName; //!< Путь к файлу с логом датчиков
  unsigned m_sensorsLogSize; //!< Ориентировочный размер файла с логом датчиков
  QString m_configFileName; //!< Путь к конфигурационному файлу

  QSettings m_settings; //!< Настройки программы
}; // class ProjectModel

#endif // PROJECTMODEL_H
