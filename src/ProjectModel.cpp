#include <include/ProjectModel.h>

#include <include/ProjectSettings.h>

#include <QDir>

ProjectModel::ProjectModel()
{
  m_projectSettings = std::shared_ptr<ProjectSettings>(new ProjectSettings(QDir::currentPath() + "/default.conf"));
}

ProjectModel::~ProjectModel()
{
}

const std::shared_ptr<ProjectSettings>& ProjectModel::getProjectSettings() const
{
  return m_projectSettings;
}

void ProjectModel::setProjectSettings(const std::shared_ptr<ProjectSettings>& projectSettings)
{
  m_projectSettings = projectSettings;
}
