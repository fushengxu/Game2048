/*
 * ���ߣ�MWN		
 * ���䣺modood@qq.com
 * �汾��1.0
 * ���ڣ�2015��5��25��
 */

#ifndef __GAME_OVER_LAYER_H__
#define __GAME_OVER_LAYER_H__

#include "cocos2d.h"

class  GameOverLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(GameOverLayer);

    virtual bool init();

	void yesCallback(cocos2d::Ref* pSender);
	void noCallback(cocos2d::Ref* pSender);
};

#endif // __GAME_OVER_LAYER_H__
