SOURCES += maxwarnings.cpp
QT = core testlib

mac:CONFIG -= app_bundle
CONFIG -= debug_and_release_target

TARGET = maxwarnings

# This app is testdata for tst_selftests
target.path = $$[QT_INSTALL_TESTS]/tst_selftests/$$TARGET
INSTALLS += target

