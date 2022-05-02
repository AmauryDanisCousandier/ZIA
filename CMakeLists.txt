cmake_minimum_required(VERSION 3.16)
project(zia)

# CONAN
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake")
    endif()

    include(${CMAKE_BINARY_DIR}/conan.cmake)
    conan_cmake_run(CONANFILE conanfile.txt )#BUILD missing)
endif()


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
# END CONAN

# API

include(ExternalProject)

ExternalProject_Add(
    ziapi
    GIT_REPOSITORY  https://github.com/martin-olivier/ZiAPI.git
    GIT_TAG         v5.0.1
    INSTALL_COMMAND ""
    TEST_COMMAND    ""
)

ExternalProject_Get_Property(ziapi SOURCE_DIR)

# END API


set(CMAKE_CXX_STANDARD 20)
set(SRCS
${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/QueueManagement/RequestOutputQueue.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/QueueManagement/ResponseInputQueue.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/QueueManagement/RequestInputQueue.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/QueueManagement/ResponseOutputQueue.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/network/server.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/network/connection.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/configManagement/ConfigManagement.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/network/coreNetwork.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/network/HeaderParsing/HeaderParsing.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/loadDll.cpp
)

include_directories(${SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS_INIT "-Wall -Wextra -g3")

add_executable(zia ${SRCS})
add_dependencies(zia ziapi)

# SHARED LIB
#add_library(TestDll SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/modules/TestDll/TestDll.cpp)
add_library(PHPModule SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/Handler.cpp)
add_library(imageModule SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/ModuleImg.cpp)
add_library(BasicModule SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/BasicModule.cpp)
# END SHARED LIB

if(UNIX)
    target_link_libraries(BasicModule PRIVATE dl)
    target_link_libraries(PHPModule PRIVATE dl)
    target_link_libraries(imageModule PRIVATE dl)
    target_link_libraries(zia PRIVATE dl -pthread)
else()
    target_link_libraries(zia ${CONAN_LIBS} -pthread)
endif()