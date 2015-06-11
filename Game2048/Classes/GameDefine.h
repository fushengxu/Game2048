/*
 * 作者：MWN		
 * 邮箱：modood@qq.com
 * 版本：1.0
 * 日期：2015年5月25日
 */

#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__

#include "cocos2d.h"

// 游戏全局
#define GAME_NAME				"2048"													// 游戏名称
#define GAME_COPYRIGHT			"Copyright (C) MWN"										// 版权信息
#define GAME_NAME_FONT_PATH		"futura-48.fnt"											// 显示游戏名称使用的字体

#define GAME_SCREEN_WIDTH		320														// 屏幕宽度
#define GAME_SCREEN_HEIGHT		Director::getInstance()->getVisibleSize().height		// 屏幕高度

#define GAME_ROWS				4														// 四行
#define GAME_COLS				4														// 四列

#define GAME_TILED_WIDTH		64														// 可移动块的宽度
#define GAME_TILED_HEIGHT		64														// 可移动块的高度
#define GAME_TILED_BORDER		5														// 网格之间边线宽度

/* 注意：
 * GAME_WIDTH  必须小于或等于 GAME_SCREEN_WIDTH
 * GAME_HEIGHT 必须小于或等于 GAME_SCREEN_HEIGHT
 * 这里 GAME_WIDTH = GAME_HEIGHT = 64*4 + 5*(4+1) = 281 < 320
 */

#define GAME_WIDTH				(GAME_TILED_WIDTH * GAME_COLS + GAME_TILED_BORDER * ( GAME_COLS + 1 ))			// 游戏宽度
#define GAME_HEIGHT				(GAME_TILED_HEIGHT	* GAME_ROWS + GAME_TILED_BORDER * ( GAME_ROWS + 1 ))		// 游戏高度

// 数字块背景颜色
#define GAME_COLOR_TILED_2		Color4B(238, 228, 218, 255 )		// 数字块背景颜色（2）
#define GAME_COLOR_TILED_4		Color4B(240, 225, 200, 255 )		// 数字块背景颜色（4）
#define GAME_COLOR_TILED_8		Color4B(240, 180, 120, 255 )		// 数字块背景颜色（8）
#define GAME_COLOR_TILED_16		Color4B(245, 150, 100, 255 )		// 数字块背景颜色（16）
#define GAME_COLOR_TILED_32		Color4B(245, 125,  95, 255 )		// 数字块背景颜色（32）
#define GAME_COLOR_TILED_64		Color4B(245,  95,  60, 255 )		// 数字块背景颜色（64）
#define GAME_COLOR_TILED_128	Color4B(240, 205, 100, 255 )		// 数字块背景颜色（128）
#define GAME_COLOR_TILED_256	Color4B(240, 205, 100, 255 )		// 数字块背景颜色（256）
#define GAME_COLOR_TILED_512	Color4B(240, 205, 100, 255 )		// 数字块背景颜色（512）
#define GAME_COLOR_TILED_1024	Color4B(240, 205, 100, 255 )		// 数字块背景颜色（1024）
#define GAME_COLOR_TILED_2048	Color4B(240, 195,  45, 255 )		// 数字块背景颜色（2048）
#define GAME_COLOR_TILED_4096	Color4B(177, 107, 167, 255 )		// 数字块背景颜色（4096）
// 表示移动方向
enum class E_MOVE_DIR												
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};
// 用于记录空网格的结构体
struct BlankTiled													
{
	int row;
	int col;
} ;


#endif // __GAME_DEFINE_H__
