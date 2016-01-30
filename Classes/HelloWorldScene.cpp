#include "HelloWorldScene.h"
#include "Lobby.hpp"
#include "DrawingCanvas.hpp"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
//    DrawingCanvas * drawingCanvas = DrawingCanvas::create();
//    
//    addChild(drawingCanvas);
    Lobby * lobby = Lobby::create();
    
    addChild(lobby);

    
    return true;
}

//void HelloWorld::draw()
//{
//    //顶点数据
//    static  GLfloat vertext[] = {
//        0.0f, 0.0f, 0.0f,
//        200.0f, 0.0f, 0.0f,
//        0.0f, 200.0f, 0.0f,
//        200.0f, 100.0f, 0.0f
//    };
//    
//    //纹理坐标
//    static GLfloat coord[] = {
//        0.0f, 1.0f,
//        1.0f, 1.0f,
//        0.0f, 0.0f,
//        1.0f, 0.0f
//    };
//    
//    //颜色设置
//    static GLfloat color[] = {
//        1.0f, 1.0f, 1.0f, 1.0f,
//        1.0f, 1.0f, 1.0f, 1.0f,
//        1.0f, 1.0f, 1.0f, 1.0f,
//        1.0f, 1.0f, 1.0f, 1.0f
//    };
//    
//    //初始化纹理
//    static Texture2D* texture2d = NULL;
//    if (!texture2d) {
//        texture2d = TextureCache::TextureCache().addImage("HelloWord.png");
//        coord[2] = coord[6] = texture2d->getMaxS();
//        coord[1] = coord[3] = texture2d->getMaxT();
//    }
//    
//    //设置着色器
//    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
//    
//    //绑定纹理
//    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, <#GLsizei stride#>, <#const GLvoid *pointer#>)
//    
//}

