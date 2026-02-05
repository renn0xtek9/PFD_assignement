#include <primary_flight_display/primary_flight_display.h>
#include <qbrush.h>
#include <qglobal.h>
#include <qnamespace.h>
#include <qtransform.h>
#include <qwidget.h>

#include <QDebug>
#include <QPainter>
#include <QPainterPath>

namespace {
int toSixteenthOfDegree(int degree) {
  return 16 * degree;
}

}  // namespace
PrimaryFlightDisplay::PrimaryFlightDisplay(QWidget* parent) : QWidget(parent) {
  this->setMinimumHeight(400);
  this->setMinimumWidth(400);
}
PrimaryFlightDisplay::~PrimaryFlightDisplay() {
}

void PrimaryFlightDisplay::updateAttitude(const QQuaternion& quaternion) noexcept {
  m_quaternion = quaternion;
  update();
}

void PrimaryFlightDisplay::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);
  QPainter painter(this);
  m_radius = qMin(width(), height()) / 2;
  m_center_x = width() / 2;
  m_center_y = height() / 2;
  m_center_point.setX(m_center_x);
  m_center_point.setY(m_center_y);

  drawAircraftShape(painter);
  drawOuterCircle(painter);
  drawYawIndicator(painter);
}

void PrimaryFlightDisplay::drawAircraftShape(QPainter& painter) {
  constexpr int CENTER_DOT_DIAMETER{5};
  constexpr int GAP_BETWEEN_WINGS{20};
  constexpr int WING_LENGTH{100};
  constexpr int LENGTH_OF_GEAR_LEG{10};

  painter.setBrush(QBrush(Qt::darkGreen));
  painter.drawEllipse(m_center_point, CENTER_DOT_DIAMETER, CENTER_DOT_DIAMETER);

  painter.setBrush(Qt::NoBrush);
  painter.setPen(QPen(Qt::darkGreen, 10));

  // Left wing
  QPoint exterior_point_wing_left(qMax(0, m_center_x - GAP_BETWEEN_WINGS - WING_LENGTH), m_center_y);
  QPoint interior_point_wing_left(qMax(0, m_center_x - GAP_BETWEEN_WINGS), m_center_y);
  QPoint lower_gear_leg_left(interior_point_wing_left.x(), m_center_point.y() + LENGTH_OF_GEAR_LEG);
  painter.drawLine(exterior_point_wing_left, interior_point_wing_left);
  painter.drawLine(interior_point_wing_left, lower_gear_leg_left);

  // right wing
  QPoint interior_point_wing_right(qMin(m_center_x + m_radius, m_center_x + GAP_BETWEEN_WINGS), m_center_y);
  QPoint exterior_point_wing_right(qMin(m_center_x + GAP_BETWEEN_WINGS + WING_LENGTH, m_center_x + m_radius),
                                   m_center_y);
  QPoint lower_gear_leg_right(interior_point_wing_right.x(), lower_gear_leg_left.y());
  painter.drawLine(interior_point_wing_right, exterior_point_wing_right);
  painter.drawLine(interior_point_wing_right, lower_gear_leg_right);
}

void PrimaryFlightDisplay::drawOuterCircle(QPainter& painter) {
  QPainterPath outer_circle_path;
  outer_circle_path.addEllipse(m_center_point, m_radius, m_radius);
  painter.setBrush(Qt::NoBrush);
  painter.setPen(QPen(Qt::black, 5));
  painter.drawPath(outer_circle_path);
}

void PrimaryFlightDisplay::drawYawIndicator(QPainter& painter) {
  painter.save();
  auto top_point_y{m_center_y};
  QPoint top_of_triangle(0, top_point_y);
  QPoint bottom_left_triangle(-15, top_point_y - 15);
  QPoint bottom_right_triangle(+15, top_point_y - 15);

  auto yaw_angle = m_quaternion.toEulerAngles().y();
  painter.translate(m_center_point);
  painter.rotate(static_cast<qreal>(yaw_angle));
  painter.drawPolygon(QPolygon({top_of_triangle, bottom_left_triangle, bottom_right_triangle}));

  painter.restore();
}
