cmake_minimum_required (VERSION 3.10.2)

project(MultiCamCui CXX)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/app/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/app/include)

if(MSVC)
    string(REPLACE "/W3" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /EHsc")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   /DBUILD_TYPE=\\\"Debug\\\"")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /DBUILD_TYPE=\\\"Release\\\"")
elseif(APPLE)
    add_compile_options(-D __MACOS__)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -fpermissive -pthread")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -DBUILD_TYPE=\\\"Debug\\\"")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DBUILD_TYPE=\\\"Release\\\"")
else()
    add_compile_options(-D TARGET_OS_LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -fpermissive -pthread")
endif()


file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)
add_executable(MultiCamCui ${SRC_FILES})

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
  PUBLIC ${PROJECT_SOURCE_DIR}/EDSDK/Header
  )

set(EDSDK_LDIR ${CMAKE_CURRENT_SOURCE_DIR}/EDSDK/Library)

if(MSVC)
    target_link_libraries(MultiCamCui PRIVATE ${EDSDK_LDIR}/WIN64/EDSDK.lib)
elseif(UNIX AND NOT APPLE)
    target_link_libraries(MultiCamCui PRIVATE ${EDSDK_LDIR}/ARM64/libEDSDK.so)
elseif(APPLE)
    target_link_libraries(MultiCamCui PRIVATE ${EDSDK_LDIR}/MAC/EDSDK.framework/EDSDK)
endif()


if(MSVC)
    add_custom_command(TARGET MultiCamCui PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${EDSDK_LDIR}/WIN64/Dll $<TARGET_FILE_DIR:MultiCamCui>
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:MultiCamCui>/resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/app/resources $<TARGET_FILE_DIR:MultiCamCui>/resources
    )
elseif(UNIX AND NOT APPLE)
    add_custom_command(TARGET MultiCamCui PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${EDSDK_LDIR}/ARM64 $<TARGET_FILE_DIR:MultiCamCui>
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:MultiCamCui>/resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/app/resources $<TARGET_FILE_DIR:MultiCamCui>/resources
    )
elseif(APPLE)
    add_custom_command(TARGET MultiCamCui PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${EDSDK_LDIR}/MAC $<TARGET_FILE_DIR:MultiCamCui>
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:MultiCamCui>/resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/app/resources $<TARGET_FILE_DIR:MultiCamCui>/resources
    )
endif()