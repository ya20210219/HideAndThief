//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : TAKASHI AKYAMA
//
//=============================================================================
#define CONIOEX
#include "conioex.h"
#include "main.h"
#include "player.h"
#include "bullet.h"
#include "wall.h"
#include "enemy.h"
#include "UI.h"
#include "map.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE_X			(0.5f)		// 地上での移動量Ｘ方向   　一回での移動量　　　//初期は0.75
#define VALUE_T_MOVE_X          (0.75f)
#define	VALUE_MOVE_Y			(0.25f)		// 地上での移動量Ｙ方向   　一回での移動量　　　//初期は0.75
#define	VALUE_RESIST_X			(0.50f)		// 地上での移動摩擦抵抗
#define	VALUE_RESIST_Y			(0.50f)		// 地上での移動摩擦抵抗

#define	LIMIT_LEFT1				(3.0f)		// 移動範囲左端             |
#define	LIMIT_RIGHT1			(77.0f)	    // 移動範囲右端             |--  画面端の設定    初期は78
#define	LIMIT_DOWN1				(13.0f)		// 移動範囲下端             |
#define	LIMIT_UP1				(8.0f)		// 移動範囲上端             |

#define	LIMIT_LEFT2				(3.0f)		// 移動範囲左端             |
#define	LIMIT_RIGHT2			(77.0f)	    // 移動範囲右端             |--  画面端の設定    初期は78
#define	LIMIT_DOWN2 			(22.0f)		// 移動範囲下端             |
#define	LIMIT_UP2				(3.0f)		// 移動範囲上端             |

#define	LIMIT_LEFT3				(3.0f)		// 移動範囲左端             |
#define	LIMIT_RIGHT3			(77.0f)	    // 移動範囲右端             |--  画面端の設定    初期は78
#define	LIMIT_DOWN3				(22.0f)		// 移動範囲下端             |
#define	LIMIT_UP3				(3.0f)		// 移動範囲上端             |

#define	LIMIT_LEFT4				(3.0f)		// 移動範囲左端             |
#define	LIMIT_RIGHT4			(47.0f)	    // 移動範囲右端             |--  画面端の設定    初期は78
#define	LIMIT_DOWN4				(14.0f)		// 移動範囲下端             |
#define	LIMIT_UP4				(3.0f)		// 移動範囲上端             |

#define	LIMIT_LEFT5				(3.0f)		// 移動範囲左端             |
#define	LIMIT_RIGHT5			(47.0f)	    // 移動範囲右端             |--  画面端の設定    初期は78
#define	LIMIT_DOWN5				(14.0f)		// 移動範囲下端             |
#define	LIMIT_UP5				(3.0f)		// 移動範囲上端             |




//()内の数値をいじれば限界の数値も変わる ウィンドウのサイズ次第で変更する

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
PLAYER g_player;						// プレイヤーワーク
extern WALL g_wall;
extern BULLET g_Bullet;
extern UI g_ui;
extern ENEMY g_enemy[10];
extern MAP g_map;

int slowBGM;


//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
void InitPlayer(void)
{
	slowBGM = opensound("BGM/magic-charge1.mp3");
	setvolume(slowBGM, 40);

	// プレイヤーワークのクリア
	g_player.fPosX = 3.0f;       //プレイヤーの初期位置
	g_player.fPosY = 4.0f;
	g_player.fPosXOLD = 0.0f;
	g_player.fPosYOLD = 0.0f;
	g_player.fMoveX = 0.0f;
	g_player.fMoveY = 0.0f;
	g_player.bShot = false;
	g_player.bMove = false;
	g_player.color = 0;
	g_player.life = 1;
	g_player.slow = 0;
	g_player.slowflag = 1;
	g_player.slowtime = 1;
	g_player.slowcooldown = 0;
	g_player.slowcooldownflag = 0;
}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void UninitPlayer(void)
{
}

