/*
 * 作者：MWN		
 * 邮箱：modood@qq.com
 * 版本：1.0
 * 日期：2015年5月25日
 */

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameDefine.h"
#include "MoveableTiled.h"

class  GameScene : public cocos2d::Layer
{
public:
	GameScene();
    CREATE_FUNC(GameScene);
    static cocos2d::Scene* createScene();
    virtual bool init();  
	
	// 功能方法
	void addNewTiled(float dt);									// 添加一个新块
	void removeTiled(MoveableTiled * tiled);					// 移除一个数字块
	void addScore(int score);									// 增加分数	
	bool isGameOver();											// 游戏是否结束
	
	// 核心方法
	void moveAllTiled(E_MOVE_DIR direction);					// 移动所有块	
	
	// 回调函数
	void restartCallback(cocos2d::Ref* pSender);				// 重新开始按钮的回调函数
	void toggleSoundOnOff(cocos2d::Ref* pSender);				// 音效切换按钮的回调函数

	// 存储数据
	void saveGame();											// 保存游戏进度
	void continueGame();										// 加载游戏进度

private:
	cocos2d::LayerColor *					mBackColorGame;		// 游戏背景节点，用于addchild 数字块节点
	cocos2d::Vector<MoveableTiled* >		mAllTiled;			// 保存所有数字块，索引值保存在 mMap中
	int			mMap[GAME_ROWS][GAME_COLS];						// 网格列表：记录网格是否为空，0 表示空网格
	
	// 需要保存到本地的数据
	bool		mCanPlaySound;									// 是否播放音效
	int			mScore;											// 保存分数
	int			mBestScore;										// 最佳记录
	int			mData[GAME_ROWS][GAME_COLS];					// 数据列表：记录网格上数据块的值，用于存储游戏进度，0表示空网格

	// 临时用到的数据
	float		mX;												// 触摸初始点 X
	float		mY;												// 触摸初始点 Y
	bool		mIsStartMove;									// 是否开始移动，如果移动的位置大于 50 像素才认为是移动了
};

#endif // __GAME_SCENE_H__
