#ifndef PROJECTSETTINGS_H
#define PROJECTSETTINGS_H

#include <QSettings>
#include <QString>

class ProjectSettings
{
public:
  ProjectSettings(const QString& fileName);

  /*!
   * \brief Сохранение настроек программы
   */
  void saveSettings();

  /*!
   * \brief Загрузка настроек программы
   */
  void loadSettings();

  /*!
   * \brief Получить путь к файлу с настройками
   * \return Путь к файлу с настройками
   */
  QString getSettingsFileName() const;

  // Setters and getters
  QString getSensorName() const;
  void setSensorName(const QString& sensorName);

  QString getProjectDir() const;
  void setProjectDir(const QString& projectDir);

  QString getSensorsLogFileName() const;
  void setSensorsLogFileName(const QString& sensorsLogFileName);

  unsigned getSensorsLogSize() const;
  void setSensorsLogSize(const unsigned& sensorsLogSize);

  QStringList getCheckedFiles() const;
  void setCheckedFiles(const QStringList& checkedFiles);

  QString getSensorsFromAllFilesFileName() const;
  void setSensorsFromAllFilesFileName(const QString& sensorsFromAllFilesFileName);

  QString getSensorsFromCheckedFilesFileName() const;
  void setSensorsFromCheckedFilesFileName(const QString& sensorsFromCheckedFilesFileName);

  QString getTraceSensorLogWriter() const;
  void setTraceSensorLogWriter(const QString& traceSensorLogWriter);

  QString getProgrammLogFileName() const;
  void setProgrammLogFileName(const QString& programmLogFileName);

private:
  QSettings m_settings; //!< Настройки программы

  QString m_sensorName; //!< Имя датчика
  QString m_projectDir; //!< Путь к директории с проектом
  QString m_sensorsLogFileName; //!< Путь к файлу с логом датчиков
  unsigned m_sensorsLogSize; //!< Ориентировочный размер файла с логом датчиков
  QStringList m_checkedFiles; //!< Список путей к отмеченным файлам
  QString m_sensorsFromAllFilesFileName; //!< Путь к файлу со всеми датчиками, найденными во всех файлах проекта
  QString m_sensorsFromCheckedFilesFileName; //!< Путь к файлу со всеми датчиками, найденными в отмеченных файлах проекта
  QString m_traceSensorLogWriter; //!< Вывод отладочной информации при записи лога датчиков
  QString m_programmLogFileName; //!< Файл с логом программы

}; // class ProjectSettings

#endif // PROJECTSETTINGS_H
