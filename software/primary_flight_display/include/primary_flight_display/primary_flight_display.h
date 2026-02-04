#ifndef PRIMARY_FLIGHT_DISPLAY_H
#define PRIMARY_FLIGHT_DISPLAY_H
#include <QWidget>

class PrimaryFlightDisplay : public QWidget {
  Q_OBJECT
 public:
  explicit PrimaryFlightDisplay(QWidget* parent = nullptr);
  ~PrimaryFlightDisplay();
};
#endif
