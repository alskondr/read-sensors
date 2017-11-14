#include "include/ProjectDirModel.h"

ProjectDirModel::ProjectDirModel() :
  QDirModel()
{}

Qt::ItemFlags ProjectDirModel::flags(const QModelIndex& index) const
{
  return QDirModel::flags(index) | Qt::ItemIsUserCheckable;
}

bool ProjectDirModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  if(role == Qt::CheckStateRole && index.column() == 0)
  {
    m_checkedItems[index] = static_cast<Qt::CheckState>(value.toInt());
    checkRelativeData(index);
    emit dataChanged(index, index.sibling(0,0));
    return true;
  }

  return QDirModel::setData(index, value, role);
}

QVariant ProjectDirModel::data(const QModelIndex& index, int role) const
{
  if(role == Qt::CheckStateRole && index.column()==0)
  {
    return QVariant(m_checkedItems[index]);
  }

  return QDirModel::data(index, role);
}

QStringList ProjectDirModel::getCheckedFiles(const QString& dirName)
{
  QStringList allFiles = getAllFiles(dirName);

  QStringList checkedFiles;
  for (auto it = m_checkedItems.begin(); it != m_checkedItems.end(); it++)
  {
    QString absoluteFileName = this->filePath(it.key());
    if (!isDir(it.key()) && it.value() == Qt::Checked && allFiles.contains(absoluteFileName))
    {
      checkedFiles.push_back(filePath(it.key()));
    }
  }

  return checkedFiles;
}

void ProjectDirModel::setCheckedFiles(const QStringList& files)
{
  m_checkedItems.clear();

  for (auto file : files)
  {
    if (!QFile::exists(file))
      continue;

    setData(this->index(file), Qt::Checked, Qt::CheckStateRole);
  }
}

QStringList ProjectDirModel::getAllFiles(const QString& dirName)
{
  QStringList allFiles;

  // Получение файлов в текущей папке
  QDir dir(dirName);
  if (!dir.exists())
    return allFiles;
  QStringList fileList = dir.entryList(QDir::Files);
  for (auto it = fileList.begin(); it != fileList.end(); it++)
  {
    QString fileName = dir.absoluteFilePath(*it);
    allFiles.push_back(fileName);
  }

  // Рекурсивный поиск в подпапках
  QStringList dirList = dir.entryList(QDir::Dirs);
  dirList.removeOne(".");
  dirList.removeOne("..");
  for (auto it = dirList.begin(); it != dirList.end(); it++)
  {
    QDir currDir = dir;
    currDir.cd(*it);
    allFiles.append(getAllFiles(currDir.absolutePath()));
  }

  return allFiles;
}

void ProjectDirModel::checkRelativeData(const QModelIndex& index)
{
  // Отметка детей узла
  Qt::CheckState state = m_checkedItems[index];
  fetchMore(index);
  if (isDir(index) && (state == Qt::Checked || state == Qt::Unchecked))
  {
    for (int i = 0; i < rowCount(index); i++)
    {
      QModelIndex child = index.child(i, 0);
      if (m_checkedItems[child] != state)
      {
        setData(child, state, Qt::CheckStateRole);
      }
    }
  }

  // Отметка родителей узла
  QModelIndex curr = index;
  while (curr.parent().isValid())
  {
    int amountCheckedItems = 0;
    bool isChecked = false;
    QModelIndex parent = curr.parent();
    for (int i = 0; i < rowCount(parent); i++)
    {
      QModelIndex child = parent.child(i, 0);
      if (m_checkedItems[child] == Qt::Checked)
      {
        amountCheckedItems++;
      }
      if (m_checkedItems[child] == Qt::PartiallyChecked)
      {
        m_checkedItems[parent] = Qt::PartiallyChecked;
        emit dataChanged(parent, parent.sibling(0,0));
        isChecked = true;
      }
    }
    if (!isChecked)
    {
      if (rowCount(parent) == amountCheckedItems)
      {
        m_checkedItems[parent] = Qt::Checked;
        emit dataChanged(parent, parent.sibling(0,0));
      }
      else if (amountCheckedItems == 0)
      {
        m_checkedItems[parent] = Qt::Unchecked;
        emit dataChanged(parent, parent.sibling(0,0));
      }
      else
      {
        m_checkedItems[parent] = Qt::PartiallyChecked;
        emit dataChanged(parent, parent.sibling(0,0));
      }
    }
    curr = parent;
  }
}

