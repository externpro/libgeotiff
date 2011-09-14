set(lib_name geotiff)
#######################################
# preprocessor
if(MSVC)
  add_definitions(
    -D_CRT_NONSTDC_NO_DEPRECATE
    -D_CRT_SECURE_NO_WARNINGS
    )
endif()
#######################################
# include directories
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/libxtiff
  ${CMAKE_CURRENT_SOURCE_DIR}/../../sdlExtern/include/wx/tiff
  )
#######################################
# library sources
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
# library
add_library(${lib_name} STATIC ${${lib_name}_libsrcs})
