#ifndef INCLUDEPROJECTMODEL_H
#define INCLUDEPROJECTMODEL_H

#include <QFileSystemModel>

class ProjectModel :
    public QFileSystemModel
{
public:
  ProjectModel();

  Qt::ItemFlags flags( const QModelIndex & index ) const;

  bool setData( const QModelIndex& index, const QVariant& value, int role );

  QVariant data( const QModelIndex& index, int role ) const;

  /*!
   * \brief Формирование списка отмеченных файлов
   * \return Список отмеченных файлов
   */
  QStringList getCheckedFiles();

  void checkRelativeData(const QModelIndex& index);
private:
  mutable QMap <QModelIndex, Qt::CheckState> m_checkedItems;
}; // class ProjectModel

#endif // INCLUDEPROJECTMODEL_H
