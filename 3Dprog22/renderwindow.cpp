#include "renderwindow.h"
#include <QTimer>
#include <QMatrix4x4>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLDebugLogger>
#include <QKeyEvent>
#include <QStatusBar>
#include <QDebug>
#include <QLabel>
#include <QApplication>
#include <QProcess>

#include <string>

#include "disc.h"
#include "graph.h"
#include "heightmap.h"
#include "light.h"
#include "octaball.h"
#include "shader.h"
#include "mainwindow.h"
#include "logger.h"
#include "trianglesurface.h"
#include "trophyobject.h"
#include "enemyobject.h"
#include "xyz.h"
#include "plane.h"
#include "tetrahedron.h"
#include "cube.h"
#include "point.h"

RenderWindow::RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow)
    : mContext(nullptr), mInitialized(false), mMainWindow(mainWindow)

{
    //This is sent to QWindow:
    setSurfaceType(QWindow::OpenGLSurface);
    setFormat(format);
    //Make the OpenGL context
    mContext = new QOpenGLContext(this);
    //Give the context the wanted OpenGL format (v4.1 Core)
    mContext->setFormat(requestedFormat());
    if (!mContext->create()) {
        delete mContext;
        mContext = nullptr;
        qDebug() << "Context could not be made - quitting this application";
    }

    //This is the matrix used to transform (rotate) the triangle
    //You could do without, but then you have to simplify the shader and shader setup
    mPmatrix = new QMatrix4x4{};
    mPmatrix->setToIdentity();
    mVmatrix = new QMatrix4x4{};
    mVmatrix->setToIdentity();

    //Make the gameloop timer:
    mRenderTimer = new QTimer(this);

    // Adding Plane Object to mObject
    plane = new Plane(QVector3D(-5.0f, 0.0f,-5.0f), QVector3D( 5.0f, 0.0f,-5.0f), QVector3D( 5.0f, 0.0f, 5.0f), QVector3D(-5.0f, 0.0f, 5.0f));
    plane->move(0.0f, -0.5f, 0.0f);
    mObjects.push_back(plane);
//    mPhysics.push_back(plane.back());

    // Setting up Light Object and adding it to mObject
    light = new Light;
    light->setPosition3D(QVector3D{-2.5f, 2.5f, 2.5f});
    lightStrength = light->mLightStrength;
    specularStrength = light->mSpecularStrength;
    mObjects.push_back(light);

    // Setting up Rain Particles
    for (int i = 0; i < maxParticles; i++)
    {
        mParticles.push_back(new Cube(0.05f, 0.05f, 0.05f, 0.0f, 0.6f, 0.6f));
    }

    // Setting up ECS

    // Setting up Entities
    player = new Entity(0); // entity with Id 0
    entities.push_back(player);
    enemy = new Entity(1);  // entity with Id 1
    entities.push_back(enemy);

    // Setting up Components
    positionComponent = new PositionComponent();
    renderComponent = new RenderComponent();
    healthComponent = new HealthComponent();
    damageComponent = new DamageComponent();
    // ... and their managers
    positionManager = new ComponentManager<PositionComponent>();
    renderManager = new ComponentManager<RenderComponent>();
    healthManager = new ComponentManager<HealthComponent>();
    damageManager = new ComponentManager<DamageComponent>();

    // Setting up Systems
    movementSystem = new MovementSystem(positionComponent, positionManager);
    renderSystem = new RenderSystem(renderComponent, renderManager);
    damageSystem = new DamageSystem(healthComponent, damageComponent, healthManager, damageManager);

    // Add components to player
    positionManager->AddComponent(player->Id, positionComponent);
    renderManager->AddComponent(player->Id, renderComponent);
    healthManager->AddComponent(player->Id, healthComponent);
    damageManager->AddComponent(player->Id, damageComponent);
    // Add components to enemy
    positionManager->AddComponent(enemy->Id, positionComponent);
    renderManager->AddComponent(enemy->Id, renderComponent);
    healthManager->AddComponent(enemy->Id, healthComponent);
    damageManager->AddComponent(enemy->Id, damageComponent);

    // Initialize components
    positionComponent->init();
    renderComponent->init();
    healthComponent->init();
    damageComponent->init();

    // To custom change some variables
    int playerPosIndex = positionManager->GetComponent(player->Id);
    int playerRenIndex = renderManager->GetComponent(player->Id);

    int enemyPosIndex = positionManager->GetComponent(enemy->Id);
    int enemyRenIndex = renderManager->GetComponent(enemy->Id);

    // Custom starting position
    positionComponent->x[enemyPosIndex] = 4.5f;

    // Give custom renders
    renderComponent->render[playerRenIndex] = new Cube(0.5f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    renderComponent->render[enemyRenIndex] = new Cube(0.5f, 1.0f, 0.5f, 1.0f, 0.0f, 0.0f);

    renderSystem->Move(enemy, positionComponent->x[enemyPosIndex], positionComponent->y[enemyPosIndex], positionComponent->z[enemyPosIndex]);

    // Setting up the camera
    cameraEye = QVector3D(
                positionComponent->x[playerPosIndex],
                positionComponent->y[playerPosIndex],
                positionComponent->z[playerPosIndex])
            + QVector3D(0, 3.0f, 6.0f);
    //cameraEye = QVector3D{-7.0f, 2.5f, 6.0f};
    cameraAt = QVector3D(
                positionComponent->x[playerPosIndex],
                positionComponent->y[playerPosIndex],
                positionComponent->z[playerPosIndex])
            - QVector3D(0, -10.0f, 0);
    //cameraAt = QVector3D{-7.0f, 0.0f, -5.0f};
    cameraUp = QVector3D{0.0f, 1.0f, 0.0f};
}

RenderWindow::~RenderWindow()
{
    //cleans up the GPU memory
    glDeleteVertexArrays( 1, &mVAO );
    glDeleteBuffers( 1, &mVBO );
}

// Sets up the general OpenGL stuff and the buffers needed to render a triangle
void RenderWindow::init()
{
    //Get the instance of the utility Output logger
    //Have to do this, else program will crash (or you have to put in nullptr tests...)
    mLogger = Logger::getInstance();

    mLogger->logText("First is: " + std::to_string(entities.front()->Id) + ", Second is: " + std::to_string(entities.back()->Id));

    //Connect the gameloop timer to the render function:
    //This makes our render loop
    connect(mRenderTimer, SIGNAL(timeout()), this, SLOT(render()));
    //********************** General OpenGL stuff **********************

    //The OpenGL context has to be set.
    //The context belongs to the instanse of this class!
    if (!mContext->makeCurrent(this)) {
        mLogger->logText("makeCurrent() failed", LogType::REALERROR);
        return;
    }

    //just to make sure we don't init several times
    //used in exposeEvent()
    if (!mInitialized)
        mInitialized = true;

    //must call this to use OpenGL functions
    initializeOpenGLFunctions();

    //Print render version info (what GPU is used):
    //Nice to see if you use the Intel GPU or the dedicated GPU on your laptop
    // - can be deleted
    mLogger->logText("The active GPU and API:", LogType::HIGHLIGHT);
    std::string tempString;
    tempString += std::string("  Vendor: ") + std::string((char*)glGetString(GL_VENDOR)) + "\n" +
            std::string("  Renderer: ") + std::string((char*)glGetString(GL_RENDERER)) + "\n" +
            std::string("  Version: ") + std::string((char*)glGetString(GL_VERSION));
    mLogger->logText(tempString);

    //Start the Qt OpenGL debugger
    //Really helpfull when doing OpenGL
    //Supported on most Windows machines - at least with NVidia GPUs
    //reverts to plain glGetError() on Mac and other unsupported PCs
    // - can be deleted
    startOpenGLDebugger();

    //general OpenGL stuff:
    glEnable(GL_DEPTH_TEST);            //enables depth sorting - must then use GL_DEPTH_BUFFER_BIT in glClear
    //    glEnable(GL_CULL_FACE);       //draws only front side of models - usually what you want - test it out!
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);    //gray color used in glClear GL_COLOR_BUFFER_BIT

    //Compile shaders:
    //NB: hardcoded path to files! You have to change this if you change directories for the project.
    //Qt makes a build-folder besides the project folder. That is why we go down one directory
    // (out of the build-folder) and then up into the project folder.
    mShaderProgram[0] = new Shader("../3Dprog22/plainshader.vert", "../3Dprog22/plainshader.frag");
    mLogger->logText("Plain shader program id: " + std::to_string(mShaderProgram[0]->getProgram()) );
    mShaderProgram[1] = new Shader("../3Dprog22/phongshader.vert", "../3Dprog22/phongshader.frag");
    mLogger->logText("Phong shader program id: " + std::to_string(mShaderProgram[1]->getProgram()) );
    mShaderProgram[2] = new Shader("../3Dprog22/textureshader.vert", "../3Dprog22/textureshader.frag");
    mLogger->logText("Phong shader program id: " + std::to_string(mShaderProgram[2]->getProgram()) );

    // Setups up different matrices for the different shaders
    setupPlainShader(0);
    setupPhongShader(1);
    setupTextureShader(2);

    // Initilizes texture
    dogTexture = new Texture((char*)("../3Dprog22/dog.jpg"));
    dogTexture->LoadTexture();
    onTexture = new Texture((char*)("../3Dprog22/onSwitch.jpg"));
    onTexture->LoadTexture();
    offTexture = new Texture((char*)("../3Dprog22/offSwitch.jpg"));
    offTexture->LoadTexture();

    glPointSize(5);

    glBindVertexArray(0);

    light->init();
    plane->init();
    renderSystem->Init();
    for (int i = 0; i < mParticles.size(); i++)
        mParticles[i]->init();
}

