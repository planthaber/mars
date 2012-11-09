project(cfg_manager)
set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "A small library to read, write, and share software parameter using yaml configuration files.")
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


pkg_check_modules(YAML REQUIRED
	yaml-cpp
)

if(NOT LOCAL_BUILD)
pkg_check_modules(DEPS
	lib_manager
	mars_utils
)
ENDIF()


include_directories(${YAML_INCLUDE_DIRS} ${DEPS_INCLUDE_DIRS}) #Yaml gives the subfolder but mars requires to include the yaml folder by it's own, this also prevents that the compiler takes the /usr/include/yaml.h version which is not compatible to the cpp version
link_directories(${YAML_LIBRARY_DIRS} ${DEPS_LIBRARY_DIRS})
add_definitions(${YAML_CLFAGS_OTHER} ${DEPS_CLFAGS_OTHER} )  #flags excluding the ones with -I

include_directories(
	include
)


set(SOURCES 
	src/CFGManager.cpp
	src/CFGParam.cpp
	src/CFGParamBool.cpp
	src/CFGParamDouble.cpp
	src/CFGParamInt.cpp
	src/CFGParamString.cpp
	src/CFGProperty.cpp
)

set(HEADERS
	include/cfg_manager/CFGClient.h
	include/cfg_manager/CFGDefs.h
	include/cfg_manager/CFGManager.h
	include/cfg_manager/CFGParam.h
	include/cfg_manager/CFGProperty.h
)

set(INTERFACE_HEADERS
	include/cfg_manager/CFGManagerInterface.h
)


add_library(${PROJECT_NAME} SHARED ${SOURCES})
if(LOCAL_BUILD)
    target_link_libraries(${PROJECT_NAME}
    mars_utils
    )
endif()

target_link_libraries(${PROJECT_NAME}
                      ${YAML_LIBRARIES}
                      ${DEPS_LIBRARIES}
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


# Install the library into the lib folder
install(TARGETS ${PROJECT_NAME} ${_INSTALL_DESTINATIONS})

# Install headers into mars include directory
install(FILES ${HEADERS} DESTINATION include/mars/${PROJECT_NAME})
install(FILES ${INTERFACE_HEADERS} DESTINATION include/mars/${PROJECT_NAME})

# Prepare and install necessary files to support finding of the library 
# using pkg-config
configure_file(${PROJECT_NAME}.pc.in ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION lib/pkgconfig)


