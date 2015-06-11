/*
 * 作者：MWN		
 * 邮箱：modood@qq.com
 * 版本：1.0
 * 日期：2015年5月25日
 */

#include "LogoScene.h"
#include "GameDefine.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* LogoScene::createScene()
{
    auto scene = Scene::create();
    auto layer = LogoScene::create();
    scene->addChild(layer);

    return scene;
}

bool LogoScene::init()
{
	if ( !Layer::init() )
    {
        return false;
    }

	// 设置背景颜色
	auto backColorLayer = LayerColor::create( Color4B(111,180,227,255) , GAME_SCREEN_WIDTH , GAME_SCREEN_HEIGHT );
	this->addChild( backColorLayer);
	backColorLayer->setAnchorPoint( Point::ZERO );
	backColorLayer->setPosition( Point::ZERO );

	// 显示游戏名称
	auto labelGameName = Label::createWithSystemFont( GAME_NAME ,"Arial",80);
	backColorLayer->addChild(labelGameName);
	labelGameName->setColor(Color3B::WHITE);
	labelGameName->setAnchorPoint( Point::ANCHOR_MIDDLE );
	labelGameName->setPosition(Point( GAME_SCREEN_WIDTH/2 , GAME_SCREEN_HEIGHT-GAME_SCREEN_HEIGHT/4 ) );

	// 显示版权信息
	auto labelCopyright = Label::createWithSystemFont( GAME_COPYRIGHT ,"Arial",20);
	backColorLayer->addChild(labelCopyright);
	labelCopyright->setColor(Color3B::WHITE);
	labelCopyright->setAnchorPoint( Point::ANCHOR_MIDDLE );
	labelCopyright->setPosition(Point( GAME_SCREEN_WIDTH/2 , GAME_SCREEN_HEIGHT/4 ) );

	// 3秒后自动跳转到游戏界面
	this->scheduleOnce( schedule_selector( LogoScene::jumpToGame) , 3 );

	return	true;
}

void LogoScene::jumpToGame(float dt)
{
	// 加载游戏音效
	SimpleAudioEngine::getInstance()->preloadEffect("voice_move.wav"); 
	SimpleAudioEngine::getInstance()->preloadEffect("voice_combine.wav"); 

	// 场景切换
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene( TransitionCrossFade::create( 0.25f , scene ) );
}