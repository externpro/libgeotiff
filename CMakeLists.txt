cmake_minimum_required(VERSION 3.31)
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES .devcontainer/cmake/xproinc.cmake)
project(libgeotiff)
include(GNUInstallDirs)
include(xpflags)
set(tiffHeaders
  tiffio.h
  tiff.h
  tiffvers.h
  tif_config.h
  tiffconf.h
  )
# TRICKY: currently relies on tiff headers from wxWidgets...
find_package(wxwidgets)
get_target_property(wxIncDirs wx::base INTERFACE_INCLUDE_DIRECTORIES)
list(FILTER wxIncDirs INCLUDE REGEX "include/wx-")
list(GET wxIncDirs 0 wxIncDir)
set(wxTiffHeaders ${tiffHeaders})
list(TRANSFORM wxTiffHeaders PREPEND "${wxIncDir}/wx/tiff/")
file(COPY ${wxTiffHeaders} DESTINATION ${CMAKE_BINARY_DIR}/tiff)
list(TRANSFORM tiffHeaders PREPEND "${CMAKE_BINARY_DIR}/tiff/")
add_subdirectory(geotiff/libgeotiff)
