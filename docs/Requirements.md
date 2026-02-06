# Primary Flight Display

## High level requirments

- [x] The PFD shall display a virtual horizon [See](..software/primary_flight_display/primary_flight_display.cpp#30)
- [x] The virtual horizon shall rotate with the roll angle [See](..software/primary_flight_display/primary_flight_display.cpp#115)
- [x] The virtual horizon shall pitch up or down with the pitch angle [See](..software/primary_flight_display/primary_flight_display.cpp#L117)
- [x] The PFD shall display additinal yaw information [See](../software/primary_flight_display/primary_flight_display.cpp#L84)

## UI requirements

- [x] The PFD shape shall be a circle [See](..software/primary_flight_display/primary_flight_display.cpp#101)
- [x] The horizon shall be reprensented by the separation line between the brown area (ground) and blue (sky) [See](..software/primary_flight_display/primary_flight_display.cpp#132)
- [x] The angle of atittude shall be marked using graduation in a 10 degree steps [See](..software/primary_flight_display/primary_flight_display.cpp#155)
- [x] The graduation of attitude angles shall always be parrallel to the artificial horizon [See](..software/primary_flight_display/primary_flight_display.cpp#115)

### Airfraft shape UI requirements

- [x] The shape of the aircraft shall be symbolize with a an green dot in the the middle of the display and an green line on both side of the dot symbolizing the wings.  [See](..software/primary_flight_display/primary_flight_display.cpp#53)
- The green symbols marking the shape of the aircraft shall not move with respect to the external frame of the artificial horizon [See](..software/primary_flight_display/primary_flight_display.cpp#53)

## Validation

- [x] A simulation tool shall be implemented to simulate aircraft attitude. [See](..software/software_in_the_loop/mainwindow.cpp)
- [x] The simulation tool shall have slider to manually set roll pitch and yaw angle of the aicraft [See](..software/software_in_the_loop/sil_command_panel.cpp#L9)
- [x] The PFD shall update in real time with every changes entered in the simulation tool. [See](..software/primary_flight_display/primary_flight_display.cpp#27)

## Software requirement

- [x] The PFD shall derive the QWidgets class [See](..software/primary_flight_display/include/primary_flight_display/primary_flight_display.h#42)

### Public API

- [x] The PFD shall implement a slot method [See](..software/primary_flight_display/include/primary_flight_display/primary_flight_display.h#25)

```cpp
void updateAttitude(const QQuaternion& quaternion) noexcept
```

- The Simulation tool shall implement this signal method [See](..software/software_in_the_loop/sil_command_panel.cpp#50)

```cpp
void attitudeChanged(QQuaternion quaternion)
```
