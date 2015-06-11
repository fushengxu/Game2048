/*
 * 作者：MWN		
 * 邮箱：modood@qq.com
 * 版本：1.0
 * 日期：2015年5月25日
 */

#ifndef __LOGO_SCENE_H__
#define __LOGO_SCENE_H__

#include "cocos2d.h"

class  LogoScene : public cocos2d::Layer
{
public:
	CREATE_FUNC(LogoScene);

    static cocos2d::Scene* createScene();

    virtual bool init();
	
	// 跳转到游戏界面：GameScene
	void jumpToGame(float dt);
};

#endif // __LOGO_SCENE_H__
