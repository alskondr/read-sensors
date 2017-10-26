#include "include/ProjectModel.h"

ProjectModel::ProjectModel():
  m_settings(QDir::currentPath() + "/default.conf", QSettings::IniFormat)
{
  loadSettings();
}

ProjectDirModel& ProjectModel::getProjectDirModel()
{
  return m_projectDirModel;
}

QString ProjectModel::getSensorName() const
{
    return m_sensorName;
}

void ProjectModel::setSensorName(const QString& sensorName)
{
    m_sensorName = sensorName;
}

QString ProjectModel::getProjectDir() const
{
    return m_projectDir;
}

void ProjectModel::setProjectDir(const QString& projectDir)
{
    m_projectDir = projectDir;
}

QString ProjectModel::getSensorsLogFileName() const
{
    return m_sensorsLogFileName;
}

void ProjectModel::setSensorsLogFileName(const QString& sensorsLogFileName)
{
    m_sensorsLogFileName = sensorsLogFileName;
}

unsigned ProjectModel::getSensorsLogSize() const
{
    return m_sensorsLogSize;
}

void ProjectModel::setSensorsLogSize(const unsigned& sensorsLogSize)
{
  m_sensorsLogSize = sensorsLogSize;
}

void ProjectModel::saveSettings()
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

void ProjectModel::loadSettings()
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
