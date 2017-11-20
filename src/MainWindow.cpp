#include <MainWindow.h>
#include <ui_MainWindow.h>

#include <SensorFinder.h>
#include <ProjectDirModel.h>
#include <ProjectSettings.h>
#include <SensorLogWriter.h>
#include <Log.h>
#include <AboutWindow.h>
#include <HelpWindow.h>

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

  // Отображение файлов проекта
  m_ui->m_projectTreeView->setModel(m_projectDirModel.get());
  m_ui->m_projectTreeView->setColumnHidden(1, true);
  m_ui->m_projectTreeView->setColumnHidden(2, true);
  m_ui->m_projectTreeView->setColumnHidden(3, true);
  m_ui->m_projectTreeView->setColumnHidden(4, true);

  // конфигурационный файл
  m_projectSettings = std::shared_ptr<ProjectSettings>(new ProjectSettings(QDir::currentPath() + "/default.conf"));
  m_projectSettings->loadSettings();

  // Лог
  Log::g_log.setLogFile(m_projectSettings->getProgrammLogFileName());
  Log::g_log.setLogWindow(m_ui->m_log);

  // Окно "О программе"
  m_aboutWindow = std::shared_ptr<AboutWindow>(new AboutWindow(this));

  // Окно "Справка"
  m_helpWindow = std::shared_ptr<HelpWindow>(new HelpWindow(this));

  connect(m_ui->m_printSensorsButton, SIGNAL(clicked(bool)), this, SLOT(printSensorsLog()));
  connect(m_ui->m_projectDirButton, SIGNAL(clicked(bool)), this, SLOT(pushProjectDirButton()));
  connect(m_ui->m_sensorsLogButton, SIGNAL(clicked(bool)), this, SLOT(pushSensorsLogButton()));
  connect(m_ui->m_findSensorsButton, SIGNAL(clicked(bool)), this, SLOT(findSensors()));

  connect(m_ui->m_exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
  connect(m_ui->m_aboutAction, SIGNAL(triggered(bool)), this, SLOT(showAboutWindow()));
  connect(m_ui->m_helpAction, SIGNAL(triggered(bool)), this, SLOT(showHelpWindow()));
  connect(m_ui->m_openAction, SIGNAL(triggered(bool)), this, SLOT(openSettings()));
  connect(m_ui->m_saveAction, SIGNAL(triggered(bool)), this, SLOT(saveSettings()));

  Log::g_log.printStringToLog(QString::fromUtf8("\"Программа по работе с датчиками в проекте\" запущена..."), Log::ALL_DEVICE);
  printSettingsToForm();
}

MainWindow::~MainWindow()
{
}

void MainWindow::printSensorsLog()
{
  Log::g_log.printStringToLog(QString::fromUtf8("Формирование лога датчиков: ") + m_projectSettings->getSensorsLogFileName(), Log::ALL_DEVICE, Qt::blue);
  m_ui->m_statusBar->showMessage(QString::fromUtf8("Формирование лога датчиков..."));

  // Save settings
  readSettingsFromForm();
  m_projectSettings->saveSettings();
  Log::g_log.printStringToLog(QString::fromUtf8("Настроеки проекта сохранены: ") + m_projectSettings->getSettingsFileName(), Log::ALL_DEVICE);

  m_sensorLogWriter->clear();

  // Фильтруем датчики и выводим их в лог
  m_sensorLogWriter->readSensors(m_sensorsFromCheckedFiles->getFindSensorsVector());
  Log::g_log.printStringToLog(QString::fromUtf8("Количество всех уникальных датчиков в проекте: ") + QString::number(m_sensorLogWriter->getAmountAllUniqueSensors()), Log::ALL_DEVICE, Qt::green);
  if (m_sensorLogWriter->printSensors(m_projectSettings->getSensorsLogFileName(), m_projectSettings->getSensorsLogSize()))
  {
    Log::g_log.printStringToLog(QString::fromUtf8("Количество уникальных датчиков, записанных в лог: ") + QString::number(m_sensorLogWriter->getAmountPrintUniqueSensors()), Log::ALL_DEVICE);
    m_sensorLogWriter->printDebug(m_projectSettings->getTraceSensorLogWriter());
  }
  else
  {
    Log::g_log.printStringToLog(QString::fromUtf8("Ошибка записи лога датчиков!!!"), Log::ALL_DEVICE, Qt::red);
  }

  m_ui->m_statusBar->showMessage(QString::fromUtf8(""));
}

void MainWindow::pushProjectDirButton()
{
  QString projectDirPath = QFileDialog::getExistingDirectory(this, "Выберите директорию с проектом...", QDir::homePath());
  if (!projectDirPath.isEmpty())
  {
    m_ui->m_projectDirLineEdit->setText(projectDirPath);
  }
}

