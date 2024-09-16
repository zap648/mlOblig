QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    camera.cpp \
    controller.cpp \
    cube.cpp \
    disc.cpp \
    enemyobject.cpp \
    graph.cpp \
    heightmap.cpp \
    interactiveobject.cpp \
    light.cpp \
    logger.cpp \
    mainwindow.cpp \
    octaball.cpp \
    plane.cpp \
    point.cpp \
    renderwindow.cpp \
    restarter.cpp \
    shader.cpp \
    stb_image.cpp \
    tetrahedon.cpp \
    texture.cpp \
    trianglesurface.cpp \
    trophyobject.cpp \
    vertex.cpp \
    visualobject.cpp \
    xyz.cpp

HEADERS += \
    camera.h \
    controller.h \
    cube.h \
    disc.h \
    enemyobject.h \
    graph.h \
    heightmap.h \
    interactiveobject.h \
    light.h \
    logger.h \
    mainwindow.h \
    octaball.h \
    plane.h \
    point.h \
    renderwindow.h \
    restarter.h \
    shader.h \
    stb_image.h \
    tetrahedon.h \
    texture.h \
    trianglesurface.h \
    trophyobject.h \
    vertex.h \
    visualobject.h \
    xyz.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    phongshader.frag \
    phongshader.vert \
    plainshader.frag \
    plainshader.vert \
    textureshader.frag \
    textureshader.vert
