#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <include/Sensor.h>

#include <QSettings>

#include <memory>
#include <vector>

class ProjectSettings;

class ProjectModel
{
public:
  ProjectModel();
  ~ProjectModel();

  /*!
   * \brief Поиск датчиков в указанных файлах
   * \param projectFiles - Список файлов с абсолютными путями, в которых необходимо искать датчики
   * \return Список датчиков, найденных в указанных файлах
   */
  std::vector<std::shared_ptr<Sensor>> readSensors(const QStringList& projectFilesList);

  /*!
   * \brief Вывод информации по датчикам в файл
   * \param sensorsList - Список датчиков
   * \param traceName - Имя выходного файла
   * \return Статус (0 - ошибка, 1 - успех)
   */
  bool printSensors(const std::vector<std::shared_ptr<Sensor>>& sensorsList, const QString& traceName);

  const std::shared_ptr<ProjectSettings>& getProjectSettings() const;
  void setProjectSettings(const std::shared_ptr<ProjectSettings>& projectSettings);

private:
  std::shared_ptr<ProjectSettings> m_projectSettings; //!< Параметры работы программы

}; // class ProjectModel

#endif // PROJECTMODEL_H
