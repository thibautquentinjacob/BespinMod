TEMPLATE    = app
HEADERS     = bconfig.h config.h dialog.h kdeini.h
FORMS       = config.ui uiDemo.ui
SOURCES     = main.cpp bconfig.cpp config.cpp kdeini.cpp
DEFINES += EXECUTABLE=1
TARGET = bespin
QMAKE_CXXFLAGS += -fPIC
VERSION       = 0.1
target.path += $$[QT_INSTALL_BINS]
INSTALLS += target
