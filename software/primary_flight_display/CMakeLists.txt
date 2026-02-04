add_library (primary_flight_display primary_flight_display.cpp)

find_package (Qt6 REQUIRED COMPONENTS Widgets)
target_link_libraries (primary_flight_display PRIVATE Qt6::Widgets Qt6::Gui)
target_sources (
  primary_flight_display
  PUBLIC
    FILE_SET
    headers
    TYPE
    HEADERS
    BASE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES
    include/primary_flight_display/primary_flight_display.h)
