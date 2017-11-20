#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

#include <memory>

namespace Ui
{
  class AboutWindow;
}

class AboutWindow:
  public QDialog
{
  Q_OBJECT

public:
  AboutWindow(QWidget *parent = 0);
  ~AboutWindow();

private:
  std::unique_ptr<Ui::AboutWindow> m_ui; // Форма окна
}; // class AboutWindow

#endif // ABOUTWINDOW_H
