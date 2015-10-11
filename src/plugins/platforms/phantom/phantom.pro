TARGET = qphantom

PLUGIN_TYPE = platforms
PLUGIN_CLASS_NAME = PhantomIntegrationPlugin
!equals(TARGET, $$QT_DEFAULT_QPA_PLUGIN): PLUGIN_EXTENDS = -
load(qt_plugin)

QT += core-private gui-private platformsupport-private

SOURCES =   main.cpp \
            phantomintegration.cpp \
            phantombackingstore.cpp
HEADERS =   phantomintegration.h \
            phantombackingstore.h

CONFIG += qpa/genericunixfontdatabase

include (../../../platformsupport/fontdatabases/fontdatabases.pri)
include (../../../platformsupport/eventdispatchers/eventdispatchers.pri)

OTHER_FILES += phantom.json
