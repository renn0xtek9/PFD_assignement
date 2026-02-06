#ifndef PRIMARY_FLIGHT_DISPLAY_H
#define PRIMARY_FLIGHT_DISPLAY_H
#include <QColor>
#include <QQuaternion>
#include <QWidget>

struct PrimaryFlightDisplayConfig {
  // Global instrument parameter
  int widget_minimum_height{400};    ///< Minimum width of the PFD
  int widget_minimum_width{400};     ///< Minimum width of the PFD
  double pfd_field_of_view_deg{60};  ///< Field of View of instrument (difference between max and min angle visible);

  QColor outer_circle_color{Qt::black};
  int outer_circle_thickness{5};

  // Aircraft symbolization
  QColor aircraft_symbol_color{Qt::darkGreen};
  int aircraft_symbol_thickness{10};  ///< Thickness of lines symbolizing the aircraft
  int center_dot_diameter{5};         ///< Diameter of center dot symbolizing the aircraft
  int gap_between_wings{20};          ///< Gap between two lines reprensenting the wings
  int wing_length{100};               ///< Lenght of lines representing the wings
  int length_of_gear_leg{10};         ///< Length of lines representing gear

  // Pitch angles graduations
  int graduation_thickness{2};             ///< Thickness of pitch angles graduation lines
  int main_graduation_width{80};           ///< Width of main graduation (10 degree steps)
  int secondary_graduation_width{50};      ///< Width of secondary graduations (5 degree steps)
  int gap_between_text_and_graduation{3};  ///< Space between graduation lines and angles text.
  QColor graduation_color{Qt::white};      ///< Color of graduation

  // Ground and sky display
  QColor sky_color_at_horizon{Qt::blue};                ///< Color of the sky near horizon
  QColor sky_color_at_veritcal{Qt::black};              ///< Color of the sky near vertical
  QColor ground_color_at_horizon{QColor(165, 42, 42)};  ///< Color of the ground near horizon
  QColor ground_color_at_veritcal{QColor(150, 75, 0)};  ///< Color of the ground near vertical

  // Yaw display
  int yaw_indicator_size{15};              ///< Size of the triangle incdicating Yaw
  QColor yaw_indicator_color{Qt::yellow};  ///< Size of the color indicator
};

class PrimaryFlightDisplay : public QWidget {
  Q_OBJECT
 public:
  explicit PrimaryFlightDisplay(QWidget* parent = nullptr,
                                PrimaryFlightDisplayConfig config = PrimaryFlightDisplayConfig{});
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

  QPoint m_center_point{};

  QQuaternion m_quaternion{};

  const PrimaryFlightDisplayConfig m_config{};

  void drawAircraftShape(QPainter& painter);
  void drawOuterCircle(QPainter& painter);
  void drawYawIndicator(QPainter& painter);
  void drawPitchIndictator(QPainter& painter);
  void drawAnglesGraduations(QPainter& painter);

  void drawRectangleWithGradient(QPainter& painter,
                                 const QPoint& top_left,
                                 const QPoint& bottom_right,
                                 const QColor& color_at_horizon,
                                 const QColor& color_at_vertical);

  void applyRoll(QPainter& painter);

  void clipPainterInsideInstrument(QPainter& painter);

  void updateParameters();
};
#endif
