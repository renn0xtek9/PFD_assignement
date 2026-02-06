#include "sil_command_panel.h"

#include <QQuaternion>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

SilCommandPanel::SilCommandPanel(QWidget* parent) : QWidget(parent) {
  m_roll_angle_slider = initializeAngleSlider(-180, 180);
  m_pitch_angle_slider = initializeAngleSlider(-180, 180);
  m_yaw_angle_slider = initializeAngleSlider(-360, 360);

  initalizeLayout();
  connect(m_pitch_angle_slider, &QSlider::valueChanged, this, &SilCommandPanel::updatePitchAngleLabel);
  connect(m_roll_angle_slider, &QSlider::valueChanged, this, &SilCommandPanel::updateRollAngleLabel);
  connect(m_yaw_angle_slider, &QSlider::valueChanged, this, &SilCommandPanel::updateYawAngleLabel);
  updatePitchAngleLabel();
  updateYawAngleLabel();
  updateRollAngleLabel();
}

SilCommandPanel::~SilCommandPanel() {
}

QSlider* SilCommandPanel::initializeAngleSlider(double min, double max) {
  QSlider* result = new QSlider(this);
  result->setMaximum(static_cast<int>(max));
  result->setMinimum(static_cast<int>(min));
  result->setOrientation(Qt::Horizontal);

  connect(result, &QSlider::valueChanged, this, &SilCommandPanel::computeAndEmitQuaternion);

  return result;
}

void SilCommandPanel::initalizeLayout() {
  this->setFixedWidth(300);
  this->setLayout(new QVBoxLayout());
  this->layout()->addWidget(&m_roll_label);
  this->layout()->addWidget(m_roll_angle_slider);
  this->layout()->addWidget(&m_pitch_label);
  this->layout()->addWidget(m_pitch_angle_slider);
  this->layout()->addWidget(&m_yaw_label);
  this->layout()->addWidget(m_yaw_angle_slider);
}

void SilCommandPanel::computeAndEmitQuaternion() {
  QQuaternion quaternion = QQuaternion::fromEulerAngles(m_pitch_angle_slider->value(), m_yaw_angle_slider->value(),
                                                        m_roll_angle_slider->value());
  emit attitudeChanged(quaternion);
}

void SilCommandPanel::updatePitchAngleLabel() {
  m_pitch_label.setText(QString("Pitch angle: ") + QString::number(m_pitch_angle_slider->value()));
}

void SilCommandPanel::updateYawAngleLabel() {
  m_yaw_label.setText(QString("Yaw angle: ") + QString::number(m_yaw_angle_slider->value()));
}
void SilCommandPanel::updateRollAngleLabel() {
  m_roll_label.setText(QString("Roll angle: ") + QString::number(m_roll_angle_slider->value()));
}
