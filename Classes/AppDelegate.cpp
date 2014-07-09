#include "AppDelegate.h"
#include "MainMenuScene.h"
#include "HeroSelectScene.h"

USING_NS_CC;
using namespace std;

typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
}Resource;

static Resource smallResource  =  { cocos2d::CCSizeMake(320, 240),  "SD" };
static Resource mediumResource =  { cocos2d::CCSizeMake(800, 480),  "HD"   };
static Resource largeResource  =  { cocos2d::CCSizeMake(1280, 800), "HDR" };
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1280, 720);

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    
//    CCTexture2D::setDefaultAlphaPixelFormat(kTexture2DPixelFormat_RGBA4444);
    
  //  CCTexture2D::setDefaultAlphaPixelFormat(kTexture2DPixelFormat_RGBA4444);
    pDirector->setOpenGLView(pEGLView);
        
    // turn on display FPS
    pDirector->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
 
    
    
    //Set design screen resolution
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionFixedHeight);
    
    CCSize frameSize = pEGLView->getFrameSize();
    
    vector<string> searchPath;
    
    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.
    
    // if the frame's height is larger than the height of medium resource size, select large resource.
//    if (frameSize.height >= largeResource.size.height)
//    {
    searchPath.push_back("fonts/eng");
     searchPath.push_back("global");
     searchPath.push_back("GUI");
    
       searchPath.push_back(largeResource.directory);
       pDirector->setContentScaleFactor(1);
//    }
//    else if (frameSize.height >= mediumResource.size.height)
//    {
//        searchPath.push_back(mediumResource.directory);
//        pDirector->setContentScaleFactor(0.5f);
//    }
//    else
//    {
//        searchPath.push_back(smallResource.directory);
//        pDirector->setContentScaleFactor(0.25f);
//    }
    searchPath.push_back("16bit");
    if(frameSize.height <= largeResource.size.height)
    {
      
        CCTexture2D::setDefaultAlphaPixelFormat(kTexture2DPixelFormat_RGBA4444);
    }
   // else
    {
//        searchPath.push_back("32bit");
//        CCTexture2D::setDefaultAlphaPixelFormat(kTexture2DPixelFormat_RGBA8888);

    }
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
    // create a scene. it's an autorelease object
    CCScene *pScene = MainMenuScene::scene();
    
    // run
    pDirector->runWithScene(pScene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