// Called each frame - doing the rendering!!!
void RenderWindow::render()
{
    mCamera.init();
    mCamera.perspective(60, (double) width()/height(), 0.1, 1000.0); // Doubles REQUIRE decimals - apparently

    //moves camera
    // LookAt position of player (if player exists)
    if (player)
    {
        int playerPosIndex = positionManager->GetComponent(player->Id);

        if (ThirdPersonView)
        {

            mCamera.lookAt(cameraEye,
                           QVector3D(
                               positionComponent->x[playerPosIndex],
                               positionComponent->y[playerPosIndex],
                               positionComponent->z[playerPosIndex]), cameraUp);
        }
        else    // If 1stPersonView
        {
            mCamera.lookAt(QVector3D(
                               positionComponent->x[playerPosIndex],
                               positionComponent->y[playerPosIndex],
                               positionComponent->z[playerPosIndex]) + QVector3D(0,0.5f,0), cameraAt, cameraUp);
        }
    }
    else    // If no interactive object
        mCamera.lookAt(cameraEye, QVector3D{0,0,0}, cameraUp);

    // ECS updates
    movementSystem->Update();
    damageSystem->Update(static_cast<float>(mTimeStart.elapsed()) / 1000 /* milliseconds to seconds*/);
    particleSystem.update(static_cast<float>(mTimeStart.elapsed()) / 1000);

    light->mLightStrength = lightStrength;
    light->mSpecularStrength = specularStrength;

    QLabel *label = new QLabel(mMainWindow);
    label->setText("first line\nsecond line");

    mTimeStart.restart(); //restart FPS clock
    mContext->makeCurrent(this); //must be called every frame (every time mContext->swapBuffers is called)

    initializeOpenGLFunctions();    //must call this every frame it seems...

    for (int i = 0; i < 2; i++)
        particleSystem.create(
                    static_cast<float>(rand() * 10) / static_cast <float> (RAND_MAX) - 5,
                    19.5,
                    static_cast<float>(rand() * 10) / static_cast <float> (RAND_MAX) - 5);
//    mLogger->logText(std::to_string(particleSystem.size));

    //clear the screen for each redraw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    {
    // What shader to use (plainshader)
    glUseProgram(mShaderProgram[0]->getProgram());
    //send data to shaders
    mCamera.update(mPmatrixUniform0, mVmatrixUniform0);

    //the actual draw call(s)
    light->draw(mMatrixUniform0);   // I could *technically* componentize these objects...
    plane->draw(mMatrixUniform0);   // but the light object is too depended on by the program, haha...
    renderSystem->Update(mMatrixUniform0);
    for (int i = 0; i < particleSystem.size; i++)
    {
        mParticles[i]->setPosition3D(QVector3D(particleSystem.x[i], particleSystem.y[i], particleSystem.z[i]));
        mParticles[i]->draw(mMatrixUniform0);
    }

    // Draws all objects using phong shading
    // What shader to use (texture & phong shader)
    glUseProgram(mShaderProgram[1]->getProgram());
    //send data to shaders
    mCamera.update(mPmatrixUniform1, mVmatrixUniform1);
    checkForGLerrors();

    //Additional parameters for light shader:
    glUniform3f(mLightPositionUniform, light->getPosition().x(), light->getPosition().y(), light->getPosition().z());
    glUniform3f(mCameraPositionUniform, cameraEye.x(), cameraEye.y(), cameraEye.z());
    glUniform3f(mLightColorUniform, light->mLightColor.x(), light->mLightColor.y(), light->mLightColor.z());
    glUniform1f(mLightStrengthUniform, light->mLightStrength);
    glUniform1f(mSpecularStrengthUniform, light->mSpecularStrength);
    //Texture for phong
//    glUniform1i(mTextureUniform1, 0);
//    heightMap->draw(mMatrixUniform1);


    // What shader to use (textureshader)
//    glUseProgram(mShaderProgram[2]->getProgram());
//    mCamera.update(mPmatrixUniform2, mVmatrixUniform2);
//    glUniform1i(mTextureUniform2, 0);

//    dogTexture->UseTexture();
//    if (ThirdPersonView) mio->draw(mMatrixUniform2);

//    if (lightSwitch) onTexture->UseTexture();
//    else offTexture->UseTexture();
//    plane->draw(mMatrixUniform2);
    }

    //Calculate framerate before
    // checkForGLerrors() because that call takes a long time
    // and before swapBuffers(), else it will show the vsync time
    calculateFramerate();

    //using our expanded OpenGL debugger to check if everything is OK.
    checkForGLerrors();

    //Qt require us to call this swapBuffers() -function.
    // swapInterval is 1 by default which means that swapBuffers() will (hopefully) block
    // and wait for vsync.
    mContext->swapBuffers(this);

    int playerPosIndex = positionManager->GetComponent(player->Id);

    // Moving player entity
    if (player)
    {
        // Movement in the x-axis
        positionComponent->dx[playerPosIndex] = 0.0f;
        if (controller.moveRight)   positionComponent->dx[playerPosIndex] += 0.1f;
        if (controller.moveLeft)    positionComponent->dx[playerPosIndex] -= 0.1f;

        // Movement in the y-axis
        positionComponent->dy[playerPosIndex] = 0.0f;
        if (controller.moveUp)      positionComponent->dy[playerPosIndex] += 0.1f;
        if (controller.moveDown)    positionComponent->dy[playerPosIndex] -= 0.1f;

        // Movement in the z-axis
        positionComponent->dz[playerPosIndex] = 0.0f;
        if (controller.moveBack)    positionComponent->dz[playerPosIndex] += 0.1f;
        if (controller.moveFor)     positionComponent->dz[playerPosIndex] -= 0.1f;

        renderSystem->Move(player,
                           positionComponent->dx[playerPosIndex],
                           positionComponent->dy[playerPosIndex],
                           positionComponent->dz[playerPosIndex]);

        cameraEye = QVector3D(
                    positionComponent->x[playerPosIndex],
                    positionComponent->y[playerPosIndex],
                    positionComponent->z[playerPosIndex])
                + QVector3D(0, 3.0f, 6.0f);
    }

    if (lightSwitch)
    {
        lightStrength = 0.7f;
        specularStrength = 0.9f;
    }
    else
    {
        lightStrength = 0.0f;
        specularStrength = 0.0f;
    }

    QVector3D playerPos= QVector3D(positionComponent->x[playerPosIndex], positionComponent->y[playerPosIndex],positionComponent->z[playerPosIndex]);

    // Checks for collisions
    for (int i = 1; i < entities.size(); i++) // entities 0 is player, so ignore player
    {
        int enemyPosIndex = damageManager->GetComponent(entities[i]->Id);
        // QVector3D has a working distance function
        QVector3D enemyPos = QVector3D(positionComponent->x[enemyPosIndex],
                                       positionComponent->y[enemyPosIndex],
                                       positionComponent->z[enemyPosIndex]);

        float distance = enemyPos.distanceToPoint(playerPos);

        // Checking if this entity contains a Damage Component
        if (damageManager->HasComponent(entities[i]->Id))
        {
            int playerDmgIndex = damageManager->GetComponent(player->Id);
            // If the entity is close enough & its damage component is no longer on cooldown
            if (distance < 1.0f)
            {
                int playerHpIndex = healthManager->GetComponent(player->Id);

                if (damageComponent->cooldown[i] < 0.0f)
                {
                    damageSystem->Damage(entities[i], player, 2.0f);
                    mLogger->logText("Player Hit! Player health is now " + std::to_string(healthComponent->health[playerHpIndex]));
                }

                if (healthComponent->health[playerHpIndex] <= 0)
                {
                    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
                    qApp->quit();
                }
            }

            if (controller.attack && damageComponent->cooldown[playerDmgIndex] < 0.0f && distance < 2.0f)
            {
                damageSystem->Damage(player, entities[i], 2.0f);
                mLogger->logText("Enemy Hit! Enemy health is now " + std::to_string(healthComponent->health[i]));
            }
        }



////         Minor pointing issue with  :)
//        // Checking if this entity contains a Damage Component
//        if (std::find(entities[i]->m_componentMask.begin(), entities[i]->m_componentMask.begin(), ComponentType::Item) != entities[i]->m_componentMask.end())
//        {
//            // If the entity is close enough
//            if (distance < 1.0f)
//            {
//                int entityIndex = componentManager->GetComponent(entities[i]->Id);

//                // Pick up entity item!
//                inventorySystem->PickUp(*entities[i], *player, *inventoryComponent, *itemComponent); // OBS! Note to self: Give these components in the initialization
//                mLogger->logText("Pickup! Player has picked up a " + itemComponent->item[entityIndex]);

//                positionComponent->y[entityPosIndex] -= 5.0f; // Moves item 5 units down to "hide" it
//            }
//        }
    }

    //just to make the triangle rotate - tweak this:
    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
        (*it)->mRotate = mRotate;
}

