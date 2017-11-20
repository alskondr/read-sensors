#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QDialog>

#include <memory>

namespace Ui {
  class HelpWindow;
}

class HelpWindow : public QDialog
{
  Q_OBJECT

public:
  explicit HelpWindow(QWidget *parent = 0);
  ~HelpWindow();

private:
  std::unique_ptr<Ui::HelpWindow> m_ui;
};

#endif // HELPWINDOW_H
