#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>
#include <QOpenGLFunctions_4_1_Core>
#include <QTimer>
#include <QElapsedTimer>
#include <vector>

#include "camera.h";
#include "particlesystem.h"
#include "component.h"
#include "componentsystem.h"
#include "cube.h"
#include "entity.h"
#include "plane.h"
#include "collisionhandler.h"
#include "controller.h"
#include "interactiveobject.h"
#include "light.h"
#include "vertex.h"
#include "visualobject.h"
#include "texture.h"

class QOpenGLContext;
class Shader;
class MainWindow;

/// This inherits from QWindow to get access to the Qt functionality and
// OpenGL surface.
// We also inherit from QOpenGLFunctions, to get access to the OpenGL functions
// This is the same as using "glad" and "glw" from general OpenGL tutorials
class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow);
    ~RenderWindow() override;

    QOpenGLContext *context() { return mContext; }

    void exposeEvent(QExposeEvent *) override;  //gets called when app is shown and resized

    bool mRotate{false};     //Check if triangle should rotate

    bool ThirdPersonView{true};

    bool lightSwitch{true};

    GLfloat lightStrength;
    GLfloat specularStrength;

    GLint trophyCount;

private slots:
    void render();          //the actual render - function

private:
//    Vertex m_v;
    std::vector<VisualObject*> mObjects;
    std::vector<VisualObject*> mTrophies;
    std::vector<VisualObject*> mEnemies;
    std::vector<PhysicsObject*> mPhysics;
    std::vector<VisualObject*> mParticles;
    VisualObject* mio;      //member interactive object

    // Entity Component System
    // Entities
    Entity* player;
    Entity* enemy;
    Entity* item;
    std::vector<Entity*> entities;
    // Components
    PositionComponent* positionComponent;
    RenderComponent* renderComponent;
    HealthComponent* healthComponent;
    DamageComponent* damageComponent;
//    ItemComponent* itemComponent;
//    InventoryComponent* inventoryComponent;
//    ControllerComponent* controllerComponent;
    ComponentManager<PositionComponent>* positionManager;
    ComponentManager<RenderComponent>* renderManager;
    ComponentManager<HealthComponent>* healthManager;
    ComponentManager<DamageComponent>* damageManager;
    // Systems
    MovementSystem* movementSystem;
    RenderSystem* renderSystem;
    DamageSystem* damageSystem;
//    InventorySystem* inventorySystem;

    ParticleSystem particleSystem;

    Plane* plane;
    Cube* cube;
    VisualObject* xyz;
    VisualObject* heightMap;
    Camera mCamera;
    Light* light{nullptr};
    Controller controller;
    CollisionHandler* mCollisionHandler;
    OctaBall* ball;

    Texture* dogTexture;
    Texture* offTexture;
    Texture* onTexture;

    void init();            //initialize things we need before rendering

    QVector3D cameraEye;
    QVector3D cameraAt;
    QVector3D cameraUp;

    QOpenGLContext *mContext{nullptr};  //Our OpenGL context
    bool mInitialized{false};

    void setupPlainShader(int shaderIndex);
    Shader *mShaderProgram[4]{nullptr};    //holds pointer the GLSL shader program
    GLint mMatrixUniform0;              //OpenGL reference to the Uniform in the shader program
    GLint mPmatrixUniform0;
    GLint mVmatrixUniform0;

    void setupPhongShader(int shaderIndex);
    GLint mMatrixUniform1;              //OpenGL reference to the Uniform in the shader program
    GLint mPmatrixUniform1;
    GLint mVmatrixUniform1;

    GLint mLightColorUniform;
    GLint mObjectColorUniform;
    GLint mAmbientLightStrengthUniform;
    GLint mLightPositionUniform;
    GLint mCameraPositionUniform;
    GLint mSpecularStrengthUniform;
    GLint mSpecularExponentUniform;
    GLint mLightStrengthUniform;
    GLint mTextureUniform1;

    void setupTextureShader(int shaderIndex);
    GLint mMatrixUniform2;
    GLint mPmatrixUniform2;
    GLint mVmatrixUniform2;
    GLint mTextureUniform2;

    GLuint mVAO;                        //OpenGL reference to our VAO
    GLuint mVBO;                        //OpenGL reference to our VBO

    QMatrix4x4 *mMVPmatrix{nullptr};         //The matrix with the transform for the object we draw
    QMatrix4x4 *mPmatrix{nullptr};
    QMatrix4x4 *mVmatrix{nullptr};

    QTimer *mRenderTimer{nullptr};           //timer that drives the gameloop
    QElapsedTimer mTimeStart;               //time variable that reads the calculated FPS

    MainWindow *mMainWindow{nullptr};        //points back to MainWindow to be able to put info in StatusBar

    class QOpenGLDebugLogger *mOpenGLDebugLogger{nullptr};  //helper class to get some clean debug info from OpenGL
    class Logger *mLogger{nullptr};         //logger - Output Log in the application

    ///Helper function that uses QOpenGLDebugLogger or plain glGetError()
    void checkForGLerrors();

    void calculateFramerate();          //as name says

    ///Starts QOpenGLDebugLogger if possible
    void startOpenGLDebugger();

protected:
    //The QWindow that we inherit from have these functions to capture
    // - mouse and keyboard.
    // Uncomment to use (you also have to make the definitions of
    // these functions in the cpp-file to use them of course!)
    //
    //    void mousePressEvent(QMouseEvent *event) override{}
    //    void mouseMoveEvent(QMouseEvent *event) override{}
    void keyPressEvent(QKeyEvent *event) override;              //the only one we use now
    void keyReleaseEvent(QKeyEvent *event) override;            //not the only one we use now
    //    void wheelEvent(QWheelEvent *event) override{}
};

#endif // RENDERWINDOW_H
