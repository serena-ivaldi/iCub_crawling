cmake_minimum_required(VERSION 2.8.9)
set(PROJECTNAME crawling_GUI)
project(crawling_GUI)

FIND_PACKAGE(YARP)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})

include(YarpIDL)


find_package(Qt5 COMPONENTS Core Gui Widgets)
include(YarpUseQt5)


include_directories(${YARP_INCLUDE_DIRS})


#compile definition file to generate source code into the desired directory
set(generated_libs_dir "${CMAKE_CURRENT_SOURCE_DIR}")
yarp_idl_to_dir(demoCrawl.thrift ${generated_libs_dir})

# CMake has compiled the file during the configuration process, so now we can include the generated .cmake file that lists all sources into "headers" and "sources" variables
include(demoCrawl_thrift.cmake)
include_directories(${generated_libs_dir}/include ${YARP_INCLUDE_DIRS})

file(GLOB crawling_GUI_SRCS *.cpp)
file(GLOB crawling_GUI_HDRS *.h)
file(GLOB crawling_GUI_QRC_FILES *.qrc)
file(GLOB crawling_GUI_UI_FILES *.ui)
 
qt5_add_resources(crawling_GUI_QRC_GEN_SRCS ${crawling_GUI_QRC_FILES})
qt5_wrap_ui(crawling_GUI_UI_GEN_SRCS ${crawling_GUI_UI_FILES})

source_group("Source Files" FILES ${crawling_GUI_SRCS})
source_group("Header Files" FILES ${crawling_GUI_HDRS})
source_group("Resources Files" FILES ${crawling_GUI_QRC_FILES})
source_group("UI Files" FILES ${crawling_GUI_UI_FILES})
source_group("Generated Files" FILES ${crawling_GUI_QRC_GEN_SRCS} ${crawling_GUI_UI_GEN_SRCS})


  add_executable(crawling_GUI WIN32 ${crawling_GUI_SRCS}
                                     ${crawling_GUI_HDRS}
                                     ${crawling_GUI_QRC_GEN_SRCS}
                                     ${crawling_GUI_UI_GEN_SRCS}
					${sources} ${headers} )
  
target_link_libraries(crawling_GUI ${YARP_LIBRARIES})

  qt5_use_modules(crawling_GUI Widgets
                               Gui)
  
 if(WIN32)
       target_link_libraries(crawling_GUI Qt5::WinMain)
  endif()

  install(TARGETS crawling_GUI
          #COMPONENT utilities
          DESTINATION ${ICUB_DIR}/bin)

  #set_target_properties(crawling_GUI PROPERTIES OUTPUT_NAME crawling_GUI)

