cmake_minimum_required(VERSION 3.10)
project(watermarker LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "E:\\opencv")

# require a C++ compiler
# use it for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find includes in the corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# run moc automatically
set(CMAKE_AUTOMOC ON)
# automatically execute on files with *.qrc (resource files)
set(CMAKE_AUTORCC ON) 

# configure Qt
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

# configure OpenCV
find_package(OpenCV REQUIRED)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
)

# your source files
set(src
    src/main.cpp
    src/window_watcher.cpp src/window_watcher.hpp
    src/main_window.cpp src/main_window.hpp
    src/first_window.cpp src/first_window.hpp
    src/second_window.cpp src/second_window.hpp
    src/image_viewer.cpp src/image_viewer.hpp
)

# name of the .exe file, window flag and the list of things to compile
add_executable(${PROJECT_NAME} ${src})

# also tell CMake to link with the libraries from find_package
# otherwise it'll think that you wanted to find those just for fun and won't link them
target_link_libraries(
    ${PROJECT_NAME}
    ${Qt5Core_LIBRARIES} 
    ${Qt5Widgets_LIBRARIES} 
    ${OpenCV_LIBRARIES}
)