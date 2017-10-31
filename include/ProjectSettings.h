#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <QSettings>
#include <QString>

class ProjectSettings
{
public:
  ProjectSettings(const QString& fileName);
  ~ProjectSettings();

  /*!
   * \brief Сохранение настроек программы
   */
  void saveSettings();

  /*!
   * \brief Загрузка настроек программы
   */
  void loadSettings();

  // Setters and getters
  QString getSensorName() const;
  void setSensorName(const QString& sensorName);

  QString getProjectDir() const;
  void setProjectDir(const QString& projectDir);

  QString getSensorsLogFileName() const;
  void setSensorsLogFileName(const QString& sensorsLogFileName);

  unsigned getSensorsLogSize() const;
  void setSensorsLogSize(const unsigned& sensorsLogSize);

private:
  QString m_sensorName; //!< Имя датчика
  QString m_projectDir; //!< Путь к директории с проектом
  QString m_sensorsLogFileName; //!< Путь к файлу с логом датчиков
  unsigned m_sensorsLogSize; //!< Ориентировочный размер файла с логом датчиков
  QString m_configFileName; //!< Путь к конфигурационному файлу

  QSettings m_settings; //!< Настройки программы

}; // class ProjectSettings

#endif // PROJECTSETTINGS_H
