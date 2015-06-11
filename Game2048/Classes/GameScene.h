/*
 * ���ߣ�MWN		
 * ���䣺modood@qq.com
 * �汾��1.0
 * ���ڣ�2015��5��25��
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
	
	// ���ܷ���
	void addNewTiled(float dt);									// ���һ���¿�
	void removeTiled(MoveableTiled * tiled);					// �Ƴ�һ�����ֿ�
	void addScore(int score);									// ���ӷ���	
	bool isGameOver();											// ��Ϸ�Ƿ����
	
	// ���ķ���
	void moveAllTiled(E_MOVE_DIR direction);					// �ƶ����п�	
	
	// �ص�����
	void restartCallback(cocos2d::Ref* pSender);				// ���¿�ʼ��ť�Ļص�����
	void toggleSoundOnOff(cocos2d::Ref* pSender);				// ��Ч�л���ť�Ļص�����

	// �洢����
	void saveGame();											// ������Ϸ����
	void continueGame();										// ������Ϸ����

private:
	cocos2d::LayerColor *					mBackColorGame;		// ��Ϸ�����ڵ㣬����addchild ���ֿ�ڵ�
	cocos2d::Vector<MoveableTiled* >		mAllTiled;			// �����������ֿ飬����ֵ������ mMap��
	int			mMap[GAME_ROWS][GAME_COLS];						// �����б���¼�����Ƿ�Ϊ�գ�0 ��ʾ������
	
	// ��Ҫ���浽���ص�����
	bool		mCanPlaySound;									// �Ƿ񲥷���Ч
	int			mScore;											// �������
	int			mBestScore;										// ��Ѽ�¼
	int			mData[GAME_ROWS][GAME_COLS];					// �����б���¼���������ݿ��ֵ�����ڴ洢��Ϸ���ȣ�0��ʾ������

	// ��ʱ�õ�������
	float		mX;												// ������ʼ�� X
	float		mY;												// ������ʼ�� Y
	bool		mIsStartMove;									// �Ƿ�ʼ�ƶ�������ƶ���λ�ô��� 50 ���ز���Ϊ���ƶ���
};

#endif // __GAME_SCENE_H__
