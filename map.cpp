//= ============================================================================
//
// プレイヤー処理 [map.cpp]
//
//=============================================================================
#define CONIOEX
#include "conioex.h"
#include "player.h"
#include "main.h"
#include "player.h"
#include "block.h"
#include "wall.h"
#include "map.h"
#include "block.h"
#include "UI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define MAP_POS_X				(1)		    // 障害物のポジションＸ方向
#define MAP_POS_Y				(23)		// 障害物のポジションＹ方向


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************



//*****************************************************************************
// グローバル変数
//*****************************************************************************
MAP g_map;
extern PLAYER g_player;
extern BLOCK g_block;
extern UI g_ui;

//=============================================================================
// ブロックの初期化処理
//=============================================================================
void InitMap(void)
{
	g_map.mapcount = 1;
	g_map.mapchangeflag = 1;

	g_map.nextmapX[0] = 77;
	g_map.nextmapY[0] = 10;

	g_map.beforemapX[1] = 3;
	g_map.beforemapY[1] = 3;
	g_map.nextmapX[1] = 77;
	g_map.nextmapY[1] = 20;
	g_map.nextmapX[2] = 77;
	g_map.nextmapY[2] = 5;
	g_map.nextmapX[3] = 3;
	g_map.nextmapY[3] = 21;

	g_map.beforemapX[2] = 3;
	g_map.beforemapY[2] = 3;
	g_map.beforemapX[3] = 3;
	g_map.beforemapY[3] = 3;

	g_map.beforemapX[4] = 47;
	g_map.beforemapY[4] = 14;
	/*int beforemapX[3];
	int beforemapY[3];*/
}
//=============================================================================
// ブロックの終了処理
//=============================================================================
void UninitMap(void)
{

}

//=============================================================================
// ブロックの更新処理
//=============================================================================
void UpdateMap(void)
{
	/*if (g_map.mapcount == 1 && g_map.mapchangeflag == 1)
	{
		msleep(20);
		clrscr();
		g_map.mapchangeflag = 0;
	}

	if (g_map.mapcount == 2 && g_map.mapchangeflag == 1)
	{
		msleep(20);
		clrscr();
		g_map.mapchangeflag = 0;
	}*/

}

