#ifndef PRIMARY_FLIGHT_DISPLAY_H
#define PRIMARY_FLIGHT_DISPLAY_H
#include <QWidget>

class PrimaryFlightDisplay : public QWidget {
  Q_OBJECT
 public:
  explicit PrimaryFlightDisplay(QWidget* parent = nullptr);
  ~PrimaryFlightDisplay();

 protected:
  void paintEvent(QPaintEvent* event) override;

  int m_center_x{};
  int m_center_y{};
  int m_radius{};

  QPoint m_center_point{};

  void drawAircraftShape(QPainter& painter);
  void drawOuterCircle(QPainter& painter);
};
#endif
