#include "include/Sensor.h"

Sensor::Sensor(QString fileName, int lineNumber, QString sensorName, int sensorNumber, int sensorState, QString stringWithSensor)
{
  m_fileName = fileName;
  m_lineNumber = lineNumber;
  m_sensorName = sensorName;
  m_sensorNumber = sensorNumber;
  m_sensorState = sensorState;
  m_stringWithSensor = stringWithSensor;
}

QString Sensor::toQString()
{
  QString out = QString("Line ") + QString::number(m_lineNumber) + ": " + m_stringWithSensor;
  return out;
}

QString Sensor::getFileName() const
{
  return m_fileName;
}

unsigned Sensor::getLineNumber() const
{
  return m_lineNumber;
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
