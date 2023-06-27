find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
message(STATUS "[${PROJECT_NAME}] QT_VERSION: ${QT_VERSION}; QT_DIR: ${QT_DIR}")

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/config.h")

add_executable(${PROJECT_NAME})

add_subdirectory(cli)
add_subdirectory(core)
add_subdirectory(ui)
add_subdirectory(models)

file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE INCS *.hpp *.h)

target_sources(${PROJECT_NAME}
  PRIVATE ${INCS} ${SRCS} # main.cpp
  PRIVATE ${CMAKE_SOURCE_DIR}/resources/win.rc
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(${PROJECT_NAME} 
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    # WIN32_EXECUTABLE TRUE
)

target_compile_options(
  ${PROJECT_NAME}
  PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4 /wd4127 /EHsc /utf-8>
  PRIVATE $<$<C_COMPILER_ID:MSVC>:/utf-8>
  PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
  PRIVATE $<$<CXX_COMPILER_ID:AppleClang>:-Wall -Wextra -Werror>
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


# include(InstallRequiredSystemLibraries)

include(${CMAKE_SOURCE_DIR}/cmake/DeployQt.cmake)
if(WIN32)
  windeployqt(${PROJECT_NAME})
endif()
