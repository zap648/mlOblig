QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    camera.cpp \
    collisionhandler.cpp \
    component.cpp \
    componentsystem.cpp \
    controller.cpp \
    cube.cpp \
    disc.cpp \
    enemyobject.cpp \
    entity.cpp \
    graph.cpp \
    heightmap.cpp \
    interactiveobject.cpp \
    light.cpp \
    logger.cpp \
    mainwindow.cpp \
    octaball.cpp \
    physicsobject.cpp \
    plane.cpp \
    point.cpp \
    renderwindow.cpp \
    restarter.cpp \
    shader.cpp \
    stb_image.cpp \
    tetrahedron.cpp \
    texture.cpp \
    tquadtre.cpp \
    trianglesurface.cpp \
    trophyobject.cpp \
    vertex.cpp \
    visualobject.cpp \
    xyz.cpp

HEADERS += \
    camera.h \
    collisionhandler.h \
    component.h \
    componentsystem.h \
    controller.h \
    cube.h \
    disc.h \
    enemyobject.h \
    entity.h \
    graph.h \
    heightmap.h \
    interactiveobject.h \
    light.h \
    logger.h \
    mainwindow.h \
    octaball.h \
    physicsobject.h \
    plane.h \
    point.h \
    renderwindow.h \
    restarter.h \
    shader.h \
    stb_image.h \
    tetrahedron.h \
    texture.h \
    tquadtre.h \
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
