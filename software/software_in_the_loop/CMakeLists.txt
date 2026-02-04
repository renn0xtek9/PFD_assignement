add_executable (software_in_the_loop main.cpp)

find_package (Qt6 REQUIRED COMPONENTS Widgets)
target_link_libraries (software_in_the_loop PRIVATE Qt6::Widgets)
target_sources (
  software_in_the_loop
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sil_command_panel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sil_command_panel.cpp)
