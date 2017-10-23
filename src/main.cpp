#include "include/MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();


//  // Ищем все датчики в директории с проектом
//  SensorsReader sensorsReader("Prob._Prob");
//  QList<Sensor> sensorsList = sensorsReader.readSensors("C:\\Projects\\Work\\triada\\java");
//  sensorsReader.printSensors(sensorsList, "traceSensors.txt");

//  // Фильтруем датчики и выводим их в лог
//  SensorsDecoder sensorsDecoder;
//  sensorsDecoder.readSensors(sensorsList);
//  sensorsDecoder.printSensors("java.log", 1285482167);

//  std::cout << "Amount all unique sensors = " << sensorsDecoder.getAmountAllUniqueSensors() << std::endl;
//  std::cout << "Amount print unique sensors = " << sensorsDecoder.getAmountPrintUniqueSensors() << std::endl;

//  sensorsDecoder.printDebug("traceSensorsVector.txt");

//  return 0;
}
