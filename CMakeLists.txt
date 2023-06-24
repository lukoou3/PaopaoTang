cmake_minimum_required(VERSION 3.22)
project(PaopaoTang)

set(CMAKE_CXX_STANDARD 14)

set(EasyX_DIR D:/apps/easyx4mingw) # 指定下载的easyx4mingw位置
include_directories(${EasyX_DIR}/include)
link_directories(${EasyX_DIR}/lib64) # 如果是32位系统，则使用lib32

link_libraries(libEasyX.a libgdi32.a libole32.a) # 链接EasyX库

add_executable(PaopaoTang main.cpp tools.cpp game.cpp items.cpp virtual_items.cpp)
add_executable(test test.cpp tools.cpp)

target_link_libraries(PaopaoTang winmm.lib)
target_link_libraries(test winmm.lib)