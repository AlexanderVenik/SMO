#include <QApplication>

#include "include/main_window.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  auto main_window = new MainWindow();

  return QApplication::exec();
}
