/*
 * ���ߣ�MWN		
 * ���䣺modood@qq.com
 * �汾��1.0
 * ���ڣ�2015��5��25��
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
	
	// ��ת����Ϸ���棺GameScene
	void jumpToGame(float dt);
};

#endif // __LOGO_SCENE_H__
