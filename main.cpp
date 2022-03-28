//=============================================================================
//
// アクションゲームサンプル [main.cpp]
// Author : TAKASHI AKIYAMA
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "block.h"
#include "wall.h"
#include "map.h"
#include "UI.h"
//#include "system.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DEBUG

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void Init(void);
void Uninit(void);
void Update(void);
void Draw(void);
void titleback(void);
extern UI g_ui;
extern PLAYER g_player;

#ifdef DEBUG
void DispFPS(void);
#endif

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int g_nCountFPS;				// FPSカウンタ
int gamereset = 1;
int BGM2 = 0;
int BGM3 = 0;
int BGM4 = 0;

//=============================================================================
// メイン関数
//=============================================================================
void main(void)
{

	DWORD dwExecLastTime;	//実行継続時間
	DWORD dwFPSLastTime;	//FPS継続時間
	DWORD dwCurrentTime;	//現在時間
	int nCountFrame;

	//int BGM1 = 0;
	//int BGM2 = 0;
	BGM2 = opensound("BGM/bgm_maoudamashii_cyber44.mp3");
	BGM3 = opensound("BGM/n139.mp3");
	BGM4 = opensound("BGM/n100(2).mp3");


	setvolume(BGM2, 40);
	setvolume(BGM3, 40);
	setvolume(BGM4, 40);

	// 分解能を設定
	timeBeginPeriod(1);

	// 各種値の初期化
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();//システム時刻がミリ秒単位で返る関数
	dwCurrentTime =
		nCountFrame = 0;

	// 初期化処理
	Init();

	// カーソル表示ＯＦＦ
	setcursortype(NOCURSOR);

	playsound(BGM4, 1);
	do
	{
		title();
		if (inport(PJ_BTNS) == 128 || inport(PK_ENTER))
		{
			g_ui.systemflag = 1;
		}

		if (inport(PK_ESC))
		{
			g_ui.systemflag = 2;
		}

	} while (g_ui.systemflag == 0);


	clrscr();
	// ゲームメイン処理
	stopsound(BGM4);

	if (g_ui.systemflag == 1)
	{
		do
		{
			tutorial();
			if (inport(PJ_BTNS) == 16 || inport(PK_O))
			{
				g_ui.buttonL = 1;
			}
			if (inport(PJ_BTNS) == 32 || inport(PK_K))
			{
				g_ui.buttonR = 1;
			}
			if (inport(PJ_BTNS) == 48)
			{
				g_ui.buttonR = 1;
				g_ui.buttonL = 1;
			}
		} while (!g_ui.buttonL == 1 || !g_ui.buttonR == 1);
	}
		clrscr();

		if (g_ui.systemflag == 1)
		{
			playsound(BGM3, 1);
			do
			{
				dwCurrentTime = timeGetTime();
				if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
				{
					g_nCountFPS = nCountFrame * 1000 / (dwCurrentTime - dwFPSLastTime);
					dwFPSLastTime = dwCurrentTime;
					nCountFrame = 0;
				}

				if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
				{
					dwExecLastTime = dwCurrentTime;




					// 更新処理
					Update();
					// 描画処理
					Draw();

					nCountFrame++;

	#ifdef DEBUG
					// FPS表示
					DispFPS();
	#endif
				}
			} while (!inport(PK_ESC) && g_ui.gameflag == 1);

			stopsound(BGM3);
			ending();
		}
		// カーソル表示ＯＮ
		setcursortype(NORMALCURSOR);

		// 終了処理
		Uninit();
	

		// 分解能を戻す
		timeEndPeriod(1);
}


//=============================================================================
// 初期化処理
//=============================================================================
void Init(void)
{
	// プレイヤーの初期化処理
	InitPlayer();
	InitEnemy();
	InitBullet();
	InitBlock();
	InitWall();
	InitUI();
	InitMap();
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	// プレイヤーの終了処理
	UninitPlayer();
	UninitEnemy();
	UninitBlock();
	UninitWall();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// プレイヤーの更新処理
	UpdatePlayer();
	Slow();
	UpdateEnemy();
	UpdateBullet();
	UpdateBlock();
	UpdateWall();
	collision();
	Wallcollision();
	mapcollision();
	UpdateUI();
	if (g_player.life == 0)
	{
		stopsound(BGM3);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// プレイヤーなど各種描画処理
	DrawPlayer();
	DrawEnemy();
	DrawBullet();
	DrawBlock();
	DrawWall();
	DrawMap();
	DrawUI();
}

void titleback(void)
{
	clrscr();
	gotoxy(40, 20);
	printf("タイトルに戻ります");
	msleep(3000);
	return;
}

#ifdef DEBUG
//=============================================================================
// FPS表示
//=============================================================================
void DispFPS(void)
{
	// 色設定
	textcolor(LIGHTGREEN);

	/*gotoxy(1, 1);
	printf("X:%5d", inport(PJ_XPOS));

	gotoxy(10, 1);
	printf("Y:%5d", inport(PJ_YPOS));

	gotoxy(20, 1);
	printf("B:%5d", inport(PJ_BTNS));
*/
	gotoxy(1, 30);
	printf("FPS:%d", g_nCountFPS);
}
#endif
