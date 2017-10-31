#include <include/ProjectSettings.h>

ProjectSettings::ProjectSettings(const QString& fileName):
  m_settings(fileName, QSettings::IniFormat)
{
  loadSettings();
}

ProjectSettings::~ProjectSettings()
{
  saveSettings();
}

QString ProjectSettings::getSensorName() const
{
    return m_sensorName;
}

void ProjectSettings::setSensorName(const QString& sensorName)
{
    m_sensorName = sensorName;
}

QString ProjectSettings::getProjectDir() const
{
    return m_projectDir;
}

void ProjectSettings::setProjectDir(const QString& projectDir)
{
    m_projectDir = projectDir;
}

QString ProjectSettings::getSensorsLogFileName() const
{
    return m_sensorsLogFileName;
}

void ProjectSettings::setSensorsLogFileName(const QString& sensorsLogFileName)
{
    m_sensorsLogFileName = sensorsLogFileName;
}

unsigned ProjectSettings::getSensorsLogSize() const
{
    return m_sensorsLogSize;
}

void ProjectSettings::setSensorsLogSize(const unsigned& sensorsLogSize)
{
  m_sensorsLogSize = sensorsLogSize;
}

void ProjectSettings::saveSettings()
{
  /*!
   * \todo Сохранение в файл с настройками списка отмеченных файлов
   */

  m_settings.setValue("project/sensorName", m_sensorName);
  m_settings.setValue("project/projectDir", m_projectDir);
  m_settings.setValue("project/sensorsLogFileName", m_sensorsLogFileName);
  m_settings.setValue("project/sensorsLogSize", m_sensorsLogSize);

  m_settings.setValue("programm/configFileName", m_configFileName);
}

void ProjectSettings::loadSettings()
{
  /*!
   * \todo Загрузка из файла с настройками списка отмеченных файлов
   */

  m_sensorName = m_settings.value("project/sensorName", "").toString();
  m_projectDir = m_settings.value("project/projectDir", "").toString();
  m_sensorsLogFileName = m_settings.value("project/sensorsLogFileName", "").toString();
  m_sensorsLogSize = m_settings.value("project/sensorsLogSize", "1").toInt();

  m_configFileName = m_settings.value("programm/configFileName", "").toString();
}
