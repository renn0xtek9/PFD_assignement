# Primary flight display widget

This widget implements a very basic primary flight display in C++ with Qt6
It uses pure C++ API of Qt (i.e. QPainter in a QWidget).
This is chosen so to avoid runtime interpretation like with a QML runner.

**Note** When testing the widget with SIL, remember that there is no flight model behind the instrument itself therefoe some data may appear contraintuitive at first glance i.e.

- roll by 180 deg
- then increase the pitch
- the PFD place the aircraft nose in the sky. This is because these operation are not like "pulling up the stick while flying on the back" in a real aircraft (no flight model involved, the PFD simply display blindly the data coming from a flight computer. The SIL mocks the flight computer output.)

**Note** Cardan locking:
At Cardan lock position (+- 90 degree pitch, roll angles becomes irrelevant therefore the PFD display the aircraft unrolled.)
