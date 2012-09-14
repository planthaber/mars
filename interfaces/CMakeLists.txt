project(mars_interfaces)
set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "This library is the base library for the MARS prject and includes the general defines, structs and classes.")
cmake_minimum_required(VERSION 2.6)

include(FindPkgConfig)

if(WIN32)
        # this fixes the error 998 from the LibManager
        SET(CMAKE_SHARED_LINKER_FLAGS "-Wl,--enable-auto-import")
        SET(CMAKE_MODULE_LINKER_FLAGS "-Wl,--enable-auto-import")
else(WIN32)
        SET(CMAKE_CXX_FLAGS "-fPIC")
endif(WIN32)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()


if(NOT LOCAL_BUILD)
pkg_check_modules(UTILS REQUIRED "mars_utils")
include_directories(${UTILS_INCLUDE_DIRS})
link_directories(${UTILS_LIBRARY_DIRS})

pkg_check_modules(DATA_BROKER REQUIRED "data_broker")
include_directories(${DATA_BROKER_INCLUDE_DIRS})
link_directories(${DATA_BROKER_LIBRARY_DIRS})
endif()

include_directories(include)


set(HEADERS
    include/interfaces/cameraStruct.h
    include/interfaces/contact_params.h
    include/interfaces/ControllerData.h
    include/interfaces/core_objects_exchange.h
    include/interfaces/GraphicData.h
    include/interfaces/JointData.h
    include/interfaces/LightData.h
    include/interfaces/MARSDefs.h
    include/interfaces/MaterialData.h
    include/interfaces/MotorData.h
    include/interfaces/nodeState.h
    include/interfaces/NodeData.h
    include/interfaces/sensor_bases.h
    include/interfaces/sim_common.h
    include/interfaces/snmesh.h
    include/interfaces/terrainStruct.h
    include/interfaces/utils.h
    include/interfaces/SceneParseException.h
)

set(SOURCES 
    src/interfaces/ControlCenter.cpp
    src/MaterialData.cpp
    src/NodeData.cpp
    src/JointData.cpp
    src/MotorData.cpp
    src/LightData.cpp
    src/GraphicData.cpp
    src/ControllerData.cpp
    src/utils.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(
        ${PROJECT_NAME}
        ${UTILS_LIBRARIES}
        ${DATA_BROKER_LIBRARIES}
)


if(WIN32)
  set(LIB_INSTALL_DIR bin) # .dll are in PATH, like executables
else(WIN32)
  set(LIB_INSTALL_DIR lib)
endif(WIN32)

set(_INSTALL_DESTINATIONS
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION ${LIB_INSTALL_DIR}
	ARCHIVE DESTINATION lib
)

# Install the library
install(TARGETS ${PROJECT_NAME} ${_INSTALL_DESTINATIONS})

# Install headers into mars include directory
install(FILES ${HEADERS} DESTINATION include/mars/interfaces)

#FILE(GLOB files "src/graphics/*.h")
#install(FILES ${files} DESTINATION include/mars/interfaces/graphics)
#FILE(GLOB files "src/sim/*.h")
#install(FILES ${files} DESTINATION include/mars/interfaces/sim)
#FILE(GLOB files "src/gui/*.h")
#install(FILES ${files} DESTINATION include/mars/interfaces/gui)

# Prepare and install necessary files to support finding of the library 
# using pkg-config
configure_file(${PROJECT_NAME}.pc.in ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION lib/pkgconfig)
