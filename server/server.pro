QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH += /usr/include/mysql \
                /usr/include/c++/7
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=  \
    build/Desktop-Debug/CMakeFiles/3.22.1/CompilerIdC/CMakeCCompilerId.c \
    build/Desktop-Debug/CMakeFiles/3.22.1/CompilerIdCXX/CMakeCXXCompilerId.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/3.22.1/CompilerIdC/CMakeCCompilerId.c \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/3.22.1/CompilerIdCXX/CMakeCXXCompilerId.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/JIRO4TO6HL/moc_basicauthmiddleware.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/JIRO4TO6HL/moc_filesystemhandler.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/JIRO4TO6HL/moc_handler.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/JIRO4TO6HL/moc_localauthmiddleware.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/JIRO4TO6HL/moc_localfile.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/JIRO4TO6HL/moc_middleware.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/JIRO4TO6HL/moc_proxyhandler.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/JIRO4TO6HL/moc_qiodevicecopier.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/JIRO4TO6HL/moc_qobjecthandler.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/JIRO4TO6HL/moc_server.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/JIRO4TO6HL/moc_socket.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/UVLADIE3JM/moc_basicauthmiddleware_p.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/UVLADIE3JM/moc_filesystemhandler_p.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/UVLADIE3JM/moc_handler_p.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/UVLADIE3JM/moc_localauthmiddleware_p.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/UVLADIE3JM/moc_localfile_p.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/UVLADIE3JM/moc_proxyhandler_p.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/UVLADIE3JM/moc_proxysocket.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/UVLADIE3JM/moc_qiodevicecopier_p.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/UVLADIE3JM/moc_qobjecthandler_p.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/UVLADIE3JM/moc_server_p.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/UVLADIE3JM/moc_socket_p.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/mocs_compilation.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/auth/client.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/auth/server.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/chatserver/apihandler.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/chatserver/main.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/fileserver/main.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/basicauthmiddleware.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/filesystemhandler.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/handler.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/localauthmiddleware.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/localfile.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/parser.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/proxyhandler.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/proxysocket.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/qiodevicecopier.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/qobjecthandler.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/range.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/server.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/socket.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/TestBasicAuthMiddleware.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/TestFilesystemHandler.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/TestHandler.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/TestIByteArray.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/TestLocalAuthMiddleware.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/TestLocalFile.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/TestMiddleware.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/TestParser.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/TestProxyHandler.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/TestQIODeviceCopier.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/TestQObjectHandler.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/TestRange.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/TestServer.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/TestSocket.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/common/qsimplehttpclient.cpp \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/common/qsocketpair.cpp \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/FVLDAU35XU/moc_AppointmentApiRequest.cpp \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/FVLDAU35XU/moc_DefaultApiRequest.cpp \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/FVLDAU35XU/moc_DocterApiRequest.cpp \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/FVLDAU35XU/moc_FileApiRequest.cpp \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/FVLDAU35XU/moc_PatientApiRequest.cpp \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/FVLDAU35XU/moc_UserApiRequest.cpp \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/XPTOFSH3MW/moc_ApiRouter.cpp \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/XPTOFSH3MW/moc_AppointmentApiHandler.cpp \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/XPTOFSH3MW/moc_DefaultApiHandler.cpp \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/XPTOFSH3MW/moc_DocterApiHandler.cpp \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/XPTOFSH3MW/moc_FileApiHandler.cpp \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/XPTOFSH3MW/moc_PatientApiHandler.cpp \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/XPTOFSH3MW/moc_UserApiHandler.cpp \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/mocs_compilation.cpp \
    src/handlers/ApiRouter.cpp \
    src/handlers/AppointmentApiHandler.cpp \
    src/handlers/DefaultApiHandler.cpp \
    src/handlers/DocterApiHandler.cpp \
    src/handlers/FileApiHandler.cpp \
    src/handlers/PatientApiHandler.cpp \
    src/handlers/UserApiHandler.cpp \
    src/main.cpp \
    src/models/Appointment.cpp \
    src/models/Doctor.cpp \
    src/models/File.cpp \
    src/models/Helpers.cpp \
    src/models/HttpFileElement.cpp \
    src/models/Inline_object.cpp \
    src/models/Inline_object_1.cpp \
    src/models/Inline_object_2.cpp \
    src/models/Inline_object_3.cpp \
    src/models/Inline_object_4.cpp \
    src/models/Inline_object_5.cpp \
    src/models/Inline_response_200.cpp \
    src/models/Inline_response_200_1.cpp \
    src/models/Inline_response_200_10.cpp \
    src/models/Inline_response_200_10_data.cpp \
    src/models/Inline_response_200_11.cpp \
    src/models/Inline_response_200_11_data.cpp \
    src/models/Inline_response_200_12.cpp \
    src/models/Inline_response_200_2.cpp \
    src/models/Inline_response_200_3.cpp \
    src/models/Inline_response_200_4.cpp \
    src/models/Inline_response_200_5.cpp \
    src/models/Inline_response_200_6.cpp \
    src/models/Inline_response_200_7.cpp \
    src/models/Inline_response_200_8.cpp \
    src/models/Inline_response_200_9.cpp \
    src/models/Inline_response_200_data.cpp \
    src/models/Inline_response_404.cpp \
    src/models/Inline_response_404_1.cpp \
    src/models/Notifications.cpp \
    src/models/Patient.cpp \
    src/models/Registration.cpp \
    src/models/User.cpp \
    src/requests/AppointmentApiRequest.cpp \
    src/requests/DefaultApiRequest.cpp \
    src/requests/DocterApiRequest.cpp \
    src/requests/FileApiRequest.cpp \
    src/requests/PatientApiRequest.cpp \
    src/requests/UserApiRequest.cpp
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../shared/release/ -lshared
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../shared/debug/ -lshared
else:unix: LIBS += -L$$OUT_PWD/../shared/ -lshared

