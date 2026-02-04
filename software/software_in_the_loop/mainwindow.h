#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <primary_flight_display/primary_flight_display.h>

#include <QHBoxLayout>
#include <QMainWindow>
#include <QWidget>

#include "sil_command_panel.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private:
  QHBoxLayout* m_main_layout;
  PrimaryFlightDisplay* m_primay_flight_display;
  SilCommandPanel* m_sil_command_panel;

  void initalizeLayout();
};
#endif  // MAINWINDOW_H
