cmake_minimum_required(VERSION 3.10)
project(CL-Bmp VERSION 4.5.6)
enable_testing()
if(NOT TARGET ${PROJECT_NAME})

option(ae2f_IS_SHARED "Is a shared library or static one." OFF)
set(ae2f_OpenCL_LIB_DIR "C:/Program Files (x86)/Intel/oneAPI/2025.0/lib/OpenCL.lib" CACHE STRING "Where library for OpenCL locates.")
set(ae2f_OpenCL_INCLUDE_DIR "C:/Program Files (x86)/Intel/oneAPI/2025.0/include/sycl/" CACHE STRING "Where headers for OpenCL headers locate.")

add_subdirectory(mod/ae2f/Bmp)
link_libraries(Bmp)

add_subdirectory(mod/ae2fCL/Core)
link_libraries(CL-Core)

ae2fCL_AppendInclude(${PROJECT_SOURCE_DIR}/mod/ae2f/Bmp/include)
ae2fCL_AppendInclude(${PROJECT_SOURCE_DIR}/mod/ae2f/Bmp/mod/ae2f/mov2/include)
ae2fCL_AppendInclude(${PROJECT_SOURCE_DIR}/mod/ae2f/Bmp/mod/ae2f/mov2/mod/ae2f/mov/include)
ae2fCL_AppendInclude(${PROJECT_SOURCE_DIR}/mod/ae2f/Bmp/mod/ae2f/mov2/mod/ae2f/mov/mod/ae2f/Core/include)

# Namespace Package
include(GNUInstallDirs)
add_library(
    ${PROJECT_NAME}
    ${ae2f_PREFIX_LIB}
    "include/ae2fCL/Bmp/Buff.h"
    "include/ae2fCL/Bmp/Dest.h"
    "include/ae2fCL/Bmp/Src.h"
    "include/ae2fCL/Bmp/Programme.h"
    "include/ae2fCL/Bmp/Bmp.h"

    "src/Buff.c"
    "src/Programme.c"
    "src/BmpCL.c"
)

ae2fCL_AddConfProjTarDep(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src)

include_directories(include)
add_subdirectory(test)

# Header
target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ae2f::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

endif()