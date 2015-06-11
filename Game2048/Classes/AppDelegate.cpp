/*
 * 作者：MWN		
 * 邮箱：modood@qq.com
 * 版本：1.0
 * 日期：2015年5月25日
 */
#include "AppDelegate.h"
#include "GameDefine.h"
#include "LogoScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("2048");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	// 设置屏幕尺寸
	if ( getTargetPlatform() == cocos2d::ApplicationProtocol::Platform::OS_WINDOWS )
	{
		glview->setFrameSize( 320 , 480 ); // Windows下调试使用
	}

	glview->setDesignResolutionSize( GAME_SCREEN_WIDTH , GAME_SCREEN_HEIGHT , ResolutionPolicy::FIXED_WIDTH );

    // create a scene. it's an autorelease object
    auto scene = LogoScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
