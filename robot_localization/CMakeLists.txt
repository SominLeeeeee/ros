cmake_minimum_required(VERSION 2.8.3)
project(robot_localization)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp 
  message_generation
)
add_message_files(FILES
  pose_msg.msg
)

generate_messages(DEPENDENCIES
  std_msgs
)
catkin_package(
  CATKIN_DEPENDS
  message_runtime
)

include_directories(
  include ${catkin_INCLUDE_DIRS}
)

add_executable(robot_marker
  src/robot_marker.cpp
)

add_dependencies(robot_marker ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})
target_link_libraries(robot_marker
  ${catkin_LIBRARIES}
)

add_executable(robot_pose
  src/robot_pose.cpp
)

add_dependencies(robot_pose ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})
target_link_libraries(robot_pose
  ${catkin_LIBRARIES}
)
