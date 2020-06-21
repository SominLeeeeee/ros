cmake_minimum_required(VERSION 2.8.3)
project(final_test)

find_package(catkin REQUIRED)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    message_generation
)

add_service_files(
  FILES
  final_srv.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs 
)

include_directories(
  include ${catkin_INCLUDE_DIRS}
)

add_executable(final_server
  src/final_server.cpp
)

add_dependencies(final_server ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(final_server
  ${catkin_LIBRARIES}
)

add_executable(final_client
  src/final_client.cpp
)

add_dependencies(final_client ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(final_client
  ${catkin_LIBRARIES}
)