cmake_minimum_required(VERSION 2.6)


function(export_includedir DIR TARGET_DIR)
    execute_process(
        COMMAND cmake -E make_directory ${PROJECT_BINARY_DIR}/include)
    execute_process(
        COMMAND cmake -E make_directory ${PROJECT_BINARY_DIR}/include/mars)
    execute_process(
        COMMAND cmake -E create_symlink ${DIR} ${PROJECT_BINARY_DIR}/include/${TARGET_DIR})
        MESSAGE("${DIR} ---  ${PROJECT_BINARY_DIR}/include/${TARGET_DIR}")
    include_directories(BEFORE ${PROJECT_BINARY_DIR}/include)
endfunction()


SET(LIB_MANAGER_INCLUDE_DIRS ${PROJECT_BINARY_DIR}/include)
SET(CFG_MANAGER_INCLUDE_DIRS ${PROJECT_BINARY_DIR}/include)
SET(LIB_MANAGER_LIBRARIES lib_manager)
SET(INTERFACES_LIBRARIES mars_interfaces)
SET(DATA_BROKER_LIBRARIES data_broker)
SET(CFG_MANAGER_LIBRARIES data_broker)
SET(UTILS_LIBRARIES mars_utils)
SET(MAIN_GUI_LIBRARIES main_gui)
SET(LOCAL_BUILD true)

ADD_DEFINITIONS( -Wfatal-errors )

include(FindPkgConfig)

pkg_check_modules(EIGEN REQUIRED "eigen3")
include_directories(${EIGEN_INCLUDE_DIRS})

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/sim/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/common/utils/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/common/gui/main_gui/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/common/lib_manager/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/common/cfg_manager/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/common/data_broker/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/include/
    #    ${PROJECT_BINARY_DIR}/include/mars
)

#export_includedir(${PROJECT_SOURCE_DIR}/common/lib_manager/src/ mars/lib_manager)
#export_includedir(${PROJECT_SOURCE_DIR}/common/utils/src/ mars/utils)
#export_includedir(${PROJECT_SOURCE_DIR}/common/cfg_manager/src/ mars/cfg_manager)
#export_includedir(${PROJECT_SOURCE_DIR}/common/gui/main_gui/src/ mars/main_gui)
#export_includedir(${PROJECT_SOURCE_DIR}/common/data_broker/src/ mars/data_broker)
#export_includedir(${PROJECT_SOURCE_DIR}/common/gui/main_gui/src/qtpropertybrowser/qtpropertymanager.h mars/main_gui/)


add_subdirectory(common)
add_subdirectory(graphics)
add_subdirectory(scene_loader)
add_subdirectory(interfaces)
add_subdirectory(sim)
add_subdirectory(gui)
add_subdirectory(app)

