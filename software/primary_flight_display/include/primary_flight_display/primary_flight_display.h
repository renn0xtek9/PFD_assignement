#ifndef PRIMARY_FLIGHT_DISPLAY_H
#define PRIMARY_FLIGHT_DISPLAY_H
#include <qquaternion.h>

#include <QWidget>

class PrimaryFlightDisplay : public QWidget {
  Q_OBJECT
 public:
  explicit PrimaryFlightDisplay(QWidget* parent = nullptr);
  ~PrimaryFlightDisplay();

 public slots:
  void updateAttitude(const QQuaternion& quaternion) noexcept;

 protected:
  void paintEvent(QPaintEvent* event) override;

  int m_center_x{};
  int m_center_y{};
  int m_radius{};
  int m_left_x{};
  int m_right_x{};
  double m_pfd_pitch_resolution{};

  const double m_pfd_field_of_view_deg{60};  // At 0 degree pitch we visualize from -30 to +30

  QPoint m_center_point{};

  QQuaternion m_quaternion{};

  void drawAircraftShape(QPainter& painter);
  void drawOuterCircle(QPainter& painter);
  void drawYawIndicator(QPainter& painter);
  void drawPitchIndictator(QPainter& painter);
  void drawAnglesGraduations(QPainter& painter);

  void clipPainterInsideInstrument(QPainter& painter);
};
#endif
