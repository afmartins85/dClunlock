QT += qml quick sql network quickcontrols2

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/unlock.cpp \
    src/authentication.cpp \
    src/connection.cpp

OTHER_FILES += \
    pages/*.qml \

RESOURCES += \
    dClockUnlock.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/unlock.h \
    src/authentication.h \
    src/connection.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    PageDevicesForm.ui.qml \
    pages/PageLoginForm.ui.qml \
    pages/PageLogin.qml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
