cmake_minimum_required(VERSION 4.3)
project(libgeotiff)
# TRICKY: currently relies on tiff library from wxWidgets (wxtiff)...
find_package(wxWidgets)
add_subdirectory(geotiff/libgeotiff)