//=============================================================================
// ブロックの描画処理
//=============================================================================
void DrawMap(void)
{
	if (g_map.mapchangeflag == 1)
	{
		msleep(20);
		clrscr();
		g_map.mapchangeflag = 0;
	}

	if (g_player.life == 1 && g_map.mapcount == 1)
	{
		gotoxy(3, 9);
		textcolor(1011);
		printf("＠");


		gotoxy(g_map.nextmapX[0], g_map.nextmapY[0]);
		textcolor(LIGHTRED);
		printf("＠");

		textbackground(7);
		textcolor(1000);
		gotoxy(1, 6);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
		textbackground(7);
		textcolor(1000);
		gotoxy(1, 14);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

		gotoxy(1, 6);
		printf("■");
		gotoxy(79, 6);
		printf("■");
		gotoxy(1, 7);
		printf("■");
		gotoxy(79, 7);
		printf("■");
		gotoxy(1, 8);
		printf("■");
		gotoxy(79, 8);
		printf("■");
		gotoxy(1, 9);
		printf("■");
		gotoxy(79, 9);
		printf("■");
		gotoxy(1, 10);
		printf("■");
		gotoxy(79, 10);
		printf("■");
		gotoxy(1, 11);
		printf("■");
		gotoxy(79, 11);
		printf("■");
		gotoxy(1, 12);
		printf("■");
		gotoxy(79, 12);
		printf("■");
		gotoxy(1, 13);
		printf("■");
		gotoxy(79, 13);
		printf("■");
		gotoxy(1, 14);
		printf("■");
		gotoxy(79, 14);
		printf("■");
	}

	if (g_player.life == 1 && g_map.mapcount == 2)
	{
		textbackground(0x0);
		gotoxy(3, 3);
		textcolor(4);
		printf("＠");


		gotoxy(77, 5);
		textcolor(LIGHTRED);
		printf("＠");

		gotoxy(77, 20);
		textcolor(LIGHTRED);
		printf("＠");

		gotoxy(3, 21);
		textcolor(LIGHTRED);
		printf("＠");

		textbackground(0x7);
		
		textcolor(1000);
		gotoxy(1, 1);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(1, 23);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

		gotoxy(1, 2);
		gotoxy(1, 2);
		printf("■");
		gotoxy(79, 2);
		printf("■");
		gotoxy(1, 3);
		printf("■");
		gotoxy(79, 3);
		printf("■");
		gotoxy(1, 4);
		printf("■");
		gotoxy(79, 4);
		printf("■");
		gotoxy(1, 5);
		printf("■");
		gotoxy(79, 5);
		printf("■");
		gotoxy(1, 6);
		printf("■");
		gotoxy(79, 6);
		printf("■");
		gotoxy(1, 7);
		printf("■");
		gotoxy(79, 7);
		printf("■");
		gotoxy(1, 8);
		printf("■");
		gotoxy(79, 8);
		printf("■");
		gotoxy(1, 9);
		printf("■");
		gotoxy(79, 9);
		printf("■");
		gotoxy(1, 10);
		printf("■");
		gotoxy(79, 10);
		printf("■");
		gotoxy(1, 11);
		printf("■");
		gotoxy(79, 11);
		printf("■");
		gotoxy(1, 12);
		printf("■");
		gotoxy(79, 12);
		printf("■");
		gotoxy(1, 13);
		printf("■");
		gotoxy(79, 13);
		printf("■");
		gotoxy(1, 14);
		printf("■");
		gotoxy(79, 14);
		printf("■");
		gotoxy(1, 15);
		printf("■");
		gotoxy(79, 15);
		printf("■");
		gotoxy(1, 16);
		printf("■");
		gotoxy(79, 16);
		printf("■");
		gotoxy(1, 17);
		printf("■");
		gotoxy(79, 17);
		printf("■");
		gotoxy(1, 18);
		printf("■");
		gotoxy(79, 18);
		printf("■");
		gotoxy(1, 19);
		printf("■");
		gotoxy(79, 19);
		printf("■");
		gotoxy(1, 20);
		printf("■");
		gotoxy(79, 20);
		printf("■");
		gotoxy(1, 21);
		printf("■");
		gotoxy(79, 21);
		printf("■");
		gotoxy(1, 22);
		printf("■");
		gotoxy(79, 22);
		printf("■");
		gotoxy(1, 23);
		printf("■");
		gotoxy(79, 23);
		printf("■");
	}

	if (g_player.life == 1 && g_map.mapcount == 3)
	{
		textbackground(0x0);
		gotoxy(3, 3);
		textcolor(4);
		printf("＠");

		textbackground(0x7);

		textcolor(1000);
		gotoxy(1, 1);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(1, 23);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
		
		gotoxy(1, 2);
		printf("■");
		gotoxy(79, 2);
		printf("■");
		gotoxy(1, 3);
		printf("■");
		gotoxy(79, 3);
		printf("■");
		gotoxy(1, 4);
		printf("■");
		gotoxy(79, 4);
		printf("■");
		gotoxy(1, 5);
		printf("■");
		gotoxy(79, 5);
		printf("■");
		gotoxy(1, 6);
		printf("■");
		gotoxy(79, 6);
		printf("■");
		gotoxy(1, 7);
		printf("■");
		gotoxy(79, 7);
		printf("■");
		gotoxy(1, 8);
		printf("■");
		gotoxy(79, 8);
		printf("■");
		gotoxy(1, 9);
		printf("■");
		gotoxy(79, 9);
		printf("■");
		gotoxy(1, 10);
		printf("■");
		gotoxy(79, 10);
		printf("■");
		gotoxy(1, 11);
		printf("■");
		gotoxy(79, 11);
		printf("■");
		gotoxy(1, 12);
		printf("■");
		gotoxy(79, 12);
		printf("■");
		gotoxy(1, 13);
		printf("■");
		gotoxy(79, 13);
		printf("■");
		gotoxy(1, 14);
		printf("■");
		gotoxy(79, 14);
		printf("■");
		gotoxy(1, 15);
		printf("■");
		gotoxy(79, 15);
		printf("■");
		gotoxy(1, 16);
		printf("■");
		gotoxy(79, 16);
		printf("■");
		gotoxy(1, 17);
		printf("■");
		gotoxy(79, 17);
		printf("■");
		gotoxy(1, 18);
		printf("■");
		gotoxy(79, 18);
		printf("■");
		gotoxy(1, 19);
		printf("■");
		gotoxy(79, 19);
		printf("■");
		gotoxy(1, 20);
		printf("■");
		gotoxy(79, 20);
		printf("■");
		gotoxy(1, 21);
		printf("■");
		gotoxy(79, 21);
		printf("■");
		gotoxy(1, 22);
		printf("■");
		gotoxy(79, 22);
		printf("■");
		gotoxy(1, 23);
		printf("■");
		gotoxy(79, 23);
		printf("■");
	}

	if (g_player.life == 1 && g_map.mapcount == 4)
	{
		textbackground(0x0);
		gotoxy(3, 3);
		textcolor(4);
		printf("＠");

		textbackground(0x7);

		textcolor(1000);
		gotoxy(1, 1);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(1, 15);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■");

		gotoxy(1, 2);
		printf("■");
		gotoxy(49, 2);
		printf("■");
		gotoxy(1, 3);
		printf("■");
		gotoxy(49, 3);
		printf("■");
		gotoxy(1, 4);
		printf("■");
		gotoxy(49, 4);
		printf("■");
		gotoxy(1, 5);
		printf("■");
		gotoxy(49, 5);
		printf("■");
		gotoxy(1, 6);
		printf("■");
		gotoxy(49, 6);
		printf("■");
		gotoxy(1, 7);
		printf("■");
		gotoxy(49, 7);
		printf("■");
		gotoxy(1, 8);
		printf("■");
		gotoxy(49, 8);
		printf("■");
		gotoxy(1, 9);
		printf("■");
		gotoxy(49, 9);
		printf("■");
		gotoxy(1, 10);
		printf("■");
		gotoxy(49, 10);
		printf("■");
		gotoxy(1, 11);
		printf("■");
		gotoxy(49, 11);
		printf("■");
		gotoxy(1, 12);
		printf("■");
		gotoxy(49, 12);
		printf("■");
		gotoxy(1, 13);
		printf("■");
		gotoxy(49, 13);
		printf("■");
		gotoxy(1, 14);
		printf("■");
		gotoxy(49, 14);
		printf("■");
		gotoxy(1, 15);
		printf("■");
		gotoxy(49, 15);
		printf("■");
		
	}


	if (g_player.life == 1 && g_map.mapcount == 5)
	{
		textbackground(0x0);
		gotoxy(47, 14);
		textcolor(4);
		printf("＠");

		textbackground(0x7);

		textcolor(1000);
		gotoxy(1, 1);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(1, 15);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■");

		gotoxy(1, 2);
		printf("■");
		gotoxy(49, 2);
		printf("■");
		gotoxy(1, 3);
		printf("■");
		gotoxy(49, 3);
		printf("■");
		gotoxy(1, 4);
		printf("■");
		gotoxy(49, 4);
		printf("■");
		gotoxy(1, 5);
		printf("■");
		gotoxy(49, 5);
		printf("■");
		gotoxy(1, 6);
		printf("■");
		gotoxy(49, 6);
		printf("■");
		gotoxy(1, 7);
		printf("■");
		gotoxy(49, 7);
		printf("■");
		gotoxy(1, 8);
		printf("■");
		gotoxy(49, 8);
		printf("■");
		gotoxy(1, 9);
		printf("■");
		gotoxy(49, 9);
		printf("■");
		gotoxy(1, 10);
		printf("■");
		gotoxy(49, 10);
		printf("■");
		gotoxy(1, 11);
		printf("■");
		gotoxy(49, 11);
		printf("■");
		gotoxy(1, 12);
		printf("■");
		gotoxy(49, 12);
		printf("■");
		gotoxy(1, 13);
		printf("■");
		gotoxy(49, 13);
		printf("■");
		gotoxy(1, 14);
		printf("■");
		gotoxy(49, 14);
		printf("■");
		gotoxy(1, 15);
		printf("■");
		gotoxy(49, 15);
		printf("■");
	}

}

