TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += \
    bishop.cpp \
    boardwidget.cpp \
    button.cpp \
    controller.cpp \
    endscreenwidget.cpp \
    engine.cpp \
    gui.cpp \
    highlightwidget.cpp \
    king.cpp \
    knight.cpp \
    main.cpp \
    graphics/graphics.cpp \
    menuwidget.cpp \
    movehintwidget.cpp \
    pawn.cpp \
    piece.cpp \
    piecewidget.cpp \
    queen.cpp \
    rook.cpp \
    widget.cpp

HEADERS += \
    bishop.h \
    boardwidget.h \
    button.h \
    controller.h \
    endscreenwidget.h \
    engine.h \
    gui.h \
    highlightwidget.h \
    king.h \
    knight.h \
    menuwidget.h \
    movehintwidget.h \
    pawn.h \
    piece.h \
    piecewidget.h \
    queen.h \
    rook.h \
    widget.h

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -llibSDL2.dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -llibSDL2.dll
else:unix: LIBS += -L$$PWD/./ -llibSDL2.dll

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -llibSDL2_ttf.dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -llibSDL2_ttf.dll
else:unix: LIBS += -L$$PWD/./ -llibSDL2_ttf.dll

INCLUDEPATH += $$PWD/SDL2
DEPENDPATH += $$PWD/SDL2

OBJECTS_DIR = .
MOC_DIR = .
RCC_DIR = .
UI_DIR = .
DESTDIR = .
