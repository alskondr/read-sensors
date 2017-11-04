#include <include/ProjectModel.h>

#include <include/ProjectSettings.h>

#include <QDir>
#include <iostream>

ProjectModel::ProjectModel()
{
  m_projectSettings = std::shared_ptr<ProjectSettings>(new ProjectSettings(QDir::currentPath() + "/default.conf"));
}

ProjectModel::~ProjectModel()
{
}

std::vector<Sensor> ProjectModel::readSensors(const QStringList& projectFilesList)
{
  std::vector<Sensor> sensorsList;

  // Перебор всех файлов проекта и поиск датчиков в них
  for (auto it = projectFilesList.begin(); it != projectFilesList.end(); it++)
  {
    QFile parseFile(*it);
    if (!parseFile.exists())
      break;

    parseFile.open(QIODevice::ReadOnly);
    if (!parseFile.isOpen())
      break;

    std::cout << it->toStdString() << std::endl;

    int strNumder = 0;
    while (!parseFile.atEnd())
    {
      strNumder++;
      QByteArray data = parseFile.readLine();
      if (data.indexOf(m_projectSettings->getSensorName()) >= 0)
      {
        int startSensorParametrs = data.indexOf(m_projectSettings->getSensorName()) + m_projectSettings->getSensorName().length() + 1;
        int endSensorParametrs = data.indexOf(")", startSensorParametrs);
        QString sensorParametrs = data.mid(startSensorParametrs, endSensorParametrs - startSensorParametrs);
        QStringList param = sensorParametrs.split(",", QString::SkipEmptyParts);
        Sensor sensor(parseFile.fileName(), strNumder, m_projectSettings->getSensorName(), param.at(0).toInt(), param.at(1).toInt(), data);
        sensorsList.push_back(sensor);
      }
    }

    parseFile.close();
  }

  return sensorsList;
}

bool ProjectModel::printSensors(std::vector<Sensor>& sensorsList, const QString& traceName)
{
  QFile trace(traceName);
  trace.open(QIODevice::WriteOnly);
  if (!trace.isOpen())
    return false;

  // Перебор всех датчиков с выводом в файл
  QString currFile;
  for (auto it = sensorsList.begin(); it != sensorsList.end(); it++)
  {
    if (QString::compare(currFile, it->getFileName()) != 0)
    {
      currFile = it->getFileName();
      trace.write("File ");
      trace.write(currFile.toStdString().c_str());
      trace.write("\n");
    }
    trace.write("  ");
    trace.write(it->toQString().toStdString().c_str());
  }

  trace.flush();
  trace.close();

  return true;
}

const std::shared_ptr<ProjectSettings>& ProjectModel::getProjectSettings() const
{
  return m_projectSettings;
}

void ProjectModel::setProjectSettings(const std::shared_ptr<ProjectSettings>& projectSettings)
{
  m_projectSettings = projectSettings;
}
