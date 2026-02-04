#ifndef SIL_COMMAND_PANEL_H
#define SIL_COMMAND_PANEL_H
#include <QLabel>
#include <QSlider>
#include <QWidget>
class SilCommandPanel : public QWidget {
  Q_OBJECT
 public:
  explicit SilCommandPanel(QWidget* parent = nullptr);
  ~SilCommandPanel();

 private:
  QSlider* m_roll_angle_slider{};
  QSlider* m_yaw_angle_slider{};
  QSlider* m_pitch_angle_slider{};

  QLabel m_roll_label{"Roll angle"};
  QLabel m_yaw_label{"Yaw angle"};
  QLabel m_pitch_label{"Pitch angle"};

  QSlider* initializeAngleSlider(double min, double max);

  void initalizeLayout();
};

#endif  // SIL_COMMAND_PANEL_H
