#include "AppDelegate.h"
//#include "HelloWorldScene.h"
#include "MapCreateScene.h"

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
 
    pEGLView -> setDesignResolutionSize(1280, 900, kResolutionShowAll); // UPTO MEIZU MXII STD.
    
    // config director - fix black-line
//    CCDirector::sharedDirector() -> setProjection(kCCDirectorProjection2D);

// fix black-line, need to find these lines:
//#ifndef CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
//#define CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL 1
//#endif
    
    // turn on display FPS
    pDirector->setDisplayStats(true);
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
	// init sprite frame cache
//	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("CSProj0.plist");

    // create a scene. it's an autorelease object
    CCScene *pScene = MapCreate::scene();

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
