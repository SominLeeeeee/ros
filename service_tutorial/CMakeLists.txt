cmake_minimum_required(VERSION 2.8.3)
project(service_tutorial)

find_package(catkin REQUIRED)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    message_generation
)

add_service_files(
  FILES
  SrvTutorial.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs 
)

include_directories(
  include ${catkin_INCLUDE_DIRS}
)

add_executable(service_server
  src/service_server.cpp
)

add_dependencies(service_server ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(service_server
  ${catkin_LIBRARIES}
)

add_executable(service_client
  src/service_client.cpp
)

add_dependencies(service_client ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(service_client
  ${catkin_LIBRARIES}
)