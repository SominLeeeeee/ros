cmake_minimum_required(VERSION 2.8.3)
project(tf_mat_example)

find_package(catkin REQUIRED)
find_package(catkin REQUIRED COMPONENTS
    roscpp
)

catkin_package()

include_directories(
    include ${catkin_INCLUDE_DIRS}
)

add_executable(example
    src/example.cpp
)

add_dependencies(example ${${PROJECT_NAME}} ${catkin_EXPORTED_TARGETS})
target_link_libraries(example
    ${catkin_LIBRARIES}
)