INCLUDEPATH += $$PWD/../shared \
DEPENDPATH += $$PWD/../shared \

QMAKE_RPATHDIR += $$OUT_PWD/../shared
QMAKE_RPATHDIR += $$OUT_PWD/../dataclass

DISTFILES += \
    CMakeLists.txt \
    Dockerfile \
    LICENSE.txt \
    README.MD \
    build/Desktop-Debug/CMakeCache.txt \
    build/Desktop-Debug/CMakeFiles/3.22.1/CMakeCCompiler.cmake \
    build/Desktop-Debug/CMakeFiles/3.22.1/CMakeCXXCompiler.cmake \
    build/Desktop-Debug/CMakeFiles/3.22.1/CMakeDetermineCompilerABI_C.bin \
    build/Desktop-Debug/CMakeFiles/3.22.1/CMakeDetermineCompilerABI_CXX.bin \
    build/Desktop-Debug/CMakeFiles/3.22.1/CMakeSystem.cmake \
    build/Desktop-Debug/CMakeFiles/3.22.1/CompilerIdC/a.out \
    build/Desktop-Debug/CMakeFiles/3.22.1/CompilerIdCXX/a.out \
    build/Desktop-Debug/CMakeFiles/CMakeDirectoryInformation.cmake \
    build/Desktop-Debug/CMakeFiles/CMakeOutput.log \
    build/Desktop-Debug/CMakeFiles/CMakeRuleHashes.txt \
    build/Desktop-Debug/CMakeFiles/QHTTPENGINE-complete \
    build/Desktop-Debug/CMakeFiles/QHTTPENGINE.dir/DependInfo.cmake \
    build/Desktop-Debug/CMakeFiles/QHTTPENGINE.dir/Labels.json \
    build/Desktop-Debug/CMakeFiles/QHTTPENGINE.dir/Labels.txt \
    build/Desktop-Debug/CMakeFiles/QHTTPENGINE.dir/build.make \
    build/Desktop-Debug/CMakeFiles/QHTTPENGINE.dir/cmake_clean.cmake \
    build/Desktop-Debug/CMakeFiles/QHTTPENGINE.dir/compiler_depend.make \
    build/Desktop-Debug/CMakeFiles/QHTTPENGINE.dir/progress.make \
    build/Desktop-Debug/CMakeFiles/TargetDirectories.txt \
    build/Desktop-Debug/CMakeFiles/cmake.check_cache \
    build/Desktop-Debug/CMakeFiles/progress.marks \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeCache.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/3.22.1/CMakeCCompiler.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/3.22.1/CMakeCXXCompiler.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/3.22.1/CMakeDetermineCompilerABI_C.bin \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/3.22.1/CMakeDetermineCompilerABI_CXX.bin \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/3.22.1/CMakeSystem.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/3.22.1/CompilerIdC/a.out \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/3.22.1/CompilerIdCXX/a.out \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/CMakeDirectoryInformation.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/CMakeOutput.log \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/CMakeRuleHashes.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/TargetDirectories.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/cmake.check_cache \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CMakeFiles/progress.marks \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CPackConfig.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/CPackSourceConfig.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/cmake_install.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/install_manifest.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/CMakeDirectoryInformation.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/Export/lib/cmake/qhttpengine/qhttpengineConfig-noconfig.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/Export/lib/cmake/qhttpengine/qhttpengineConfig.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/progress.marks \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/DependInfo.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/build.make \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/cmake_clean.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/compiler_depend.internal \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/compiler_depend.make \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/depend.make \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/flags.make \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/link.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/progress.make \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/qhttpengine_autogen/mocs_compilation.cpp.o.d \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/src/basicauthmiddleware.cpp.o.d \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/src/filesystemhandler.cpp.o.d \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/src/handler.cpp.o.d \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/src/localauthmiddleware.cpp.o.d \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/src/localfile.cpp.o.d \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/src/parser.cpp.o.d \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/src/proxyhandler.cpp.o.d \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/src/proxysocket.cpp.o.d \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/src/qiodevicecopier.cpp.o.d \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/src/qobjecthandler.cpp.o.d \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/src/range.cpp.o.d \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/src/server.cpp.o.d \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/src/socket.cpp.o.d \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine_autogen.dir/AutogenInfo.json \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine_autogen.dir/AutogenUsed.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine_autogen.dir/DependInfo.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine_autogen.dir/ParseCache.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine_autogen.dir/build.make \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine_autogen.dir/cmake_clean.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine_autogen.dir/compiler_depend.make \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine_autogen.dir/progress.make \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/cmake_install.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/libqhttpengine.so \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/libqhttpengine.so.1 \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/libqhttpengine.so.1.0.1 \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine.pc \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengineConfigVersion.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-stamp/QHTTPENGINE-build \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-stamp/QHTTPENGINE-configure \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-stamp/QHTTPENGINE-done \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-stamp/QHTTPENGINE-download \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-stamp/QHTTPENGINE-gitclone-lastrun.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-stamp/QHTTPENGINE-gitinfo.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-stamp/QHTTPENGINE-install \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-stamp/QHTTPENGINE-mkdir \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-stamp/QHTTPENGINE-patch \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/CMakeLists.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/LICENSE.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/README.md \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/doc/CMakeLists.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/doc/Doxyfile.in \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/doc/index.md \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/doc/overrides.css \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/CMakeLists.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/auth/CMakeLists.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/chatserver/CMakeLists.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/chatserver/static/css/style.css \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/chatserver/static/index.html \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/chatserver/static/js/chat.js \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/chatserver/static/js/jquery.min.js \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/fileserver/CMakeLists.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/CMakeLists.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/qhttpengine.pc.in \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/CMakeLists.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/cert.pem \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/common/CMakeLists.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/key.pem \
    build/Desktop-Debug/QHTTPENGINE-prefix/tmp/QHTTPENGINE-cfgcmd.txt \
    build/Desktop-Debug/QHTTPENGINE-prefix/tmp/QHTTPENGINE-cfgcmd.txt.in \
    build/Desktop-Debug/QHTTPENGINE-prefix/tmp/QHTTPENGINE-gitclone.cmake \
    build/Desktop-Debug/QHTTPENGINE-prefix/tmp/QHTTPENGINE-gitupdate.cmake \
    build/Desktop-Debug/Testing/Temporary/LastTest.log \
    build/Desktop-Debug/cmake_install.cmake \
    build/Desktop-Debug/qtcsettings.cmake \
    build/Desktop-Debug/src/CMakeFiles/CMakeDirectoryInformation.cmake \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/DependInfo.cmake \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/build.make \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/cmake_clean.cmake \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/compiler_depend.make \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/cpp-qt5-qhttpengine-server_autogen/mocs_compilation.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/depend.make \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/flags.make \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/handlers/ApiRouter.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/handlers/AppointmentApiHandler.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/handlers/DefaultApiHandler.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/handlers/DocterApiHandler.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/handlers/FileApiHandler.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/handlers/PatientApiHandler.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/handlers/UserApiHandler.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/link.txt \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/main.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Appointment.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Doctor.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/File.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Helpers.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/HttpFileElement.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_object.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_object_1.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_object_2.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_object_3.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_object_4.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_object_5.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_1.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_10.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_10_data.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_11.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_11_data.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_12.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_2.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_3.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_4.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_5.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_6.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_7.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_8.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_9.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_200_data.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_404.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Inline_response_404_1.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Notifications.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Patient.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/Registration.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/models/User.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/progress.make \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/requests/AppointmentApiRequest.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/requests/DefaultApiRequest.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/requests/DocterApiRequest.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/requests/FileApiRequest.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/requests/PatientApiRequest.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/requests/UserApiRequest.cpp.o.d \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server_autogen.dir/AutogenInfo.json \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server_autogen.dir/AutogenUsed.txt \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server_autogen.dir/DependInfo.cmake \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server_autogen.dir/ParseCache.txt \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server_autogen.dir/build.make \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server_autogen.dir/cmake_clean.cmake \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server_autogen.dir/compiler_depend.make \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server_autogen.dir/progress.make \
    build/Desktop-Debug/src/CMakeFiles/progress.marks \
    build/Desktop-Debug/src/cmake_install.cmake \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server \
    build/Desktop-Debug/src/gmon.out \
    external/lib/cmake/qhttpengine/qhttpengineConfig-noconfig.cmake \
    external/lib/cmake/qhttpengine/qhttpengineConfig.cmake \
    external/lib/cmake/qhttpengine/qhttpengineConfigVersion.cmake \
    external/lib/libqhttpengine.so \
    external/lib/libqhttpengine.so.1 \
    external/lib/libqhttpengine.so.1.0.1 \
    external/lib/pkgconfig/qhttpengine.pc \
    src/CMakeLists.txt

