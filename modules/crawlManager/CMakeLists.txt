cmake_minimum_required(VERSION 2.8)

set(PROJECTNAME crawlManager)
project(${PROJECTNAME})



FIND_PACKAGE(YARP)
FIND_PACKAGE(ICUB)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH ${ICUB_MODULE_PATH})

include_directories(${ICUB_INCLUDE_DIRS} ${YARP_INCLUDE_DIRS})


FILE(GLOB folder_source *.cpp)
FILE(GLOB folder_header *.h)
SOURCE_GROUP("Source Files" FILES ${folder_source})
SOURCE_GROUP("Header Files" FILES ${folder_header})


IF(folder_source)
    ADD_EXECUTABLE(${PROJECTNAME} 
        ${folder_source} 
        ${folder_header}
    )
ELSE (folder_source)
    MESSAGE(FATAL_ERROR "No source code files found. Please add something")
ENDIF (folder_source)

SOURCE_GROUP("Source Files" FILES ${folder_source})

TARGET_LINK_LIBRARIES(${PROJECTNAME} ${YARP_LIBRARIES})
INSTALL(TARGETS ${PROJECTNAME} DESTINATION ${ICUB_DIR}/bin)

