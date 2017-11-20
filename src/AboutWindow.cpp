#include <AboutWindow.h>
#include <ui_AboutWindow.h>

AboutWindow::AboutWindow(QWidget *parent) :
  QDialog(parent),
  m_ui(new Ui::AboutWindow)
{
  m_ui->setupUi(this);

  // PROJECT_VERSION определяется в read-sensors.pro
  QString about = QString::fromUtf8("Программа по работе с датчиками в проекте\n") +
                 QString::fromUtf8("Версия ") + QString::number(PROJECT_VERSION);


  QString author = QString::fromUtf8("© Кондратьев Александр") + QString::fromUtf8("\n") +
                   QString::fromUtf8("alskondr@yandex.ru");

  m_ui->m_aboutLabel->setText(about);
  m_ui->m_authorLabel->setText(author);
}

AboutWindow::~AboutWindow()
{
}
