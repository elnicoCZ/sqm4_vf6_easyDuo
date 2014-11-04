#include "easyduo.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
  puts("\n -------------");
  puts(" |  EasyDuo  |");
  puts(" -------------");
  puts(" For all features use SQM4-EasyBoard with SQM4-VF6 Vybrid module.");
  puts(" - measures accelerometer data on CM4 core and sends it to CA5 core using MCC");
  puts(" - displays data on LCD");
  puts(" - runs WebGL server with accelerometer data visualization");
  puts(" - plays multimedia (video, image slideshow, camera)");
  puts(" - controls LED using GUI and button\n");
  puts("Welcome to the Vybrid world: Rich Applications in Real Time!");
  puts("More on www.sqm4.com.\n");

  QApplication a(argc, argv);
  EasyDuo w;
  w.showFullScreen();
  return a.exec();
}
