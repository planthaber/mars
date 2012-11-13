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
endif()

include_directories(include)
link_directories(${UTILS_LIBRARY_DIRS})
include_directories(${UTILS_INCLUDE_DIRS})


set(HEADERS
    include/interfaces/camera_sensor_config.h   include/interfaces/MaterialData.h
    include/interfaces/cameraStruct.h           include/interfaces/MotorData.h
    include/interfaces/contact_params.h         include/interfaces/NodeData.h
    include/interfaces/ControllerData.h         include/interfaces/nodeState.h
    include/interfaces/core_objects_exchange.h  include/interfaces/sensor_bases.h
    include/interfaces/GraphicData.h            include/interfaces/sim_common.h
    include/interfaces/JointData.h              include/interfaces/snmesh.h
    include/interfaces/jointStruct.h            include/interfaces/terrainStruct.h
    include/interfaces/LightData.h              include/interfaces/utils.h
    include/interfaces/MARSDefs.h
    include/interfaces/exceptions/SceneParseException.h
    include/interfaces/graphics/DrawInterface.h
    include/interfaces/graphics/draw_structs.h
    include/interfaces/graphics/GraphicsCameraInterface.h
    include/interfaces/graphics/GraphicsEventClient.h
    include/interfaces/graphics/GraphicsEventInterface.h
    include/interfaces/graphics/GraphicsGuiInterface.h
    include/interfaces/graphics/GraphicsManagerInterface.h
    include/interfaces/graphics/GraphicsUpdateInterface.h
    include/interfaces/graphics/GraphicsWindowInterface.h
    include/interfaces/graphics/GuiEventInterface.h
    include/interfaces/gui/MarsGuiInterface.h
    include/interfaces/sim/ControlCenter.h
    include/interfaces/sim/ControllerInterface.h
    include/interfaces/sim/ControllerManagerInterface.h
    include/interfaces/sim/EntityManagerInterface.h
    include/interfaces/sim/JointInterface.h
    include/interfaces/sim/JointManagerInterface.h
    include/interfaces/sim/LoadCenter.h
    include/interfaces/sim/LoadSceneInterface.h
    include/interfaces/sim/MarsPluginTemplate.h
    include/interfaces/sim/MotorManagerInterface.h
    include/interfaces/sim/NodeInterface.h
    include/interfaces/sim/NodeManagerInterface.h
    include/interfaces/sim/PhysicsInterface.h
    include/interfaces/sim/PluginInterface.h
    include/interfaces/sim/SensorInterface.h
    include/interfaces/sim/SensorManagerInterface.h
    include/interfaces/sim/SimulatorInterface.h

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
#install(FILES ${HEADERS} DESTINATION include/mars/interfaces)

FILE(GLOB files "include/interfaces/*.h")
install(FILES ${files} DESTINATION include/mars/interfaces)
FILE(GLOB files "include/interfaces/graphics/*.h")
install(FILES ${files} DESTINATION include/mars/interfaces/graphics)
FILE(GLOB files "include/interfaces/sim/*.h")
install(FILES ${files} DESTINATION include/mars/interfaces/sim)
FILE(GLOB files "include/interfaces/gui/*.h")
install(FILES ${files} DESTINATION include/mars/interfaces/gui)

# Prepare and install necessary files to support finding of the library 
# using pkg-config
configure_file(${PROJECT_NAME}.pc.in ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION lib/pkgconfig)
