#include "Log.h"

#include <QColor>
#include <QDateTime>

namespace Log
{
  LogWriter::LogWriter()
  {
    m_logFile = NULL;
    m_logWindow = NULL;
  }

  LogWriter::~LogWriter()
  {
    if (m_logFile != NULL)
    {
      if (m_logFile->isOpen())
        m_logFile->close();
      delete m_logFile;
    }
  }

  void LogWriter::printStringToLog(const QString& message, unsigned device, const QColor& color)
  {
    QString upgradeMessage = QTime::currentTime().toString() + QString::fromUtf8(" >>> ") + message;

    if (device == FILE || device == ALL_DEVICE)
    {
      if (m_logFile != NULL && m_logFile->isOpen())
        m_logFile->write(upgradeMessage.toUtf8() + "\n");
    }
    if (device == WINDOW || device == ALL_DEVICE)
    {
      if (m_logWindow != NULL)
      {
        m_logWindow->setTextColor(color);
        m_logWindow->append(upgradeMessage);
      }
    }
  }

  void LogWriter::setLogFile(const QString& fileName)
  {
    if (m_logFile != NULL)
    {
      if (m_logFile->isOpen())
        m_logFile->close();
      delete m_logFile;
    }

    m_logFile = new QFile(fileName);
    m_logFile->open(QIODevice::WriteOnly | QIODevice::Text);
  }

  void LogWriter::setLogWindow(QTextEdit* logWindow)
  {
    m_logWindow = logWindow;
    QFont font;
    font.setPointSize(8);
    m_logWindow->setFont(font);
  }

  LogWriter g_log;
}
