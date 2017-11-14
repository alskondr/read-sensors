#ifndef LOG_H
#define LOG_H

#include <QFile>
#include <QTextStream>

class Log:
  public QObject
{
  Q_OBJECT
public:
  /*!
   * \brief Конструктор Log
   * \param fileName - имя файла с логом
   */
  Log(const QString& fileName);

  ~Log();

  /*!
   * \brief Запись строки в лог
   * \param message - строка
   * \param level - уровень вывода
   * \param color - цвет строки
   */
  void printStringToLog(const QString& message, unsigned level, const QColor& color);

  //! Описание устройств вывода
  enum LogDevice
  {
    FILE = 0,
    WINDOW = 1,
    ALL = 2
  };

  /*!
   * \brief Сигнал о записи строки в лог
   * \param message - строка
   * \param level - уровень вывода
   * \param color - цвет строки
   */
  Q_SIGNAL void printLog(const QString& message, unsigned level, const QColor& color);

private:
  QFile m_logFile; //!< Файл с логом программы
  QTextStream m_logStream; //!< Поток для записи лога программы

}; // class Log

#endif // LOG_H
