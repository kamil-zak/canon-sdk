cmake_minimum_required (VERSION 3.10.2)

project(MultiCamCui CXX)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/include)

add_compile_options(-D TARGET_OS_LINUX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -fpermissive -pthread")

add_executable (MultiCamCui
    ${SRC_DIR}/CameraEvent.cpp
    ${SRC_DIR}/FileControl.cpp
    ${SRC_DIR}/MultiCamCui.cpp
    ${SRC_DIR}/PreSetting.cpp
    ${SRC_DIR}/CameraModel.cpp
    ${SRC_DIR}/utility.cpp
)

set_target_properties(MultiCamCui PROPERTIES
	CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    BUILD_RPATH "$ORIGIN"
    INSTALL_RPATH "$ORIGIN"
)

target_include_directories(MultiCamCui
  PUBLIC ${SRC_DIR}
  PUBLIC ${INC_DIR}
  PUBLIC ${PROJECT_SOURCE_DIR}/../EDSDK/Header
  )

set(EDSDK_LDIR ${CMAKE_CURRENT_SOURCE_DIR}/../EDSDK)
target_link_libraries(MultiCamCui
    PRIVATE
    ${EDSDK_LDIR}/Library/ARM64/libEDSDK.so
)


add_custom_command(TARGET MultiCamCui PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${EDSDK_LDIR}/Library/ARM64 $<TARGET_FILE_DIR:MultiCamCui>
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:MultiCamCui>/resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:MultiCamCui>/resources
)