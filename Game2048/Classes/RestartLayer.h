/*
 * ���ߣ�MWN		
 * ���䣺modood@qq.com
 * �汾��1.0
 * ���ڣ�2015��5��25��
 */

#ifndef __RESTART_LAYER_H__
#define __RESTART_LAYER_H__

#include "cocos2d.h"

class  RestartLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(RestartLayer);

    virtual bool init();

	void yesCallback(cocos2d::Ref* pSender);
	void noCallback(cocos2d::Ref* pSender);
};

#endif // __RESTART_LAYER_H__
