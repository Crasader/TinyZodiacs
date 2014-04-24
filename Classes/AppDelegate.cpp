#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

        

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    
    
    //Set design screen resolution
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1024, 768, kResolutionShowAll);

    // if the frame's height is larger than the height of medium resource size, select large resource.
//    if (frameSize.height >= largeResource.size.height)
//    {
       //searchPath.push_back(largeResource.directory);
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
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

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
