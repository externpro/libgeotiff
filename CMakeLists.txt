cmake_minimum_required(VERSION 3.31)
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES .devcontainer/cmake/xproinc.cmake)
project(libgeotiff)
# TRICKY: currently relies on tiff library from wxWidgets (wxtiff)...
find_package(wxwidgets)
add_subdirectory(geotiff/libgeotiff)
