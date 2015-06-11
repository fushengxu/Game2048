/*
 * ���ߣ�MWN		
 * ���䣺modood@qq.com
 * �汾��1.0
 * ���ڣ�2015��5��25��
 */

#include "GameOverLayer.h"
#include "GameDefine.h"
#include "GameScene.h"

USING_NS_CC;

bool GameOverLayer::init()
{
	if ( !Layer::init() )
    {
        return false;
    }
	// ����UI
	auto backColor = LayerColor::create(Color4B::GRAY, GAME_WIDTH - 70 ,GAME_WIDTH /2 );
	this->addChild( backColor );
	backColor->ignoreAnchorPointForPosition( false );
	backColor->setAnchorPoint( Point::ANCHOR_MIDDLE );
	backColor->setPosition( Point( GAME_SCREEN_WIDTH/2 , GAME_SCREEN_HEIGHT/2 ) );

	auto labelTips = Label::createWithSystemFont("GAME OVER" ,"Arial",30);
	labelTips->setAnchorPoint( Point::ANCHOR_MIDDLE );
	labelTips->setPosition( Point( backColor->getContentSize().width/2 , backColor->getContentSize().height*3/4 ) );
	backColor->addChild(labelTips);

	auto itemYES = MenuItemFont::create("Restart",CC_CALLBACK_1(GameOverLayer::yesCallback, this));
	itemYES->setFontSizeObj(15);
	itemYES->setPosition( Point (60,40 ) );
	auto itemNO = MenuItemFont::create("Cancel",CC_CALLBACK_1(GameOverLayer::noCallback, this));
	itemNO->setFontSizeObj(15);
	itemNO->setPosition( Point ( backColor->getContentSize().width - 55 ,40 ) );

	auto menu  = Menu::create( itemYES , itemNO , NULL);
	backColor->addChild( menu );
	menu->setAnchorPoint(Point::ZERO);
	menu->setPosition(Point::ZERO);


	// �����´��ݴ���
	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = [&] ( Touch* t , Event* e)
	{
		return true;
	};
	eventListener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( eventListener , this );

	return true;
}

void GameOverLayer::yesCallback(cocos2d::Ref* pSender)
{
	// ���ñ��ر������Ϸ��¼
	UserDefault::getInstance()->setIntegerForKey("mScore",0);
	UserDefault::getInstance()->flush();

	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameOverLayer::noCallback(cocos2d::Ref* pSender)
{
	this->removeFromParentAndCleanup(true);
}