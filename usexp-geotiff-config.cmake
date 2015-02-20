# GEOTIFF_FOUND - geotiff was found
# GEOTIFF_INCLUDE_DIR - the geotiff include directory
# GEOTIFF_LIBRARIES - the geotiff libraries
set(prj geotiff)
# this file (-config) installed to share/cmake (see top-level CMakeLists.txt)
get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(XP_ROOTDIR "${SELF_DIR}/../.." ABSOLUTE)
# targets file (-targets) installed to lib${NUMBITS}/cmake
include(${XP_ROOTDIR}/lib${NUMBITS}/cmake/${prj}-targets.cmake)
string(TOUPPER ${prj} PRJ)
find_path(${PRJ}_INCLUDE_DIR geotiff/geotiff.h PATHS ${XP_ROOTDIR}/include NO_DEFAULT_PATH)
set(${PRJ}_LIBRARIES geotiff)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(${prj}
  REQUIRED_VARS
    ${PRJ}_INCLUDE_DIR
    ${PRJ}_LIBRARIES
  )
mark_as_advanced(${PRJ}_INCLUDE_DIR ${PRJ}_LIBRARIES)
