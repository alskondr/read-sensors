#ifndef SENSORSDECODER_H
#define SENSORSDECODER_H

#include "Sensor.h"

#include <QList>

#include <vector>
#include <set>

class SensorsDecoder
{
public:
  SensorsDecoder();

  typedef std::vector<std::vector<std::pair<int, int> > > SensorsVector;

  /*!
   * \brief Чтение списка датчиков и составление вектора с ними,
   * удаляя датчики встречаемые ранее в файле с одинаковыми номерами и состояниями,
   * а также содержащиеся в блоке else, если между этими датчиками нет других.
   * При этом осуществляется формирование векторов всех найденных уникальных датчиков и всех удаленных датчиков (не уникальные)
   * \param sensorsList - список датчиков
   */
  void readSensors(QList<Sensor> sensorsList);

  /*!
   * \brief Вывод лога датчиков в файл до указанного размера и формирование множества всех уникальных выведенных в файл датчиков
   * \param fileName - Имя файла, в который будут дописываться датчики
   * \param fileSize - Размер файла, до которого нужно писать файл
   * \return Процент вхождения датчиков (количество всех датчиков / количество выведенных в лог датчиков)
   */
  double printSensors(const QString& fileName, const int fileSize);

  /*!
   * \brief Вывод отладочной информации по формирования вектора датчиков в файл
   * \param fileName - имя файла
   * \return Статус (0 - ошибка, 1 - успех)
   */
  bool printDebug(const QString& fileName);

  SensorsVector getSensors() const;

  /*!
   * \brief Функция возвращает количество уникальных сенсоров, записанных в лог
   * \return Количество уникальных сенсоров, записанных в лог
   */
  int getAmountPrintUniqueSensors() const;

  /*!
   * \brief Функция возвращает количество уникальных сенсоров, считанных из входного списка
   * \return Количество уникальных сенсоров, считанных из входного списка
   */
  int getAmountAllUniqueSensors() const;

private:
  SensorsVector m_sensors; //! Структура для хранения датчиков датчиков, разбитых по файлам
  std::vector<std::pair<int, int> > m_delSensors; //! Вектор с удаленными датчиками при считывании датчиков
  std::set<std::pair<int, int> > m_allUniqueSensors; //! Номера всех датчиков, которые приходят на вход
  std::set<std::pair<int, int> > m_printUniqueSensors; //! Номера записанных сенсоров в лог
};

#endif // SENSORSDECODER_H
