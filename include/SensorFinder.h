#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <Sensor.h>

#include <QSettings>

#include <vector>

class ProjectSettings;

class SensorFinder
{
public:

  /*!
   * \brief Поиск датчиков в указанных файлах
   * \param projectFilesList - Список файлов с абсолютными путями, в которых необходимо искать датчики
   * \param sensorName - Имя датчика
   * \return Статус (0 - ошибка, 1 - успех)
   */
  bool findSensors(const QStringList& projectFilesList, const QString& sensorName);

  /*!
   * \brief Вывод информации по датчикам в файл
   * \param traceName - Имя выходного файла
   * \return Статус (0 - ошибка, 1 - успех)
   */
  bool printSensors(const QString& traceName);

  /*!
   * \brief Возвращает количество найденных сенсоров
   * \return Количество найденных сенсоров
   */
  unsigned getSensorsCount() const;

  /*!
   * \brief Очистка списка найденных датчиков
   */
  void clear();

  const std::vector<Sensor>& getFindSensorsVector() const;

private:
  std::vector<Sensor> m_findSensorsVector; //!< Вектор всех датчиков найденных в проекте

}; // class ProjectModel

#endif // PROJECTMODEL_H