//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void UpdatePlayer(void)
{
	if (g_player.life == 1)
	{
		g_player.fPosXOLD = g_player.fPosX;
		g_player.fPosYOLD = g_player.fPosY;


		// 左移動
		if (inport(PJ_XPOS) == 0 || inport(PK_A))
		{
			// ここを考える
			g_player.fMoveX -= VALUE_MOVE_X;
			g_player.bMove = true;
		}

		// 右移動
		if (inport(PJ_XPOS) == 65535 || inport(PK_D))
		{
			// ここを考える
			g_player.fMoveX += VALUE_MOVE_X;
			g_player.bMove = true;
		}

		// 上移動
		if (inport(PJ_YPOS) == 0 || inport(PK_W))
		{
			// ここを考える
			g_player.fMoveY -= VALUE_MOVE_Y;
			g_player.bMove = true;
		}

		// 下移動
		if (inport(PJ_YPOS) == 65535 || inport(PK_S))
		{
			// ここを考える
			g_player.fMoveY += VALUE_MOVE_Y;
			g_player.bMove = true;
		}

		
		if (inport(PJ_BTNS) == 1 && g_Bullet.bulletcount > 0 || inport(PK_SP) && g_Bullet.bulletcount > 0)
		{// 攻撃
			if (!g_player.bShot)    //弾が発射されてなかったらという意味
			{
				g_Bullet.bulletcount--;
				if (g_player.fPosX >= 3.0f && g_player.fPosX <= 77.0f)     //プレイヤーが画面内(範囲内)でのみ発射
				{

					if (g_ui.flag == 1)
					{
						// 弾の設定
						SetBullet(g_player.fPosX - 2.0f + g_player.fMoveX, g_player.fPosY, 1.0f, 0.0f, BULLETTYPE_PLAYER);   //発射位置(弾の発生位置)
						//                                                            x方向 y方向      ↑弾の発射の構造体
						g_player.bShot = true;     //弾を撃ってるかどうかの判定
					
					}
					if (g_ui.flag == 2)
					{
						// 弾の設定
						SetBullet(g_player.fPosX + 2.0f + g_player.fMoveX, g_player.fPosY, 1.0f, 0.0f, BULLETTYPE_PLAYER);   //発射位置(弾の発生位置)
						//                                                            x方向 y方向      ↑弾の発射の構造体
						g_player.bShot = true;     //弾を撃ってるかどうかの判定
				
					}
					if (g_ui.flag == 3)
					{
						// 弾の設定
						SetBullet(g_player.fPosX, g_player.fPosY + g_player.fMoveY + 1.0f, 0.0f, 1.0f, BULLETTYPE_PLAYER);   //発射位置(弾の発生位置)
						//                                                            x方向 y方向      ↑弾の発射の構造体
						g_player.bShot = true;     //弾を撃ってるかどうかの判定
					
					}
					if (g_ui.flag == 4)
					{
						// 弾の設定
						SetBullet(g_player.fPosX, g_player.fPosY + g_player.fMoveY - 1.0f, 0.0f, 1.0f, BULLETTYPE_PLAYER);   //発射位置(弾の発生位置)
						//                                                            x方向 y方向      ↑弾の発射の構造体
						g_player.bShot = true;     //弾を撃ってるかどうかの判定
					
					}
				}
				
			}
		}
		else
		{
			if (g_player.bShot)
			{       // ショット中
				g_player.bShot = false;
			}
		}


		// 抵抗を加える
		g_player.fMoveX += (0.0f - g_player.fMoveX) * VALUE_RESIST_X;  //逆方向に力を加えている
		g_player.fMoveY += (0.0f - g_player.fMoveY) * VALUE_RESIST_Y;


		// 位置更新

		g_player.fPosX += g_player.fMoveX;
		g_player.fPosY += g_player.fMoveY;

		if (g_map.mapcount == 1)
		{
			// 画面端の処理
			if (g_player.fPosX < LIMIT_LEFT1)
			{
				g_player.fPosX = LIMIT_LEFT1;       //画面の限界がLIMIT_LEFTなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosY > LIMIT_DOWN1)
			{
				g_player.fPosY = LIMIT_DOWN1;       //画面の限界がLIMIT_DOWNなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosX > LIMIT_RIGHT1)
			{
				g_player.fPosX = LIMIT_RIGHT1;      //画面の限界がLIMIT_RIGHTなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosY < LIMIT_UP1)
			{

				g_player.fPosY = LIMIT_UP1;         //画面の限界がLIMIT_UPなので移動した数値を限界の数値にして移動してないように見える
			}
		}

		if (g_map.mapcount == 2)
		{

			if (g_player.fPosX < LIMIT_LEFT2)
			{
				g_player.fPosX = LIMIT_LEFT2;       //画面の限界がLIMIT_LEFTなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosY > LIMIT_DOWN2)
			{
				g_player.fPosY = LIMIT_DOWN2;       //画面の限界がLIMIT_DOWNなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosX > LIMIT_RIGHT2)
			{
				g_player.fPosX = LIMIT_RIGHT2;      //画面の限界がLIMIT_RIGHTなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosY < LIMIT_UP2)
			{
				g_player.fPosY = LIMIT_UP2;         //画面の限界がLIMIT_UPなので移動した数値を限界の数値にして移動してないように見える
			}
		}

		if (g_map.mapcount == 3)
		{
			if (g_player.fPosX < LIMIT_LEFT3)
			{
				g_player.fPosX = LIMIT_LEFT3;       //画面の限界がLIMIT_LEFTなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosY > LIMIT_DOWN3)
			{
				g_player.fPosY = LIMIT_DOWN3;       //画面の限界がLIMIT_DOWNなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosX > LIMIT_RIGHT3)
			{
				g_player.fPosX = LIMIT_RIGHT3;      //画面の限界がLIMIT_RIGHTなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosY < LIMIT_UP3)
			{
				g_player.fPosY = LIMIT_UP3;         //画面の限界がLIMIT_UPなので移動した数値を限界の数値にして移動してないように見える
			}
		}

		if (g_map.mapcount == 4)
		{
			if (g_player.fPosX < LIMIT_LEFT4)
			{
				g_player.fPosX = LIMIT_LEFT4;       //画面の限界がLIMIT_LEFTなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosY > LIMIT_DOWN4)
			{
				g_player.fPosY = LIMIT_DOWN4;       //画面の限界がLIMIT_DOWNなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosX > LIMIT_RIGHT4)
			{
				g_player.fPosX = LIMIT_RIGHT4;      //画面の限界がLIMIT_RIGHTなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosY < LIMIT_UP4)
			{
				g_player.fPosY = LIMIT_UP4;         //画面の限界がLIMIT_UPなので移動した数値を限界の数値にして移動してないように見える
			}
		}

		if (g_map.mapcount == 5)
		{
			if (g_player.fPosX < LIMIT_LEFT5)
			{
				g_player.fPosX = LIMIT_LEFT5;       //画面の限界がLIMIT_LEFTなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosY > LIMIT_DOWN5)
			{
				g_player.fPosY = LIMIT_DOWN5;       //画面の限界がLIMIT_DOWNなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosX > LIMIT_RIGHT5)
			{
				g_player.fPosX = LIMIT_RIGHT5;      //画面の限界がLIMIT_RIGHTなので移動した数値を限界の数値にして移動してないように見える
			}
			if (g_player.fPosY < LIMIT_UP5)
			{
				g_player.fPosY = LIMIT_UP5;         //画面の限界がLIMIT_UPなので移動した数値を限界の数値にして移動してないように見える
			}
		}

		if (g_enemy[0].life == 1 && g_enemy[0].flag == 0 && g_map.mapcount == 2)
		{
			if ((int)g_player.fPosX > g_enemy[0].fEeyePosX[0] - 2.0f && (int)g_player.fPosX < g_enemy[0].fEeyePosX[0] + 2.0f && (int)g_player.fPosY >= g_enemy[0].fEeyePosY[0] && (int)g_player.fPosY <= g_enemy[0].fEeyePosY[0] + 1.0f)
			{
				g_player.life = 0;
			}
			
			if ((int)g_player.fPosX > g_enemy[0].fEeyePosX[2] - 2.0f && (int)g_player.fPosX < g_enemy[0].fEeyePosX[2] + 2.0f && (int)g_player.fPosY >= g_enemy[0].fEeyePosY[2] && (int)g_player.fPosY <= g_enemy[0].fEeyePosY[2] + 1.0f)
			{
				g_player.life = 0;
			}
			
			if ((int)g_player.fPosX >= g_enemy[0].fEeyePosX[6] - 4.0f && (int)g_player.fPosX <= g_enemy[0].fEeyePosX[6] + 4.0f && (int)g_player.fPosY >= g_enemy[0].fEeyePosY[6] && (int)g_player.fPosY <= g_enemy[0].fEeyePosY[6] + 1.0f)
			{
				g_player.life = 0;
			}
			
		}
		if (g_enemy[0].life == 1 && g_enemy[0].flag == 1 && g_map.mapcount == 2)
		{
			if ((int)g_player.fPosX > g_enemy[0].fEeyePosX[0] - 1.0f && (int)g_player.fPosX < g_enemy[0].fEeyePosX[0] + 1.0f && (int)g_player.fPosY <= g_enemy[0].fEeyePosY[0] && (int)g_player.fPosY >= g_enemy[0].fEeyePosY[0] - 2.0f)
			{
				g_player.life = 0;
			}
			
			if ((int)g_player.fPosX > g_enemy[0].fEeyePosX[2] - 2.0f && (int)g_player.fPosX < g_enemy[0].fEeyePosX[2] + 2.0f && (int)g_player.fPosY <= g_enemy[0].fEeyePosY[2] && (int)g_player.fPosY >= g_enemy[0].fEeyePosY[2] - 2.0f)
			{
				g_player.life = 0;
			}
			
			if ((int)g_player.fPosX > g_enemy[0].fEeyePosX[6] - 4.0f && (int)g_player.fPosX < g_enemy[0].fEeyePosX[6] + 4.0f && (int)g_player.fPosY <= g_enemy[0].fEeyePosY[6] && (int)g_player.fPosY >= g_enemy[0].fEeyePosY[6] - 2.0f)
			{
				g_player.life = 0;
			}
			
		}

		if (g_enemy[1].life == 1 && g_enemy[1].flag == 0 && g_map.mapcount == 2)
		{
			if ((int)g_player.fPosX > g_enemy[1].fEeyePosX[0] - 2.0f && (int)g_player.fPosX < g_enemy[1].fEeyePosX[0] + 2.0f && (int)g_player.fPosY >= g_enemy[1].fEeyePosY[0] && (int)g_player.fPosY <= g_enemy[1].fEeyePosY[0] + 1.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[1].fEeyePosX[2] - 2.0f && (int)g_player.fPosX < g_enemy[1].fEeyePosX[2] + 2.0f && (int)g_player.fPosY >= g_enemy[1].fEeyePosY[2] && (int)g_player.fPosY <= g_enemy[1].fEeyePosY[2] + 1.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX >= g_enemy[1].fEeyePosX[6] - 4.0f && (int)g_player.fPosX <= g_enemy[1].fEeyePosX[6] + 4.0f && (int)g_player.fPosY >= g_enemy[1].fEeyePosY[6] && (int)g_player.fPosY <= g_enemy[1].fEeyePosY[6] + 1.0f)
			{
				g_player.life = 0;
			}

		}
		if (g_enemy[1].life == 1 && g_enemy[1].flag == 1 && g_map.mapcount == 2)
		{
			if ((int)g_player.fPosX > g_enemy[1].fEeyePosX[0] - 1.0f && (int)g_player.fPosX < g_enemy[1].fEeyePosX[0] + 1.0f && (int)g_player.fPosY <= g_enemy[1].fEeyePosY[0] && (int)g_player.fPosY >= g_enemy[1].fEeyePosY[0] - 2.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[1].fEeyePosX[2] - 2.0f && (int)g_player.fPosX < g_enemy[1].fEeyePosX[2] + 2.0f && (int)g_player.fPosY <= g_enemy[1].fEeyePosY[2] && (int)g_player.fPosY >= g_enemy[1].fEeyePosY[2] - 2.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[1].fEeyePosX[6] - 4.0f && (int)g_player.fPosX < g_enemy[1].fEeyePosX[6] + 4.0f && (int)g_player.fPosY <= g_enemy[1].fEeyePosY[6] && (int)g_player.fPosY >= g_enemy[1].fEeyePosY[6] - 2.0f)
			{
				g_player.life = 0;
			}

		}
		if (g_enemy[3].life == 1 && g_enemy[3].flag == 0 && g_map.mapcount == 2)
		{
			if ((int)g_player.fPosX > g_enemy[3].fEeyePosX[0] - 2.0f && (int)g_player.fPosX < g_enemy[3].fEeyePosX[0] + 2.0f && (int)g_player.fPosY >= g_enemy[3].fEeyePosY[0] && (int)g_player.fPosY <= g_enemy[3].fEeyePosY[0] + 1.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[3].fEeyePosX[2] - 2.0f && (int)g_player.fPosX < g_enemy[3].fEeyePosX[2] + 2.0f && (int)g_player.fPosY >= g_enemy[3].fEeyePosY[2] && (int)g_player.fPosY <= g_enemy[3].fEeyePosY[2] + 1.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX >= g_enemy[3].fEeyePosX[6] - 4.0f && (int)g_player.fPosX <= g_enemy[3].fEeyePosX[6] + 4.0f && (int)g_player.fPosY >= g_enemy[3].fEeyePosY[6] && (int)g_player.fPosY <= g_enemy[3].fEeyePosY[6] + 1.0f)
			{
				g_player.life = 0;
			}

		}
		if (g_enemy[3].life == 1 && g_enemy[3].flag == 1 && g_map.mapcount == 2)
		{
			if ((int)g_player.fPosX > g_enemy[3].fEeyePosX[0] - 1.0f && (int)g_player.fPosX < g_enemy[3].fEeyePosX[0] + 1.0f && (int)g_player.fPosY <= g_enemy[3].fEeyePosY[0] && (int)g_player.fPosY >= g_enemy[3].fEeyePosY[0] - 2.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[3].fEeyePosX[2] - 2.0f && (int)g_player.fPosX < g_enemy[3].fEeyePosX[2] + 2.0f && (int)g_player.fPosY <= g_enemy[3].fEeyePosY[2] && (int)g_player.fPosY >= g_enemy[3].fEeyePosY[2] - 2.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[3].fEeyePosX[6] - 4.0f && (int)g_player.fPosX < g_enemy[3].fEeyePosX[6] + 4.0f && (int)g_player.fPosY <= g_enemy[3].fEeyePosY[6] && (int)g_player.fPosY >= g_enemy[3].fEeyePosY[6] - 2.0f)
			{
				g_player.life = 0;
			}

		}
		if (g_enemy[4].life == 1 && g_enemy[4].flag == 0 && g_map.mapcount == 3)
		{
			if ((int)g_player.fPosX > g_enemy[4].fEeyePosX[0] - 1.0f && (int)g_player.fPosX < g_enemy[4].fEeyePosX[0] + 1.0f && (int)g_player.fPosY >= g_enemy[4].fEeyePosY[0] && (int)g_player.fPosY <= g_enemy[4].fEeyePosY[0])
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[4].fEeyePosX[2] - 2.0f && (int)g_player.fPosX < g_enemy[4].fEeyePosX[2] - 1.0f && (int)g_player.fPosY >= g_enemy[4].fEeyePosY[2] - 1 && (int)g_player.fPosY <= g_enemy[4].fEeyePosY[2] + 1)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX >= g_enemy[4].fEeyePosX[6] - 3.0f && (int)g_player.fPosX <= g_enemy[4].fEeyePosX[6] - 2.0f && (int)g_player.fPosY >= g_enemy[4].fEeyePosY[6] - 2 && (int)g_player.fPosY <= g_enemy[4].fEeyePosY[6] + 2)
			{
				g_player.life = 0;
			}

		}

		if (g_enemy[4].life == 1 && g_enemy[4].flag == 1 && g_map.mapcount == 3)
		{
			if ((int)g_player.fPosX > g_enemy[4].fEeyePosX[0] + 1.0f && (int)g_player.fPosX < g_enemy[4].fEeyePosX[0] + 2.0f && (int)g_player.fPosY >= g_enemy[4].fEeyePosY[0] && (int)g_player.fPosY <= g_enemy[4].fEeyePosY[0] )
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[4].fEeyePosX[2] + 1.0f && (int)g_player.fPosX < g_enemy[4].fEeyePosX[2] + 2.0f && (int)g_player.fPosY >= g_enemy[4].fEeyePosY[2] - 1 && (int)g_player.fPosY <= g_enemy[4].fEeyePosY[2] + 1)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[4].fEeyePosX[6] + 1.0f && (int)g_player.fPosX < g_enemy[4].fEeyePosX[6] + 2.0f && (int)g_player.fPosY >= g_enemy[4].fEeyePosY[6] - 2 && (int)g_player.fPosY <= g_enemy[4].fEeyePosY[6] + 2)
			{
				g_player.life = 0;
			}

		}

		if (g_enemy[5].life == 1 && g_enemy[5].flag == 1 && g_map.mapcount == 5)
		{
			if ((int)g_player.fPosX > g_enemy[5].fEeyePosX[0] + 1.0f && (int)g_player.fPosX < g_enemy[5].fEeyePosX[0] + 2.0f && (int)g_player.fPosY >= g_enemy[5].fEeyePosY[0] && (int)g_player.fPosY <= g_enemy[5].fEeyePosY[0])
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[5].fEeyePosX[2] + 1.0f && (int)g_player.fPosX < g_enemy[5].fEeyePosX[2] + 2.0f && (int)g_player.fPosY >= g_enemy[5].fEeyePosY[2] - 1 && (int)g_player.fPosY <= g_enemy[5].fEeyePosY[2] + 1)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[5].fEeyePosX[6] + 1.0f && (int)g_player.fPosX < g_enemy[5].fEeyePosX[6] + 2.0f && (int)g_player.fPosY >= g_enemy[5].fEeyePosY[6] - 2 && (int)g_player.fPosY <= g_enemy[5].fEeyePosY[6] + 2)
			{
				g_player.life = 0;
			}

		}


		if (g_enemy[0].cameralife >= 1)
		{
			if (g_map.mapcount == 2)
			{
				if ((int)g_player.fPosX > g_enemy[0].fEcameraPosX && (int)g_player.fPosX < g_enemy[0].fEcameraPosX + 18 && (int)g_player.fPosY < g_enemy[0].fEcameraPosY + 2 && (int)g_player.fPosY > g_enemy[0].fEcameraPosY - 2)
				{
					g_player.life = 0;
				}
			}

			if (g_map.mapcount == 3)
			{
				if ((int)g_player.fPosX > 40 && (int)g_player.fPosX < 48 && (int)g_player.fPosY < 15 && (int)g_player.fPosY > 8)
				{
					g_player.life = 0;
				}
			}

			if (g_map.mapcount == 5)
			{
				if ((int)g_player.fPosX > 19 && (int)g_player.fPosX < 27 && (int)g_player.fPosY < 12 && (int)g_player.fPosY > 2)
				{
					g_player.life = 0;
				}
			}

			if (g_map.mapcount == 4)
			{
				if ((int)g_player.fPosX > 19 && (int)g_player.fPosX < 27 && (int)g_player.fPosY < 12 && (int)g_player.fPosY > 2)
				{
					g_player.life = 0;
				}
			}
		}

		if (g_enemy[2].life == 1 && g_map.mapcount == 1)
		{
			if ((int)g_player.fPosX > g_enemy[2].fEPosX + 1.0f && (int)g_player.fPosX < g_enemy[2].fEPosX + 7.0f && (int)g_player.fPosY >= g_enemy[2].fEPosY - 2.0f && (int)g_player.fPosY <= g_enemy[2].fEPosY + 2.0f)
			{
				g_player.life = 0;
			}
		}
	}
}

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void DrawPlayer(void)
{	// 現在の位置
	if (g_player.life == 1 && g_ui.gameflag == 1)
	{
		textbackground(0);
		textcolor(0000);
		gotoxy((int)(g_player.fPosXOLD), (int)(g_player.fPosYOLD - 1.0f));      //先に消す
		printf("  ");
		gotoxy((int)(g_player.fPosXOLD), (int)(g_player.fPosYOLD));
		printf("  ");

		
			if (g_player.color == 0)
			{
				textcolor(1111);
				gotoxy((int)(g_player.fPosX), (int)(g_player.fPosY - 1.0f));
				printf("●");
				gotoxy((int)(g_player.fPosX), (int)(g_player.fPosY));
				printf("■");
			}
			if (g_player.color == 1)
			{
				textcolor(CYAN);
				gotoxy((int)(g_player.fPosX), (int)(g_player.fPosY - 1.0f));
				printf("●");
				gotoxy((int)(g_player.fPosX), (int)(g_player.fPosY));
				printf("■");
			}
	}
	
}

void Slow(void)
{
	if (inport(PJ_BTNS) == 8 && g_player.slowflag == 1 || inport(PK_G) && g_player.slowflag == 1)
	{
		playsound(slowBGM, 0);
		g_player.slow = 1;
		g_player.slowflag = 0;
	}

	if (g_player.slow == 1)
	{
		g_player.slowtime++;
	}

	if (g_player.slowtime % 180 == 0)
	{
		g_player.slow = 0;
		g_player.slowtime = 1;
		g_player.slowcooldownflag = 1;

	}
	if (g_player.slowcooldownflag == 1)
	{
		g_player.slowcooldown++;
		
	}
	if (g_player.slowcooldown % 600 == 0)
	{
		g_player.slowcooldown = 1;
		g_player.slowcooldownflag = 0;
		g_player.slowflag = 1;
	}
}
