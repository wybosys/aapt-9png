cmake_minimum_required(VERSION 2.10)
project(aapt-9png)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

find_package(PkgConfig REQUIRED)
pkg_check_modules(PNG libpng REQUIRED)

find_package(ZLIB REQUIRED)
pkg_check_modules(JSONCPP jsoncpp REQUIRED)

include_directories(
    ${ZLIB_INCLUDE_DIRS}
    src
    )

set(LIB_SRC
    src/9png.cpp
    src/android-platform.cpp
    src/android-images.cpp
    )

set(CLI_SRC
    src/cli.cpp)

add_library(aapt9png SHARED ${LIB_SRC})
target_include_directories(aapt9png 
    PUBLIC ${PNG_INCLUDE_DIRS}
    PUBLIC ${JSONCPP_INCLUDE_DIRS}
    )
target_link_directories(aapt9png 
    PUBLIC ${PNG_LIBRARY_DIRS}
    PUBLIC ${JSONCPP_LIBRARY_DIRS}
    )
target_link_libraries(aapt9png 
    ${PNG_LIBRARIES} 
    ${JSONCPP_LIBRARIES} 
    )

add_executable(aapt-9png ${CLI_SRC})
target_link_libraries(aapt-9png aapt9png)
