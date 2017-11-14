#include "Log.h"

#include <QColor>
#include <QDateTime>

Log::Log(const QString& fileName):
  m_logFile(fileName)
{
  m_logFile.open(QIODevice::WriteOnly | QIODevice::Text);
  m_logStream.setDevice(&m_logFile);
}

Log::~Log()
{
  m_logFile.close();
}

void Log::printStringToLog(const QString& message, unsigned level, const QColor& color = Qt::black)
{
  QString upgradeMessage = QDateTime::currentDateTime().toString() + message;
  m_logStream << upgradeMessage;

  Q_EMIT printLog(upgradeMessage, level, color);
}
