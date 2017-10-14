#include "SensorsReader.h"

#include <QDir>
#include <QFile>

SensorsReader::SensorsReader()
{

}

SensorsReader::SensorsReader(const QString& sensorName)
{
  m_sensorName = sensorName;
}

bool SensorsReader::printSensors(QList<Sensor>& sensorsList, const QString& traceName)
{
  QFile trace(traceName);
  trace.open(QIODevice::WriteOnly);
  if (!trace.isOpen())
  {
    return false;
  }

  // Перебор всех датчиков с выводом в файл
  QString currFile;
  for (QList<Sensor>::Iterator it = sensorsList.begin(); it != sensorsList.end(); it++)
  {
    if (QString::compare(currFile, (*it).getFileName()) != 0)
    {
      currFile = (*it).getFileName();
      trace.write("File ");
      trace.write(currFile.toStdString().c_str());
      trace.write("\n");
    }
    trace.write("  ");
    trace.write((*it).toQString().toStdString().c_str());
  }

  trace.flush();
  trace.close();

  return true;
}

QList<Sensor> SensorsReader::readSensors(const QString& dirName)
{
  QList<Sensor> sensorsList;

  QDir dir(dirName);
  if (!dir.exists())
  {
    return sensorsList;
  }

  // Поиск датчиков в текущей папке
  QStringList fileList = dir.entryList(QDir::Files);
  for (QStringList::Iterator it = fileList.begin(); it != fileList.end(); it++)
  {
    QString fileName = dir.absoluteFilePath(*it);
    QFile parseFile(fileName);
    parseFile.open(QIODevice::ReadOnly);
    if (!parseFile.isOpen())
    {
      break;
    }

    int strNumder = 0;
    while (!parseFile.atEnd())
    {
      strNumder++;
      QByteArray data = parseFile.readLine();
      if (data.indexOf(m_sensorName) >= 0)
      {
        int startSensorParametrs = data.indexOf(m_sensorName) + m_sensorName.length() + 1;
        int endSensorParametrs = data.indexOf(")", startSensorParametrs);
        QString sensorParametrs = data.mid(startSensorParametrs, endSensorParametrs - startSensorParametrs);
        QStringList param = sensorParametrs.split(",", QString::SkipEmptyParts);
        Sensor sensor(fileName, strNumder, m_sensorName, param.at(0).toInt(), param.at(1).toInt(), data);
        sensorsList.push_back(sensor);
      }
    }

    parseFile.close();
  }

  // Рекурсивный поиск в подпапках
  QStringList dirList = dir.entryList(QDir::Dirs);
  dirList.removeOne(".");
  dirList.removeOne("..");
  for (QStringList::Iterator it = dirList.begin(); it != dirList.end(); it++)
  {
    QDir currDir = dir;
    currDir.cd(*it);
    sensorsList.append(readSensors(currDir.absolutePath()));
  }

  return sensorsList;
}

QString SensorsReader::getSensorName() const
{
  return m_sensorName;
}

void SensorsReader::setSensorName(const QString &sensorName)
{
  m_sensorName = sensorName;
}
