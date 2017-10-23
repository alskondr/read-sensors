#include "include/SensorsDecoder.h"

#include <QFile>
#include <QTextStream>

SensorsDecoder::SensorsDecoder()
{

}

SensorsDecoder::SensorsVector SensorsDecoder::getSensors() const
{
  return m_sensors;
}

int SensorsDecoder::getAmountPrintUniqueSensors() const
{
  return m_printUniqueSensors.size();
}

int SensorsDecoder::getAmountAllUniqueSensors() const
{
  return m_allUniqueSensors.size();
}

void SensorsDecoder::readSensors(QList<Sensor> sensorsList)
{
  m_sensors.clear();

  QString currFile = "";
  std::vector<std::pair<int, int> > sensorsOnFile;
  for (QList<Sensor>::Iterator it = sensorsList.begin(); it != sensorsList.end(); it++)
  {
    bool isSave = true;
    if (QString::compare(currFile, (*it).getFileName()) != 0)
    {
      currFile = (*it).getFileName();
      if (sensorsOnFile.size() > 0)
      {
        m_sensors.push_back(sensorsOnFile);
      }
      sensorsOnFile.clear();
    }
    std::pair<int, int> sensor;
    sensor.first = (*it).getSensorNumber();
    sensor.second = (*it).getSensorState();

    m_allUniqueSensors.insert(sensor);

    // Удаление датчиков с блока else
    // (если в строке с датчиком встречается else, а в следующей строке также указан текущий датчик,
    // то они удаляются из результирующего вектора датчиков)
    if (((*it).getStringWithSensor().contains("else") || (*it).getStringWithSensor().contains("catch")) && (*it).getSensorNumber() == (*(it+1)).getSensorNumber())
    {
      it++;
      std::pair<int, int> sensor;
      sensor.first = (*it).getSensorNumber();
      sensor.second = (*it).getSensorState();
      m_allUniqueSensors.insert(sensor);
      continue;
    }

    // Перебор всех уже записанных в вектор датчиков, для удаления повторов
    for (std::vector<std::pair<int, int> >::iterator delIt = sensorsOnFile.begin(); delIt != sensorsOnFile.end(); delIt++)
    {
      // Выбрасываем из текущего вектора датчики в состоянии 2 (второй параметр датчика равен 2) с равным номером текущему,
      // которые встречались выше
      if (sensor.second == 2 && (*delIt).second == 2 && (*delIt).first == sensor.first)
      {
        m_delSensors.push_back(*delIt);
        sensorsOnFile.erase(delIt);
        delIt--;
      }
      // Не записываем в вектор датчики в состоянии 1 (второй параметр датчика равен 1) с номером равным уже записанному в вектор
      if (sensor.second == 1 && (*delIt).second == 1 && (*delIt).first == sensor.first)
      {
        m_delSensors.push_back(sensor);
        isSave = false;
      }
    }

    if (isSave)
    {
      sensorsOnFile.push_back(sensor);
    }
  }
  m_sensors.push_back(sensorsOnFile);
}

double SensorsDecoder::printSensors(const QString& fileName, const int fileSize)
{
  QFile out(fileName);
  out.open(QIODevice::Append | QIODevice::Text);
  if (!out.isOpen())
  {
    return 0.0;
  }

  QTextStream outStream(&out);

  // Вывод датчиков в файл пока он не достигнет указанного размера
  while (out.size() < fileSize)
  {
    // Делим файлы с датчиками на 10 частей, берем рандомно одну из них и выводим в файл
    int partSize = m_sensors.size() / 10;
    int startFileNumber = (rand() % 10) * partSize;
    int endFileNumber = startFileNumber + partSize + 10;
    for (SensorsVector::iterator fileIt = m_sensors.begin() + startFileNumber; fileIt != (endFileNumber < m_sensors.size() ? m_sensors.begin() + endFileNumber : m_sensors.end()); fileIt++)
    {
      for (std::vector<std::pair<int, int> >::iterator sensorIt = (*fileIt).begin(); sensorIt != (*fileIt).end(); sensorIt++)
      {
        outStream << (*sensorIt).first << ":" << (*sensorIt).second << "\n";
        m_printUniqueSensors.insert(*sensorIt);
      }
    }
  }

  out.close();

  return (double)m_printUniqueSensors.size() / (double)m_allUniqueSensors.size();
}

bool SensorsDecoder::printDebug(const QString& fileName)
{
  QFile out(fileName);
  out.open(QIODevice::WriteOnly);
  if (!out.isOpen())
  {
    return false;
  }

  for (SensorsVector::iterator fileIt = m_sensors.begin(); fileIt != m_sensors.end(); fileIt++)
  {
    out.write("file\n");
    for (std::vector<std::pair<int, int> >::iterator sensorIt = (*fileIt).begin(); sensorIt != (*fileIt).end(); sensorIt++)
    {
      out.write("  sensor:");
      out.write(QString::number((*sensorIt).first).toStdString().c_str());
      out.write(":");
      out.write(QString::number((*sensorIt).second).toStdString().c_str());
      out.write("\n");
    }
  }

  out.write("\n\n\nDeleted sensors: ");
  out.write(QString::number(m_delSensors.size()).toStdString().c_str());
  out.write(":\n");
  for (std::vector<std::pair<int, int> >::iterator sensorIt = m_delSensors.begin(); sensorIt != m_delSensors.end(); sensorIt++)
  {
    out.write("  sensor:");
    out.write(QString::number((*sensorIt).first).toStdString().c_str());
    out.write(":");
    out.write(QString::number((*sensorIt).second).toStdString().c_str());
    out.write("\n");
  }

  out.close();

  return true;
}
