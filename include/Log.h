#ifndef LOG_H
#define LOG_H

#include <QFile>
#include <QTextStream>

class Log
{
public:
  Log(QString fileName);

  ~Log();

  /*!
   * \brief Запись строки в лог
   * \param message - строка
   * \param level - уровень вывода
   * \param color - цвет строки
   */
  void printStringToLog(QString message, unsigned level, QColor color = Qt::black);

private:
  QFile m_logFile; //!< Файл с логом программы
  QTextStream m_logStream; //!< Поток для записи лога программы

}; // class Log

#endif // LOG_H
