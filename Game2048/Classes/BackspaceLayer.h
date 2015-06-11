/*
 * 作者：MWN		
 * 邮箱：modood@qq.com
 * 版本：1.0
 * 日期：2015年5月25日
 */

#ifndef __BACKSPACE_LAYER_H__
#define __BACKSPACE_LAYER_H__

#include "cocos2d.h"

class  BackspaceLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(BackspaceLayer);

    virtual bool init();

	void yesCallback(cocos2d::Ref* pSender);
	void noCallback(cocos2d::Ref* pSender);
};

#endif // __BACKSPACE_LAYER_H__
