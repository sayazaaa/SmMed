set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

OPTION(NODEBUG  "Deactivate No debugging option" "OFF")

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -fPIC -Wall -Wno-unused-variable")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++14 -Wall -Wno-unused-variable")

if(${NODEBUG} STREQUAL "OFF")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -pg -g3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -g3")
else (${NODEBUG} STREQUAL "OFF")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -s -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s -O3")
endif(${NODEBUG} STREQUAL "OFF")

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
link_directories(/usr/lib)

find_library(UUID_LIBRARIES uuid)
find_path(UUID_INCLUDE_DIR uuid.h)
file(GLOB SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/models/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/handlers/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/requests/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/db/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

include_directories(
    /usr/include/mysql
    /usr/include/mysql++
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Network_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/models
    ${CMAKE_CURRENT_SOURCE_DIR}/handlers
    ${CMAKE_CURRENT_SOURCE_DIR}/requests
    ${BOTAN_INCLUDE_DIRS}
    ${UUIS_INCLUDE_DIRS}
    /usr/include/botan-2
)

link_directories(
    ${CMAKE_PREFIX_PATH}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    /usr/lib
)

add_executable(${PROJECT_NAME} ${SRCS})
add_dependencies(${PROJECT_NAME} QHTTPENGINE)
target_link_libraries(${PROJECT_NAME} Qt5Core Qt5Network ssl crypto qhttpengine mysqlpp botan-2 uuid)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
