# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "08_OtherControl_autogen"
  "CMakeFiles\\08_OtherControl_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\08_OtherControl_autogen.dir\\ParseCache.txt"
  )
endif()
