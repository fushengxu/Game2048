/*
 * ���ߣ�MWN		
 * ���䣺modood@qq.com
 * �汾��1.0
 * ���ڣ�2015��5��25��
 */

#include "GameScene.h"
#include "GameDefine.h"
#include "MoveableTiled.h"
#include "SimpleAudioEngine.h"
#include "RestartLayer.h"
#include "GameOverLayer.h"
#include "BackspaceLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

GameScene::GameScene()
{
	// ��ʼ�����ֿ��б�
	for( int r = 0 ; r < GAME_ROWS ; r++ )
	{
		for (int c = 0; c < GAME_COLS; c++)
		{
			mMap[r][c] = 0 ;
		}
	}

	// ��ȡ��Ѽ�¼����Ч����
	this->mCanPlaySound = UserDefault::getInstance()->getBoolForKey("mCanPlaySound",true);
	this->mBestScore = UserDefault::getInstance()->getIntegerForKey("mBestScore",0);

	// ��ȡ�ϴ���Ϸ�˳�ʱ������
	this->mScore = UserDefault::getInstance()->getIntegerForKey("mScore",0);
	mData[0][0] = UserDefault::getInstance()->getIntegerForKey("00",0);
	mData[0][1] = UserDefault::getInstance()->getIntegerForKey("01",0);
	mData[0][2] = UserDefault::getInstance()->getIntegerForKey("02",0);
	mData[0][3] = UserDefault::getInstance()->getIntegerForKey("03",0);

	mData[1][0] = UserDefault::getInstance()->getIntegerForKey("10",0);
	mData[1][1] = UserDefault::getInstance()->getIntegerForKey("11",0);
	mData[1][2] = UserDefault::getInstance()->getIntegerForKey("12",0);
	mData[1][3] = UserDefault::getInstance()->getIntegerForKey("13",0);

	mData[2][0] = UserDefault::getInstance()->getIntegerForKey("20",0);
	mData[2][1] = UserDefault::getInstance()->getIntegerForKey("21",0);
	mData[2][2] = UserDefault::getInstance()->getIntegerForKey("22",0);
	mData[2][3] = UserDefault::getInstance()->getIntegerForKey("23",0);

	mData[3][0] = UserDefault::getInstance()->getIntegerForKey("30",0);
	mData[3][1] = UserDefault::getInstance()->getIntegerForKey("31",0);
	mData[3][2] = UserDefault::getInstance()->getIntegerForKey("32",0);
	mData[3][3] = UserDefault::getInstance()->getIntegerForKey("33",0);
	
}

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
	if ( !Layer::init() )
    {
        return false;
    }
	
	// 1.���ó���������ɫ===========================================================================================
	auto backColorLayer = LayerColor::create( Color4B(250, 250, 240, 255) , GAME_SCREEN_WIDTH , GAME_SCREEN_HEIGHT );
	this->addChild(backColorLayer, 0 );
	backColorLayer->setAnchorPoint( Point::ZERO );
	backColorLayer->setPosition( Point::ZERO );

	// 2.��ʾ��Ϸ���ơ���Ϸ�˵�================================================================================
	auto labelGameName = Label::createWithBMFont( GAME_NAME_FONT_PATH , GAME_NAME );
	this->addChild( labelGameName , 1  );
	labelGameName->setScale(1.2f);
	labelGameName->setAnchorPoint( Point::ZERO );
	labelGameName->setPosition( Point( (GAME_SCREEN_WIDTH - GAME_WIDTH )/2, GAME_SCREEN_HEIGHT - GAME_SCREEN_HEIGHT/5 ) );

	// ���¿�ʼ��ť
	auto itemRestart = MenuItemImage::create("restart_normal.png", "restart_selected.png" , CC_CALLBACK_1(GameScene::restartCallback, this) );
	itemRestart->setScale(0.35f);
	itemRestart->setOpacity(170);
	itemRestart->setAnchorPoint( Point::ANCHOR_BOTTOM_RIGHT );
	itemRestart->setPosition( Point( (GAME_SCREEN_WIDTH - GAME_WIDTH )/2 + GAME_WIDTH - 60 , GAME_SCREEN_HEIGHT - GAME_SCREEN_HEIGHT/6 - 1));

	// ��Ч���ذ�ť
	auto itemSoundOn = MenuItemImage::create("sound_on.png","sound_on.png" );
	auto itemSoundOff = MenuItemImage::create("sound_off.png","sound_off.png" );
	itemSoundOn->setOpacity(170);
	itemSoundOff->setOpacity(170);
	MenuItemToggle * itemSoundToggle;
	if ( this->mCanPlaySound )
	{
		itemSoundToggle = MenuItemToggle::createWithCallback(	CC_CALLBACK_1(GameScene::toggleSoundOnOff, this), itemSoundOn , itemSoundOff ,NULL  );
	}
	else
	{
		itemSoundToggle = MenuItemToggle::createWithCallback(	CC_CALLBACK_1(GameScene::toggleSoundOnOff, this), itemSoundOff , itemSoundOn,NULL  );
	}
	itemSoundToggle->setScale(0.35f);
	itemSoundToggle->setAnchorPoint( Point::ANCHOR_BOTTOM_RIGHT );
	itemSoundToggle->setPosition( Point( (GAME_SCREEN_WIDTH - GAME_WIDTH )/2 + GAME_WIDTH , GAME_SCREEN_HEIGHT - GAME_SCREEN_HEIGHT/6) );

	auto menu = Menu::create( itemRestart , itemSoundToggle  ,NULL );
	menu->setAnchorPoint(Point::ZERO);
	menu->setPosition(Point::ZERO);
	this->addChild( menu , 1);
	
	// 3.���÷�������Ѽ�¼=================================================================================================
	auto labelScore = Label::createWithSystemFont( StringUtils::format( "SCORE:%d" , this->mScore ), "Arial" , 20 );
	this->addChild( labelScore , 1 );
	labelScore->setTag(10);
	labelScore->setColor(Color3B::GRAY);
	labelScore->setAnchorPoint( Point::ZERO );
	labelScore->setPosition(Point( (GAME_SCREEN_WIDTH - GAME_WIDTH )/2 , GAME_SCREEN_HEIGHT - GAME_SCREEN_HEIGHT/4 ) );
	
	auto labelBestScore = Label::createWithSystemFont( StringUtils::format( "BEST:%d" , this->mBestScore ), "Arial" , 20 );
	this->addChild( labelBestScore , 1 );
	labelBestScore->setTag(20);
	labelBestScore->setColor(Color3B::GRAY);
	labelBestScore->setAnchorPoint( Point::ANCHOR_BOTTOM_RIGHT );
	labelBestScore->setPosition(Point( (GAME_SCREEN_WIDTH - GAME_WIDTH )/2 + GAME_WIDTH , GAME_SCREEN_HEIGHT - GAME_SCREEN_HEIGHT/4 ) );


	// 4.������Ϸ������ɫ(�߿���ɫ)========================================================================================
	this->mBackColorGame = LayerColor::create(	Color4B(190, 175, 160, 255)	, GAME_WIDTH , GAME_HEIGHT );
	this->addChild( this->mBackColorGame , 1 );
	this->mBackColorGame->ignoreAnchorPointForPosition( false );
	this->mBackColorGame->setAnchorPoint( Point::ANCHOR_MIDDLE );
	this->mBackColorGame->setPosition( Point( GAME_SCREEN_WIDTH/2 , GAME_SCREEN_HEIGHT/2.5 ) );

	// 5.������Ϸ���񱳾���ɫ==============================================================================================
	for ( int row = 0; row < GAME_ROWS; row++)
	{
		for (int col = 0; col < GAME_COLS; col++)
		{
			auto backColorTiled = LayerColor::create( Color4B(205, 190, 180, 255) , GAME_TILED_WIDTH , GAME_TILED_HEIGHT);
			this->mBackColorGame->addChild( backColorTiled , 0 );
			backColorTiled->setAnchorPoint( Point::ZERO );
			backColorTiled->setPosition( Point( GAME_TILED_WIDTH  * col + GAME_TILED_BORDER * ( col + 1 ) ,
												GAME_TILED_HEIGHT * row + GAME_TILED_BORDER * ( row + 1 ) ) );
		}
	}

	// 6.�����һ�����������ɵ�һ�����ֿ飬��������ϴ��˳�ʱ��״̬======================================================
	if ( this->mScore == 0 )
	{
		this->addNewTiled(0.0f);
	}else
	{
		this->continueGame();
	}

	// 7.��������==========================================================================================================
	auto eventListenerTouch = EventListenerTouchOneByOne::create();
	eventListenerTouch->onTouchBegan = [&] ( Touch* t , Event* e)
	{
		// ��¼��ʼ������
		this->mX = t->getLocation().x;
		this->mY = t->getLocation().y;
		this->mIsStartMove = false;
		return true;
	};

	eventListenerTouch->onTouchMoved = [&] ( Touch* t , Event* e)
	{
		auto x = t->getLocation().x;
		auto y = t->getLocation().y;

		// ����ƶ���λ�ô��� 50 ���ز���Ϊ���ƶ���
		if ( !this->mIsStartMove && 
				( abs( this->mX - x ) > 50 || abs( this->mY - y ) > 50 ) )
		{
			this->mIsStartMove = true;
			E_MOVE_DIR direction ;
			if ( abs( this->mX - x ) >  abs( this->mY - y ) )	
			{
				if ( this->mX < x )
				{   // �����ƶ�
					direction = E_MOVE_DIR::RIGHT;

				}else
				{   // �����ƶ�
					direction = E_MOVE_DIR::LEFT;
				}
			}else   
			{
				if ( this->mY < y )
				{   // �����ƶ�
					direction = E_MOVE_DIR::UP;
				}else
				{   // �����ƶ�
					direction = E_MOVE_DIR::DOWN;
				}
			}
			this->moveAllTiled(direction);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( eventListenerTouch , this );

	// 8.���ؼ�����==========================================================================================================
	auto eventListenerKeyboard = EventListenerKeyboard::create();
	eventListenerKeyboard->onKeyReleased =[&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if(EventKeyboard::KeyCode::KEY_RETURN == keyCode || EventKeyboard::KeyCode::KEY_ESCAPE == keyCode || EventKeyboard::KeyCode::KEY_BACKSPACE == keyCode)
		{
			// �ж���Ϸ���Ƿ��жԻ����еĻ��Ƴ��Ի���û�еĻ������˳���Ϸ�Ի���
			if ( this->getChildByTag(1000) )
			{
				this->getChildByTag(1000)->removeFromParentAndCleanup(true);
			}
			else if ( this->getChildByTag(2000) )
			{
				this->getChildByTag(2000)->removeFromParentAndCleanup(true);
			}
			else if ( this->getChildByTag(3000) )
			{
				this->getChildByTag(3000)->removeFromParentAndCleanup(true);
			}
			else
			{
				auto layer = BackspaceLayer::create();
				this->addChild(layer, 100);
				layer->setTag(3000);
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( eventListenerKeyboard , this );

	return true;
}

void GameScene::addNewTiled(float dt)	// �и� float ����������Ϊ�÷���Ҫ��Ϊ�ص�����
{
	// �������п�����
	std::vector<BlankTiled> blankTiledVec;	
	for( int r = 0 ; r < GAME_ROWS ; r++ )
	{
		for (int c = 0; c < GAME_COLS; c++)
		{
			if (mMap[r][c] == 0 )
			{
				BlankTiled blankTiled = { r , c };
				blankTiledVec.push_back(blankTiled);
			}
		}
	}
	// ���ѡ��һ��������
	srand(time(NULL));
	int index = rand() % blankTiledVec.size();
	auto row =  blankTiledVec.at(index).row;
	auto col =  blankTiledVec.at(index).col;

	// ����һ�����ֿ飬��ָ���Ŀ���������ʾ����
	auto moveableTiled = MoveableTiled::create();
	moveableTiled->showAt( row , col );

	// �������ֿ���Ϣ
	mAllTiled.pushBack( moveableTiled );
	mMap[row][col] = mAllTiled.getIndex( moveableTiled ) + 1 ;  // +1 ����Ϊ��һ������������mAllTiled����Ϊ0�����Ա�����+1
																// ��ˣ��ڵ��� mAllTiled.at() ��ʱ������ mMap �б����ֵ��-1
	this->mBackColorGame->addChild( moveableTiled , 1);

	// ������Ϸ����
	this->saveGame();

	// ʵ���¿������ָ���������ֹbug:���ٵ��ƶ�����ֻ����һ�����ֿ�
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this,true);
}


void GameScene::removeTiled(MoveableTiled * tiled)
{
	auto index = this->mAllTiled.getIndex( tiled );
	this->mAllTiled.erase(index);
	tiled->removeFromParentAndCleanup(true);
	// ���� mMap �б��������ֵ
	for (int r = 0; r < GAME_ROWS; r++)
	{
		for (int c = 0; c < GAME_COLS; c++)
		{
			if (mMap[r][c] > index + 1 )  // +1 ����Ϊ����������mMapǰ����+1��
			{
				mMap[r][c] --;
			}
			 
		}
	}
}

void GameScene::addScore(int score)
{
	this->mScore += score;
	auto labelScore = (Label *) this->getChildByTag(10);
	labelScore->setString( StringUtils::format( "SCORE:%d" , this->mScore ) );
	if (this->mScore > this->mBestScore )
	{
		this->mBestScore = this->mScore ;
		
		// �洢�¼�¼
		UserDefault::getInstance()->setIntegerForKey("mBestScore",this->mBestScore);
		UserDefault::getInstance()->flush();

		auto labelBestScore = (Label *) this->getChildByTag(20);
		labelBestScore->setString( StringUtils::format( "BEST:%d" , this->mBestScore ) );
	}
}

bool GameScene::isGameOver()
{
	// �ж���Ϸ���Ƿ��п��������������ֿ�
	for (int r = 0; r < GAME_ROWS; r++)
	{
		for (int c = 0; c < GAME_COLS; c++)
		{
			if ( mMap[r][c] == 0 )
			{
				return false;
			}
		}
	}
	/* ��Ϸ���Ѿ�û�п������ж��Ƿ�����ƶ������Ƿ��� ���ڵ� ������ȵ� ���ֿ飩
	 * �㷨�������½ǵ����ֿ鿪ʼ���жϸ����ֿ��ֵ���Ϸ����ҷ������ֿ��ֵ�Ƿ����
	 *		 ���Ϸ�����ֻ�ж��ҷ������ֿ��ֵ
	 *		 ���ҷ�����ֻ�ж��Ϸ������ֿ��ֵ
	 */

	// �ж��Ϸ����ҷ������ֿ�
	for (int r = 0; r < GAME_ROWS - 1; r++)
	{
		for (int c = 0; c < GAME_COLS - 1 ; c++)
		{
			if (	 ( mAllTiled.at(mMap[r][c]-1)->mNumber == mAllTiled.at(mMap[r+1][c]-1)->mNumber )
				  || ( mAllTiled.at(mMap[r][c]-1)->mNumber == mAllTiled.at(mMap[r][c+1]-1)->mNumber ) )
			{
				return false;
			} 
		}
	}

	// ���Ϸ�����ֻ�ж��ҷ������ֿ�
	for (int c = 0; c < GAME_COLS - 1; c++)
	{
		if ( mAllTiled.at(mMap[GAME_ROWS-1][c]-1)->mNumber == mAllTiled.at(mMap[GAME_ROWS-1][c+1]-1)->mNumber )
		{
			return false;
		}
	}

	// ���ҷ�����ֻ�ж��Ϸ������ֿ�
	for (int r = 0; r < GAME_ROWS - 1; r++)
	{
		if ( mAllTiled.at(mMap[r][GAME_COLS-1]-1)->mNumber == mAllTiled.at(mMap[r+1][GAME_COLS-1]-1)->mNumber )
		{
			return false;
		}
	}
	return true;
}

void GameScene::restartCallback(cocos2d::Ref* pSender)
{
	auto layer = RestartLayer::create();
	this->addChild(layer, 100);
	layer->setTag(1000);
}

void GameScene::toggleSoundOnOff(cocos2d::Ref* pSender)
{
	if (this->mCanPlaySound)
	{
		this->mCanPlaySound = false;
	}else
	{
		this->mCanPlaySound = true;
	}
	UserDefault::getInstance()->setBoolForKey("mCanPlaySound", this->mCanPlaySound );
	UserDefault::getInstance()->flush();
}

void GameScene::saveGame()
{
	// ��ȡ�����ֿ��ֵ���浽����
	for (int r = 0; r < GAME_ROWS; r++)
	{
		for (int c = 0; c < GAME_COLS; c++)
		{
			if ( mMap[r][c] == 0 )
			{
				mData[r][c] = 0;
			}else
			{
				
				mData[r][c] = mAllTiled.at(mMap[r][c] - 1 )->mNumber;
			}
		}
	}
	// �������ֿ��ֵ�ͷ�����ע�⣺ֻ��Ӧ�� 4 * 4 �������Ϸ��
	UserDefault::getInstance()->setIntegerForKey("00",mData[0][0]);
	UserDefault::getInstance()->setIntegerForKey("01",mData[0][1]);
	UserDefault::getInstance()->setIntegerForKey("02",mData[0][2]);
	UserDefault::getInstance()->setIntegerForKey("03",mData[0][3]);

	UserDefault::getInstance()->setIntegerForKey("10",mData[1][0]);
	UserDefault::getInstance()->setIntegerForKey("11",mData[1][1]);
	UserDefault::getInstance()->setIntegerForKey("12",mData[1][2]);
	UserDefault::getInstance()->setIntegerForKey("13",mData[1][3]);

	UserDefault::getInstance()->setIntegerForKey("20",mData[2][0]);
	UserDefault::getInstance()->setIntegerForKey("21",mData[2][1]);
	UserDefault::getInstance()->setIntegerForKey("22",mData[2][2]);
	UserDefault::getInstance()->setIntegerForKey("23",mData[2][3]);

	UserDefault::getInstance()->setIntegerForKey("30",mData[3][0]);
	UserDefault::getInstance()->setIntegerForKey("31",mData[3][1]);
	UserDefault::getInstance()->setIntegerForKey("32",mData[3][2]);
	UserDefault::getInstance()->setIntegerForKey("33",mData[3][3]);

	UserDefault::getInstance()->setIntegerForKey("mScore",this->mScore);
	UserDefault::getInstance()->flush();
}

void GameScene::continueGame()
{
	for (int r = 0; r < GAME_ROWS; r++)
	{
		for (int c = 0; c < GAME_COLS; c++)
		{
			if ( mData[r][c] != 0 )
			{
				// ����һ�����ֿ飬��ָ���Ŀ���������ʾ����
				auto moveableTiled = MoveableTiled::create();
				moveableTiled->showAt( r , c );
				moveableTiled->changeNumber(mData[r][c]);

				// �������ֿ���Ϣ
				mAllTiled.pushBack( moveableTiled );
				mMap[r][c] = mAllTiled.getIndex( moveableTiled ) + 1 ;  // +1 ����Ϊ��һ������������mAllTiled����Ϊ0�����Ա�����+1
																			// ��ˣ��ڵ��� mAllTiled.at() ��ʱ������ mMap �б����ֵ��-1
				this->mBackColorGame->addChild( moveableTiled , 1);
			}
		}
	}
}

void GameScene::moveAllTiled(E_MOVE_DIR direction)
{
	/* �ϲ��㷨��1.��ǰ�ĺϲ����磺2 2 2 �����ƶ����Ϊ 4 2
	 *			 2.һ�λ�����ͬһ�����ֿ�ֻ�ϲ�һ�Σ��磺2 2 4 �����ƶ����Ϊ 4 4 ������ 8
	 */
	bool isChange = false;		// �ж��Ƿ��ƶ���ϲ������û���򲻲����¿�
	bool isUpgrade = false;		// �ж��Ƿ������ֿ�ϲ����ϲ��򲥷źϲ���Ч�����򲥷��ƶ���Ч
	bool isCombine[GAME_ROWS][GAME_COLS] = {false};		// ���ڼ�¼�ϲ����Ŀ飬ʵ��ͬһ���ֿ�ֻ�ϲ�һ��
	switch (direction)
	{
	// �����ƶ�====================================================================================
	case E_MOVE_DIR::UP:
		for(int c = 0; c < GAME_COLS ; c++ )
		{
			for (int r = GAME_ROWS-2; r >= 0; r--)
			{
				if (mMap[r][c])
				{
					auto index = mMap[r][c];
					auto moveableTiled_s = mAllTiled.at( index - 1 ); // -1 ����Ϊ����������mMapǰ����+1��
					// �жϵ�ǰ�ƶ��Ŀ�ǰ���������Ƿ�Ϊ�գ�Ϊ�����ƶ�
					while ( (r + 1 < GAME_ROWS) && (mMap[r+1][c] == 0) )
					{
						mMap[r+1][c] = index;
						mMap[r][c] = 0;
						moveableTiled_s->moveBy( 1 , 0 );
						r++;
						isChange = true;
					}
					// �жϵ�ǰ�ƶ��Ŀ�ǰ���Ŀ��ڱ��δ������Ƿ�ϲ���
					if ( (r + 1 < GAME_ROWS) && (mMap[r+1][c] != 0) && !isCombine[r+1][c] )
					{
						auto moveableTiled_t = mAllTiled.at( mMap[r+1][c] - 1 );
						// �ж��Ƿ���ͬ����ͬ��ϲ�
						if ( moveableTiled_t->mNumber == moveableTiled_s->mNumber )
						{
							mMap[r][c] = 0;
							isChange = true;
							isUpgrade = true ;
							isCombine[r+1][c] = true;
							
							moveableTiled_t->changeNumber( moveableTiled_t->mNumber*2 );
							moveableTiled_t->blinking();

							this->addScore(moveableTiled_t->mNumber);

							this->removeTiled(moveableTiled_s);
						}
					}
				}
			}
		}
		break;
	// �����ƶ�====================================================================================
	case E_MOVE_DIR::DOWN:
		for(int c = 0; c < GAME_COLS ; c++ )
		{
			for (int r = 1; r < GAME_ROWS; r++)
			{
				if (mMap[r][c])
				{
					auto index = mMap[r][c];
					auto moveableTiled_s = mAllTiled.at( index - 1 ); // -1 ����Ϊ����������mMapǰ����+1��
					while ( (r - 1 >= 0) && (mMap[r-1][c] == 0) )
					{
						mMap[r-1][c] = index;
						mMap[r][c] = 0;
						moveableTiled_s->moveBy( -1 , 0 );
						r--;
						isChange = true;
					}
					// �жϵ�ǰ�ƶ��Ŀ�ǰ���Ŀ��ڱ��δ������Ƿ�ϲ���
					if ( (r - 1 >= 0) && (mMap[r-1][c] != 0) && !isCombine[r-1][c]  )
					{
						auto moveableTiled_t = mAllTiled.at( mMap[r-1][c] - 1 );
						// �ж��Ƿ���ͬ����ͬ��ϲ�
						if ( moveableTiled_t->mNumber == moveableTiled_s->mNumber )
						{
							mMap[r][c] = 0;
							isChange = true;
							isUpgrade = true ;
							isCombine[r-1][c] = true;
							
							moveableTiled_t->changeNumber( moveableTiled_t->mNumber*2 );
							moveableTiled_t->blinking();

							this->addScore(moveableTiled_t->mNumber);

							this->removeTiled(moveableTiled_s);
						}
					}
				}
			}
		}
		break;
	// �����ƶ�====================================================================================
	case E_MOVE_DIR::LEFT:
		for(int r = 0; r < GAME_ROWS ; r++ )
		{
			for (int c = 1; c < GAME_COLS; c++)
			{
				if (mMap[r][c])
				{
					auto index = mMap[r][c];
					auto moveableTiled_s = mAllTiled.at( index - 1 ); // -1 ����Ϊ����������mMapǰ����+1��
					while ( (c - 1 >= 0) && (mMap[r][c - 1] == 0) )
					{
						mMap[r][c - 1] = index;
						mMap[r][c] = 0;
						moveableTiled_s->moveBy( 0 , -1 );
						c--;
						isChange = true;
					}
					// �жϵ�ǰ�ƶ��Ŀ�ǰ���Ŀ��ڱ��δ������Ƿ�ϲ���
					if ( (c - 1 >= 0) && (mMap[r][c - 1] != 0) && !isCombine[r][c - 1]  )
					{
						auto moveableTiled_t = mAllTiled.at( mMap[r][c - 1] - 1 );
						// �ж��Ƿ���ͬ����ͬ��ϲ�
						if ( moveableTiled_t->mNumber == moveableTiled_s->mNumber )
						{
							mMap[r][c] = 0;
							isChange = true;
							isUpgrade = true ;
							isCombine[r][c - 1] = true;
							
							moveableTiled_t->changeNumber( moveableTiled_t->mNumber*2 );
							moveableTiled_t->blinking();

							this->addScore(moveableTiled_t->mNumber);

							this->removeTiled(moveableTiled_s);
						}
					}
				}
			}
		}
		break;
	// �����ƶ�====================================================================================
	case E_MOVE_DIR::RIGHT:
		for(int r = 0; r < GAME_ROWS ; r++ )
		{
			for (int c = GAME_COLS-2; c >= 0; c--)
			{
				if (mMap[r][c])
				{
					auto index = mMap[r][c];
					auto moveableTiled_s = mAllTiled.at( index - 1 ); // -1 ����Ϊ����������mMapǰ����+1��
					while ( (c + 1 < GAME_COLS) && (mMap[r][c+1] == 0) )
					{
						mMap[r][c+1] = index;
						mMap[r][c] = 0;
						moveableTiled_s->moveBy( 0 , 1 );
						c++;
						isChange = true;
					}
					// �жϵ�ǰ�ƶ��Ŀ�ǰ���Ŀ��ڱ��δ������Ƿ�ϲ���
					if ( (c + 1 < GAME_COLS) && (mMap[r][c+1] != 0) && !isCombine[r][c+1] )
					{
						auto moveableTiled_t = mAllTiled.at( mMap[r][c + 1] - 1 );
						// �ж��Ƿ���ͬ����ͬ��ϲ�
						if ( moveableTiled_t->mNumber == moveableTiled_s->mNumber )
						{
							mMap[r][c] = 0;
							isChange = true;
							isUpgrade = true ;
							isCombine[r][c+1] = true;

							moveableTiled_t->changeNumber( moveableTiled_t->mNumber*2 );
							moveableTiled_t->blinking();

							this->addScore(moveableTiled_t->mNumber);

							this->removeTiled(moveableTiled_s);
						}
					}
				}
			}
		}
		break;
	// Ĭ�� ������ =================================================================================
	default:  // do nothing
		break;
	}
	// ����¿顢������Ч���ж���Ϸ����=============================================================
	if(isChange)
	{
		// ������Ч
		if (this->mCanPlaySound)
		{
			if (isUpgrade)
			{
				SimpleAudioEngine::getInstance()->playEffect("voice_combine.wav");
			}else
			{
				SimpleAudioEngine::getInstance()->playEffect("voice_move.wav");
			}
		}
		// ʵ���ƶ���������ͣ��������ֹbug:���ٵ��ƶ�����ֻ����һ�����ֿ�
		Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this,true);

		this->scheduleOnce( schedule_selector( GameScene::addNewTiled) , 0.20f );
	}else
	{
		// �ж���Ϸ�Ƿ����
		if (this->isGameOver())
		{
			auto layer = GameOverLayer::create();
			this->addChild(layer, 100);
			layer->setTag(2000);
		}
	}
}
