set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/resources/icon\\\\icon.ico")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_CONTACT "Moth <QianMoth@qq.com>")
set(CPACK_PACKAGE_VENDOR "MOTH") # 公司名称
set(CPACK_PACKAGE_HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL}) # 网址
# 系统信息
set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
string(TOLOWER ${CPACK_SYSTEM_NAME} CPACK_SYSTEM_NAME)
# 编译时间
string(TIMESTAMP COMPILE_TIME %Y%m%d_%H%M%S)
# 输出名称
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_SYSTEM_NAME}")
# 输出目录
set(CPACK_PACKAGE_DIRECTORY ${PROJECT_BINARY_DIR}/package)

if(WIN32) # Include all dynamically linked runtime libraries such as MSVCRxxx.dll
  list(APPEND CPACK_GENERATOR "NSIS")

  set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}")

  set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\${CPACK_PACKAGE_NAME}.exe")
  # set(CPACK_NSIS_MUI_ICON "${CPACK_PACKAGE_ICON}") # 安装包图标
  # set(CPACK_NSIS_MUI_UNIICON "${CPACK_PACKAGE_ICON}") # 删除图标
  set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_NAME} ${CPACK_PACKAGE_VERSION}") # 控制面板
  set(CPACK_NSIS_PACKAGE_NAME "${CPACK_PACKAGE_NAME}")
  # set(CPACK_NSIS_MODIFY_PATH "ON")

  set(CPACK_NSIS_CREATE_ICONS_EXTRA "CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${CPACK_PACKAGE_NAME}.lnk' '$INSTDIR\\\\bin\\\\${CPACK_PACKAGE_NAME}.exe'")
  set(CPACK_NSIS_DELETE_ICONS_EXTRA "Delete '$SMPROGRAMS\\\\$START_MENU\\\\${CPACK_PACKAGE_NAME}.lnk'")
  
  set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "CreateShortCut '$DESKTOP\\\\${CPACK_PACKAGE_NAME}.lnk' '$INSTDIR\\\\bin\\\\${CPACK_PACKAGE_NAME}.exe'")
  set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "Delete '$DESKTOP\\\\${CPACK_PACKAGE_NAME}.lnk'")

elseif(APPLE)
  set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/resources/icon/icon.icns")
  list(APPEND CPACK_GENERATOR "DragNDrop")
else()
  # list(APPEND CPACK_GENERATOR "DEB")
  # set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON) # ldd oflow
endif()

message(STATUS "[cpack] CPack generators: ${CPACK_GENERATOR}, Time: ${COMPILE_TIME}")

include(CPack)