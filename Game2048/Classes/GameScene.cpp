/*
 * 作者：MWN		
 * 邮箱：modood@qq.com
 * 版本：1.0
 * 日期：2015年5月25日
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
	// 初始化数字块列表
	for( int r = 0 ; r < GAME_ROWS ; r++ )
	{
		for (int c = 0; c < GAME_COLS; c++)
		{
			mMap[r][c] = 0 ;
		}
	}

	// 读取最佳记录和音效设置
	this->mCanPlaySound = UserDefault::getInstance()->getBoolForKey("mCanPlaySound",true);
	this->mBestScore = UserDefault::getInstance()->getIntegerForKey("mBestScore",0);

	// 读取上次游戏退出时的数据
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
	
	// 1.设置场景背景颜色===========================================================================================
	auto backColorLayer = LayerColor::create( Color4B(250, 250, 240, 255) , GAME_SCREEN_WIDTH , GAME_SCREEN_HEIGHT );
	this->addChild(backColorLayer, 0 );
	backColorLayer->setAnchorPoint( Point::ZERO );
	backColorLayer->setPosition( Point::ZERO );

	// 2.显示游戏名称、游戏菜单================================================================================
	auto labelGameName = Label::createWithBMFont( GAME_NAME_FONT_PATH , GAME_NAME );
	this->addChild( labelGameName , 1  );
	labelGameName->setScale(1.2f);
	labelGameName->setAnchorPoint( Point::ZERO );
	labelGameName->setPosition( Point( (GAME_SCREEN_WIDTH - GAME_WIDTH )/2, GAME_SCREEN_HEIGHT - GAME_SCREEN_HEIGHT/5 ) );

	// 重新开始按钮
	auto itemRestart = MenuItemImage::create("restart_normal.png", "restart_selected.png" , CC_CALLBACK_1(GameScene::restartCallback, this) );
	itemRestart->setScale(0.35f);
	itemRestart->setOpacity(170);
	itemRestart->setAnchorPoint( Point::ANCHOR_BOTTOM_RIGHT );
	itemRestart->setPosition( Point( (GAME_SCREEN_WIDTH - GAME_WIDTH )/2 + GAME_WIDTH - 60 , GAME_SCREEN_HEIGHT - GAME_SCREEN_HEIGHT/6 - 1));

	// 音效开关按钮
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
	
	// 3.设置分数、最佳记录=================================================================================================
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


	// 4.设置游戏背景颜色(边框颜色)========================================================================================
	this->mBackColorGame = LayerColor::create(	Color4B(190, 175, 160, 255)	, GAME_WIDTH , GAME_HEIGHT );
	this->addChild( this->mBackColorGame , 1 );
	this->mBackColorGame->ignoreAnchorPointForPosition( false );
	this->mBackColorGame->setAnchorPoint( Point::ANCHOR_MIDDLE );
	this->mBackColorGame->setPosition( Point( GAME_SCREEN_WIDTH/2 , GAME_SCREEN_HEIGHT/2.5 ) );

	// 5.设置游戏网格背景颜色==============================================================================================
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

	// 6.如果第一次运行则生成第一个数字块，否则继续上次退出时的状态======================================================
	if ( this->mScore == 0 )
	{
		this->addNewTiled(0.0f);
	}else
	{
		this->continueGame();
	}

	// 7.触摸处理==========================================================================================================
	auto eventListenerTouch = EventListenerTouchOneByOne::create();
	eventListenerTouch->onTouchBegan = [&] ( Touch* t , Event* e)
	{
		// 记录开始触摸点
		this->mX = t->getLocation().x;
		this->mY = t->getLocation().y;
		this->mIsStartMove = false;
		return true;
	};

	eventListenerTouch->onTouchMoved = [&] ( Touch* t , Event* e)
	{
		auto x = t->getLocation().x;
		auto y = t->getLocation().y;

		// 如果移动的位置大于 50 像素才认为是移动了
		if ( !this->mIsStartMove && 
				( abs( this->mX - x ) > 50 || abs( this->mY - y ) > 50 ) )
		{
			this->mIsStartMove = true;
			E_MOVE_DIR direction ;
			if ( abs( this->mX - x ) >  abs( this->mY - y ) )	
			{
				if ( this->mX < x )
				{   // 向右移动
					direction = E_MOVE_DIR::RIGHT;

				}else
				{   // 向左移动
					direction = E_MOVE_DIR::LEFT;
				}
			}else   
			{
				if ( this->mY < y )
				{   // 向上移动
					direction = E_MOVE_DIR::UP;
				}else
				{   // 向下移动
					direction = E_MOVE_DIR::DOWN;
				}
			}
			this->moveAllTiled(direction);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( eventListenerTouch , this );

	// 8.返回键处理==========================================================================================================
	auto eventListenerKeyboard = EventListenerKeyboard::create();
	eventListenerKeyboard->onKeyReleased =[&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if(EventKeyboard::KeyCode::KEY_RETURN == keyCode || EventKeyboard::KeyCode::KEY_ESCAPE == keyCode || EventKeyboard::KeyCode::KEY_BACKSPACE == keyCode)
		{
			// 判断游戏中是否有对话框，有的话移除对话框；没有的话产生退出游戏对话框
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

void GameScene::addNewTiled(float dt)	// 有个 float 参数，是因为该方法要做为回调函数
{
	// 保存所有空网格
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
	// 随机选出一个空网格
	srand(time(NULL));
	int index = rand() % blankTiledVec.size();
	auto row =  blankTiledVec.at(index).row;
	auto col =  blankTiledVec.at(index).col;

	// 创建一个数字块，在指定的空网格上显示出来
	auto moveableTiled = MoveableTiled::create();
	moveableTiled->showAt( row , col );

	// 保存数字块信息
	mAllTiled.pushBack( moveableTiled );
	mMap[row][col] = mAllTiled.getIndex( moveableTiled ) + 1 ;  // +1 是因为第一个存入容器的mAllTiled索引为0，所以必须先+1
																// 因此，在调用 mAllTiled.at() 的时候必须对 mMap 中保存的值先-1
	this->mBackColorGame->addChild( moveableTiled , 1);

	// 保存游戏进度
	this->saveGame();

	// 实现新块产生后恢复触摸，防止bug:快速地移动两次只产生一个数字块
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this,true);
}


void GameScene::removeTiled(MoveableTiled * tiled)
{
	auto index = this->mAllTiled.getIndex( tiled );
	this->mAllTiled.erase(index);
	tiled->removeFromParentAndCleanup(true);
	// 纠正 mMap 中保存的索引值
	for (int r = 0; r < GAME_ROWS; r++)
	{
		for (int c = 0; c < GAME_COLS; c++)
		{
			if (mMap[r][c] > index + 1 )  // +1 是因为将索引存入mMap前是先+1的
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
		
		// 存储新记录
		UserDefault::getInstance()->setIntegerForKey("mBestScore",this->mBestScore);
		UserDefault::getInstance()->flush();

		auto labelBestScore = (Label *) this->getChildByTag(20);
		labelBestScore->setString( StringUtils::format( "BEST:%d" , this->mBestScore ) );
	}
}

bool GameScene::isGameOver()
{
	// 判断游戏中是否还有空网格可以添加数字块
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
	/* 游戏中已经没有空网格，判断是否可以移动（即是否有 相邻的 数字相等的 数字块）
	 * 算法：从左下角的数字块开始，判断该数字块的值与上方和右方的数字块的值是否相等
	 *		 最上方的行只判断右方的数字块的值
	 *		 最右方的列只判断上方的数字块的值
	 */

	// 判断上方和右方的数字块
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

	// 最上方的行只判断右方的数字块
	for (int c = 0; c < GAME_COLS - 1; c++)
	{
		if ( mAllTiled.at(mMap[GAME_ROWS-1][c]-1)->mNumber == mAllTiled.at(mMap[GAME_ROWS-1][c+1]-1)->mNumber )
		{
			return false;
		}
	}

	// 最右方的列只判断上方的数字块
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
	// 读取各数字块的值保存到本地
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
	// 保存数字块的值和分数（注意：只适应于 4 * 4 网格的游戏）
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
				// 创建一个数字块，在指定的空网格上显示出来
				auto moveableTiled = MoveableTiled::create();
				moveableTiled->showAt( r , c );
				moveableTiled->changeNumber(mData[r][c]);

				// 保存数字块信息
				mAllTiled.pushBack( moveableTiled );
				mMap[r][c] = mAllTiled.getIndex( moveableTiled ) + 1 ;  // +1 是因为第一个存入容器的mAllTiled索引为0，所以必须先+1
																			// 因此，在调用 mAllTiled.at() 的时候必须对 mMap 中保存的值先-1
				this->mBackColorGame->addChild( moveableTiled , 1);
			}
		}
	}
}