//This function is called from Qt when window is exposed (shown)
// and when it is resized
//exposeEvent is a overridden function from QWindow that we inherit from
void RenderWindow::exposeEvent(QExposeEvent *)
{
    //if not already initialized - run init() function - happens on program start up
    if (!mInitialized)
        init();

    //This is just to support modern screens with "double" pixels (Macs and some 4k Windows laptops)
    const qreal retinaScale = devicePixelRatio();

    //Set viewport width and height to the size of the QWindow we have set up for OpenGL
    glViewport(0, 0, static_cast<GLint>(width() * retinaScale), static_cast<GLint>(height() * retinaScale));

    //If the window actually is exposed to the screen we start the main loop
    //isExposed() is a function in QWindow
    if (isExposed())
    {
        //This timer runs the actual MainLoop
        //16 means 16ms = 60 Frames pr second (should be 16.6666666 to be exact...)
        mRenderTimer->start(16);
        mTimeStart.start();
    }
}

//The way this function is set up is that we start the clock before doing the draw call,
// and check the time right after it is finished (done in the render function)
//This will approximate what framerate we COULD have.
//The actual frame rate on your monitor is limited by the vsync and is probably 60Hz
void RenderWindow::calculateFramerate()
{
    long nsecElapsed = mTimeStart.nsecsElapsed();
    static int frameCount{0};                       //counting actual frames for a quick "timer" for the statusbar

    if (mMainWindow)            //if no mainWindow, something is really wrong...
    {
        ++frameCount;
        if (frameCount > 30)    //once pr 30 frames = update the message == twice pr second (on a 60Hz monitor)
        {
            //showing some statistics in status bar
            mMainWindow->statusBar()->showMessage(" Time pr FrameDraw: " +
                                                  QString::number(nsecElapsed/1000000.f, 'g', 4) + " ms  |  " +
                                                  "FPS (approximated): " + QString::number(1E9 / nsecElapsed, 'g', 7));
            frameCount = 0;     //reset to show a new message in 30 frames
        }
    }
}

