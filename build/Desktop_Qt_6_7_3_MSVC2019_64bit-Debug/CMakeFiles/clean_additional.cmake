# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\WeRarelyChat_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\WeRarelyChat_autogen.dir\\ParseCache.txt"
  "WeRarelyChat_autogen"
  )
endif()
