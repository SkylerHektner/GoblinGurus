#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T20:12:34
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3505_Final_Project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += "$$PWD/../../Box2D-master/Box2D"

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    gamecontroller.cpp \
    goblin.cpp \
    questionmanager.cpp \
    question.cpp \
    pathfinder.cpp \
    difficultyselector.cpp \
    ../../Box2D-master/Box2D/Box2D/Collision/Shapes/b2ChainShape.cpp \
    ../../Box2D-master/Box2D/Box2D/Collision/Shapes/b2CircleShape.cpp \
    ../../Box2D-master/Box2D/Box2D/Collision/Shapes/b2EdgeShape.cpp \
    ../../Box2D-master/Box2D/Box2D/Collision/Shapes/b2PolygonShape.cpp \
    ../../Box2D-master/Box2D/Box2D/Collision/b2BroadPhase.cpp \
    ../../Box2D-master/Box2D/Box2D/Collision/b2CollideCircle.cpp \
    ../../Box2D-master/Box2D/Box2D/Collision/b2CollideEdge.cpp \
    ../../Box2D-master/Box2D/Box2D/Collision/b2CollidePolygon.cpp \
    ../../Box2D-master/Box2D/Box2D/Collision/b2Collision.cpp \
    ../../Box2D-master/Box2D/Box2D/Collision/b2Distance.cpp \
    ../../Box2D-master/Box2D/Box2D/Collision/b2DynamicTree.cpp \
    ../../Box2D-master/Box2D/Box2D/Collision/b2TimeOfImpact.cpp \
    ../../Box2D-master/Box2D/Box2D/Common/b2BlockAllocator.cpp \
    ../../Box2D-master/Box2D/Box2D/Common/b2Draw.cpp \
    ../../Box2D-master/Box2D/Box2D/Common/b2Math.cpp \
    ../../Box2D-master/Box2D/Box2D/Common/b2Settings.cpp \
    ../../Box2D-master/Box2D/Box2D/Common/b2StackAllocator.cpp \
    ../../Box2D-master/Box2D/Box2D/Common/b2Timer.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2Contact.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2GearJoint.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2Joint.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2MotorJoint.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2RopeJoint.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2WeldJoint.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2WheelJoint.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/b2Body.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/b2ContactManager.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/b2Fixture.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/b2Island.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/b2World.cpp \
    ../../Box2D-master/Box2D/Box2D/Dynamics/b2WorldCallbacks.cpp \
    ../../Box2D-master/Box2D/Box2D/Rope/b2Rope.cpp \
    effect.cpp

