#ifndef LOG_H
#define LOG_H

#include <QFile>
#include <QTextEdit>

namespace Log
{
  class LogWriter:
    public QObject
  {
    Q_OBJECT
  public:
    LogWriter();
    ~LogWriter();

    /*!
     * \brief Запись строки в лог
     * \param message - строка
     * \param device - уровень вывода
     * \param color - цвет строки
     */
    Q_SLOT void printStringToLog(const QString& message, unsigned device, const QColor& color = Qt::black);

    /*!
     * \brief Сигнал о записи строки в лог
     * \param message - строка
     * \param level - уровень вывода
     * \param color - цвет строки
     */
    Q_SIGNAL void printLog(const QString& message, unsigned level, const QColor& color = Qt::black);

    void setLogFile(const QString& fileName);
    void setLogWindow(QTextEdit* logWindow);

  private:
    QFile* m_logFile; //!< Файл с логом программы
    QTextEdit* m_logWindow; //!< Виджет для записи лога

  }; // class Log

  //! Описание устройств вывода
  enum LogDevice
  {
    FILE = 0,
    WINDOW = 1,
    ALL_DEVICE = 2
  };

  extern LogWriter g_log; //!< Лог
}

#endif // LOG_H
