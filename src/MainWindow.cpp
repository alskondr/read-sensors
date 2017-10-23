#include "include/MainWindow.h"
#include "ui_MainWindow.h"

#include <QTextFrame>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->m_projectTreeView->setModel(&m_projectDirModel);
  ui->m_projectTreeView->setColumnHidden(1, true);
  ui->m_projectTreeView->setColumnHidden(2, true);
  ui->m_projectTreeView->setColumnHidden(3, true);
  ui->m_projectTreeView->setColumnHidden(4, true);
  ui->m_projectTreeView->setRootIndex(m_projectDirModel.setRootPath(QDir::currentPath()));

  connect(ui->m_printSensorsButton, SIGNAL(clicked(bool)), this, SLOT(printSensorsLog()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::printSensorsLog()
{
//  // Ищем все датчики в директории с проектом
//  SensorsReader sensorsReader(ui->m_sensorNameLineEdit->text());
//  QList<Sensor> sensorsList = sensorsReader.readSensors(ui->m_projectDirLineEdit->text());
//  sensorsReader.printSensors(sensorsList, "traceSensors.txt");


//  // Фильтруем датчики и выводим их в лог
//  SensorsDecoder sensorsDecoder;
//  sensorsDecoder.readSensors(sensorsList);
//  sensorsDecoder.printSensors(ui->m_sensorsLogLineEdit->text(), ui->m_logSizeLineEdit->text().toInt());

//  QTextFrameFormat format;
//  format.setBackground(Qt::red);
//  ui->m_log->document()->rootFrame()->setFrameFormat(format);
//  ui->m_log->append(QString("Amount all unique sensors = ") + QString::number(sensorsDecoder.getAmountAllUniqueSensors()) + "\n");
//  format.setBackground(Qt::blue);
//  ui->m_log->document()->rootFrame()->setFrameFormat(format);
//  ui->m_log->append(QString("Amount print unique sensors = ") + QString::number(sensorsDecoder.getAmountPrintUniqueSensors()) + "\n");
//  std::cout << "Amount all unique sensors = " << sensorsDecoder.getAmountAllUniqueSensors() << std::endl;
//  std::cout << "Amount print unique sensors = " << sensorsDecoder.getAmountPrintUniqueSensors() << std::endl;

  //  sensorsDecoder.printDebug("traceSensorsVector.txt");

  m_projectDirModel.getCheckedFiles();
}