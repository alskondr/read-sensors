#include "include/Log.h"

#include <QColor>

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

void Log::printStringToLog(QString message, unsigned level, QColor color = Qt::black)
{
  m_logStream << message;
}
