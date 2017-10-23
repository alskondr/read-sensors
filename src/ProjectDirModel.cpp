#include "include\ProjectModel.h"

#include <iostream>

ProjectModel::ProjectModel() :
  QFileSystemModel()
{

}

Qt::ItemFlags ProjectModel::flags(const QModelIndex& index) const
{
  return QFileSystemModel::flags(index) | Qt::ItemIsUserCheckable;
}

bool ProjectModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  if(role == Qt::CheckStateRole && index.column() == 0)
  {
    std::cout << m_checkedItems.size() << std::endl;
    m_checkedItems[index] = static_cast<Qt::CheckState>(value.toInt());
    checkRelativeData(index);
    emit dataChanged(index, index.sibling(0,0));
    return true;
  }

  return QFileSystemModel::setData(index, value, role);
}

QVariant ProjectModel::data(const QModelIndex& index, int role) const
{
  if(role == Qt::CheckStateRole && index.column()==0)
  {
    return QVariant(m_checkedItems[index]);
  }

  return QFileSystemModel::data(index, role);
}

QStringList ProjectModel::getCheckedFiles()
{
  QStringList checkedFiles;
  for (QMap<QModelIndex, Qt::CheckState>::Iterator it = m_checkedItems.begin(); it != m_checkedItems.end(); it++)
  {
    if (!isDir(it.key()) && it.value() == Qt::Checked)
    {
      checkedFiles.push_back(filePath(it.key()));
    }
  }
  return checkedFiles;
}

void ProjectModel::checkRelativeData(const QModelIndex& index)
{
  // Отметка детей директории
  Qt::CheckState state = m_checkedItems [index];
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



//  if ( state == Qt::Checked || state == Qt::Unchecked ) {
//    for ( int i = 0; i < rowCount(index); i++ ) {
//      QModelIndex child = index.child(i, 0);
//      if (m_checkedItems [child] != state )
//        setData(child, state, Qt::CheckStateRole);
//    }
//  }

//  QModelIndex parent = index.parent();
//  if (parent.isValid()) {
//    state = m_checkedItems [parent.child(0, 0)];
//    if (state == Qt::PartiallyChecked)
//      m_checkedItems[parent] = state;
//    else {
//      int i = 1;
//      while (i < rowCount(parent) && m_checkedItems [parent.child(i, 0)] == state)
//        i++;
//      if (i != rowCount(index))
//        state = Qt::PartiallyChecked;
//      //setData(parent, state, Qt::CheckStateRole);
//      m_checkedItems [parent] = state;
//    }
//  }
}

