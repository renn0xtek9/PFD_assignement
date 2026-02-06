#include "mainwindow.h"

#include <qboxlayout.h>
#include <qwidget.h>

#include <QHBoxLayout>
#include <QWidget>

#include "primary_flight_display/primary_flight_display.h"
#include "sil_command_panel.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  this->setWindowTitle("Primary Flight Display validation");
  m_sil_command_panel = new SilCommandPanel(this);

  m_primay_flight_display = new PrimaryFlightDisplay(this);
  connect(m_sil_command_panel, &SilCommandPanel::attitudeChanged, m_primay_flight_display,
          &PrimaryFlightDisplay::updateAttitude);

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
