/*
 * 作者：MWN		
 * 邮箱：modood@qq.com
 * 版本：1.0
 * 日期：2015年5月25日
 */

#include "MoveableTiled.h"
#include "GameDefine.h"

USING_NS_CC;

bool MoveableTiled::init()
{
	if ( !Node::init() )
    {
        return false;
    }

	// 60%的概率产生2，40%的概率产生4
	this->mNumber = rand()%10 > 3 ? 2 : 4 ;	

	// 背景
	LayerColor * backColorTiled ;
	switch (this->mNumber)
	{
	case 2:		backColorTiled = LayerColor::create( GAME_COLOR_TILED_2 , GAME_TILED_WIDTH , GAME_TILED_HEIGHT );
				break;

	case 4:		backColorTiled = LayerColor::create( GAME_COLOR_TILED_4 , GAME_TILED_WIDTH , GAME_TILED_HEIGHT );
				break;

	default:	// do nothing
				break;
	}
	this->addChild( backColorTiled , 0 );
	backColorTiled->ignoreAnchorPointForPosition(false);
	backColorTiled->setAnchorPoint(Point::ANCHOR_MIDDLE);
	backColorTiled->setPosition(Point( GAME_TILED_WIDTH/2 , GAME_TILED_HEIGHT/2 ));
	backColorTiled->setTag(100);
	

	// 数字
	auto label = Label::createWithSystemFont( StringUtils::format( "%d" , this->mNumber ), "Arial" , 40 );
	this->addChild( label , 1 );
	label->setColor( Color3B(119,110,101) );
	label->setAnchorPoint( Point::ANCHOR_MIDDLE );
	label->setPosition( Point(	GAME_TILED_WIDTH/2 , GAME_TILED_HEIGHT/2 ) );
	label->setTag(200);

	return true;
}

void MoveableTiled::showAt( int row, int col)
{
	this->setPosition( Point(	GAME_TILED_WIDTH * col + GAME_TILED_BORDER * ( col + 1 ) ,
								GAME_TILED_WIDTH * row + GAME_TILED_BORDER * ( row + 1 ) ) );
}

void MoveableTiled::moveBy( int d_row, int d_col)
{
	this->runAction(MoveBy::create( 0.10f ,  Point(	(( GAME_TILED_WIDTH  + GAME_TILED_BORDER ) * d_col ) ,
													(( GAME_TILED_WIDTH  + GAME_TILED_BORDER ) * d_row )  ) ) );
}

void MoveableTiled::changeNumber(int value)
{
	// 数字块的值翻倍
	this->mNumber = value;

	auto label = (Label *) this->getChildByTag(200);
	label->setString( StringUtils::format( "%d" , this->mNumber ) );
	// 设置字体大小
	if (this->mNumber >= 16 )
	{
		label->setColor( Color3B::WHITE );
		if (this->mNumber <= 64)
		{
			label->setSystemFontSize(35);
		}
		else if ( this->mNumber >= 128 && this->mNumber <= 512)
		{
			label->setSystemFontSize(30);
		}
		else if ( this->mNumber >= 1024 && this->mNumber <= 8192)
		{
			label->setSystemFontSize(25);
		}
		else if ( this->mNumber >= 16384)
		{
			label->setSystemFontSize(20);
		}
	}

	// 移除旧的背景颜色
	auto backColorTiled_old = (LayerColor *) this->getChildByTag(100);
	backColorTiled_old->removeFromParentAndCleanup(true);
	// 添加新的背景颜色
	LayerColor * backColorTiled ;
	switch (this->mNumber)
	{
	case 2:			backColorTiled = LayerColor::create( GAME_COLOR_TILED_2 ,	 GAME_TILED_WIDTH , GAME_TILED_HEIGHT );break;
	case 4:			backColorTiled = LayerColor::create( GAME_COLOR_TILED_4 ,	 GAME_TILED_WIDTH , GAME_TILED_HEIGHT );break;
	case 8:			backColorTiled = LayerColor::create( GAME_COLOR_TILED_8 ,	 GAME_TILED_WIDTH , GAME_TILED_HEIGHT );break;
	case 16:		backColorTiled = LayerColor::create( GAME_COLOR_TILED_16 ,	 GAME_TILED_WIDTH , GAME_TILED_HEIGHT );break;
	case 32:		backColorTiled = LayerColor::create( GAME_COLOR_TILED_32 ,	 GAME_TILED_WIDTH , GAME_TILED_HEIGHT );break;
	case 64:		backColorTiled = LayerColor::create( GAME_COLOR_TILED_64 ,	 GAME_TILED_WIDTH , GAME_TILED_HEIGHT );break;
	case 128:		backColorTiled = LayerColor::create( GAME_COLOR_TILED_128 ,  GAME_TILED_WIDTH , GAME_TILED_HEIGHT );break;
	case 256:		backColorTiled = LayerColor::create( GAME_COLOR_TILED_256 ,	 GAME_TILED_WIDTH , GAME_TILED_HEIGHT );break;
	case 512:		backColorTiled = LayerColor::create( GAME_COLOR_TILED_512 ,	 GAME_TILED_WIDTH , GAME_TILED_HEIGHT );break;
	case 1024:		backColorTiled = LayerColor::create( GAME_COLOR_TILED_1024 , GAME_TILED_WIDTH , GAME_TILED_HEIGHT );break;
	case 2048:		backColorTiled = LayerColor::create( GAME_COLOR_TILED_2048 , GAME_TILED_WIDTH , GAME_TILED_HEIGHT );break;
	default:		backColorTiled = LayerColor::create( GAME_COLOR_TILED_4096 , GAME_TILED_WIDTH , GAME_TILED_HEIGHT );break;
	}
	this->addChild( backColorTiled , 0 );
	backColorTiled->ignoreAnchorPointForPosition(false);
	backColorTiled->setAnchorPoint(Point::ANCHOR_MIDDLE);
	backColorTiled->setPosition(Point( GAME_TILED_WIDTH/2 , GAME_TILED_HEIGHT/2 ));
	backColorTiled->setTag(100);
}
void MoveableTiled::blinking()
{	
	auto backColorTiled = (LayerColor *) this->getChildByTag(100);
	// 合并时产生先放大再恢复的特效
	auto seqAct = Sequence::create( ScaleTo::create(0.05f,1.25f) , ScaleTo::create(0.05f,1.0f) , NULL );
	backColorTiled->runAction(seqAct);
}