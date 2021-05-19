cmake_minimum_required(VERSION 3.10)
project(watermarker LANGUAGES CXX)

list(APPEND CMAKE_PREFIX_PATH "E:/opt/opencv")
list(APPEND CMAKE_PREFIX_PATH "E:/opt/Qt/5.15.0/mingw81_64/lib/cmake")
list(APPEND CMAKE_PREFIX_PATH "E:/opt/vcpkg/packages/fmt_x86-mingw-static/share/fmt")

# require a C++ compiler
# use it for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

# find includes in the corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# configure Qt
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)
set(CMAKE_AUTOMOC ON) # run moc automatically
set(CMAKE_AUTORCC ON) # automatically execute on files with *.qrc (resource files)

# configure OpenCV
find_package(OpenCV REQUIRED)

# configure {fmt}
find_package(fmt CONFIG REQUIRED)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
   ${Qt5Widgets_INCLUDE_DIRS}
   ${Qt5Core_INCLUDE_DIRS}
   ${OpenCV_INCLUDE_DIRS}
)

# external libraries 
set(lib
   lib/logger/logger.cpp lib/logger/logger.hpp
)

# source files
set(src
   src/main.cpp
   src/window_watcher.cpp src/window_watcher.hpp
   src/main_window.cpp src/main_window.hpp
   src/first_window.cpp src/first_window.hpp
   src/second_window.cpp src/second_window.hpp
   src/image_viewer.cpp src/image_viewer.hpp
   src/wm_widget.cpp src/wm_widget.hpp
   ${lib}
)

# name of the .exe file, window flag and the list of things to compile
add_executable(${PROJECT_NAME} ${src}) # add WIN32 between project name and src to disable console

# also tell CMake to link with the libraries from find_package
# otherwise it'll think that you wanted to find those just for fun and won't link them
target_link_libraries(
   ${PROJECT_NAME}
   ${Qt5Core_LIBRARIES} 
   ${Qt5Widgets_LIBRARIES} 
   ${OpenCV_LIBRARIES}
   fmt::fmt
)