#cmake file for project association #±íÊ¾×¢ÊÍ 
#author:	chenjb
#created:	2014-09-09
PROJECT(Utils)

MESSAGE(STATUS "Project: Utils")
MESSAGE(STATUS "Project Directory: ${Utils_SOURCE_DIR}")

INCLUDE_DIRECTORIES(${poeU5802_SOURCE_DIR}/prebuild/__json-c_install/include/json/)
INCLUDE_DIRECTORIES(${Utils_SOURCE_DIR}/include)

AUX_SOURCE_DIRECTORY(./src DIR_SRCS)
ADD_LIBRARY(Utils_s STATIC ${DIR_SRCS})

SET_TARGET_PROPERTIES(Utils_s PROPERTIES OUTPUT_NAME "Utils")
SET_TARGET_PROPERTIES(Utils_s PROPERTIES ARCHIVE_OUTPUT_DIRECTORY  "${poeU5802_SOURCE_DIR}/__install/lib")