HEADERS += \
        mainwindow.h \
    gamecontroller.h \
    goblin.h \
    questionmanager.h \
    question.h \
    pathfinder.h \
    difficultyselector.h \
    ../../SFML-2.4.2/include/SFML/Audio/AlResource.hpp \
    ../../SFML-2.4.2/include/SFML/Audio/Export.hpp \
    ../../SFML-2.4.2/include/SFML/Audio/InputSoundFile.hpp \
    ../../SFML-2.4.2/include/SFML/Audio/Listener.hpp \
    ../../SFML-2.4.2/include/SFML/Audio/Music.hpp \
    ../../SFML-2.4.2/include/SFML/Audio/OutputSoundFile.hpp \
    ../../SFML-2.4.2/include/SFML/Audio/Sound.hpp \
    ../../SFML-2.4.2/include/SFML/Audio/SoundBuffer.hpp \
    ../../SFML-2.4.2/include/SFML/Audio/SoundBufferRecorder.hpp \
    ../../SFML-2.4.2/include/SFML/Audio/SoundFileFactory.hpp \
    ../../SFML-2.4.2/include/SFML/Audio/SoundFileReader.hpp \
    ../../SFML-2.4.2/include/SFML/Audio/SoundFileWriter.hpp \
    ../../SFML-2.4.2/include/SFML/Audio/SoundRecorder.hpp \
    ../../SFML-2.4.2/include/SFML/Audio/SoundSource.hpp \
    ../../SFML-2.4.2/include/SFML/Audio/SoundStream.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/BlendMode.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/CircleShape.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Color.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/ConvexShape.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Drawable.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Export.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Font.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Glsl.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Glyph.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Image.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/PrimitiveType.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Rect.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/RectangleShape.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/RenderStates.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/RenderTarget.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/RenderTexture.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/RenderWindow.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Shader.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Shape.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Sprite.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Text.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Texture.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Transform.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Transformable.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/Vertex.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/VertexArray.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics/View.hpp \
    ../../SFML-2.4.2/include/SFML/Network/Export.hpp \
    ../../SFML-2.4.2/include/SFML/Network/Ftp.hpp \
    ../../SFML-2.4.2/include/SFML/Network/Http.hpp \
    ../../SFML-2.4.2/include/SFML/Network/IpAddress.hpp \
    ../../SFML-2.4.2/include/SFML/Network/Packet.hpp \
    ../../SFML-2.4.2/include/SFML/Network/Socket.hpp \
    ../../SFML-2.4.2/include/SFML/Network/SocketHandle.hpp \
    ../../SFML-2.4.2/include/SFML/Network/SocketSelector.hpp \
    ../../SFML-2.4.2/include/SFML/Network/TcpListener.hpp \
    ../../SFML-2.4.2/include/SFML/Network/TcpSocket.hpp \
    ../../SFML-2.4.2/include/SFML/Network/UdpSocket.hpp \
    ../../SFML-2.4.2/include/SFML/System/Clock.hpp \
    ../../SFML-2.4.2/include/SFML/System/Err.hpp \
    ../../SFML-2.4.2/include/SFML/System/Export.hpp \
    ../../SFML-2.4.2/include/SFML/System/FileInputStream.hpp \
    ../../SFML-2.4.2/include/SFML/System/InputStream.hpp \
    ../../SFML-2.4.2/include/SFML/System/Lock.hpp \
    ../../SFML-2.4.2/include/SFML/System/MemoryInputStream.hpp \
    ../../SFML-2.4.2/include/SFML/System/Mutex.hpp \
    ../../SFML-2.4.2/include/SFML/System/NativeActivity.hpp \
    ../../SFML-2.4.2/include/SFML/System/NonCopyable.hpp \
    ../../SFML-2.4.2/include/SFML/System/Sleep.hpp \
    ../../SFML-2.4.2/include/SFML/System/String.hpp \
    ../../SFML-2.4.2/include/SFML/System/Thread.hpp \
    ../../SFML-2.4.2/include/SFML/System/ThreadLocal.hpp \
    ../../SFML-2.4.2/include/SFML/System/ThreadLocalPtr.hpp \
    ../../SFML-2.4.2/include/SFML/System/Time.hpp \
    ../../SFML-2.4.2/include/SFML/System/Utf.hpp \
    ../../SFML-2.4.2/include/SFML/System/Vector2.hpp \
    ../../SFML-2.4.2/include/SFML/System/Vector3.hpp \
    ../../SFML-2.4.2/include/SFML/Window/Context.hpp \
    ../../SFML-2.4.2/include/SFML/Window/ContextSettings.hpp \
    ../../SFML-2.4.2/include/SFML/Window/Event.hpp \
    ../../SFML-2.4.2/include/SFML/Window/Export.hpp \
    ../../SFML-2.4.2/include/SFML/Window/GlResource.hpp \
    ../../SFML-2.4.2/include/SFML/Window/Joystick.hpp \
    ../../SFML-2.4.2/include/SFML/Window/Keyboard.hpp \
    ../../SFML-2.4.2/include/SFML/Window/Mouse.hpp \
    ../../SFML-2.4.2/include/SFML/Window/Sensor.hpp \
    ../../SFML-2.4.2/include/SFML/Window/Touch.hpp \
    ../../SFML-2.4.2/include/SFML/Window/VideoMode.hpp \
    ../../SFML-2.4.2/include/SFML/Window/Window.hpp \
    ../../SFML-2.4.2/include/SFML/Window/WindowHandle.hpp \
    ../../SFML-2.4.2/include/SFML/Window/WindowStyle.hpp \
    ../../SFML-2.4.2/include/SFML/Audio.hpp \
    ../../SFML-2.4.2/include/SFML/Config.hpp \
    ../../SFML-2.4.2/include/SFML/Graphics.hpp \
    ../../SFML-2.4.2/include/SFML/Main.hpp \
    ../../SFML-2.4.2/include/SFML/Network.hpp \
    ../../SFML-2.4.2/include/SFML/OpenGL.hpp \
    ../../SFML-2.4.2/include/SFML/System.hpp \
    ../../SFML-2.4.2/include/SFML/Window.hpp \
    ../../Box2D-master/Box2D/Box2D/Collision/Shapes/b2ChainShape.h \
    ../../Box2D-master/Box2D/Box2D/Collision/Shapes/b2CircleShape.h \
    ../../Box2D-master/Box2D/Box2D/Collision/Shapes/b2EdgeShape.h \
    ../../Box2D-master/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h \
    ../../Box2D-master/Box2D/Box2D/Collision/Shapes/b2Shape.h \
    ../../Box2D-master/Box2D/Box2D/Collision/b2BroadPhase.h \
    ../../Box2D-master/Box2D/Box2D/Collision/b2Collision.h \
    ../../Box2D-master/Box2D/Box2D/Collision/b2Distance.h \
    ../../Box2D-master/Box2D/Box2D/Collision/b2DynamicTree.h \
    ../../Box2D-master/Box2D/Box2D/Collision/b2TimeOfImpact.h \
    ../../Box2D-master/Box2D/Box2D/Common/b2BlockAllocator.h \
    ../../Box2D-master/Box2D/Box2D/Common/b2Draw.h \
    ../../Box2D-master/Box2D/Box2D/Common/b2GrowableStack.h \
    ../../Box2D-master/Box2D/Box2D/Common/b2Math.h \
    ../../Box2D-master/Box2D/Box2D/Common/b2Settings.h \
    ../../Box2D-master/Box2D/Box2D/Common/b2StackAllocator.h \
    ../../Box2D-master/Box2D/Box2D/Common/b2Timer.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2CircleContact.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2Contact.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2ContactSolver.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2PolygonContact.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2GearJoint.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2Joint.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2MotorJoint.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2MouseJoint.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2PrismaticJoint.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2PulleyJoint.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2RevoluteJoint.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2RopeJoint.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2WeldJoint.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2WheelJoint.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/b2Body.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/b2ContactManager.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/b2Fixture.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/b2Island.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/b2TimeStep.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/b2World.h \
    ../../Box2D-master/Box2D/Box2D/Dynamics/b2WorldCallbacks.h \
    ../../Box2D-master/Box2D/Box2D/Rope/b2Rope.h \
    ../../Box2D-master/Box2D/Box2D/Box2D.h \
    effect.h

FORMS += \
        mainwindow.ui \
    difficultyselector.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../SFML-2.4.2/lib/ -lsfml-window.2.4.2 -lsfml-main-d -lsfml-audio-d -lsfml-graphics-d -lsfml-system-d -lsfml-network-d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../SFML-2.4.2/lib/ -lsfml-window.2.4.2d -lsfml-audio.2.4.2d -lsfml-graphics.2.4.2d -lsfml-system.2.4.2d -lsfml-network.2.4.2d
else:unix: LIBS += -L$$PWD/../../SFML-2.4.2/lib/ -lsfml-window.2.4.2 -lsfml-audio.2.4.2 -lsfml-graphics.2.4.2 -lsfml-system.2.4.2

INCLUDEPATH += $$PWD/../../SFML-2.4.2/include
DEPENDPATH += $$PWD/../../SFML-2.4.2/include

