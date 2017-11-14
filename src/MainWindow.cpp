#include <MainWindow.h>
#include <ui_MainWindow.h>

#include <SensorFinder.h>
#include <ProjectDirModel.h>
#include <ProjectSettings.h>
#include <SensorLogWriter.h>

#include <QTextFrame>
#include <QFileDialog>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::MainWindow),
  m_projectDirModel(new ProjectDirModel),
  m_sensorsFromAllFiles(new SensorFinder),
  m_sensorsFromCheckedFiles(new SensorFinder),
  m_sensorLogWriter(new SensorLogWriter)
{
  m_ui->setupUi(this);

  m_projectSettings = std::shared_ptr<ProjectSettings>(new ProjectSettings(QDir::currentPath() + "/default.conf"));

  m_ui->m_projectTreeView->setModel(m_projectDirModel.get());
  m_ui->m_projectTreeView->setColumnHidden(1, true);
  m_ui->m_projectTreeView->setColumnHidden(2, true);
  m_ui->m_projectTreeView->setColumnHidden(3, true);
  m_ui->m_projectTreeView->setColumnHidden(4, true);

  m_projectSettings->loadSettings();
  printSettingsToForm();

  connect(m_ui->m_printSensorsButton, SIGNAL(clicked(bool)), this, SLOT(printSensorsLog()));
  connect(m_ui->m_projectDirButton, SIGNAL(clicked(bool)), this, SLOT(pushProjectDirButton()));
  connect(m_ui->m_sensorsLogButton, SIGNAL(clicked(bool)), this, SLOT(pushSensorsLogButton()));
  connect(m_ui->m_findSensorsButton, SIGNAL(clicked(bool)), this, SLOT(findSensors()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::printSensorsLog()
{
  // Save settings
  readSettingsFromForm();
  m_projectSettings->saveSettings();

  m_sensorLogWriter->clear();

  // Фильтруем датчики и выводим их в лог
  m_sensorLogWriter->readSensors(m_sensorsFromCheckedFiles->getFindSensorsVector());
  m_sensorLogWriter->printSensors(m_projectSettings->getSensorsLogFileName(), m_projectSettings->getSensorsLogSize());

  m_ui->m_log->append(QString("Amount all unique sensors = ") + QString::number(m_sensorLogWriter->getAmountAllUniqueSensors()) + "\n");
  m_ui->m_log->append(QString("Amount print unique sensors = ") + QString::number(m_sensorLogWriter->getAmountPrintUniqueSensors()) + "\n");
  std::cout << "Amount all unique sensors = " << m_sensorLogWriter->getAmountAllUniqueSensors() << std::endl;
  std::cout << "Amount print unique sensors = " << m_sensorLogWriter->getAmountPrintUniqueSensors() << std::endl;
  m_sensorLogWriter->printDebug("traceSensorsVector.txt");
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

void MainWindow::findSensors()
{
  // Save settings
  readSettingsFromForm();
  m_projectSettings->saveSettings();

  // Set project to ProjectDirModel
  m_ui->m_projectTreeView->setRootIndex(m_projectDirModel->index(m_projectSettings->getProjectDir()));
  m_projectDirModel->setData(m_projectDirModel->index(m_projectSettings->getProjectDir()), Qt::Checked, Qt::CheckStateRole);

  // Find sensors
  // Sensors from all files
  m_sensorsFromAllFiles->clear();
  m_sensorsFromAllFiles->findSensors(m_projectDirModel->getAllFiles(m_projectSettings->getProjectDir()), m_projectSettings->getSensorName());
  m_sensorsFromAllFiles->printSensors(QString::fromUtf8("sensors-from-all-files.txt"));
  // Sensors from checked files
  m_sensorsFromCheckedFiles->clear();
  m_sensorsFromCheckedFiles->findSensors(m_projectDirModel->getCheckedFiles(m_projectSettings->getProjectDir()), m_projectSettings->getSensorName());
  m_sensorsFromCheckedFiles->printSensors(QString::fromUtf8("sensors-from-checked-files.txt"));
}

void MainWindow::printSettingsToForm()
{
  m_ui->m_sensorNameLineEdit->setText(m_projectSettings->getSensorName());
  m_ui->m_projectDirLineEdit->setText(m_projectSettings->getProjectDir());
  m_ui->m_sensorsLogLineEdit->setText(m_projectSettings->getSensorsLogFileName());

  unsigned level = 0;
  double logSize = m_projectSettings->getSensorsLogSize();
  while (logSize >= KILO)
  {
    logSize = logSize / KILO;
    level++;
  }
  m_ui->m_logSizeLineEdit->setText(QString::number(logSize));
  m_ui->m_logSizeComboBox->setCurrentIndex(level);
}

void MainWindow::readSettingsFromForm()
{
  /*!
   * \todo Проверка директории с проектом на существование
   */

  m_projectSettings->setSensorName(m_ui->m_sensorNameLineEdit->text());
  m_projectSettings->setProjectDir(m_ui->m_projectDirLineEdit->text());
  m_projectSettings->setSensorsLogFileName(m_ui->m_sensorsLogLineEdit->text());

  double logSize = m_ui->m_logSizeLineEdit->text().toDouble() * pow(KILO, m_ui->m_logSizeComboBox->currentIndex());
  m_projectSettings->setSensorsLogSize((int)logSize);
}
