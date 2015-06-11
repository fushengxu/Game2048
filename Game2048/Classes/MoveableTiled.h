/*
 * 作者：MWN		
 * 邮箱：modood@qq.com
 * 版本：1.0
 * 日期：2015年5月25日
 */

#ifndef __MOVEABLE_TILED_H__
#define __MOVEABLE_TILED_H__

#include "cocos2d.h"

class  MoveableTiled : public cocos2d::Node
{
public:

    CREATE_FUNC(MoveableTiled);

    virtual bool init(); 

	void showAt( int row, int col);					// 显示在 r 行 c 列
	void moveBy( int d_row, int d_col);				// 移动 r 行 c 列（相对移动，不是绝对移动）
	void changeNumber(int value);					// 合并升级
	void blinking();								// 闪烁，合并时调用

	int mNumber;									// 数字						
};

#endif // __MOVEABLE_TILED_H__