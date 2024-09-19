# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\samp1_1_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\samp1_1_autogen.dir\\ParseCache.txt"
  "samp1_1_autogen"
  )
endif()
