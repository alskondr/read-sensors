#include <include/ProjectSettings.h>

#include <QDir>

ProjectSettings::ProjectSettings(const QString& fileName):
  m_settings(fileName, QSettings::IniFormat)
{
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

QStringList ProjectSettings::getCheckedFiles() const
{
  return m_checkedFiles;
}

void ProjectSettings::setCheckedFiles(const QStringList& checkedFiles)
{
  m_checkedFiles = checkedFiles;
}

QString ProjectSettings::getSensorsFromAllFilesFileName() const
{
  return m_sensorsFromAllFilesFileName;
}

void ProjectSettings::setSensorsFromAllFilesFileName(const QString& sensorsFromAllFilesFileName)
{
  m_sensorsFromAllFilesFileName = sensorsFromAllFilesFileName;
}

QString ProjectSettings::getSensorsFromCheckedFilesFileName() const
{
  return m_sensorsFromCheckedFilesFileName;
}

void ProjectSettings::setSensorsFromCheckedFilesFileName(const QString& sensorsFromCheckedFilesFileName)
{
  m_sensorsFromCheckedFilesFileName = sensorsFromCheckedFilesFileName;
}

QString ProjectSettings::getTraceSensorLogWriter() const
{
  return m_traceSensorLogWriter;
}

void ProjectSettings::setTraceSensorLogWriter(const QString& traceSensorLogWriter)
{
  m_traceSensorLogWriter = traceSensorLogWriter;
}

QString ProjectSettings::getProgrammLogFileName() const
{
  return m_programmLogFileName;
}

void ProjectSettings::setProgrammLogFileName(const QString& programmLogFileName)
{
  m_programmLogFileName = programmLogFileName;
}

void ProjectSettings::saveSettings()
{
  m_settings.setValue("sensorName", m_sensorName);
  m_settings.setValue("projectDir", m_projectDir);
  m_settings.setValue("sensorsLogFileName", m_sensorsLogFileName);
  m_settings.setValue("sensorsLogSize", m_sensorsLogSize);
  m_settings.setValue("checkedFiles", m_checkedFiles);
  m_settings.setValue("sensorsFromAllFilesFileName", m_sensorsFromAllFilesFileName);
  m_settings.setValue("sensorsFromCheckedFilesFileName", m_sensorsFromCheckedFilesFileName);
  m_settings.setValue("traceSensorsLogWriter", m_traceSensorLogWriter);
  m_settings.setValue("programmLogFileName", m_programmLogFileName);
}

void ProjectSettings::loadSettings()
{
  m_sensorName = m_settings.value("sensorName", "").toString();
  m_projectDir = m_settings.value("projectDir", "").toString();
  m_sensorsLogFileName = m_settings.value("sensorsLogFileName", "").toString();
  m_sensorsLogSize = m_settings.value("sensorsLogSize", "1").toInt();
  m_checkedFiles = m_settings.value("checkedFiles").toStringList();
  m_sensorsFromAllFilesFileName = m_settings.value("sensorsFromAllFilesFileName", QDir::currentPath() + QString::fromUtf8("/sensors-from-all-files.txt")).toString();
  m_sensorsFromCheckedFilesFileName = m_settings.value("sensorsFromCheckedFilesFileName", QDir::currentPath() + QString::fromUtf8("/sensors-from-checked-files.txt")).toString();
  m_traceSensorLogWriter = m_settings.value("traceSensorsLogWriter", QDir::currentPath() + QString::fromUtf8("/trace-sensor-log-writer.txt")).toString();
  m_programmLogFileName = m_settings.value("programmLogFileName", QDir::currentPath() + QString::fromUtf8("/log.txt")).toString();
}
