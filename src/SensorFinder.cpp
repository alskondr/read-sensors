#include <SensorFinder.h>

#include <ProjectSettings.h>
#include <Log.h>

#include <QFile>

bool SensorFinder::findSensors(const QStringList& projectFilesList, const QString& sensorName)
{
  // Перебор всех файлов проекта и поиск датчиков в них
  for (auto it = projectFilesList.begin(); it != projectFilesList.end(); it++)
  {
    QFile parseFile(*it);
    if (!parseFile.exists())
      continue;

    parseFile.open(QIODevice::ReadOnly);
    if (!parseFile.isOpen())
      continue;

    Log::g_log.printStringToLog(*it, Log::FILE);

    int strNumder = 0;
    while (!parseFile.atEnd())
    {
      strNumder++;
      QByteArray data = parseFile.readLine();
      if (data.indexOf(sensorName) >= 0)
      {
        int startSensorParametrs = data.indexOf(sensorName) + sensorName.length() + 1;
        int endSensorParametrs = data.indexOf(")", startSensorParametrs);
        QString sensorParametrs = data.mid(startSensorParametrs, endSensorParametrs - startSensorParametrs);
        QStringList param = sensorParametrs.split(",", QString::SkipEmptyParts);
        Sensor sensor(parseFile.fileName(), strNumder, sensorName, param.at(0).toInt(), param.at(1).toInt(), data);
        m_findSensorsVector.push_back(sensor);
      }
    }

    parseFile.close();
  }

  return true;
}

bool SensorFinder::printSensors(const QString& traceName)
{
  QFile trace(traceName);
  trace.open(QIODevice::WriteOnly);
  if (!trace.isOpen())
    return false;

  // Перебор всех датчиков с выводом в файл
  QString currFile;
  for (auto it = m_findSensorsVector.begin(); it != m_findSensorsVector.end(); it++)
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

unsigned SensorFinder::getSensorsCount() const
{
  return m_findSensorsVector.size();
}

void SensorFinder::clear()
{
  m_findSensorsVector.clear();
}

const std::vector<Sensor>& SensorFinder::getFindSensorsVector() const
{
  return m_findSensorsVector;
}
