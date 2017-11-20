#ifndef INCLUDEPROJECTMODEL_H
#define INCLUDEPROJECTMODEL_H

#include <QDirModel>

class ProjectDirModel:
  public QDirModel
{
public:
  ProjectDirModel();

  Qt::ItemFlags flags( const QModelIndex & index ) const;

  bool setData( const QModelIndex& index, const QVariant& value, int role );

  QVariant data( const QModelIndex& index, int role ) const;

  /*!
   * \brief Рекурсивное формирование списка отмеченных файлов из указанной директории
   * \param Имя папки
   * \return Список отмеченных файлов
   */
  QStringList getCheckedFiles(const QString& dirName);

  /*!
   * \brief Отметка указанных файлов
   * \param files - файлы
   */
  void setCheckedFiles(const QStringList& files);

  /*!
   * \brief Рекурсивное формирование списка всех файлов из указанной директории
   * \param Имя папки
   * \return Список всех файлов
   */
  QStringList getAllFiles(const QString& dirName);
private:
  /*!
   * \brief Внесение отметок для родственных узлов дерева для текущего узла
   * \param index - узел, для которого отмечаются родственники
   */
  void checkRelativeData(const QModelIndex& index);

  QMap<QModelIndex, Qt::CheckState> m_checkedItems; //!< Мапа отметок файлов и папок
}; // class ProjectDirModel

#endif // INCLUDEPROJECTMODEL_H
