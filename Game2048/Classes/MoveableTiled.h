/*
 * ���ߣ�MWN		
 * ���䣺modood@qq.com
 * �汾��1.0
 * ���ڣ�2015��5��25��
 */

#ifndef __MOVEABLE_TILED_H__
#define __MOVEABLE_TILED_H__

#include "cocos2d.h"

class  MoveableTiled : public cocos2d::Node
{
public:

    CREATE_FUNC(MoveableTiled);

    virtual bool init(); 

	void showAt( int row, int col);					// ��ʾ�� r �� c ��
	void moveBy( int d_row, int d_col);				// �ƶ� r �� c �У�����ƶ������Ǿ����ƶ���
	void changeNumber(int value);					// �ϲ�����
	void blinking();								// ��˸���ϲ�ʱ����

	int mNumber;									// ����						
};

#endif // __MOVEABLE_TILED_H__