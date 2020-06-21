cmake_minimum_required(VERSION 2.8.3)
project(turtlesim_pose_viewer)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  rospy
  roscpp
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS
)

include_directories(
  include ${catkin_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

add_executable(turtlesim_pose_viewer
  src/turtlesim_pose_viewer.cpp
)
add_dependencies(turtlesim_pose_viewer ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS})
target_link_libraries(turtlesim_pose_viewer
  ${catkin_LIBRARIES}
)