void GameScene::moveAllTiled(E_MOVE_DIR direction)
{
	/* 合并算法：1.靠前的合并，如：2 2 2 向左移动结果为 4 2
	 *			 2.一次滑动中同一个数字块只合并一次，如：2 2 4 向左移动结果为 4 4 而不是 8
	 */
	bool isChange = false;		// 判断是否移动或合并，如果没有则不产生新块
	bool isUpgrade = false;		// 判断是否有数字块合并，合并则播放合并音效，否则播放移动音效
	bool isCombine[GAME_ROWS][GAME_COLS] = {false};		// 用于记录合并过的块，实现同一数字块只合并一次
	switch (direction)
	{
	// 向上移动====================================================================================
	case E_MOVE_DIR::UP:
		for(int c = 0; c < GAME_COLS ; c++ )
		{
			for (int r = GAME_ROWS-2; r >= 0; r--)
			{
				if (mMap[r][c])
				{
					auto index = mMap[r][c];
					auto moveableTiled_s = mAllTiled.at( index - 1 ); // -1 是因为将索引存入mMap前是先+1的
					// 判断当前移动的块前方的网格是否为空，为空则移动
					while ( (r + 1 < GAME_ROWS) && (mMap[r+1][c] == 0) )
					{
						mMap[r+1][c] = index;
						mMap[r][c] = 0;
						moveableTiled_s->moveBy( 1 , 0 );
						r++;
						isChange = true;
					}
					// 判断当前移动的块前方的块在本次触摸中是否合并过
					if ( (r + 1 < GAME_ROWS) && (mMap[r+1][c] != 0) && !isCombine[r+1][c] )
					{
						auto moveableTiled_t = mAllTiled.at( mMap[r+1][c] - 1 );
						// 判断是否相同，相同则合并
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
	// 向下移动====================================================================================
	case E_MOVE_DIR::DOWN:
		for(int c = 0; c < GAME_COLS ; c++ )
		{
			for (int r = 1; r < GAME_ROWS; r++)
			{
				if (mMap[r][c])
				{
					auto index = mMap[r][c];
					auto moveableTiled_s = mAllTiled.at( index - 1 ); // -1 是因为将索引存入mMap前是先+1的
					while ( (r - 1 >= 0) && (mMap[r-1][c] == 0) )
					{
						mMap[r-1][c] = index;
						mMap[r][c] = 0;
						moveableTiled_s->moveBy( -1 , 0 );
						r--;
						isChange = true;
					}
					// 判断当前移动的块前方的块在本次触摸中是否合并过
					if ( (r - 1 >= 0) && (mMap[r-1][c] != 0) && !isCombine[r-1][c]  )
					{
						auto moveableTiled_t = mAllTiled.at( mMap[r-1][c] - 1 );
						// 判断是否相同，相同则合并
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
	// 向左移动====================================================================================
	case E_MOVE_DIR::LEFT:
		for(int r = 0; r < GAME_ROWS ; r++ )
		{
			for (int c = 1; c < GAME_COLS; c++)
			{
				if (mMap[r][c])
				{
					auto index = mMap[r][c];
					auto moveableTiled_s = mAllTiled.at( index - 1 ); // -1 是因为将索引存入mMap前是先+1的
					while ( (c - 1 >= 0) && (mMap[r][c - 1] == 0) )
					{
						mMap[r][c - 1] = index;
						mMap[r][c] = 0;
						moveableTiled_s->moveBy( 0 , -1 );
						c--;
						isChange = true;
					}
					// 判断当前移动的块前方的块在本次触摸中是否合并过
					if ( (c - 1 >= 0) && (mMap[r][c - 1] != 0) && !isCombine[r][c - 1]  )
					{
						auto moveableTiled_t = mAllTiled.at( mMap[r][c - 1] - 1 );
						// 判断是否相同，相同则合并
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
	// 向右移动====================================================================================
	case E_MOVE_DIR::RIGHT:
		for(int r = 0; r < GAME_ROWS ; r++ )
		{
			for (int c = GAME_COLS-2; c >= 0; c--)
			{
				if (mMap[r][c])
				{
					auto index = mMap[r][c];
					auto moveableTiled_s = mAllTiled.at( index - 1 ); // -1 是因为将索引存入mMap前是先+1的
					while ( (c + 1 < GAME_COLS) && (mMap[r][c+1] == 0) )
					{
						mMap[r][c+1] = index;
						mMap[r][c] = 0;
						moveableTiled_s->moveBy( 0 , 1 );
						c++;
						isChange = true;
					}
					// 判断当前移动的块前方的块在本次触摸中是否合并过
					if ( (c + 1 < GAME_COLS) && (mMap[r][c+1] != 0) && !isCombine[r][c+1] )
					{
						auto moveableTiled_t = mAllTiled.at( mMap[r][c + 1] - 1 );
						// 判断是否相同，相同则合并
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
	// 默认 ：错误 =================================================================================
	default:  // do nothing
		break;
	}
	// 添加新块、播放音效、判断游戏结束=============================================================
	if(isChange)
	{
		// 播放音效
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
		// 实现移动过程中暂停触摸，防止bug:快速地移动两次只产生一个数字块
		Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this,true);

		this->scheduleOnce( schedule_selector( GameScene::addNewTiled) , 0.20f );
	}else
	{
		// 判断游戏是否结束
		if (this->isGameOver())
		{
			auto layer = GameOverLayer::create();
			this->addChild(layer, 100);
			layer->setTag(2000);
		}
	}
}
