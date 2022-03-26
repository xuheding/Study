# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "04_QtPaintDevice_autogen"
  "CMakeFiles\\04_QtPaintDevice_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\04_QtPaintDevice_autogen.dir\\ParseCache.txt"
  )
endif()
