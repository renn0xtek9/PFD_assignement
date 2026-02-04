# Primary Flight Display

## High level requirments

- The PFD shall display a virtual horizon
- The virtual horizon shall rotate with the roll angle
- The virutal horizon shall pitch up or down with the pitch angle
- The PFD shall display additinal yaw information

## UI requirements

- The PFD shape shall be a circle
- The horizon shall be reprensented by the separation line between the brown area (ground) and blue (sky)
- The angle of atittude shall be marked using graduation in a 10 degree steps
- The graduation of attitude angles shall always be parrallel to the artificial horizon

### Airfraft shape UI requirements

- The shape of the aircraft shall be symbolize with a an orange dot in the the middle of the display and an orange line on both side oft he dot symbolizing the wings.
- The orange symbols marking the shape of the aircraft shall not move with respect to the external frame of the artificial horizon

## Validation

- A simulation tool shall be implemented to simulate aircraft attitude.
- The simulation tool shall have slider to manually set roll pitch and yaw angle of the aicraft
- The PFD shall update in real time with every changes entered in the simulation tool.

## Software requirement

- The PFD shall derive the QWidgets class

### Public API

- The PFD shall implement a slot method

```cpp
void updateAttitude(const QQuaternion& quaternion) noexcept
```

- The Simulation tool shall implement this signal method

```cpp
void attitudeChanged(QQuaternion quaternion)
```