//Uses QOpenGLDebugLogger if this is present
//Reverts to glGetError() if not
void RenderWindow::checkForGLerrors()
{
    if(mOpenGLDebugLogger)  //if our machine got this class to work
    {
        const QList<QOpenGLDebugMessage> messages = mOpenGLDebugLogger->loggedMessages();
        for (const QOpenGLDebugMessage &message : messages)
        {
            if (!(message.type() == message.OtherType)) // get rid of uninteresting "object ...
                                                        // will use VIDEO memory as the source for
                                                        // buffer object operations"
                // valid error message:
                mLogger->logText(message.message().toStdString(), LogType::REALERROR);
        }
    }
    else
    {
        GLenum err = GL_NO_ERROR;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            mLogger->logText("glGetError returns " + std::to_string(err), LogType::REALERROR);
            switch (err) {
            case 1280:
                mLogger->logText("GL_INVALID_ENUM - Given when an enumeration parameter is not a "
                                "legal enumeration for that function.");
                break;
            case 1281:
                mLogger->logText("GL_INVALID_VALUE - Given when a value parameter is not a legal "
                                "value for that function.");
                break;
            case 1282:
                mLogger->logText("GL_INVALID_OPERATION - Given when the set of state for a command "
                                "is not legal for the parameters given to that command. "
                                "It is also given for commands where combinations of parameters "
                                "define what the legal parameters are.");
                break;
            }
        }
    }
}