void MainWindow::pushSensorsLogButton()
{
  QString sensorsLogPath = QFileDialog::getOpenFileName(this, "Выбирете файл лога с сенсорами...");
  if (!sensorsLogPath.isEmpty())
  {
    m_ui->m_sensorsLogLineEdit->setText(sensorsLogPath);
  }
}

void MainWindow::findSensors()
{
  Log::g_log.printStringToLog(QString::fromUtf8("Поиск датчиков в проекте: ") + m_projectSettings->getProjectDir(), Log::ALL_DEVICE, Qt::blue);
  m_ui->m_statusBar->showMessage(QString::fromUtf8("Поиск датчиков..."));

  // Save settings
  readSettingsFromForm();
  m_projectSettings->saveSettings();
  Log::g_log.printStringToLog(QString::fromUtf8("Настроеки проекта сохранены: ") + m_projectSettings->getSettingsFileName(), Log::ALL_DEVICE);

  // Set project to ProjectDirModel
  Log::g_log.printStringToLog(QString::fromUtf8("Загрузка проекта: ") + m_projectSettings->getProjectDir(), Log::ALL_DEVICE);
  m_ui->m_projectTreeView->setRootIndex(m_projectDirModel->index(m_projectSettings->getProjectDir()));

  // Find sensors
  // Sensors from all files
  Log::g_log.printStringToLog(QString::fromUtf8("Поиск датчиков во всех файлах проекта..."), Log::ALL_DEVICE);
  m_sensorsFromAllFiles->clear();
  m_sensorsFromAllFiles->findSensors(m_projectDirModel->getAllFiles(m_projectSettings->getProjectDir()), m_projectSettings->getSensorName());
  m_sensorsFromAllFiles->printSensors(m_projectSettings->getSensorsFromAllFilesFileName());
  Log::g_log.printStringToLog(QString::fromUtf8("Найдено датчиков: ") + QString::number(m_sensorsFromAllFiles->getSensorsCount()), Log::ALL_DEVICE, Qt::green);
  // Sensors from checked files
  Log::g_log.printStringToLog(QString::fromUtf8("Поиск датчиков в отмеченных файлах проекта..."), Log::ALL_DEVICE);
  m_sensorsFromCheckedFiles->clear();
  m_sensorsFromCheckedFiles->findSensors(m_projectDirModel->getCheckedFiles(m_projectSettings->getProjectDir()), m_projectSettings->getSensorName());
  m_sensorsFromCheckedFiles->printSensors(m_projectSettings->getSensorsFromCheckedFilesFileName());
  Log::g_log.printStringToLog(QString::fromUtf8("Найдено датчиков: ") + QString::number(m_sensorsFromCheckedFiles->getSensorsCount()), Log::ALL_DEVICE, Qt::green);

  m_ui->m_statusBar->showMessage(QString::fromUtf8(""));
}

void MainWindow::showAboutWindow()
{
  m_aboutWindow->show();
}

void MainWindow::showHelpWindow()
{
  m_helpWindow->show();
}

void MainWindow::openSettings()
{
  QString settingsFileName = QFileDialog::getOpenFileName(this, "Выбирете файл c настройками...", m_projectSettings->getSettingsFileName(), QString::fromUtf8("Настройки проекта (*.conf);;Все файлы (*)"));
  if (!settingsFileName.isEmpty())
  {
    m_projectSettings.reset();
    m_projectSettings = std::shared_ptr<ProjectSettings>(new ProjectSettings(settingsFileName));
    m_projectSettings->loadSettings();
    printSettingsToForm();
  }
}

void MainWindow::saveSettings()
{
  QString settingsFileName = QFileDialog::getSaveFileName(this, "Выбирете файл для сохранения настроек...", m_projectSettings->getSettingsFileName(), QString::fromUtf8("Настройки проекта (*.conf);;Все файлы (*)"));
  if (!settingsFileName.isEmpty())
  {
    m_projectSettings.reset();
    m_projectSettings = std::shared_ptr<ProjectSettings>(new ProjectSettings(settingsFileName));
    readSettingsFromForm();
    m_projectSettings->saveSettings();
    Log::g_log.printStringToLog(QString::fromUtf8("Настроеки проекта сохранены: ") + m_projectSettings->getSettingsFileName(), Log::ALL_DEVICE);
  }
}

void MainWindow::printSettingsToForm()
{
  Log::g_log.printStringToLog(QString::fromUtf8("Загрузка настроек: ") + m_projectSettings->getSettingsFileName(), Log::ALL_DEVICE);

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

  Log::g_log.printStringToLog(QString::fromUtf8("Загрузка проекта: ") + m_projectSettings->getProjectDir(), Log::ALL_DEVICE);
  m_ui->m_projectTreeView->setRootIndex(m_projectDirModel->index(m_projectSettings->getProjectDir()));
  m_projectDirModel->setCheckedFiles(m_projectSettings->getCheckedFiles());
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
  m_projectSettings->setCheckedFiles(m_projectDirModel->getCheckedFiles(m_projectSettings->getProjectDir()));
}
