TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bishop.cpp \
        controller.cpp \
        engine.cpp \
        gui.cpp \
        king.cpp \
        knight.cpp \
        main.cpp \
        graphics/graphics.cpp \
        pawn.cpp \
        piece.cpp \
        queen.cpp \
        rook.cpp


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

HEADERS += \
    bishop.h \
    controller.h \
    engine.h \
    gui.h \
    king.h \
    knight.h \
    knight.h \
    pawn.h \
    piece.h \
    queen.h \
    rook.h
