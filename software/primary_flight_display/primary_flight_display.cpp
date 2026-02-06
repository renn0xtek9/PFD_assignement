#include <primary_flight_display/primary_flight_display.h>
#include <qbrush.h>
#include <qglobal.h>
#include <qnamespace.h>
#include <qtransform.h>
#include <qwidget.h>

#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QRect>
#include <vector>
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
  m_pfd_pitch_resolution = static_cast<double>(2 * m_radius) / m_pfd_field_of_view_deg;
  m_left_x = m_center_x - m_radius;
  m_right_x = m_center_x + m_radius;

  drawPitchIndictator(painter);
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

void PrimaryFlightDisplay::clipPainterInsideInstrument(QPainter& painter) {
  QPainterPath clip_path;
  clip_path.addEllipse(QPointF(m_center_x, m_center_y), m_radius, m_radius);
  painter.setClipPath(clip_path);
}
void PrimaryFlightDisplay::drawPitchIndictator(QPainter& painter) {
  painter.save();
  auto pitch_angle_deg = m_quaternion.toEulerAngles().x();
  qDebug() << " Pitch angle  " << pitch_angle_deg;
  const double horizon_height_px{m_center_y + pitch_angle_deg * m_pfd_pitch_resolution};

  clipPainterInsideInstrument(painter);

  QPoint horizontal_line_left(m_left_x, 0);
  QPoint horizontal_line_right(m_right_x, 0);

  QPoint sky_top_left(m_left_x, -180 * m_pfd_pitch_resolution);
  QPoint sky_top_middle(m_right_x - (m_right_x - m_left_x) / 2, sky_top_left.y());
  QPoint ground_bottom_middle(m_right_x - (m_right_x - m_left_x) / 2, 180 * m_pfd_pitch_resolution);
  QPoint ground_bottom_right(horizontal_line_right.x(), ground_bottom_middle.y());

  // Draw sky
  painter.setPen(Qt::NoPen);

  painter.translate(0, static_cast<qreal>(horizon_height_px));

  QLinearGradient sky_gradient(sky_top_middle, QPoint(sky_top_middle.x(), horizontal_line_right.y()));
  sky_gradient.setColorAt(0.0, Qt::blue);
  sky_gradient.setColorAt(0.5, Qt::black);
  sky_gradient.setColorAt(1.0, Qt::blue);
  painter.setBrush(sky_gradient);
  painter.drawRect(QRect(sky_top_left, horizontal_line_right));
  painter.setBrush(Qt::NoBrush);

  // Draw ground
  QLinearGradient ground_gradient(QPoint(ground_bottom_middle.x(), horizontal_line_right.y()), ground_bottom_middle);
  ground_gradient.setColorAt(0.0, QColor(165, 42, 42));
  ground_gradient.setColorAt(0.5, QColor(150, 75, 0));
  ground_gradient.setColorAt(1.0, QColor(165, 42, 42));
  painter.setBrush(ground_gradient);
  painter.drawRect(QRect(horizontal_line_left, ground_bottom_right));
  painter.setBrush(Qt::NoBrush);

  // Draw horizon and graduations
  painter.setPen(QPen(Qt::white, 2));
  painter.drawLine(horizontal_line_left, horizontal_line_right);
  drawAnglesGraduations(painter);

  painter.restore();
}

void PrimaryFlightDisplay::drawAnglesGraduations(QPainter& painter) {
  std::vector<int> graduation_angles_deg{};

  const int angle_max_deg{110};  // purposedly beyond 90 degree to display additional graduation when vertical
  for (int graduation_angle_deg = -angle_max_deg; graduation_angle_deg <= angle_max_deg; graduation_angle_deg += 5) {
    graduation_angles_deg.emplace_back(graduation_angle_deg);
  }

  constexpr int MAIN_GRADUATION_WIDTH{80};
  constexpr int SECONDARY_GRADUATION_WIDTH{50};
  constexpr int MARGIN_GRADUATION_AND_TEXT{3};

  for (const auto& angle : graduation_angles_deg) {
    auto graduation_width = MAIN_GRADUATION_WIDTH;
    if ((angle % 10) != 0) {
      graduation_width = SECONDARY_GRADUATION_WIDTH;
    }

    int graduation_height_px = angle * m_pfd_pitch_resolution;

    QString text = QString::number(-angle);
    QFontMetrics fm(painter.font());
    QRect textRect = fm.boundingRect(text);
    textRect.moveCenter(QPoint(m_center_x, graduation_height_px));
    painter.drawText(textRect, Qt::AlignCenter, text);

    const int graduation_left_px{m_center_x - graduation_width / 2};
    const int graduation_right_px{m_center_x + graduation_width / 2};

    QPoint left_point(graduation_left_px, graduation_height_px);
    QPoint right_point(graduation_right_px, graduation_height_px);
    painter.drawLine(left_point, QPoint(textRect.left() - MARGIN_GRADUATION_AND_TEXT, graduation_height_px));
    painter.drawLine(QPoint(textRect.right() + MARGIN_GRADUATION_AND_TEXT, graduation_height_px), right_point);
  }
}
