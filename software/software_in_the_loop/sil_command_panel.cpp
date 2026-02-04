#include "sil_command_panel.h"

#include <qboxlayout.h>
#include <qnamespace.h>
#include <qwidget.h>

#include <QSlider>
#include <QVBoxLayout>

SilCommandPanel::SilCommandPanel(QWidget* parent) : QWidget(parent) {
  m_roll_angle_slider = initializeAngleSlider(-90, 90);
  m_pitch_angle_slider = initializeAngleSlider(-90, 90);
  m_yaw_angle_slider = initializeAngleSlider(-180, 180);

  initalizeLayout();
}

SilCommandPanel::~SilCommandPanel() {
}

QSlider* SilCommandPanel::initializeAngleSlider(double min, double max) {
  QSlider* result = new QSlider(this);
  result->setMaximum(static_cast<int>(max));
  result->setMinimum(static_cast<int>(min));
  result->setOrientation(Qt::Horizontal);
  return result;
}

void SilCommandPanel::initalizeLayout() {
  this->setFixedWidth(300);
  this->setLayout(new QVBoxLayout());
  this->layout()->addWidget(&m_roll_label);
  this->layout()->addWidget(m_roll_angle_slider);
  this->layout()->addWidget(&m_yaw_label);
  this->layout()->addWidget(m_yaw_angle_slider);
  this->layout()->addWidget(&m_pitch_label);
  this->layout()->addWidget(m_pitch_angle_slider);
}
