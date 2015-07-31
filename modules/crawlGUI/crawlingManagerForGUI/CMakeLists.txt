cmake_minimum_required(VERSION 2.8)

set(PROJECTNAME crawlingManagerForGui)
project(${PROJECTNAME})

FIND_PACKAGE(YARP)
FIND_PACKAGE(ICUB)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH ${ICUB_MODULE_PATH})

include(YarpIDL)

include_directories(${ICUB_INCLUDE_DIRS} ${YARP_INCLUDE_DIRS})

#compile definition file to generate source code into the desired directory
set(generated_libs_dir "${CMAKE_CURRENT_SOURCE_DIR}")
yarp_idl_to_dir(demoCrawl.thrift ${generated_libs_dir})

# CMake has compiled the file during the configuration process, so now we can include the generated .cmake file that lists all sources into "headers" and "sources" variables
include(demoCrawl_thrift.cmake)
include_directories(${generated_libs_dir}/include ${YARP_INCLUDE_DIRS})


FILE(GLOB folder_source *.cpp)
FILE(GLOB folder_header *.h)
SOURCE_GROUP("Source Files" FILES ${folder_source})
SOURCE_GROUP("Header Files" FILES ${folder_header})


IF(folder_source)
    ADD_EXECUTABLE(${PROJECTNAME} 
        ${folder_source} ${sources} ${headers}
        ${folder_header}
    )
ELSE (folder_source)
    MESSAGE(FATAL_ERROR "No source code files found. Please add something")
ENDIF (folder_source)

SOURCE_GROUP("Source Files" FILES ${folder_source})

TARGET_LINK_LIBRARIES(${PROJECTNAME} ${YARP_LIBRARIES})
INSTALL(TARGETS ${PROJECTNAME} DESTINATION ${ICUB_DIR}/bin)

