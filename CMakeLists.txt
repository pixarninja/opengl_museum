cmake_minimum_required(VERSION 3.5)
project(window)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(window ${SOURCE_FILES})
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.1 REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(window_executable ${SOURCE_FILES})

target_link_libraries(window ${OPENGL_LIBRARIES} GLEW::GLEW glfw ${GLFW_LIBRARIES})
target_link_libraries(window glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})
target_include_directories(window_executable PUBLIC ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})


set_target_properties(window_executable PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        )
