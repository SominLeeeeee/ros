cmake_minimum_required(VERSION 2.8.3)
project(multiple_topic_pkg)
add_compile_options(-std=c++11)

find_package(catkin REQUIRED)

find_package(catkin REQUIRED COMPONENTS 
  message_generation
  roscpp
)

add_message_files(FILES
  my_topic_two.msg
  my_topic_one.msg
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

add_executable(multiple_pub
  src/multiple_pub.cpp
)

add_dependencies(multiple_pub ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})
target_link_libraries(multiple_pub
  ${catkin_LIBRARIES}
)

add_executable(multiple_sub
  src/multiple_sub.cpp
)

add_dependencies(multiple_sub ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})
target_link_libraries(multiple_sub
  ${catkin_LIBRARIES}
)