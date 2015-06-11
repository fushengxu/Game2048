/*
 * 作者：MWN		
 * 邮箱：modood@qq.com
 * 版本：1.0
 * 日期：2015年5月25日
 */

#include "RestartLayer.h"
#include "GameDefine.h"
#include "GameScene.h"

USING_NS_CC;

bool RestartLayer::init()
{
	if ( !Layer::init() )
    {
        return false;
    }
	// 设置UI
	auto backColor = LayerColor::create(Color4B::GRAY, GAME_WIDTH - 70 ,GAME_WIDTH /2 );
	this->addChild( backColor );
	backColor->ignoreAnchorPointForPosition( false );
	backColor->setAnchorPoint( Point::ANCHOR_MIDDLE );
	backColor->setPosition( Point( GAME_SCREEN_WIDTH/2 , GAME_SCREEN_HEIGHT/2 ) );

	auto labelTips = Label::createWithSystemFont("Are you sure to reset ?" ,"Arial",15);
	labelTips->setAnchorPoint( Point::ANCHOR_MIDDLE );
	labelTips->setPosition( Point( backColor->getContentSize().width/2 , backColor->getContentSize().height*3/4 ) );
	backColor->addChild(labelTips);

	auto itemYES = MenuItemFont::create("Yes",CC_CALLBACK_1(RestartLayer::yesCallback, this));
	itemYES->setFontSizeObj(20);
	itemYES->setPosition( Point (60,40 ) );
	auto itemNO = MenuItemFont::create("No",CC_CALLBACK_1(RestartLayer::noCallback, this));
	itemNO->setFontSizeObj(20);
	itemNO->setPosition( Point ( backColor->getContentSize().width - 60 ,40 ) );

	auto menu  = Menu::create( itemYES , itemNO , NULL);
	backColor->addChild( menu );
	menu->setAnchorPoint(Point::ZERO);
	menu->setPosition(Point::ZERO);


	// 不向下传递触摸
	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = [&] ( Touch* t , Event* e)
	{
		return true;
	};
	eventListener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( eventListener , this );

	return true;
}

void RestartLayer::yesCallback(cocos2d::Ref* pSender)
{
	// 重置本地保存的游戏记录
	UserDefault::getInstance()->setIntegerForKey("mScore",0);
	UserDefault::getInstance()->flush();

	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void RestartLayer::noCallback(cocos2d::Ref* pSender)
{
	this->removeFromParentAndCleanup(true);
}