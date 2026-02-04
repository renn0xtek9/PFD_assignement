#include "mainwindow.h"

#include <qboxlayout.h>
#include <qwidget.h>

#include <QHBoxLayout>
#include <QWidget>

#include "sil_command_panel.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  m_sil_command_panel = new SilCommandPanel(this);
  m_primay_flight_display = new QWidget(this);

  this->setWindowTitle("Primary Flight Display validation");

  initalizeLayout();
}

MainWindow::~MainWindow() {
}

void MainWindow::initalizeLayout() {
  QWidget* centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);
  QHBoxLayout* layout = new QHBoxLayout(centralWidget);
  layout->addWidget(m_primay_flight_display);
  layout->addWidget(m_sil_command_panel);
}
