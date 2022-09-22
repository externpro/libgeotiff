cmake_minimum_required(VERSION 3.12)
project(geotiff)
include(GNUInstallDirs)
include(flags OPTIONAL)
set(lib_name ${PROJECT_NAME})
#######################################
set(${lib_name}_libsrcs
  defs.h
  geo_config.h
  geo_keyp.h
  geokeys.h
  geonames.h
  geotiff.h
  geotiffio.h
  geovalues.h
  cpl_csv.c
  cpl_serv.c
  cpl_serv.h
  geo_extra.c
  geo_free.c
  geo_get.c
  geo_names.c
  geo_new.c
  geo_normalize.c
  geo_normalize.h
  geo_print.c
  geo_set.c
  geo_tiffp.c
  geo_tiffp.h
  geo_trans.c
  geo_write.c
  geotiff_proj4.c
  libxtiff/xtiff.c
  libxtiff/xtiffio.h
  )
#######################################
foreach(TYPE MAJOR MINOR POINT)
  set(verString "^VERSION_${TYPE}=+([0-9]+)?")
  set(verFile configure.in)
  file(STRINGS ${verFile} verNum REGEX "${verString}")
  string(REGEX REPLACE "${verString}" "\\1" ver${TYPE} ${verNum})
endforeach()
set(GTIF_VER ${verMAJOR}.${verMINOR}.${verPOINT})
#######################################
add_library(${lib_name} STATIC ${${lib_name}_libsrcs})
if(MSVC)
  target_compile_definitions(${lib_name} PRIVATE
    -D_CRT_NONSTDC_NO_DEPRECATE
    -D_CRT_SECURE_NO_WARNINGS
    )
endif()
string(REPLACE "${CMAKE_INSTALL_PREFIX}/" "" wxtiff ${WX_INCLUDE}/wx/tiff)
target_include_directories(${lib_name} PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${wxtiff}>
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/libxtiff
  # TRICKY: currently relies on tiff headers from wxWidgets...
  ${WX_INCLUDE}/wx/tiff # pass in with -DWX_INCLUDE
  )
#######################################
set(targetsFile ${PROJECT_NAME}-targets)
install(TARGETS ${lib_name} EXPORT ${targetsFile}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
file(GLOB hdrs ${CMAKE_SOURCE_DIR}/*.h)
file(GLOB incs ${CMAKE_SOURCE_DIR}/*.inc)
install(FILES ${hdrs} ${incs} ${CMAKE_SOURCE_DIR}/libxtiff/xtiffio.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
  )
if(DEFINED XP_NAMESPACE)
  set(nameSpace NAMESPACE ${XP_NAMESPACE}::)
endif()
if(NOT DEFINED XP_INSTALL_CMAKEDIR)
  set(XP_INSTALL_CMAKEDIR ${CMAKE_INSTALL_DATADIR}/cmake)
endif()
install(EXPORT ${targetsFile} DESTINATION ${XP_INSTALL_CMAKEDIR} ${nameSpace})
