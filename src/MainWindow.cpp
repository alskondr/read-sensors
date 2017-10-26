#include "include/MainWindow.h"
#include "ui_MainWindow.h"

#include <QTextFrame>
#include <QFileDialog>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);

  m_ui->m_projectTreeView->setModel(&m_projectModel.getProjectDirModel());
  m_ui->m_projectTreeView->setColumnHidden(1, true);
  m_ui->m_projectTreeView->setColumnHidden(2, true);
  m_ui->m_projectTreeView->setColumnHidden(3, true);
  m_ui->m_projectTreeView->setColumnHidden(4, true);
  m_ui->m_projectTreeView->setRootIndex(m_projectModel.getProjectDirModel().index(QDir::homePath()));
  m_projectModel.getProjectDirModel().setData(m_projectModel.getProjectDirModel().index(QDir::homePath()), Qt::Checked, Qt::CheckStateRole);

  connect(m_ui->m_printSensorsButton, SIGNAL(clicked(bool)), this, SLOT(printSensorsLog()));
  connect(m_ui->m_projectDirButton, SIGNAL(clicked(bool)), this, SLOT(pushProjectDirButton()));
  connect(m_ui->m_sensorsLogButton, SIGNAL(clicked(bool)), this, SLOT(pushSensorsLogButton()));
}

MainWindow::~MainWindow()
{
  delete m_ui;
}

void MainWindow::printSensorsLog()
{
//  // Ищем все датчики в директории с проектом
//  SensorsReader sensorsReader(m_ui->m_sensorNameLineEdit->text());
//  QList<Sensor> sensorsList = sensorsReader.readSensors(m_ui->m_projectDirLineEdit->text());
//  sensorsReader.printSensors(sensorsList, "traceSensors.txt");


//  // Фильтруем датчики и выводим их в лог
//  SensorsDecoder sensorsDecoder;
//  sensorsDecoder.readSensors(sensorsList);
//  sensorsDecoder.printSensors(m_ui->m_sensorsLogLineEdit->text(), m_ui->m_logSizeLineEdit->text().toInt());

//  QTextFrameFormat format;
//  format.setBackground(Qt::red);
//  m_ui->m_log->document()->rootFrame()->setFrameFormat(format);
//  m_ui->m_log->append(QString("Amount all unique sensors = ") + QString::number(sensorsDecoder.getAmountAllUniqueSensors()) + "\n");
//  format.setBackground(Qt::blue);
//  m_ui->m_log->document()->rootFrame()->setFrameFormat(format);
//  m_ui->m_log->append(QString("Amount print unique sensors = ") + QString::number(sensorsDecoder.getAmountPrintUniqueSensors()) + "\n");
//  std::cout << "Amount all unique sensors = " << sensorsDecoder.getAmountAllUniqueSensors() << std::endl;
//  std::cout << "Amount print unique sensors = " << sensorsDecoder.getAmountPrintUniqueSensors() << std::endl;

  //  sensorsDecoder.printDebug("traceSensorsVector.txt");

  m_projectModel.getProjectDirModel().getCheckedFiles();
}

void MainWindow::pushProjectDirButton()
{
  QString projectDirPath = QFileDialog::getExistingDirectory(0, "Выберите директорию с проектом...", QDir::homePath());
  if (!projectDirPath.isEmpty())
  {
    m_ui->m_projectDirLineEdit->setText(projectDirPath);
  }
}

void MainWindow::pushSensorsLogButton()
{
  QString sensorsLogPath = QFileDialog::getOpenFileName(0, "Выбирете файл лога с сенсорами...");
  if (!sensorsLogPath.isEmpty())
  {
    m_ui->m_sensorsLogLineEdit->setText(sensorsLogPath);
  }
}
