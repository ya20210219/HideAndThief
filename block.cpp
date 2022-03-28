//= ============================================================================
//
// プレイヤー処理 [block.cpp]
// Author : TAKASHI AKYAMA
//
//=============================================================================
#define CONIOEX
#include "conioex.h"
#include "main.h"
#include "player.h"
#include "block.h"
#include "enemy.h"
#include "map.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BLOCK_POS_X				(13)		// 障害物のポジションＸ方向
#define BLOCK_POS_Y				(12)		// 障害物のポジションＹ方向

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
BLOCK g_block;
extern MAP g_map;
extern PLAYER g_player;
extern BULLET g_Bullet;

int BGM5;
int BGM6;
//=============================================================================
// ブロックの初期化処理
//=============================================================================
void InitBlock(void)
{
	// プレイヤーワークのクリア
	g_block.PosX = BLOCK_POS_X;
	g_block.PosY = BLOCK_POS_Y;
	g_block.thief = 1;
	g_block.blocktime = 0;
	g_block.ammoblock = 1;
	BGM5 = opensound("BGM/decision4.mp3");
	BGM6 = opensound("BGM/pistolready.mp3");
}
//=============================================================================
// ブロックの終了処理
//=============================================================================
void UninitBlock(void)
{

}

//=============================================================================
// ブロックの更新処理
//=============================================================================
void UpdateBlock(void)
{
	g_block.PosX = BLOCK_POS_X;
	g_block.PosY = BLOCK_POS_Y;
	if (g_block.thief == 0)
	{
		g_block.blocktime++;
	}
}

//=============================================================================
// ブロックの描画処理
//=============================================================================
void DrawBlock(void)
{
	if (g_player.life == 1 && g_block.thief == 1 && g_map.mapcount == 3)
	{
		//①オブジェクトの配置
		textcolor(1110);
		gotoxy(g_block.PosX, g_block.PosY);
		printf("宝");
	}

	if (g_map.mapcount == 5 && g_block.ammoblock == 1)
	{
		gotoxy(5, 3);
		textcolor(GREEN);
		printf("■");
	}
}

//=============================================================================
// 当たり判定練習
//=============================================================================
void collision(void)
{
	//②当たり判定の設定
	if (g_block.thief == 1 && (int)(g_player.fPosX) > g_block.PosX - 2.0f && (int)(g_player.fPosX) < g_block.PosX + 2.0f && (int)(g_player.fPosY) >= g_block.PosY - 1.0f && (int)(g_player.fPosY) <= g_block.PosY + 1.0f && g_map.mapcount == 3)
	{

		gotoxy(10, 27);
		textcolor(WHITE);
		printf("擦った！");
		playsound(BGM5, 0);
		g_block.thief = 0;
		msleep(20);
		clrscr();
		gotoxy(10, 27);
		textcolor(WHITE);
		printf("盗んだ！");
	
	}
	if (g_block.blocktime == 100)
	{
		gotoxy(10, 27);
		textcolor(0000);
		printf("■■■■■■");
	}

	if (g_block.ammoblock == 1 && (int)(g_player.fPosX) > 5 - 1.0f && (int)(g_player.fPosX) < 5 + 1.0f && (int)(g_player.fPosY) >= 3 - 1.0f && (int)(g_player.fPosY) <= 3 + 1.0f && g_map.mapcount == 5)
	{
		gotoxy(10, 27);
		textcolor(WHITE);
		printf("弾薬を補給した!");
		playsound(BGM6, 0);
		g_block.ammoblock = 0;
		g_Bullet.bulletcount = g_Bullet.bulletcount + 5;
		msleep(20);
		clrscr();
		gotoxy(10, 27);
		textcolor(WHITE);
		printf("弾薬を補給した!");
	}

	if (g_block.blocktime == 100)
	{
		gotoxy(10, 27);
		textcolor(0000);
		printf("■■■■■■■■");
	}
}