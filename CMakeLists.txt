cmake_minimum_required(VERSION 3.14)
project(compress_tool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置 vcpkg工具链路径
set(VCPKG_PATH "E:/workspace/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
if(WIN32)
    set(VCPKG_TARGET_TRIPLET "x64-windows")
elseif(APPLE)
    set(VCPKG_TARGET_TRIPLET "x64-osx")
elseif(UNIX)
    set(VCPKG_TARGET_TRIPLET "x64-linux")
else()
    message(FATAL_ERROR "Unsupported platform.")
endif()
set(CMAKE_PREFIX_PATH "${VCPKG_PATH}/installed/${VCPKG_TARGET_TRIPLET};${CMAKE_PREFIX_PATH}")

find_package(unofficial-bit7z CONFIG REQUIRED)

# 添加头文件目录，供外部项目使用
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 源文件
set(COMPRESS_SRCS
    src/ArchiveTool.cpp
)

# 创建静态库
add_library(compress_tool STATIC ${COMPRESS_SRCS})
# 导出头文件路径
target_include_directories(compress_tool PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 链接 bit7z
target_link_libraries(compress_tool PRIVATE unofficial::bit7z::bit7z64)

# 拷贝 7zip.dll 或 lib7zip.a 到输出目录
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${VCPKG_PATH}/installed/x64-windows/bin/7zip.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Copying 7zip.dll to output directory"
    )
elseif(UNIX)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${VCPKG_PATH}/installed/x64-linux/lib/lib7zip.a"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Copying lib7zip.a to output directory"
    )
endif()

# === 测试 ===
option(BUILD_COMPRESS_TOOL_TEST "Build test executable" OFF)
if(BUILD_COMPRESS_TOOL_TEST)
    add_executable(compress_tool_test tests/main.cpp)
    target_link_libraries(compress_tool_test PRIVATE compress_tool)
    target_include_directories(compress_tool_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()
