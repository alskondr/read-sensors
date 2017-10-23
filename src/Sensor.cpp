#include "include/Sensor.h"

Sensor::Sensor(QString fileName, int line, QString sensorName, int sensorNumber, int sensorState, QString stringWithSensor)
{
  m_fileName = fileName;
  m_line = line;
  m_sensorName = sensorName;
  m_sensorNumber = sensorNumber;
  m_sensorState = sensorState;
  m_stringWithSensor = stringWithSensor;
}

QString Sensor::toQString() const
{
  QString out = QString("Line ") + QString::number(m_line) + ": " + m_stringWithSensor;
  return out;
}

QString Sensor::getFileName() const
{
  return m_fileName;
}

int Sensor::getLine() const
{
  return m_line;
}

QString Sensor::getStringWithSensor() const
{
  return m_stringWithSensor;
}

QString Sensor::getSensorName() const
{
  return m_sensorName;
}

int Sensor::getSensorNumber() const
{
  return m_sensorNumber;
}

int Sensor::getSensorState() const
{
  return m_sensorState;
}
