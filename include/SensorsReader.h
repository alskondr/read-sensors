#ifndef SENSORSREADER_H
#define SENSORSREADER_H

#include "Sensor.h"

#include <QString>
#include <QList>

class SensorsReader
{
public:
  SensorsReader();

  /*!
   * \brief Конструктор для класса SensorsReader
   * \param sensorName - Имя датчика
   */
  SensorsReader(const QString& sensorName);

  /*!
   * \brief Вывод информации по датчикам в файл
   * \param sensorsList - Список датчиков
   * \param traceName - Имя выходного файла
   * \return Статус (0 - ошибка, 1 - успех)
   */
  static bool printSensors(QList<Sensor>& sensorsList, const QString& traceName);

  /*!
   * \brief Рекурсивный поиск датчиков, начиная с указанной папки
   * \param dirName - Имя папки начала поиска
   * \return Список датчиков
   */
  QList<Sensor> readSensors(const QString& dirName);

  QString getSensorName() const;
  void setSensorName(const QString &sensorName);

private:
  QString m_sensorName; //! Название сенсора, который необходимо найти
}; // class SensorsReader

#endif // SENSORSREADER_H
