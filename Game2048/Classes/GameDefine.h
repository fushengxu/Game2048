/*
 * ���ߣ�MWN		
 * ���䣺modood@qq.com
 * �汾��1.0
 * ���ڣ�2015��5��25��
 */

#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__

#include "cocos2d.h"

// ��Ϸȫ��
#define GAME_NAME				"2048"													// ��Ϸ����
#define GAME_COPYRIGHT			"Copyright (C) MWN"										// ��Ȩ��Ϣ
#define GAME_NAME_FONT_PATH		"futura-48.fnt"											// ��ʾ��Ϸ����ʹ�õ�����

#define GAME_SCREEN_WIDTH		320														// ��Ļ���
#define GAME_SCREEN_HEIGHT		Director::getInstance()->getVisibleSize().height		// ��Ļ�߶�

#define GAME_ROWS				4														// ����
#define GAME_COLS				4														// ����

#define GAME_TILED_WIDTH		64														// ���ƶ���Ŀ��
#define GAME_TILED_HEIGHT		64														// ���ƶ���ĸ߶�
#define GAME_TILED_BORDER		5														// ����֮����߿��

/* ע�⣺
 * GAME_WIDTH  ����С�ڻ���� GAME_SCREEN_WIDTH
 * GAME_HEIGHT ����С�ڻ���� GAME_SCREEN_HEIGHT
 * ���� GAME_WIDTH = GAME_HEIGHT = 64*4 + 5*(4+1) = 281 < 320
 */

#define GAME_WIDTH				(GAME_TILED_WIDTH * GAME_COLS + GAME_TILED_BORDER * ( GAME_COLS + 1 ))			// ��Ϸ���
#define GAME_HEIGHT				(GAME_TILED_HEIGHT	* GAME_ROWS + GAME_TILED_BORDER * ( GAME_ROWS + 1 ))		// ��Ϸ�߶�

// ���ֿ鱳����ɫ
#define GAME_COLOR_TILED_2		Color4B(238, 228, 218, 255 )		// ���ֿ鱳����ɫ��2��
#define GAME_COLOR_TILED_4		Color4B(240, 225, 200, 255 )		// ���ֿ鱳����ɫ��4��
#define GAME_COLOR_TILED_8		Color4B(240, 180, 120, 255 )		// ���ֿ鱳����ɫ��8��
#define GAME_COLOR_TILED_16		Color4B(245, 150, 100, 255 )		// ���ֿ鱳����ɫ��16��
#define GAME_COLOR_TILED_32		Color4B(245, 125,  95, 255 )		// ���ֿ鱳����ɫ��32��
#define GAME_COLOR_TILED_64		Color4B(245,  95,  60, 255 )		// ���ֿ鱳����ɫ��64��
#define GAME_COLOR_TILED_128	Color4B(240, 205, 100, 255 )		// ���ֿ鱳����ɫ��128��
#define GAME_COLOR_TILED_256	Color4B(240, 205, 100, 255 )		// ���ֿ鱳����ɫ��256��
#define GAME_COLOR_TILED_512	Color4B(240, 205, 100, 255 )		// ���ֿ鱳����ɫ��512��
#define GAME_COLOR_TILED_1024	Color4B(240, 205, 100, 255 )		// ���ֿ鱳����ɫ��1024��
#define GAME_COLOR_TILED_2048	Color4B(240, 195,  45, 255 )		// ���ֿ鱳����ɫ��2048��
#define GAME_COLOR_TILED_4096	Color4B(177, 107, 167, 255 )		// ���ֿ鱳����ɫ��4096��
// ��ʾ�ƶ�����
enum class E_MOVE_DIR												
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};
// ���ڼ�¼������Ľṹ��
struct BlankTiled													
{
	int row;
	int col;
} ;


#endif // __GAME_DEFINE_H__
