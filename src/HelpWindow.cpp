#include <HelpWindow.h>
#include <ui_HelpWindow.h>

#include <QFile>

HelpWindow::HelpWindow(QWidget *parent) :
  QDialog(parent),
  m_ui(new Ui::HelpWindow)
{
  m_ui->setupUi(this);

  QFont font;
  font.setPointSize(9);
  m_ui->m_helpBrowser->setFont(font);

  QFile helpFile(":/help.html");
  if (helpFile.open(QIODevice::ReadOnly))
  {
    QString helpText = helpFile.readAll();
    m_ui->m_helpBrowser->setHtml(helpText);
    helpFile.close();
  }
  else
  {
    m_ui->m_helpBrowser->setText(QString::fromUtf8("Ошибка загрузки файла справки!"));
  }

}

HelpWindow::~HelpWindow()
{
}