//Tries to start the extended OpenGL debugger that comes with Qt
//Usually works on Windows machines, but not on Mac...
void RenderWindow::startOpenGLDebugger()
{
    QOpenGLContext * temp = this->context();
    if (temp)
    {
        QSurfaceFormat format = temp->format();
        if (! format.testOption(QSurfaceFormat::DebugContext))
            mLogger->logText("This system can not use QOpenGLDebugLogger, so we revert to glGetError()",
                             LogType::HIGHLIGHT);

        if(temp->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
        {
            mLogger->logText("This system can log extended OpenGL errors", LogType::HIGHLIGHT);
            mOpenGLDebugLogger = new QOpenGLDebugLogger(this);
            if (mOpenGLDebugLogger->initialize()) // initializes in the current context
                mLogger->logText("Started Qt OpenGL debug logger");
        }
    }
}

void RenderWindow::setupPlainShader(int shaderIndex)
{
    mShaderProgram[shaderIndex]->use();
    mPmatrixUniform0 = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "pmatrix");
    mVmatrixUniform0 = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "vmatrix");
    mMatrixUniform0 = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "matrix");
}

void RenderWindow::setupPhongShader(int shaderIndex)
{
    mShaderProgram[shaderIndex]->use();
    mMatrixUniform1 = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "matrix" );
    mVmatrixUniform1 = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "vmatrix" );
    mPmatrixUniform1 = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "pmatrix" );

    mLightColorUniform = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "lightColour" );
    mObjectColorUniform = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "objectColour" );
    mAmbientLightStrengthUniform = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "ambientStrength" );
    mLightPositionUniform = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "lightPosition" );
    mSpecularStrengthUniform = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "specularStrength" );
    mSpecularExponentUniform = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "specularExponent" );
    mLightStrengthUniform = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "lightStrength" );
    mCameraPositionUniform = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "cameraPosition" );
    mTextureUniform1 = glGetUniformLocation(mShaderProgram[shaderIndex]->getProgram(), "textureSampler");
}

