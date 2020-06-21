cmake_minimum_required(VERSION 2.8.3)
project(marker_visualizer)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp 
  message_generation
  marker_visualizer_msgs
)

catkin_package(
  CATKIN_DEPENDS
  message_runtime
  marker_visualizer_msgs
)

include_directories(
  include ${catkin_INCLUDE_DIRS}
)

add_executable(marker_selector
  src/marker_selector.cpp
)

add_dependencies(marker_selector ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})
target_link_libraries(marker_selector
  ${catkin_LIBRARIES}
)

add_executable(marker_publisher
  src/marker_publisher.cpp
)

add_dependencies(marker_publisher ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})
target_link_libraries(marker_publisher
  ${catkin_LIBRARIES}
)
