#ifndef SENSOR_H
#define SENSOR_H

#include <QString>

class Sensor
{
public:
  /*!
   * \brief Конструктор класса Sensor
   * \param fileName - Имя файла с датчиком
   * \param line - Номер строки с датчиком
   * \param stringWithSensor - Строка, содержащая датчик
   */
  Sensor(QString fileName, int line, QString sensorName, int sensorNumber, int sensorState, QString stringWithSensor);

  /*!
   * \brief Сериализация сенсора в QString
   * \return QString с описанием датчика
   */
  QString toQString() const;

  QString getFileName() const;

  int getLine() const;

  QString getStringWithSensor() const;

  QString getSensorName() const;

  int getSensorNumber() const;

  int getSensorState() const;

private:
  QString m_fileName; //! Имя файла, в котором найден датчик
  int m_line; //! Номер строки, в которой найден датчик
  QString m_sensorName; //! Имя датчика
  int m_sensorNumber; //! Номер датчика
  int m_sensorState; //! Состояние датчика
  QString m_stringWithSensor; //! Строка, содержащая датчик
}; // class Sensor

#endif // SENSOR_H