void RenderWindow::setupTextureShader(int shaderIndex)
{
    mShaderProgram[shaderIndex]->use();
    mPmatrixUniform2 = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "pmatrix");
    mVmatrixUniform2 = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "vmatrix");
    mMatrixUniform2 = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "matrix");
    mTextureUniform2 = glGetUniformLocation( mShaderProgram[shaderIndex]->getProgram(), "textureSampler");
}

//Event sent from Qt when program receives a keyPress
// NB - see renderwindow.h for signatures on keyRelease and mouse input
void RenderWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        mMainWindow->close();       //Shuts down the whole program
    }

    //You get the keyboard input like this
    //movement
    if (event->key() == Qt::Key_A) controller.moveLeft = true;
    if (event->key() == Qt::Key_D) controller.moveRight = true;
    if (event->key() == Qt::Key_W) controller.moveFor = true;
    if (event->key() == Qt::Key_S) controller.moveBack = true;
    if (event->key() == Qt::Key_E) controller.moveUp = true;
    if (event->key() == Qt::Key_Q) controller.moveDown = true;
    if (event->key() == Qt::Key_Space) controller.attack = true;

    //Change camera view
    if (event->key() == Qt::Key_C) ThirdPersonView = !ThirdPersonView;

    if (event->key() == Qt::Key_L) lightSwitch = !lightSwitch;
}

void RenderWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A) controller.moveLeft = false;
    if (event->key() == Qt::Key_D) controller.moveRight = false;
    if (event->key() == Qt::Key_W) controller.moveFor = false;
    if (event->key() == Qt::Key_S) controller.moveBack = false;
    if (event->key() == Qt::Key_E) controller.moveUp = false;
    if (event->key() == Qt::Key_Q) controller.moveDown = false;
    if (event->key() == Qt::Key_Space) controller.attack = false;
}