SUBDIRS += \
    src/server.pro

RESOURCES += \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/chatserver/resources.qrc \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/resource.qrc

TRANSLATIONS += \
    build/Desktop-Debug/CMakeFiles/QHTTPENGINE.dir/compiler_depend.ts \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine.dir/compiler_depend.ts \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/CMakeFiles/qhttpengine_autogen.dir/compiler_depend.ts \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server.dir/compiler_depend.ts \
    build/Desktop-Debug/src/CMakeFiles/cpp-qt5-qhttpengine-server_autogen.dir/compiler_depend.ts

HEADERS += \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_autogen/moc_predefs.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE-build/src/qhttpengine_export.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/examples/chatserver/apihandler.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/include/qhttpengine/basicauthmiddleware.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/include/qhttpengine/filesystemhandler.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/include/qhttpengine/handler.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/include/qhttpengine/ibytearray.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/include/qhttpengine/localauthmiddleware.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/include/qhttpengine/localfile.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/include/qhttpengine/middleware.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/include/qhttpengine/parser.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/include/qhttpengine/proxyhandler.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/include/qhttpengine/qiodevicecopier.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/include/qhttpengine/qobjecthandler.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/include/qhttpengine/range.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/include/qhttpengine/server.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/include/qhttpengine/socket.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/qhttpengine_export.h.in \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/resource.rc.in \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/basicauthmiddleware_p.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/filesystemhandler_p.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/handler_p.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/localauthmiddleware_p.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/localfile_p.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/proxyhandler_p.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/proxysocket.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/qiodevicecopier_p.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/qobjecthandler_p.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/range_p.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/server_p.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/src/src/socket_p.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/common/qsimplehttpclient.h \
    build/Desktop-Debug/QHTTPENGINE-prefix/src/QHTTPENGINE/tests/common/qsocketpair.h \
    build/Desktop-Debug/src/cpp-qt5-qhttpengine-server_autogen/moc_predefs.h \
    external/include/qhttpengine/basicauthmiddleware.h \
    external/include/qhttpengine/filesystemhandler.h \
    external/include/qhttpengine/handler.h \
    external/include/qhttpengine/ibytearray.h \
    external/include/qhttpengine/localauthmiddleware.h \
    external/include/qhttpengine/localfile.h \
    external/include/qhttpengine/middleware.h \
    external/include/qhttpengine/parser.h \
    external/include/qhttpengine/proxyhandler.h \
    external/include/qhttpengine/qhttpengine_export.h \
    external/include/qhttpengine/qiodevicecopier.h \
    external/include/qhttpengine/qobjecthandler.h \
    external/include/qhttpengine/range.h \
    external/include/qhttpengine/server.h \
    external/include/qhttpengine/socket.h \
    src/handlers/ApiRouter.h \
    src/handlers/AppointmentApiHandler.h \
    src/handlers/DefaultApiHandler.h \
    src/handlers/DocterApiHandler.h \
    src/handlers/FileApiHandler.h \
    src/handlers/PatientApiHandler.h \
    src/handlers/UserApiHandler.h \
    src/models/Appointment.h \
    src/models/Doctor.h \
    src/models/Enum.h \
    src/models/File.h \
    src/models/Helpers.h \
    src/models/HttpFileElement.h \
    src/models/Inline_object.h \
    src/models/Inline_object_1.h \
    src/models/Inline_object_2.h \
    src/models/Inline_object_3.h \
    src/models/Inline_object_4.h \
    src/models/Inline_object_5.h \
    src/models/Inline_response_200.h \
    src/models/Inline_response_200_1.h \
    src/models/Inline_response_200_10.h \
    src/models/Inline_response_200_10_data.h \
    src/models/Inline_response_200_11.h \
    src/models/Inline_response_200_11_data.h \
    src/models/Inline_response_200_12.h \
    src/models/Inline_response_200_2.h \
    src/models/Inline_response_200_3.h \
    src/models/Inline_response_200_4.h \
    src/models/Inline_response_200_5.h \
    src/models/Inline_response_200_6.h \
    src/models/Inline_response_200_7.h \
    src/models/Inline_response_200_8.h \
    src/models/Inline_response_200_9.h \
    src/models/Inline_response_200_data.h \
    src/models/Inline_response_404.h \
    src/models/Inline_response_404_1.h \
    src/models/Notifications.h \
    src/models/Object.h \
    src/models/Patient.h \
    src/models/Registration.h \
    src/models/User.h \
    src/requests/AppointmentApiRequest.h \
    src/requests/DefaultApiRequest.h \
    src/requests/DocterApiRequest.h \
    src/requests/FileApiRequest.h \
    src/requests/PatientApiRequest.h \
    src/requests/UserApiRequest.h

