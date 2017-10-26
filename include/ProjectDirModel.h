#ifndef INCLUDEPROJECTMODEL_H
#define INCLUDEPROJECTMODEL_H

#include <QDirModel>

class ProjectDirModel :
    public QDirModel
{
public:
  ProjectDirModel();

  Qt::ItemFlags flags( const QModelIndex & index ) const;

  bool setData( const QModelIndex& index, const QVariant& value, int role );

  QVariant data( const QModelIndex& index, int role ) const;

  /*!
   * \brief Формирование списка отмеченных файлов
   * \return Список отмеченных файлов
   */
  QStringList getCheckedFiles();

  /*!
   * \brief Формирование списка всех файлов
   * \return Список всех файлов
   */
  QStringList getAllFiles();

  /*!
   * \brief Внесение отметок для родственных узлов дерева для текущего узла
   * \param index - узел, для которого отмечаются родственники
   */
  void checkRelativeData(const QModelIndex& index);
private:
  mutable QMap <QModelIndex, Qt::CheckState> m_checkedItems; //!< Мапа отметок файлов и папок
}; // class ProjectModel

#endif // INCLUDEPROJECTMODEL_H
