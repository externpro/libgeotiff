# This script modifies TIFF header files in the build directory
# to replace '#ifdef __APPLE__'
# with '#if defined(__unix__) || defined(__APPLE__)'
foreach(hdr
  "${CMAKE_BINARY_DIR}/tiff/tiff.h"
  "${CMAKE_BINARY_DIR}/tiff/tif_config.h"
  )
  if(EXISTS ${hdr})
    file(READ ${hdr} hdrContent)
    string(REPLACE
      "#ifdef __APPLE__"
      "#if defined(__unix__) || defined(__APPLE__)"
      MODIFIED_CONTENT
      "${hdrContent}"
    )
    file(WRITE ${hdr} "${MODIFIED_CONTENT}")
  endif()
endforeach()
