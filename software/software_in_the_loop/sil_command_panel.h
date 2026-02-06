#ifndef SIL_COMMAND_PANEL_H
#define SIL_COMMAND_PANEL_H
#include <QLabel>
#include <QQuaternion>
#include <QSlider>
#include <QWidget>
class SilCommandPanel : public QWidget {
  Q_OBJECT
 public:
  explicit SilCommandPanel(QWidget* parent = nullptr);
  ~SilCommandPanel();

 signals:
  void attitudeChanged(QQuaternion quaternion);

 private:
  QSlider* m_roll_angle_slider{};
  QSlider* m_yaw_angle_slider{};
  QSlider* m_pitch_angle_slider{};

  QLabel m_roll_label{};
  QLabel m_yaw_label{};
  QLabel m_pitch_label{};

  QSlider* initializeAngleSlider(double min, double max);

  void initalizeLayout();

 private slots:
  void computeAndEmitQuaternion();
  void updatePitchAngleLabel();
  void updateRollAngleLabel();
  void updateYawAngleLabel();
};

#endif  // SIL_COMMAND_PANEL_H