void mapcollision(void)
{
	if (g_map.mapcount == 1 && (int)g_player.fPosX > g_map.nextmapX[0] - 1.0f && (int)g_player.fPosX < g_map.nextmapX[0] + 1.0f && (int)g_player.fPosY >= g_map.nextmapY[0] && (int)g_player.fPosY <= g_map.nextmapY[0] + 1.0f)
	{
		g_map.mapcount = 2;
		g_player.fPosX = 5.0f;
		g_player.fPosY = 3.0f;
		msleep(20);
		clrscr();
		g_map.mapchangeflag = 1;
	}

	if (g_map.mapcount == 2 && (int)g_player.fPosX > g_map.beforemapX[1] - 1.0f && (int)g_player.fPosX < g_map.beforemapX[1] + 1.0f && (int)g_player.fPosY >= g_map.beforemapY[1] && (int)g_player.fPosY <= g_map.beforemapY[1] + 1.0f)
	{
		g_map.mapcount = 1;
		g_player.fPosX = 75;
		g_player.fPosY = 11;
		msleep(20);
		clrscr();
		g_map.mapchangeflag = 1;
	}

	if (g_map.mapcount == 2 && (int)g_player.fPosX > g_map.nextmapX[1] - 1.0f && (int)g_player.fPosX < g_map.nextmapX[1] + 1.0f && (int)g_player.fPosY >= g_map.nextmapY[1] && (int)g_player.fPosY <= g_map.nextmapY[1] + 1.0f)
	{
		g_map.mapcount = 3;
		g_player.fPosX = 5.0f;
		g_player.fPosY = 3.0f;
		msleep(20);
		clrscr();
		g_map.mapchangeflag = 1;
	}

	if (g_map.mapcount == 2 && (int)g_player.fPosX > g_map.nextmapX[2] - 1.0f && (int)g_player.fPosX < g_map.nextmapX[2] + 1.0f && (int)g_player.fPosY >= g_map.nextmapY[2] && (int)g_player.fPosY <= g_map.nextmapY[2] + 1.0f)
	{
		g_map.mapcount = 4;
		g_player.fPosX = 5.0f;
		g_player.fPosY = 3.0f;
		msleep(20);
		clrscr();
		g_map.mapchangeflag = 1;
	}

	if (g_map.mapcount == 2 && (int)g_player.fPosX > g_map.nextmapX[3] - 1.0f && (int)g_player.fPosX < g_map.nextmapX[3] + 1.0f && (int)g_player.fPosY >= g_map.nextmapY[3] && (int)g_player.fPosY <= g_map.nextmapY[3] + 1.0f)
	{
		g_map.mapcount = 5;
		g_player.fPosX = 44;
		g_player.fPosY = 14;
		msleep(20);
		clrscr();
		g_map.mapchangeflag = 1;
	}

	if (g_map.mapcount == 5 && (int)g_player.fPosX > g_map.beforemapX[4] - 1.0f && (int)g_player.fPosX < g_map.beforemapX[4] + 1.0f && (int)g_player.fPosY >= g_map.beforemapY[4] && (int)g_player.fPosY <= g_map.beforemapY[4] + 1.0f)
	{
		g_map.mapcount = 2;
		g_player.fPosX = 5;
		g_player.fPosY = 21;
		msleep(20);
		clrscr();
		g_map.mapchangeflag = 1;
	}

	if (g_map.mapcount == 3 && (int)g_player.fPosX > g_map.beforemapX[2] - 1.0f && (int)g_player.fPosX < g_map.beforemapX[2] + 1.0f && (int)g_player.fPosY >= g_map.beforemapY[2] && (int)g_player.fPosY <= g_map.beforemapY[2] + 1.0f)
	{
		g_map.mapcount = 2;
		g_player.fPosX = 77;
		g_player.fPosY = 20;
		msleep(20);
		clrscr();
		g_map.mapchangeflag = 1;
	}


	if (g_map.mapcount == 4 && (int)g_player.fPosX > g_map.beforemapX[3] - 1.0f && (int)g_player.fPosX < g_map.beforemapX[3] + 1.0f && (int)g_player.fPosY >= g_map.beforemapY[3] && (int)g_player.fPosY <= g_map.beforemapY[3] + 1.0f)
	{
		g_map.mapcount = 2;
		g_player.fPosX = 74;
		g_player.fPosY = 5;
		msleep(20);
		clrscr();
		g_map.mapchangeflag = 1;
	}
}