project(cpp-qt5-qhttpengine-server)

include(ExternalProject)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external)

# ExternalProject_Add(QHTTPENGINE
#     GIT_REPOSITORY https://github.com/etherealjoy/qhttpengine.git

#     #SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external
#     CMAKE_ARGS  -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
#                 -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
# )

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

add_subdirectory(src)
