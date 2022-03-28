//=============================================================================
//
// プレイヤー処理 [player.cpp]
//
//=============================================================================
#define CONIOEX
#include "conioex.h"
#include "player.h"
#include "main.h"
#include "ui.h"
#include "enemy.h"
#include "bullet.h"
#include "wall.h"
#include "map.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE_X			(0.3f)		// 地上での移動量Ｘ方向   　一回での移動量　　　//初期は0.75
#define VALUE_T_MOVE_X          (0.75f)
#define	VALUE_MOVE_Y			(0.1f)		// 地上での移動量Ｙ方向   　一回での移動量　　　//初期は0.75
#define	VALUE_RESIST_X			(0.50f)		// 地上での移動摩擦抵抗
#define	VALUE_RESIST_Y			(0.50f)		// 地上での移動摩擦抵抗
#define	LIMIT_LEFT				(3.0f)		// 移動範囲左端             |
#define	LIMIT_RIGHT				(77.0f)	    // 移動範囲右端             |--  画面端の設定    初期は78
#define	LIMIT_DOWN				(22.0f)		// 移動範囲下端             |
#define	LIMIT_UP				(3.0f)		// 移動範囲上端             |

#define ENEMYCAMERA_POS_X1				(3)		// 監視カメラ1のポジションＸ方向
#define ENEMYCAMERA_POS_Y1				(12)	// 監視カメラ1のポジションＹ方向

#define ENEMYCAMERA_POS_X2				(20)		// 監視カメラ2のポジションＸ方向
#define ENEMYCAMERA_POS_Y2				(8)	// 監視カメラ2のポジションＹ方向


//()内の数値をいじれば限界の数値も変わる ウィンドウのサイズ次第で変更する

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
ENEMY g_enemy[10];						// プレイヤーワーク
extern PLAYER g_player;
extern WALL g_wall;
extern BULLET g_Bullet;
extern UI g_ui;
extern MAP g_map;

//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
void InitEnemy(void)
{

	g_enemy[0].fEPosX = 36.0f;       //敵1の初期位置
	g_enemy[0].fEPosY = 3.0f;
	/*g_enemy[0].fEeyePosX[10] = 56;
	g_enemy[0].fEeyePosY[10] = 2;*/
	g_enemy[0].fEeyePosXOLD[10] = 0.0f;
	g_enemy[0].fEeyePosYOLD[10] = 0.0f;
	g_enemy[0].fEPosXOLD = 0.0f;
	g_enemy[0].fEPosYOLD = 0.0f;
	g_enemy[0].fEMoveX = 0.0f;
	g_enemy[0].fEMoveY = 0.0f;
	g_enemy[0].fEcameraPosX = 3;
	g_enemy[0].fEcameraPosY = 12;
	g_enemy[0].flag = 0;
	g_enemy[0].life = 1;
	g_enemy[0].count = 0;
	g_enemy[0].cameralife = 3;

	g_enemy[1].fEPosX = 45.0f;       //敵2の初期位置
	g_enemy[1].fEPosY = 13.0f;
	/*g_enemy[1].fEeyePosX[10] = 56;
	g_enemy[1].fEeyePosY[10] = 2;*/
	g_enemy[1].fEeyePosXOLD[10] = 0.0f;
	g_enemy[1].fEeyePosYOLD[10] = 0.0f;
	g_enemy[1].fEPosXOLD = 0.0f;
	g_enemy[1].fEPosYOLD = 0.0f;
	g_enemy[1].fEMoveX = 0.0f;
	g_enemy[1].fEMoveY = 0.0f;
	g_enemy[1].flag = 0;
	g_enemy[1].life = 1;

	g_enemy[2].fEPosX = 60.0f;       //敵3の初期位置
	g_enemy[2].fEPosY = 11.0f;
	/*g_enemy[2].fEeyePosX[10] = 56;
	g_enemy[2].fEeyePosY[10] = 2;*/
	g_enemy[2].fEeyePosXOLD[10] = 0.0f;
	g_enemy[2].fEeyePosYOLD[10] = 0.0f;
	g_enemy[2].fEPosXOLD = 0.0f;
	g_enemy[2].fEPosYOLD = 0.0f;
	g_enemy[2].fEMoveX = 0.0f;
	g_enemy[2].fEMoveY = 0.0f;
	//g_enemy[2].fEcameraPosX = 50;
	//g_enemy[2].fEcameraPosY = 7;
	g_enemy[2].life = 1;

	g_enemy[3].fEPosX = 65.0f;       //敵4の初期位置
	g_enemy[3].fEPosY = 18.0f;
	/*g_enemy[3].fEeyePosX[10] = 56;
	g_enemy[3].fEeyePosY[10] = 2;*/
	g_enemy[3].fEeyePosXOLD[10] = 0.0f;
	g_enemy[3].fEeyePosYOLD[10] = 0.0f;
	g_enemy[3].fEPosXOLD = 0.0f;
	g_enemy[3].fEPosYOLD = 0.0f;
	g_enemy[3].fEMoveX = 0.0f;
	g_enemy[3].fEMoveY = 0.0f;
	g_enemy[3].flag = 0;
	g_enemy[3].life = 1;

	g_enemy[4].fEPosX = 60.0f;       //敵5の初期位置
	g_enemy[4].fEPosY = 5.0f;
	/*g_enemy[4].fEeyePosX[10] = 56;
	g_enemy[4].fEeyePosY[10] = 2;*/
	g_enemy[4].fEeyePosXOLD[10] = 0.0f;
	g_enemy[4].fEeyePosYOLD[10] = 0.0f;
	g_enemy[4].fEPosXOLD = 0.0f;
	g_enemy[4].fEPosYOLD = 0.0f;
	g_enemy[4].fEMoveX = 0.0f;
	g_enemy[4].fEMoveY = 0.0f;
	g_enemy[4].flag = 0;
	g_enemy[4].life = 1;
	g_enemy[1].fEcameraPosX = 44;
	g_enemy[1].fEcameraPosY = 8;

	g_enemy[5].fEPosX = 26.0f;       //敵5の初期位置
	g_enemy[5].fEPosY = 11.0f;
	/*g_enemy[5].fEeyePosX[10] = 56;
	g_enemy[5].fEeyePosY[10] = 2;*/
	g_enemy[5].fEeyePosXOLD[10] = 0.0f;
	g_enemy[5].fEeyePosYOLD[10] = 0.0f;
	g_enemy[5].fEPosXOLD = 0.0f;
	g_enemy[5].fEPosYOLD = 0.0f;
	g_enemy[5].fEMoveX = 0.0f;
	g_enemy[5].fEMoveY = 0.0f;
	g_enemy[5].flag = 0;
	g_enemy[5].life = 1;
	g_enemy[5].fEcameraPosX = 44;
	g_enemy[5].fEcameraPosY = 8;
}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void UninitEnemy(void)
{
}

//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void UpdateEnemy(void)
{
	if (g_map.mapcount == 1)
	{
		g_enemy[2].fEPosXOLD = g_enemy[2].fEPosX;
		g_enemy[2].fEPosYOLD = g_enemy[2].fEPosY;

		g_enemy[2].fEeyePosXOLD[0] = g_enemy[2].fEeyePosX[0];
		g_enemy[2].fEeyePosYOLD[0] = g_enemy[2].fEeyePosY[0];
		g_enemy[2].fEeyePosXOLD[1] = g_enemy[2].fEeyePosX[1];
		g_enemy[2].fEeyePosYOLD[1] = g_enemy[2].fEeyePosY[1];
		g_enemy[2].fEeyePosXOLD[2] = g_enemy[2].fEeyePosX[2];
		g_enemy[2].fEeyePosYOLD[2] = g_enemy[2].fEeyePosY[2];
		g_enemy[2].fEeyePosXOLD[3] = g_enemy[2].fEeyePosX[3];
		g_enemy[2].fEeyePosYOLD[3] = g_enemy[2].fEeyePosY[3];
		g_enemy[2].fEeyePosXOLD[4] = g_enemy[2].fEeyePosX[4];
		g_enemy[2].fEeyePosYOLD[4] = g_enemy[2].fEeyePosY[4];
		g_enemy[2].fEeyePosXOLD[5] = g_enemy[2].fEeyePosX[5];
		g_enemy[2].fEeyePosYOLD[5] = g_enemy[2].fEeyePosY[5];
		g_enemy[2].fEeyePosXOLD[6] = g_enemy[2].fEeyePosX[6];
		g_enemy[2].fEeyePosYOLD[6] = g_enemy[2].fEeyePosY[6];
		g_enemy[2].fEeyePosXOLD[7] = g_enemy[2].fEeyePosX[7];
		g_enemy[2].fEeyePosYOLD[7] = g_enemy[2].fEeyePosY[7];
		g_enemy[2].fEeyePosXOLD[8] = g_enemy[2].fEeyePosX[8];
		g_enemy[2].fEeyePosYOLD[8] = g_enemy[2].fEeyePosY[8];

		/*g_enemy[2].fEcameraPosX = ENEMYCAMERA_POS_X2;
		g_enemy[2].fEcameraPosY = ENEMYCAMERA_POS_Y2;*/
	}

	if (g_map.mapcount == 2)
	{
		g_enemy[0].fEPosXOLD = g_enemy[0].fEPosX;
		g_enemy[0].fEPosYOLD = g_enemy[0].fEPosY;

		g_enemy[1].fEPosXOLD = g_enemy[1].fEPosX;
		g_enemy[1].fEPosYOLD = g_enemy[1].fEPosY;

		g_enemy[3].fEPosXOLD = g_enemy[3].fEPosX;
		g_enemy[3].fEPosYOLD = g_enemy[3].fEPosY;

		g_enemy[0].fEcameraPosX = ENEMYCAMERA_POS_X1;
		g_enemy[0].fEcameraPosY = ENEMYCAMERA_POS_Y1;

		g_enemy[0].fEeyePosXOLD[0] = g_enemy[0].fEeyePosX[0];
		g_enemy[0].fEeyePosYOLD[0] = g_enemy[0].fEeyePosY[0];
		g_enemy[0].fEeyePosXOLD[1] = g_enemy[0].fEeyePosX[1];
		g_enemy[0].fEeyePosYOLD[1] = g_enemy[0].fEeyePosY[1];
		g_enemy[0].fEeyePosXOLD[2] = g_enemy[0].fEeyePosX[2];
		g_enemy[0].fEeyePosYOLD[2] = g_enemy[0].fEeyePosY[2];
		g_enemy[0].fEeyePosXOLD[3] = g_enemy[0].fEeyePosX[3];
		g_enemy[0].fEeyePosYOLD[3] = g_enemy[0].fEeyePosY[3];
		g_enemy[0].fEeyePosXOLD[4] = g_enemy[0].fEeyePosX[4];
		g_enemy[0].fEeyePosYOLD[4] = g_enemy[0].fEeyePosY[4];
		g_enemy[0].fEeyePosXOLD[5] = g_enemy[0].fEeyePosX[5];
		g_enemy[0].fEeyePosYOLD[5] = g_enemy[0].fEeyePosY[5];
		g_enemy[0].fEeyePosXOLD[6] = g_enemy[0].fEeyePosX[6];
		g_enemy[0].fEeyePosYOLD[6] = g_enemy[0].fEeyePosY[6];
		g_enemy[0].fEeyePosXOLD[7] = g_enemy[0].fEeyePosX[7];
		g_enemy[0].fEeyePosYOLD[7] = g_enemy[0].fEeyePosY[7];
		g_enemy[0].fEeyePosXOLD[8] = g_enemy[0].fEeyePosX[8];
		g_enemy[0].fEeyePosYOLD[8] = g_enemy[0].fEeyePosY[8];

		g_enemy[1].fEeyePosXOLD[0] = g_enemy[1].fEeyePosX[0];
		g_enemy[1].fEeyePosYOLD[0] = g_enemy[1].fEeyePosY[0];
		g_enemy[1].fEeyePosXOLD[1] = g_enemy[1].fEeyePosX[1];
		g_enemy[1].fEeyePosYOLD[1] = g_enemy[1].fEeyePosY[1];
		g_enemy[1].fEeyePosXOLD[2] = g_enemy[1].fEeyePosX[2];
		g_enemy[1].fEeyePosYOLD[2] = g_enemy[1].fEeyePosY[2];
		g_enemy[1].fEeyePosXOLD[3] = g_enemy[1].fEeyePosX[3];
		g_enemy[1].fEeyePosYOLD[3] = g_enemy[1].fEeyePosY[3];
		g_enemy[1].fEeyePosXOLD[4] = g_enemy[1].fEeyePosX[4];
		g_enemy[1].fEeyePosYOLD[4] = g_enemy[1].fEeyePosY[4];
		g_enemy[1].fEeyePosXOLD[5] = g_enemy[1].fEeyePosX[5];
		g_enemy[1].fEeyePosYOLD[5] = g_enemy[1].fEeyePosY[5];
		g_enemy[1].fEeyePosXOLD[6] = g_enemy[1].fEeyePosX[6];
		g_enemy[1].fEeyePosYOLD[6] = g_enemy[1].fEeyePosY[6];
		g_enemy[1].fEeyePosXOLD[7] = g_enemy[1].fEeyePosX[7];
		g_enemy[1].fEeyePosYOLD[7] = g_enemy[1].fEeyePosY[7];
		g_enemy[1].fEeyePosXOLD[8] = g_enemy[1].fEeyePosX[8];
		g_enemy[1].fEeyePosYOLD[8] = g_enemy[1].fEeyePosY[8];

		g_enemy[3].fEeyePosXOLD[0] = g_enemy[3].fEeyePosX[0];
		g_enemy[3].fEeyePosYOLD[0] = g_enemy[3].fEeyePosY[0];
		g_enemy[3].fEeyePosXOLD[1] = g_enemy[3].fEeyePosX[1];
		g_enemy[3].fEeyePosYOLD[1] = g_enemy[3].fEeyePosY[1];
		g_enemy[3].fEeyePosXOLD[2] = g_enemy[3].fEeyePosX[2];
		g_enemy[3].fEeyePosYOLD[2] = g_enemy[3].fEeyePosY[2];
		g_enemy[3].fEeyePosXOLD[3] = g_enemy[3].fEeyePosX[3];
		g_enemy[3].fEeyePosYOLD[3] = g_enemy[3].fEeyePosY[3];
		g_enemy[3].fEeyePosXOLD[4] = g_enemy[3].fEeyePosX[4];
		g_enemy[3].fEeyePosYOLD[4] = g_enemy[3].fEeyePosY[4];
		g_enemy[3].fEeyePosXOLD[5] = g_enemy[3].fEeyePosX[5];
		g_enemy[3].fEeyePosYOLD[5] = g_enemy[3].fEeyePosY[5];
		g_enemy[3].fEeyePosXOLD[6] = g_enemy[3].fEeyePosX[6];
		g_enemy[3].fEeyePosYOLD[6] = g_enemy[3].fEeyePosY[6];
		g_enemy[3].fEeyePosXOLD[7] = g_enemy[3].fEeyePosX[7];
		g_enemy[3].fEeyePosYOLD[7] = g_enemy[3].fEeyePosY[7];
		g_enemy[3].fEeyePosXOLD[8] = g_enemy[3].fEeyePosX[8];
		g_enemy[3].fEeyePosYOLD[8] = g_enemy[3].fEeyePosY[8];
	}

	if (g_map.mapcount == 3)
	{
		g_enemy[4].fEPosXOLD = g_enemy[4].fEPosX;
		g_enemy[4].fEPosYOLD = g_enemy[4].fEPosY;

		g_enemy[1].fEcameraPosX = ENEMYCAMERA_POS_X1;
		g_enemy[1].fEcameraPosY = ENEMYCAMERA_POS_Y1;

		g_enemy[4].fEeyePosXOLD[0] = g_enemy[4].fEeyePosX[0];
		g_enemy[4].fEeyePosYOLD[0] = g_enemy[4].fEeyePosY[0];
		g_enemy[4].fEeyePosXOLD[1] = g_enemy[4].fEeyePosX[1];
		g_enemy[4].fEeyePosYOLD[1] = g_enemy[4].fEeyePosY[1];
		g_enemy[4].fEeyePosXOLD[2] = g_enemy[4].fEeyePosX[2];
		g_enemy[4].fEeyePosYOLD[2] = g_enemy[4].fEeyePosY[2];
		g_enemy[4].fEeyePosXOLD[3] = g_enemy[4].fEeyePosX[3];
		g_enemy[4].fEeyePosYOLD[3] = g_enemy[4].fEeyePosY[3];
		g_enemy[4].fEeyePosXOLD[4] = g_enemy[4].fEeyePosX[4];
		g_enemy[4].fEeyePosYOLD[4] = g_enemy[4].fEeyePosY[4];
		g_enemy[4].fEeyePosXOLD[5] = g_enemy[4].fEeyePosX[5];
		g_enemy[4].fEeyePosYOLD[5] = g_enemy[4].fEeyePosY[5];
		g_enemy[4].fEeyePosXOLD[6] = g_enemy[4].fEeyePosX[6];
		g_enemy[4].fEeyePosYOLD[6] = g_enemy[4].fEeyePosY[6];
		g_enemy[4].fEeyePosXOLD[7] = g_enemy[4].fEeyePosX[7];
		g_enemy[4].fEeyePosYOLD[7] = g_enemy[4].fEeyePosY[7];
		g_enemy[4].fEeyePosXOLD[8] = g_enemy[4].fEeyePosX[8];
		g_enemy[4].fEeyePosYOLD[8] = g_enemy[4].fEeyePosY[8];
	}

	if (g_map.mapcount == 5)
	{
		g_enemy[5].fEPosXOLD = g_enemy[5].fEPosX;
		g_enemy[5].fEPosYOLD = g_enemy[5].fEPosY;

		g_enemy[5].fEeyePosXOLD[0] = g_enemy[5].fEeyePosX[0];
		g_enemy[5].fEeyePosYOLD[0] = g_enemy[5].fEeyePosY[0];
		g_enemy[5].fEeyePosXOLD[1] = g_enemy[5].fEeyePosX[1];
		g_enemy[5].fEeyePosYOLD[1] = g_enemy[5].fEeyePosY[1];
		g_enemy[5].fEeyePosXOLD[2] = g_enemy[5].fEeyePosX[2];
		g_enemy[5].fEeyePosYOLD[2] = g_enemy[5].fEeyePosY[2];
		g_enemy[5].fEeyePosXOLD[3] = g_enemy[5].fEeyePosX[3];
		g_enemy[5].fEeyePosYOLD[3] = g_enemy[5].fEeyePosY[3];
		g_enemy[5].fEeyePosXOLD[4] = g_enemy[5].fEeyePosX[4];
		g_enemy[5].fEeyePosYOLD[4] = g_enemy[5].fEeyePosY[4];
		g_enemy[5].fEeyePosXOLD[5] = g_enemy[5].fEeyePosX[5];
		g_enemy[5].fEeyePosYOLD[5] = g_enemy[5].fEeyePosY[5];
		g_enemy[5].fEeyePosXOLD[6] = g_enemy[5].fEeyePosX[6];
		g_enemy[5].fEeyePosYOLD[6] = g_enemy[5].fEeyePosY[6];
		g_enemy[5].fEeyePosXOLD[7] = g_enemy[5].fEeyePosX[7];
		g_enemy[5].fEeyePosYOLD[7] = g_enemy[5].fEeyePosY[7];
		g_enemy[5].fEeyePosXOLD[8] = g_enemy[5].fEeyePosX[8];
		g_enemy[5].fEeyePosYOLD[8] = g_enemy[5].fEeyePosY[8];
	}

		
		if (g_enemy[0].flag == 0 && g_player.slow == 0)
		{
			g_enemy[0].fEMoveY += VALUE_MOVE_Y;
		}

		if (g_enemy[0].flag == 1 && g_player.slow == 0)
		{
			g_enemy[0].fEMoveY -= VALUE_MOVE_Y;
		}

		if (g_enemy[1].flag == 0 && g_player.slow == 0)
		{
			g_enemy[1].fEMoveY += VALUE_MOVE_Y;
		}

		if (g_enemy[1].flag == 1 && g_player.slow == 0)
		{
			g_enemy[1].fEMoveY -= VALUE_MOVE_Y;
		}

		if (g_enemy[3].flag == 0 && g_player.slow == 0)
		{
			g_enemy[3].fEMoveY += VALUE_MOVE_Y;
		}

		if (g_enemy[3].flag == 1 && g_player.slow == 0)
		{
			g_enemy[3].fEMoveY -= VALUE_MOVE_Y;
		}

		if (g_enemy[4].flag == 0 && g_player.slow == 0)
		{
			g_enemy[4].fEMoveX -= VALUE_MOVE_X;
		}

		if (g_enemy[4].flag == 1 && g_player.slow == 0)
		{
			g_enemy[4].fEMoveX += VALUE_MOVE_X;
		}
		if (g_enemy[5].flag == 0 && g_player.slow == 0)
		{
			g_enemy[5].fEMoveX -= VALUE_MOVE_X;
		}
		if (g_enemy[5].flag == 1 && g_player.slow == 0)
		{
			g_enemy[5].fEMoveX += VALUE_MOVE_X;
		}

		if (g_enemy[0].flag == 0 && g_player.slow == 1)
		{
			g_enemy[0].fEMoveY += VALUE_MOVE_Y / 2;
		}

		if (g_enemy[0].flag == 1 && g_player.slow == 1)
		{
			g_enemy[0].fEMoveY -= VALUE_MOVE_Y / 2;
		}

		if (g_enemy[1].flag == 0 && g_player.slow == 1)
		{
			g_enemy[1].fEMoveY += VALUE_MOVE_Y / 2;
		}

		if (g_enemy[1].flag == 1 && g_player.slow == 1)
		{
			g_enemy[1].fEMoveY -= VALUE_MOVE_Y / 2;
		}

		if (g_enemy[3].flag == 0 && g_player.slow == 1)
		{
			g_enemy[3].fEMoveY += VALUE_MOVE_Y / 2;
		}

		if (g_enemy[3].flag == 1 && g_player.slow == 1)
		{
			g_enemy[3].fEMoveY -= VALUE_MOVE_Y / 2;
		}

		if (g_enemy[4].flag == 0 && g_player.slow == 1)
		{
			g_enemy[4].fEMoveX -= VALUE_MOVE_X / 2;
		}

		if (g_enemy[4].flag == 1 && g_player.slow == 1)
		{
			g_enemy[4].fEMoveX += VALUE_MOVE_X / 2;
		}

		if (g_enemy[5].flag == 0 && g_player.slow == 1)
		{
			g_enemy[5].fEMoveX -= VALUE_MOVE_X / 2;
		}

		if (g_enemy[5].flag == 1 && g_player.slow == 1)
		{
			g_enemy[5].fEMoveX += VALUE_MOVE_X / 2;
		}


		// 抵抗を加える
		g_enemy[0].fEMoveY += (0.0f - g_enemy[0].fEMoveY) * VALUE_RESIST_Y;
		g_enemy[1].fEMoveY += (0.0f - g_enemy[1].fEMoveY) * VALUE_RESIST_Y;
		g_enemy[3].fEMoveY += (0.0f - g_enemy[3].fEMoveY) * VALUE_RESIST_Y;
		g_enemy[4].fEMoveX += (0.0f - g_enemy[4].fEMoveX) * VALUE_RESIST_Y;
		g_enemy[5].fEMoveX += (0.0f - g_enemy[5].fEMoveX) * VALUE_RESIST_Y;


		if (g_map.mapcount == 1 && g_enemy[2].life == 1)
		{
				g_enemy[2].fEeyePosX[0] = g_enemy[2].fEPosX + 2.0f;
				g_enemy[2].fEeyePosY[0] = g_enemy[2].fEPosY;

				g_enemy[2].fEeyePosX[1] = g_enemy[2].fEPosX + 4;
				g_enemy[2].fEeyePosY[1] = g_enemy[2].fEPosY - 1;

				g_enemy[2].fEeyePosX[2] = g_enemy[2].fEPosX + 4;
				g_enemy[2].fEeyePosY[2] = g_enemy[2].fEPosY;

				g_enemy[2].fEeyePosX[3] = g_enemy[2].fEPosX + 4;
				g_enemy[2].fEeyePosY[3] = g_enemy[2].fEPosY + 1;

				g_enemy[2].fEeyePosX[4] = g_enemy[2].fEPosX + 4;
				g_enemy[2].fEeyePosY[4] = g_enemy[2].fEPosY - 2;

				g_enemy[2].fEeyePosX[5] = g_enemy[2].fEPosX + 4;
				g_enemy[2].fEeyePosY[5] = g_enemy[2].fEPosY - 1;

				g_enemy[2].fEeyePosX[6] = g_enemy[2].fEPosX + 4;
				g_enemy[2].fEeyePosY[6] = g_enemy[2].fEPosY;

				g_enemy[2].fEeyePosX[7] = g_enemy[2].fEPosX + 4;
				g_enemy[2].fEeyePosY[7] = g_enemy[2].fEPosY + 1;

				g_enemy[2].fEeyePosX[8] = g_enemy[2].fEPosX + 4;
				g_enemy[2].fEeyePosY[8] = g_enemy[2].fEPosY + 2;
			
		}

		if (g_map.mapcount == 2)
		{
			// 位置更新
			if (g_enemy[0].life == 1 && g_ui.gameflag == 1)
			{
				g_enemy[0].fEPosY += g_enemy[0].fEMoveY;
			}
			if (g_enemy[1].life == 1 && g_ui.gameflag == 1)
			{
				g_enemy[1].fEPosY += g_enemy[1].fEMoveY;
			}

			if (g_enemy[3].life == 1 && g_ui.gameflag == 1)
			{
				g_enemy[3].fEPosY += g_enemy[3].fEMoveY;
			}

			if (g_enemy[0].life == 1 && g_enemy[0].flag == 0)
			{
				g_enemy[0].fEeyePosX[0] = g_enemy[0].fEPosX;
				g_enemy[0].fEeyePosY[0] = g_enemy[0].fEPosY + 1;

				g_enemy[0].fEeyePosX[1] = g_enemy[0].fEPosX - 2;
				g_enemy[0].fEeyePosY[1] = g_enemy[0].fEPosY + 2;

				g_enemy[0].fEeyePosX[2] = g_enemy[0].fEPosX;
				g_enemy[0].fEeyePosY[2] = g_enemy[0].fEPosY + 2;

				g_enemy[0].fEeyePosX[3] = g_enemy[0].fEPosX + 2;
				g_enemy[0].fEeyePosY[3] = g_enemy[0].fEPosY + 2;

				g_enemy[0].fEeyePosX[4] = g_enemy[0].fEPosX - 4;
				g_enemy[0].fEeyePosY[4] = g_enemy[0].fEPosY + 3;

				g_enemy[0].fEeyePosX[5] = g_enemy[0].fEPosX - 2;
				g_enemy[0].fEeyePosY[5] = g_enemy[0].fEPosY + 3;

				g_enemy[0].fEeyePosX[6] = g_enemy[0].fEPosX;
				g_enemy[0].fEeyePosY[6] = g_enemy[0].fEPosY + 3;

				g_enemy[0].fEeyePosX[7] = g_enemy[0].fEPosX + 2;
				g_enemy[0].fEeyePosY[7] = g_enemy[0].fEPosY + 3;

				g_enemy[0].fEeyePosX[8] = g_enemy[0].fEPosX + 4;
				g_enemy[0].fEeyePosY[8] = g_enemy[0].fEPosY + 3;
			}

			if (g_enemy[0].life == 1 && g_enemy[0].flag == 1)
			{
				g_enemy[0].fEeyePosX[0] = g_enemy[0].fEPosX;
				g_enemy[0].fEeyePosY[0] = g_enemy[0].fEPosY - 2;

				g_enemy[0].fEeyePosX[1] = g_enemy[0].fEPosX - 2;
				g_enemy[0].fEeyePosY[1] = g_enemy[0].fEPosY - 3;

				g_enemy[0].fEeyePosX[2] = g_enemy[0].fEPosX;
				g_enemy[0].fEeyePosY[2] = g_enemy[0].fEPosY - 3;

				g_enemy[0].fEeyePosX[3] = g_enemy[0].fEPosX + 2;
				g_enemy[0].fEeyePosY[3] = g_enemy[0].fEPosY - 3;

				g_enemy[0].fEeyePosX[4] = g_enemy[0].fEPosX - 4;
				g_enemy[0].fEeyePosY[4] = g_enemy[0].fEPosY - 4;

				g_enemy[0].fEeyePosX[5] = g_enemy[0].fEPosX - 2;
				g_enemy[0].fEeyePosY[5] = g_enemy[0].fEPosY - 4;

				g_enemy[0].fEeyePosX[6] = g_enemy[0].fEPosX;
				g_enemy[0].fEeyePosY[6] = g_enemy[0].fEPosY - 4;

				g_enemy[0].fEeyePosX[7] = g_enemy[0].fEPosX + 2;
				g_enemy[0].fEeyePosY[7] = g_enemy[0].fEPosY - 4;

				g_enemy[0].fEeyePosX[8] = g_enemy[0].fEPosX + 4;
				g_enemy[0].fEeyePosY[8] = g_enemy[0].fEPosY - 4;
			}

			if (g_enemy[1].life == 1 && g_enemy[1].flag == 0)
			{
				g_enemy[1].fEeyePosX[0] = g_enemy[1].fEPosX;
				g_enemy[1].fEeyePosY[0] = g_enemy[1].fEPosY + 1;

				g_enemy[1].fEeyePosX[1] = g_enemy[1].fEPosX - 2;
				g_enemy[1].fEeyePosY[1] = g_enemy[1].fEPosY + 2;

				g_enemy[1].fEeyePosX[2] = g_enemy[1].fEPosX;
				g_enemy[1].fEeyePosY[2] = g_enemy[1].fEPosY + 2;

				g_enemy[1].fEeyePosX[3] = g_enemy[1].fEPosX + 2;
				g_enemy[1].fEeyePosY[3] = g_enemy[1].fEPosY + 2;

				g_enemy[1].fEeyePosX[4] = g_enemy[1].fEPosX - 4;
				g_enemy[1].fEeyePosY[4] = g_enemy[1].fEPosY + 3;

				g_enemy[1].fEeyePosX[5] = g_enemy[1].fEPosX - 2;
				g_enemy[1].fEeyePosY[5] = g_enemy[1].fEPosY + 3;

				g_enemy[1].fEeyePosX[6] = g_enemy[1].fEPosX;
				g_enemy[1].fEeyePosY[6] = g_enemy[1].fEPosY + 3;

				g_enemy[1].fEeyePosX[7] = g_enemy[1].fEPosX + 2;
				g_enemy[1].fEeyePosY[7] = g_enemy[1].fEPosY + 3;

				g_enemy[1].fEeyePosX[8] = g_enemy[1].fEPosX + 4;
				g_enemy[1].fEeyePosY[8] = g_enemy[1].fEPosY + 3;
			}

			if (g_enemy[1].life == 1 && g_enemy[1].flag == 1)
			{
				g_enemy[1].fEeyePosX[0] = g_enemy[1].fEPosX;
				g_enemy[1].fEeyePosY[0] = g_enemy[1].fEPosY - 2;

				g_enemy[1].fEeyePosX[1] = g_enemy[1].fEPosX - 2;
				g_enemy[1].fEeyePosY[1] = g_enemy[1].fEPosY - 3;

				g_enemy[1].fEeyePosX[2] = g_enemy[1].fEPosX;
				g_enemy[1].fEeyePosY[2] = g_enemy[1].fEPosY - 3;

				g_enemy[1].fEeyePosX[3] = g_enemy[1].fEPosX + 2;
				g_enemy[1].fEeyePosY[3] = g_enemy[1].fEPosY - 3;

				g_enemy[1].fEeyePosX[4] = g_enemy[1].fEPosX - 4;
				g_enemy[1].fEeyePosY[4] = g_enemy[1].fEPosY - 4;

				g_enemy[1].fEeyePosX[5] = g_enemy[1].fEPosX - 2;
				g_enemy[1].fEeyePosY[5] = g_enemy[1].fEPosY - 4;

				g_enemy[1].fEeyePosX[6] = g_enemy[1].fEPosX;
				g_enemy[1].fEeyePosY[6] = g_enemy[1].fEPosY - 4;

				g_enemy[1].fEeyePosX[7] = g_enemy[1].fEPosX + 2;
				g_enemy[1].fEeyePosY[7] = g_enemy[1].fEPosY - 4;

				g_enemy[1].fEeyePosX[8] = g_enemy[1].fEPosX + 4;
				g_enemy[1].fEeyePosY[8] = g_enemy[1].fEPosY - 4;
			}

			if (g_enemy[3].life == 1 && g_enemy[3].flag == 0)
			{
				g_enemy[3].fEeyePosX[0] = g_enemy[3].fEPosX;
				g_enemy[3].fEeyePosY[0] = g_enemy[3].fEPosY + 1;

				g_enemy[3].fEeyePosX[1] = g_enemy[3].fEPosX - 2;
				g_enemy[3].fEeyePosY[1] = g_enemy[3].fEPosY + 2;

				g_enemy[3].fEeyePosX[2] = g_enemy[3].fEPosX;
				g_enemy[3].fEeyePosY[2] = g_enemy[3].fEPosY + 2;

				g_enemy[3].fEeyePosX[3] = g_enemy[3].fEPosX + 2;
				g_enemy[3].fEeyePosY[3] = g_enemy[3].fEPosY + 2;

				g_enemy[3].fEeyePosX[4] = g_enemy[3].fEPosX - 4;
				g_enemy[3].fEeyePosY[4] = g_enemy[3].fEPosY + 3;

				g_enemy[3].fEeyePosX[5] = g_enemy[3].fEPosX - 2;
				g_enemy[3].fEeyePosY[5] = g_enemy[3].fEPosY + 3;

				g_enemy[3].fEeyePosX[6] = g_enemy[3].fEPosX;
				g_enemy[3].fEeyePosY[6] = g_enemy[3].fEPosY + 3;

				g_enemy[3].fEeyePosX[7] = g_enemy[3].fEPosX + 2;
				g_enemy[3].fEeyePosY[7] = g_enemy[3].fEPosY + 3;

				g_enemy[3].fEeyePosX[8] = g_enemy[3].fEPosX + 4;
				g_enemy[3].fEeyePosY[8] = g_enemy[3].fEPosY + 3;
			}

			if (g_enemy[3].life == 1 && g_enemy[3].flag == 1)
			{
				g_enemy[3].fEeyePosX[0] = g_enemy[3].fEPosX;
				g_enemy[3].fEeyePosY[0] = g_enemy[3].fEPosY - 2;

				g_enemy[3].fEeyePosX[1] = g_enemy[3].fEPosX - 2;
				g_enemy[3].fEeyePosY[1] = g_enemy[3].fEPosY - 3;

				g_enemy[3].fEeyePosX[2] = g_enemy[3].fEPosX;
				g_enemy[3].fEeyePosY[2] = g_enemy[3].fEPosY - 3;

				g_enemy[3].fEeyePosX[3] = g_enemy[3].fEPosX + 2;
				g_enemy[3].fEeyePosY[3] = g_enemy[3].fEPosY - 3;

				g_enemy[3].fEeyePosX[4] = g_enemy[3].fEPosX - 4;
				g_enemy[3].fEeyePosY[4] = g_enemy[3].fEPosY - 4;

				g_enemy[3].fEeyePosX[5] = g_enemy[3].fEPosX - 2;
				g_enemy[3].fEeyePosY[5] = g_enemy[3].fEPosY - 4;

				g_enemy[3].fEeyePosX[6] = g_enemy[3].fEPosX;
				g_enemy[3].fEeyePosY[6] = g_enemy[3].fEPosY - 4;

				g_enemy[3].fEeyePosX[7] = g_enemy[3].fEPosX + 2;
				g_enemy[3].fEeyePosY[7] = g_enemy[3].fEPosY - 4;

				g_enemy[3].fEeyePosX[8] = g_enemy[3].fEPosX + 4;
				g_enemy[3].fEeyePosY[8] = g_enemy[3].fEPosY - 4;
			}

			if (g_enemy[0].fEPosY > LIMIT_DOWN - 3)
			{
				//g_enemy.fEPosY = LIMIT_DOWN;       //画面の限界がLIMIT_DOWNなので移動した数値を限界の数値にして移動してないように見える
				g_enemy[0].flag = 1;

			}

			if (g_enemy[0].fEPosY < LIMIT_UP + 3)
			{
				//g_enemy.fEPosY = LIMIT_UP;         //画面の限界がLIMIT_UPなので移動した数値を限界の数値にして移動してないように見える
				g_enemy[0].flag = 0;
			}


			if (g_enemy[1].fEPosY > LIMIT_DOWN - 3)
			{
				//g_enemy.fEPosY = LIMIT_DOWN;       //画面の限界がLIMIT_DOWNなので移動した数値を限界の数値にして移動してないように見える
				g_enemy[1].flag = 1;

			}

			if (g_enemy[1].fEPosY < LIMIT_UP + 3)
			{
				//g_enemy.fEPosY = LIMIT_UP;         //画面の限界がLIMIT_UPなので移動した数値を限界の数値にして移動してないように見える
				g_enemy[1].flag = 0;
			}

			if (g_enemy[3].fEPosY > LIMIT_DOWN - 3)
			{
				//g_enemy.fEPosY = LIMIT_DOWN;       //画面の限界がLIMIT_DOWNなので移動した数値を限界の数値にして移動してないように見える
				g_enemy[3].flag = 1;

			}

			if (g_enemy[3].fEPosY < LIMIT_UP + 3)
			{
				//g_enemy.fEPosY = LIMIT_UP;         //画面の限界がLIMIT_UPなので移動した数値を限界の数値にして移動してないように見える
				g_enemy[3].flag = 0;
			}
		}
	
		if (g_map.mapcount == 3)
		{
			if (g_enemy[4].life == 1 && g_ui.gameflag == 1)
			{
				g_enemy[4].fEPosX += g_enemy[4].fEMoveX;
			}

			if (g_enemy[4].life == 1 && g_enemy[4].flag == 0)
			{
				g_enemy[4].fEeyePosX[0] = g_enemy[4].fEPosX - 2;
				g_enemy[4].fEeyePosY[0] = g_enemy[4].fEPosY - 1;

				g_enemy[4].fEeyePosX[1] = g_enemy[4].fEPosX - 4;
				g_enemy[4].fEeyePosY[1] = g_enemy[4].fEPosY - 2;

				g_enemy[4].fEeyePosX[2] = g_enemy[4].fEPosX - 4;
				g_enemy[4].fEeyePosY[2] = g_enemy[4].fEPosY - 1;

				g_enemy[4].fEeyePosX[3] = g_enemy[4].fEPosX - 4;
				g_enemy[4].fEeyePosY[3] = g_enemy[4].fEPosY;

				g_enemy[4].fEeyePosX[4] = g_enemy[4].fEPosX - 6;
				g_enemy[4].fEeyePosY[4] = g_enemy[4].fEPosY - 3;

				g_enemy[4].fEeyePosX[5] = g_enemy[4].fEPosX - 6;
				g_enemy[4].fEeyePosY[5] = g_enemy[4].fEPosY - 2;

				g_enemy[4].fEeyePosX[6] = g_enemy[4].fEPosX - 6;
				g_enemy[4].fEeyePosY[6] = g_enemy[4].fEPosY - 1;

				g_enemy[4].fEeyePosX[7] = g_enemy[4].fEPosX - 6;
				g_enemy[4].fEeyePosY[7] = g_enemy[4].fEPosY;

				g_enemy[4].fEeyePosX[8] = g_enemy[4].fEPosX - 6;
				g_enemy[4].fEeyePosY[8] = g_enemy[4].fEPosY + 1;
			}

			if (g_enemy[4].life == 1 && g_enemy[4].flag == 1)
			{
				g_enemy[4].fEeyePosX[0] = g_enemy[4].fEPosX + 2;
				g_enemy[4].fEeyePosY[0] = g_enemy[4].fEPosY - 1;

				g_enemy[4].fEeyePosX[1] = g_enemy[4].fEPosX + 4;
				g_enemy[4].fEeyePosY[1] = g_enemy[4].fEPosY - 2;

				g_enemy[4].fEeyePosX[2] = g_enemy[4].fEPosX + 4;
				g_enemy[4].fEeyePosY[2] = g_enemy[4].fEPosY - 1;

				g_enemy[4].fEeyePosX[3] = g_enemy[4].fEPosX + 4;
				g_enemy[4].fEeyePosY[3] = g_enemy[4].fEPosY;

				g_enemy[4].fEeyePosX[4] = g_enemy[4].fEPosX + 6;
				g_enemy[4].fEeyePosY[4] = g_enemy[4].fEPosY - 3;

				g_enemy[4].fEeyePosX[5] = g_enemy[4].fEPosX + 6;
				g_enemy[4].fEeyePosY[5] = g_enemy[4].fEPosY - 2;

				g_enemy[4].fEeyePosX[6] = g_enemy[4].fEPosX + 6;
				g_enemy[4].fEeyePosY[6] = g_enemy[4].fEPosY - 1;

				g_enemy[4].fEeyePosX[7] = g_enemy[4].fEPosX + 6;
				g_enemy[4].fEeyePosY[7] = g_enemy[4].fEPosY;

				g_enemy[4].fEeyePosX[8] = g_enemy[4].fEPosX + 6;
				g_enemy[4].fEeyePosY[8] = g_enemy[4].fEPosY + 1;
			}

			if (g_enemy[4].fEPosX < LIMIT_LEFT + 5)
			{
				//g_enemy.fEPosY = LIMIT_DOWN;       //画面の限界がLIMIT_LEFTなので移動した数値を限界の数値にして移動してないように見える
				g_enemy[4].flag = 1;

			}

			if (g_enemy[4].fEPosX > LIMIT_RIGHT - 5)
			{
				//g_enemy.fEPosY = LIMIT_UP;         //画面の限界がLIMIT_RIGHTなので移動した数値を限界の数値にして移動してないように見える
				g_enemy[4].flag = 0;
			}
		}

		if (g_map.mapcount == 5)
		{
			if (g_enemy[5].life == 1 && g_ui.gameflag == 1)
			{
				g_enemy[5].fEPosX += g_enemy[5].fEMoveX;
			}

			if (g_enemy[5].life == 1 && g_enemy[5].flag == 0)
			{
				g_enemy[5].fEeyePosX[0] = g_enemy[5].fEPosX - 2;
				g_enemy[5].fEeyePosY[0] = g_enemy[5].fEPosY - 1;

				g_enemy[5].fEeyePosX[1] = g_enemy[5].fEPosX - 4;
				g_enemy[5].fEeyePosY[1] = g_enemy[5].fEPosY - 2;

				g_enemy[5].fEeyePosX[2] = g_enemy[5].fEPosX - 4;
				g_enemy[5].fEeyePosY[2] = g_enemy[5].fEPosY - 1;

				g_enemy[5].fEeyePosX[3] = g_enemy[5].fEPosX - 4;
				g_enemy[5].fEeyePosY[3] = g_enemy[5].fEPosY;

				g_enemy[5].fEeyePosX[4] = g_enemy[5].fEPosX - 6;
				g_enemy[5].fEeyePosY[4] = g_enemy[5].fEPosY - 3;

				g_enemy[5].fEeyePosX[5] = g_enemy[5].fEPosX - 6;
				g_enemy[5].fEeyePosY[5] = g_enemy[5].fEPosY - 2;

				g_enemy[5].fEeyePosX[6] = g_enemy[5].fEPosX - 6;
				g_enemy[5].fEeyePosY[6] = g_enemy[5].fEPosY - 1;

				g_enemy[5].fEeyePosX[7] = g_enemy[5].fEPosX - 6;
				g_enemy[5].fEeyePosY[7] = g_enemy[5].fEPosY;

				g_enemy[5].fEeyePosX[8] = g_enemy[5].fEPosX - 6;
				g_enemy[5].fEeyePosY[8] = g_enemy[5].fEPosY + 1;
			}

			if (g_enemy[5].life == 1 && g_enemy[5].flag == 1)
			{
				g_enemy[5].fEeyePosX[0] = g_enemy[5].fEPosX + 2;
				g_enemy[5].fEeyePosY[0] = g_enemy[5].fEPosY - 1;

				g_enemy[5].fEeyePosX[1] = g_enemy[5].fEPosX + 4;
				g_enemy[5].fEeyePosY[1] = g_enemy[5].fEPosY - 2;

				g_enemy[5].fEeyePosX[2] = g_enemy[5].fEPosX + 4;
				g_enemy[5].fEeyePosY[2] = g_enemy[5].fEPosY - 1;

				g_enemy[5].fEeyePosX[3] = g_enemy[5].fEPosX + 4;
				g_enemy[5].fEeyePosY[3] = g_enemy[5].fEPosY;

				g_enemy[5].fEeyePosX[4] = g_enemy[5].fEPosX + 6;
				g_enemy[5].fEeyePosY[4] = g_enemy[5].fEPosY - 3;

				g_enemy[5].fEeyePosX[5] = g_enemy[5].fEPosX + 6;
				g_enemy[5].fEeyePosY[5] = g_enemy[5].fEPosY - 2;

				g_enemy[5].fEeyePosX[6] = g_enemy[5].fEPosX + 6;
				g_enemy[5].fEeyePosY[6] = g_enemy[5].fEPosY - 1;

				g_enemy[5].fEeyePosX[7] = g_enemy[5].fEPosX + 6;
				g_enemy[5].fEeyePosY[7] = g_enemy[5].fEPosY;
			
				g_enemy[5].fEeyePosX[8] = g_enemy[5].fEPosX + 6;
				g_enemy[5].fEeyePosY[8] = g_enemy[5].fEPosY + 1;
			}

			if (g_enemy[5].fEPosX < LIMIT_LEFT + 6)
			{
				//g_enemy.fEPosY = LIMIT_DOWN;       //画面の限界がLIMIT_LEFTなので移動した数値を限界の数値にして移動してないように見える
				g_enemy[5].flag = 1;

			}

			if (g_enemy[5].fEPosX > LIMIT_RIGHT - 36)
			{
				//g_enemy.fEPosY = LIMIT_UP;         //画面の限界がLIMIT_RIGHTなので移動した数値を限界の数値にして移動してないように見える
				g_enemy[5].flag = 0;
			}
		}
}

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void DrawEnemy(void)
{
	if (g_player.life == 1 && g_map.mapcount == 2)
	{
		// 敵の現在の位置の描画

		if (g_enemy[0].life == 0)        //敵にタマが当たったら
		{
			gotoxy((int)(g_enemy[0].fEPosXOLD), (int)(g_enemy[0].fEPosYOLD - 1.0f));      //先に消す
			printf("  ");
			gotoxy((int)(g_enemy[0].fEPosXOLD), (int)(g_enemy[0].fEPosYOLD));
			printf("  ");

			gotoxy((int)(g_enemy[0].fEPosX), (int)(g_enemy[0].fEPosY - 1.0f));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEPosX), (int)(g_enemy[0].fEPosY));
			printf("  ");

			gotoxy((int)(g_enemy[0].fEeyePosX[0]), (int)(g_enemy[0].fEeyePosY[0]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosX[1]), (int)(g_enemy[0].fEeyePosY[1]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosX[2]), (int)(g_enemy[0].fEeyePosY[2]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosX[3]), (int)(g_enemy[0].fEeyePosY[3]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosX[4]), (int)(g_enemy[0].fEeyePosY[4]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosX[5]), (int)(g_enemy[0].fEeyePosY[5]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosX[6]), (int)(g_enemy[0].fEeyePosY[6]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosX[7]), (int)(g_enemy[0].fEeyePosY[7]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosX[8]), (int)(g_enemy[0].fEeyePosY[8]));
			printf("  ");

			g_enemy[0].life = 2;
		}

		if (g_enemy[1].life == 0)        //敵にタマが当たったら
		{
			gotoxy((int)(g_enemy[1].fEPosXOLD), (int)(g_enemy[1].fEPosYOLD - 1.0f));      //先に消す
			printf("  ");
			gotoxy((int)(g_enemy[1].fEPosXOLD), (int)(g_enemy[1].fEPosYOLD));
			printf("  ");

			gotoxy((int)(g_enemy[1].fEPosX), (int)(g_enemy[1].fEPosY - 1.0f));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEPosX), (int)(g_enemy[1].fEPosY));
			printf("  ");

			gotoxy((int)(g_enemy[1].fEeyePosX[0]), (int)(g_enemy[1].fEeyePosY[0]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosX[1]), (int)(g_enemy[1].fEeyePosY[1]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosX[2]), (int)(g_enemy[1].fEeyePosY[2]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosX[3]), (int)(g_enemy[1].fEeyePosY[3]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosX[4]), (int)(g_enemy[1].fEeyePosY[4]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosX[5]), (int)(g_enemy[1].fEeyePosY[5]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosX[6]), (int)(g_enemy[1].fEeyePosY[6]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosX[7]), (int)(g_enemy[1].fEeyePosY[7]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosX[8]), (int)(g_enemy[1].fEeyePosY[8]));
			printf("  ");

			g_enemy[1].life = 2;
		}

		if (g_enemy[3].life == 0)        //敵にタマが当たったら
		{
			gotoxy((int)(g_enemy[3].fEPosXOLD), (int)(g_enemy[3].fEPosYOLD - 1.0f));      //先に消す
			printf("  ");
			gotoxy((int)(g_enemy[3].fEPosXOLD), (int)(g_enemy[3].fEPosYOLD));
			printf("  ");

			gotoxy((int)(g_enemy[3].fEPosX), (int)(g_enemy[3].fEPosY - 1.0f));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEPosX), (int)(g_enemy[3].fEPosY));
			printf("  ");

			gotoxy((int)(g_enemy[3].fEeyePosX[0]), (int)(g_enemy[3].fEeyePosY[0]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosX[1]), (int)(g_enemy[3].fEeyePosY[1]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosX[2]), (int)(g_enemy[3].fEeyePosY[2]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosX[3]), (int)(g_enemy[3].fEeyePosY[3]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosX[4]), (int)(g_enemy[3].fEeyePosY[4]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosX[5]), (int)(g_enemy[3].fEeyePosY[5]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosX[6]), (int)(g_enemy[3].fEeyePosY[6]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosX[7]), (int)(g_enemy[3].fEeyePosY[7]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosX[8]), (int)(g_enemy[3].fEeyePosY[8]));
			printf("  ");

			g_enemy[3].life = 2;
		}

		if (g_enemy[0].life == 1)
		{
			textcolor(0001);
			gotoxy((int)(g_enemy[0].fEPosXOLD), (int)(g_enemy[0].fEPosYOLD - 1.0f));      //先に消す
			printf("  ");
			gotoxy((int)(g_enemy[0].fEPosXOLD), (int)(g_enemy[0].fEPosYOLD));
			printf("  ");

			gotoxy((int)(g_enemy[0].fEPosX), (int)(g_enemy[0].fEPosY - 1.0f));
			printf("●");
			gotoxy((int)(g_enemy[0].fEPosX), (int)(g_enemy[0].fEPosY));
			printf("■");
		}

		if (g_enemy[1].life == 1)
		{
			textcolor(0001);
			gotoxy((int)(g_enemy[1].fEPosXOLD), (int)(g_enemy[1].fEPosYOLD - 1.0f));      //先に消す
			printf("  ");
			gotoxy((int)(g_enemy[1].fEPosXOLD), (int)(g_enemy[1].fEPosYOLD));
			printf("  ");

			gotoxy((int)(g_enemy[1].fEPosX), (int)(g_enemy[1].fEPosY - 1.0f));
			printf("●");
			gotoxy((int)(g_enemy[1].fEPosX), (int)(g_enemy[1].fEPosY));
			printf("■");
		}

		if (g_enemy[3].life == 1)
		{
			textcolor(0001);
			gotoxy((int)(g_enemy[3].fEPosXOLD), (int)(g_enemy[3].fEPosYOLD - 1.0f));      //先に消す
			printf("  ");
			gotoxy((int)(g_enemy[3].fEPosXOLD), (int)(g_enemy[3].fEPosYOLD));
			printf("  ");

			gotoxy((int)(g_enemy[3].fEPosX), (int)(g_enemy[3].fEPosY - 1.0f));
			printf("●");
			gotoxy((int)(g_enemy[3].fEPosX), (int)(g_enemy[3].fEPosY));
			printf("■");
		}

		if (g_enemy[0].flag == 0 && g_enemy[0].life == 1)
		{
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[0]), (int)(g_enemy[0].fEeyePosYOLD[0]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[1]), (int)(g_enemy[0].fEeyePosYOLD[1]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[2]), (int)(g_enemy[0].fEeyePosYOLD[2]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[3]), (int)(g_enemy[0].fEeyePosYOLD[3]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[4]), (int)(g_enemy[0].fEeyePosYOLD[4]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[5]), (int)(g_enemy[0].fEeyePosYOLD[5]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[6]), (int)(g_enemy[0].fEeyePosYOLD[6]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[7]), (int)(g_enemy[0].fEeyePosYOLD[7]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[8]), (int)(g_enemy[0].fEeyePosYOLD[8]));
			printf("  ");

			textcolor(0xAA);
			gotoxy((int)(g_enemy[0].fEeyePosX[0]), (int)(g_enemy[0].fEeyePosY[0]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[1]), (int)(g_enemy[0].fEeyePosY[1]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[2]), (int)(g_enemy[0].fEeyePosY[2]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[3]), (int)(g_enemy[0].fEeyePosY[3]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[4]), (int)(g_enemy[0].fEeyePosY[4]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[5]), (int)(g_enemy[0].fEeyePosY[5]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[6]), (int)(g_enemy[0].fEeyePosY[6]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[7]), (int)(g_enemy[0].fEeyePosY[7]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[8]), (int)(g_enemy[0].fEeyePosY[8]));
			printf("※");
		}

		if (g_enemy[0].flag == 1 && g_enemy[0].life == 1)
		{
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[0]), (int)(g_enemy[0].fEeyePosYOLD[0]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[1]), (int)(g_enemy[0].fEeyePosYOLD[1]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[2]), (int)(g_enemy[0].fEeyePosYOLD[2]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[3]), (int)(g_enemy[0].fEeyePosYOLD[3]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[4]), (int)(g_enemy[0].fEeyePosYOLD[4]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[5]), (int)(g_enemy[0].fEeyePosYOLD[5]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[6]), (int)(g_enemy[0].fEeyePosYOLD[6]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[7]), (int)(g_enemy[0].fEeyePosYOLD[7]));
			printf("  ");
			gotoxy((int)(g_enemy[0].fEeyePosXOLD[8]), (int)(g_enemy[0].fEeyePosYOLD[8]));
			printf("  ");

			textcolor(0xAA);
			gotoxy((int)(g_enemy[0].fEeyePosX[0]), (int)(g_enemy[0].fEeyePosY[0]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[1]), (int)(g_enemy[0].fEeyePosY[1]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[2]), (int)(g_enemy[0].fEeyePosY[2]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[3]), (int)(g_enemy[0].fEeyePosY[3]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[4]), (int)(g_enemy[0].fEeyePosY[4]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[5]), (int)(g_enemy[0].fEeyePosY[5]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[6]), (int)(g_enemy[0].fEeyePosY[6]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[7]), (int)(g_enemy[0].fEeyePosY[7]));
			printf("※");
			gotoxy((int)(g_enemy[0].fEeyePosX[8]), (int)(g_enemy[0].fEeyePosY[8]));
			printf("※");
		}

		if (g_enemy[1].flag == 0 && g_enemy[1].life == 1)
		{
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[0]), (int)(g_enemy[1].fEeyePosYOLD[0]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[1]), (int)(g_enemy[1].fEeyePosYOLD[1]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[2]), (int)(g_enemy[1].fEeyePosYOLD[2]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[3]), (int)(g_enemy[1].fEeyePosYOLD[3]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[4]), (int)(g_enemy[1].fEeyePosYOLD[4]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[5]), (int)(g_enemy[1].fEeyePosYOLD[5]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[6]), (int)(g_enemy[1].fEeyePosYOLD[6]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[7]), (int)(g_enemy[1].fEeyePosYOLD[7]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[8]), (int)(g_enemy[1].fEeyePosYOLD[8]));
			printf("  ");

			textcolor(0xAA);
			gotoxy((int)(g_enemy[1].fEeyePosX[0]), (int)(g_enemy[1].fEeyePosY[0]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[1]), (int)(g_enemy[1].fEeyePosY[1]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[2]), (int)(g_enemy[1].fEeyePosY[2]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[3]), (int)(g_enemy[1].fEeyePosY[3]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[4]), (int)(g_enemy[1].fEeyePosY[4]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[5]), (int)(g_enemy[1].fEeyePosY[5]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[6]), (int)(g_enemy[1].fEeyePosY[6]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[7]), (int)(g_enemy[1].fEeyePosY[7]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[8]), (int)(g_enemy[1].fEeyePosY[8]));
			printf("※");
		}

		if (g_enemy[1].flag == 1 && g_enemy[1].life == 1)
		{
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[0]), (int)(g_enemy[1].fEeyePosYOLD[0]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[1]), (int)(g_enemy[1].fEeyePosYOLD[1]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[2]), (int)(g_enemy[1].fEeyePosYOLD[2]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[3]), (int)(g_enemy[1].fEeyePosYOLD[3]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[4]), (int)(g_enemy[1].fEeyePosYOLD[4]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[5]), (int)(g_enemy[1].fEeyePosYOLD[5]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[6]), (int)(g_enemy[1].fEeyePosYOLD[6]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[7]), (int)(g_enemy[1].fEeyePosYOLD[7]));
			printf("  ");
			gotoxy((int)(g_enemy[1].fEeyePosXOLD[8]), (int)(g_enemy[1].fEeyePosYOLD[8]));
			printf("  ");

			textcolor(0xAA);
			gotoxy((int)(g_enemy[1].fEeyePosX[0]), (int)(g_enemy[1].fEeyePosY[0]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[1]), (int)(g_enemy[1].fEeyePosY[1]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[2]), (int)(g_enemy[1].fEeyePosY[2]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[3]), (int)(g_enemy[1].fEeyePosY[3]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[4]), (int)(g_enemy[1].fEeyePosY[4]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[5]), (int)(g_enemy[1].fEeyePosY[5]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[6]), (int)(g_enemy[1].fEeyePosY[6]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[7]), (int)(g_enemy[1].fEeyePosY[7]));
			printf("※");
			gotoxy((int)(g_enemy[1].fEeyePosX[8]), (int)(g_enemy[1].fEeyePosY[8]));
			printf("※");
		}

		if (g_enemy[3].flag == 0 && g_enemy[3].life == 1)
		{
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[0]), (int)(g_enemy[3].fEeyePosYOLD[0]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[1]), (int)(g_enemy[3].fEeyePosYOLD[1]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[2]), (int)(g_enemy[3].fEeyePosYOLD[2]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[3]), (int)(g_enemy[3].fEeyePosYOLD[3]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[4]), (int)(g_enemy[3].fEeyePosYOLD[4]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[5]), (int)(g_enemy[3].fEeyePosYOLD[5]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[6]), (int)(g_enemy[3].fEeyePosYOLD[6]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[7]), (int)(g_enemy[3].fEeyePosYOLD[7]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[8]), (int)(g_enemy[3].fEeyePosYOLD[8]));
			printf("  ");

			textcolor(0xAA);
			gotoxy((int)(g_enemy[3].fEeyePosX[0]), (int)(g_enemy[3].fEeyePosY[0]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[1]), (int)(g_enemy[3].fEeyePosY[1]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[2]), (int)(g_enemy[3].fEeyePosY[2]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[3]), (int)(g_enemy[3].fEeyePosY[3]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[4]), (int)(g_enemy[3].fEeyePosY[4]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[5]), (int)(g_enemy[3].fEeyePosY[5]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[6]), (int)(g_enemy[3].fEeyePosY[6]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[7]), (int)(g_enemy[3].fEeyePosY[7]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[8]), (int)(g_enemy[3].fEeyePosY[8]));
			printf("※");
		}

		if (g_enemy[3].flag == 1 && g_enemy[3].life == 1)
		{
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[0]), (int)(g_enemy[3].fEeyePosYOLD[0]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[1]), (int)(g_enemy[3].fEeyePosYOLD[1]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[2]), (int)(g_enemy[3].fEeyePosYOLD[2]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[3]), (int)(g_enemy[3].fEeyePosYOLD[3]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[4]), (int)(g_enemy[3].fEeyePosYOLD[4]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[5]), (int)(g_enemy[3].fEeyePosYOLD[5]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[6]), (int)(g_enemy[3].fEeyePosYOLD[6]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[7]), (int)(g_enemy[3].fEeyePosYOLD[7]));
			printf("  ");
			gotoxy((int)(g_enemy[3].fEeyePosXOLD[8]), (int)(g_enemy[3].fEeyePosYOLD[8]));
			printf("  ");

			textcolor(0xAA);
			gotoxy((int)(g_enemy[3].fEeyePosX[0]), (int)(g_enemy[3].fEeyePosY[0]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[1]), (int)(g_enemy[3].fEeyePosY[1]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[2]), (int)(g_enemy[3].fEeyePosY[2]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[3]), (int)(g_enemy[3].fEeyePosY[3]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[4]), (int)(g_enemy[3].fEeyePosY[4]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[5]), (int)(g_enemy[3].fEeyePosY[5]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[6]), (int)(g_enemy[3].fEeyePosY[6]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[7]), (int)(g_enemy[3].fEeyePosY[7]));
			printf("※");
			gotoxy((int)(g_enemy[3].fEeyePosX[8]), (int)(g_enemy[3].fEeyePosY[8]));
			printf("※");
		}

		textcolor(0001);
		gotoxy(g_enemy[0].fEcameraPosX, g_enemy[0].fEcameraPosY);
		printf("目");

		if (g_enemy[0].cameralife >= 1)
		{
			textcolor(0xAA);
			gotoxy(g_enemy[0].fEcameraPosX + 2, g_enemy[0].fEcameraPosY - 1);
			printf("※※※※※※※※");

			gotoxy(g_enemy[0].fEcameraPosX + 2, g_enemy[0].fEcameraPosY);
			printf("※※※※※※※※");

			gotoxy(g_enemy[0].fEcameraPosX + 2, g_enemy[0].fEcameraPosY + 1);
			printf("※※※※※※※※");
		}
	}

	if (g_player.life == 1 && g_map.mapcount == 3)
	{
		if (g_enemy[4].life == 0)        //敵にタマが当たったら
		{
			gotoxy((int)(g_enemy[4].fEPosXOLD), (int)(g_enemy[4].fEPosYOLD - 1.0f));      //先に消す
			printf("  ");
			gotoxy((int)(g_enemy[4].fEPosXOLD), (int)(g_enemy[4].fEPosYOLD));
			printf("  ");

			gotoxy((int)(g_enemy[4].fEPosX), (int)(g_enemy[4].fEPosY - 1.0f));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEPosX), (int)(g_enemy[4].fEPosY));
			printf("  ");

			gotoxy((int)(g_enemy[4].fEeyePosX[0]), (int)(g_enemy[4].fEeyePosY[0]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosX[1]), (int)(g_enemy[4].fEeyePosY[1]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosX[2]), (int)(g_enemy[4].fEeyePosY[2]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosX[3]), (int)(g_enemy[4].fEeyePosY[3]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosX[4]), (int)(g_enemy[4].fEeyePosY[4]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosX[5]), (int)(g_enemy[4].fEeyePosY[5]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosX[6]), (int)(g_enemy[4].fEeyePosY[6]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosX[7]), (int)(g_enemy[4].fEeyePosY[7]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosX[8]), (int)(g_enemy[4].fEeyePosY[8]));
			printf("  ");

			g_enemy[4].life = 2;
		}

		if (g_enemy[4].flag == 0 && g_enemy[4].life == 1)
		{
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[0]), (int)(g_enemy[4].fEeyePosYOLD[0]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[1]), (int)(g_enemy[4].fEeyePosYOLD[1]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[2]), (int)(g_enemy[4].fEeyePosYOLD[2]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[3]), (int)(g_enemy[4].fEeyePosYOLD[3]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[4]), (int)(g_enemy[4].fEeyePosYOLD[4]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[5]), (int)(g_enemy[4].fEeyePosYOLD[5]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[6]), (int)(g_enemy[4].fEeyePosYOLD[6]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[7]), (int)(g_enemy[4].fEeyePosYOLD[7]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[8]), (int)(g_enemy[4].fEeyePosYOLD[8]));
			printf("  ");

			textcolor(0xAA);
			gotoxy((int)(g_enemy[4].fEeyePosX[0]), (int)(g_enemy[4].fEeyePosY[0]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[1]), (int)(g_enemy[4].fEeyePosY[1]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[2]), (int)(g_enemy[4].fEeyePosY[2]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[3]), (int)(g_enemy[4].fEeyePosY[3]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[4]), (int)(g_enemy[4].fEeyePosY[4]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[5]), (int)(g_enemy[4].fEeyePosY[5]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[6]), (int)(g_enemy[4].fEeyePosY[6]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[7]), (int)(g_enemy[4].fEeyePosY[7]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[8]), (int)(g_enemy[4].fEeyePosY[8]));
			printf("※");
		}

		if (g_enemy[4].flag == 1 && g_enemy[4].life == 1)
		{
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[0]), (int)(g_enemy[4].fEeyePosYOLD[0]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[1]), (int)(g_enemy[4].fEeyePosYOLD[1]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[2]), (int)(g_enemy[4].fEeyePosYOLD[2]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[3]), (int)(g_enemy[4].fEeyePosYOLD[3]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[4]), (int)(g_enemy[4].fEeyePosYOLD[4]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[5]), (int)(g_enemy[4].fEeyePosYOLD[5]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[6]), (int)(g_enemy[4].fEeyePosYOLD[6]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[7]), (int)(g_enemy[4].fEeyePosYOLD[7]));
			printf("  ");
			gotoxy((int)(g_enemy[4].fEeyePosXOLD[8]), (int)(g_enemy[4].fEeyePosYOLD[8]));
			printf("  ");

			textcolor(0xAA);
			gotoxy((int)(g_enemy[4].fEeyePosX[0]), (int)(g_enemy[4].fEeyePosY[0]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[1]), (int)(g_enemy[4].fEeyePosY[1]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[2]), (int)(g_enemy[4].fEeyePosY[2]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[3]), (int)(g_enemy[4].fEeyePosY[3]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[4]), (int)(g_enemy[4].fEeyePosY[4]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[5]), (int)(g_enemy[4].fEeyePosY[5]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[6]), (int)(g_enemy[4].fEeyePosY[6]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[7]), (int)(g_enemy[4].fEeyePosY[7]));
			printf("※");
			gotoxy((int)(g_enemy[4].fEeyePosX[8]), (int)(g_enemy[4].fEeyePosY[8]));
			printf("※");
		}
			textcolor(0001);
			gotoxy(44, 8);
			printf("目");
			if (g_enemy[0].cameralife >= 1)
			{
				textcolor(LIGHTGREEN);
				gotoxy(42, 9);
				printf("※※※");
				gotoxy(42, 10);
				printf("※※※");
				gotoxy(42, 11);
				printf("※※※");
				gotoxy(42, 12);
				printf("※※※");
				gotoxy(42, 13);
				printf("※※※");
				gotoxy(42, 14);
				printf("※※※");
				gotoxy(42, 15);
				printf("※※※");
				gotoxy(42, 16);
				printf("※※※");
			}
		

		if (g_enemy[4].life == 1)
		{
			textcolor(0001);
			gotoxy((int)(g_enemy[4].fEPosXOLD), (int)(g_enemy[4].fEPosYOLD - 1.0f));      //先に消す
			printf("  ");
			gotoxy((int)(g_enemy[4].fEPosXOLD), (int)(g_enemy[4].fEPosYOLD));
			printf("  ");

			gotoxy((int)(g_enemy[4].fEPosX), (int)(g_enemy[4].fEPosY - 1.0f));
			printf("●");
			gotoxy((int)(g_enemy[4].fEPosX), (int)(g_enemy[4].fEPosY));
			printf("■");
		}
	}

	if (g_player.life == 1 && g_map.mapcount == 5)
	{
		if (g_enemy[5].life == 0)        //敵にタマが当たったら
		{
			gotoxy((int)(g_enemy[5].fEPosXOLD), (int)(g_enemy[5].fEPosYOLD - 1.0f));      //先に消す
			printf("  ");
			gotoxy((int)(g_enemy[5].fEPosXOLD), (int)(g_enemy[5].fEPosYOLD));
			printf("  ");

			gotoxy((int)(g_enemy[5].fEPosX), (int)(g_enemy[5].fEPosY - 1.0f));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEPosX), (int)(g_enemy[5].fEPosY));
			printf("  ");

			gotoxy((int)(g_enemy[5].fEeyePosX[0]), (int)(g_enemy[5].fEeyePosY[0]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosX[1]), (int)(g_enemy[5].fEeyePosY[1]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosX[2]), (int)(g_enemy[5].fEeyePosY[2]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosX[3]), (int)(g_enemy[5].fEeyePosY[3]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosX[4]), (int)(g_enemy[5].fEeyePosY[4]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosX[5]), (int)(g_enemy[5].fEeyePosY[5]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosX[6]), (int)(g_enemy[5].fEeyePosY[6]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosX[7]), (int)(g_enemy[5].fEeyePosY[7]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosX[8]), (int)(g_enemy[5].fEeyePosY[8]));
			printf("  ");

			g_enemy[5].life = 2;
		}

		if (g_enemy[5].flag == 0 && g_enemy[5].life == 1)
		{
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[0]), (int)(g_enemy[5].fEeyePosYOLD[0]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[1]), (int)(g_enemy[5].fEeyePosYOLD[1]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[2]), (int)(g_enemy[5].fEeyePosYOLD[2]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[3]), (int)(g_enemy[5].fEeyePosYOLD[3]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[4]), (int)(g_enemy[5].fEeyePosYOLD[4]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[5]), (int)(g_enemy[5].fEeyePosYOLD[5]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[6]), (int)(g_enemy[5].fEeyePosYOLD[6]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[7]), (int)(g_enemy[5].fEeyePosYOLD[7]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[8]), (int)(g_enemy[5].fEeyePosYOLD[8]));
			printf("  ");

			textcolor(0xAA);
			gotoxy((int)(g_enemy[5].fEeyePosX[0]), (int)(g_enemy[5].fEeyePosY[0]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[1]), (int)(g_enemy[5].fEeyePosY[1]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[2]), (int)(g_enemy[5].fEeyePosY[2]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[3]), (int)(g_enemy[5].fEeyePosY[3]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[4]), (int)(g_enemy[5].fEeyePosY[4]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[5]), (int)(g_enemy[5].fEeyePosY[5]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[6]), (int)(g_enemy[5].fEeyePosY[6]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[7]), (int)(g_enemy[5].fEeyePosY[7]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[8]), (int)(g_enemy[5].fEeyePosY[8]));
			printf("※");
		}

		if (g_enemy[5].flag == 1 && g_enemy[5].life == 1)
		{
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[0]), (int)(g_enemy[5].fEeyePosYOLD[0]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[1]), (int)(g_enemy[5].fEeyePosYOLD[1]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[2]), (int)(g_enemy[5].fEeyePosYOLD[2]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[3]), (int)(g_enemy[5].fEeyePosYOLD[3]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[4]), (int)(g_enemy[5].fEeyePosYOLD[4]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[5]), (int)(g_enemy[5].fEeyePosYOLD[5]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[6]), (int)(g_enemy[5].fEeyePosYOLD[6]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[7]), (int)(g_enemy[5].fEeyePosYOLD[7]));
			printf("  ");
			gotoxy((int)(g_enemy[5].fEeyePosXOLD[8]), (int)(g_enemy[5].fEeyePosYOLD[8]));
			printf("  ");

			textcolor(0xAA);
			gotoxy((int)(g_enemy[5].fEeyePosX[0]), (int)(g_enemy[5].fEeyePosY[0]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[1]), (int)(g_enemy[5].fEeyePosY[1]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[2]), (int)(g_enemy[5].fEeyePosY[2]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[3]), (int)(g_enemy[5].fEeyePosY[3]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[4]), (int)(g_enemy[5].fEeyePosY[4]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[5]), (int)(g_enemy[5].fEeyePosY[5]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[6]), (int)(g_enemy[5].fEeyePosY[6]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[7]), (int)(g_enemy[5].fEeyePosY[7]));
			printf("※");
			gotoxy((int)(g_enemy[5].fEeyePosX[8]), (int)(g_enemy[5].fEeyePosY[8]));
			printf("※");
		}
		
		if (g_enemy[5].life == 1)
		{
			textcolor(0001);
			gotoxy((int)(g_enemy[5].fEPosXOLD), (int)(g_enemy[5].fEPosYOLD - 1.0f));      //先に消す
			printf("  ");
			gotoxy((int)(g_enemy[5].fEPosXOLD), (int)(g_enemy[5].fEPosYOLD));
			printf("  ");

			gotoxy((int)(g_enemy[5].fEPosX), (int)(g_enemy[5].fEPosY - 1.0f));
			printf("● ");
			gotoxy((int)(g_enemy[5].fEPosX), (int)(g_enemy[5].fEPosY));
			printf("■ ");
		}

		textcolor(0001);
		gotoxy(23, 2);
		printf("目");
		if (g_enemy[0].cameralife >= 1)
		{
			textcolor(LIGHTGREEN);
			gotoxy(21, 3);
			printf("※※※");
			gotoxy(21, 4);
			printf("※※※");
			gotoxy(21, 5);
			printf("※※※");
			gotoxy(21, 6);
			printf("※※※");
			gotoxy(21, 7);
			printf("※※※");
			gotoxy(21, 8);
			printf("※※※");
			gotoxy(21, 9);
			printf("※※※");
			gotoxy(21, 10);
			printf("※※※");
		}
	}
	if (g_map.mapcount == 4)
	{
		textcolor(0001);
		gotoxy(23, 2);
		printf("目");
		if (g_enemy[0].cameralife >= 1)
		{
			textcolor(LIGHTGREEN);
			gotoxy(21, 3);
			printf("※※※");
			gotoxy(21, 4);
			printf("※※※");
			gotoxy(21, 5);
			printf("※※※");
			gotoxy(21, 6);
			printf("※※※");
			gotoxy(21, 7);
			printf("※※※");
			gotoxy(21, 8);
			printf("※※※");
			gotoxy(21, 9);
			printf("※※※");
			gotoxy(21, 10);
			printf("※※※");
		}
		if (g_enemy[0].cameralife <= 0)
		{
			textcolor(LIGHTGREEN);
			gotoxy(21, 3);
			printf("      ");
			gotoxy(21, 4);
			printf("      ");
			gotoxy(21, 5);
			printf("      ");
			gotoxy(21, 6);
			printf("      ");
			gotoxy(21, 7);
			printf("      ");
			gotoxy(21, 8);
			printf("      ");
			gotoxy(21, 9);
			printf("      ");
			gotoxy(21, 10);
			printf("      ");
		}
	}

		if (g_player.life == 1 && g_map.mapcount == 1)
		{
			if (g_enemy[2].life == 0)        //敵にタマが当たったら
			{
				gotoxy((int)(g_enemy[2].fEPosXOLD), (int)(g_enemy[2].fEPosYOLD - 1.0f));      //先に消す
				printf("  ");
				gotoxy((int)(g_enemy[2].fEPosXOLD), (int)(g_enemy[2].fEPosYOLD));
				printf("  ");

				gotoxy((int)(g_enemy[2].fEPosX), (int)(g_enemy[2].fEPosY - 1.0f));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEPosX), (int)(g_enemy[2].fEPosY));
				printf("  ");

				gotoxy((int)(g_enemy[2].fEPosX + 2), (int)(g_enemy[2].fEPosY - 1));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEPosX + 4), (int)(g_enemy[2].fEPosY - 2));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEPosX + 4), (int)(g_enemy[2].fEPosY - 1));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEPosX + 4), (int)(g_enemy[2].fEPosY));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEPosX + 6), (int)(g_enemy[2].fEPosY - 3));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEPosX + 6), (int)(g_enemy[2].fEPosY - 2));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEPosX + 6), (int)(g_enemy[2].fEPosY - 1));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEPosX + 6), (int)(g_enemy[2].fEPosY));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEPosX + 6), (int)(g_enemy[2].fEPosY + 1));
				printf("  ");

				g_enemy[2].life = 2;
			}

			if (g_enemy[2].life == 1 && g_map.mapcount == 1)
			{
				textcolor(0001);
				gotoxy((int)(g_enemy[2].fEPosXOLD), (int)(g_enemy[2].fEPosYOLD - 1.0f));      //先に消す
				printf("  ");
				gotoxy((int)(g_enemy[2].fEPosXOLD), (int)(g_enemy[2].fEPosYOLD));
				printf("  ");

				gotoxy((int)(g_enemy[2].fEPosX), (int)(g_enemy[2].fEPosY - 1.0f));
				printf("●");
				gotoxy((int)(g_enemy[2].fEPosX), (int)(g_enemy[2].fEPosY));
				printf("■");

				/*gotoxy((int)(g_enemy[2].fEPosX), (int)(g_enemy[2].fEPosY));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEeyePosXOLD[1]), (int)(g_enemy[2].fEeyePosYOLD[1]));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEeyePosXOLD[2]), (int)(g_enemy[2].fEeyePosYOLD[2]));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEeyePosXOLD[3]), (int)(g_enemy[2].fEeyePosYOLD[3]));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEeyePosXOLD[4]), (int)(g_enemy[2].fEeyePosYOLD[4]));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEeyePosXOLD[5]), (int)(g_enemy[2].fEeyePosYOLD[5]));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEeyePosXOLD[6]), (int)(g_enemy[2].fEeyePosYOLD[6]));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEeyePosXOLD[7]), (int)(g_enemy[2].fEeyePosYOLD[7]));
				printf("  ");
				gotoxy((int)(g_enemy[2].fEeyePosXOLD[8]), (int)(g_enemy[2].fEeyePosYOLD[8]));
				printf("  ");*/

				textcolor(0xAA);
				gotoxy((int)(g_enemy[2].fEPosX + 2), (int)(g_enemy[2].fEPosY - 1));
				printf("※");
				gotoxy((int)(g_enemy[2].fEPosX + 4), (int)(g_enemy[2].fEPosY - 2));
				printf("※");
				gotoxy((int)(g_enemy[2].fEPosX + 4), (int)(g_enemy[2].fEPosY - 1));
				printf("※");
				gotoxy((int)(g_enemy[2].fEPosX + 4), (int)(g_enemy[2].fEPosY));
				printf("※");
				gotoxy((int)(g_enemy[2].fEPosX + 6), (int)(g_enemy[2].fEPosY - 3));
				printf("※");
				gotoxy((int)(g_enemy[2].fEPosX + 6), (int)(g_enemy[2].fEPosY - 2));
				printf("※");
				gotoxy((int)(g_enemy[2].fEPosX + 6), (int)(g_enemy[2].fEPosY - 1));
				printf("※");
				gotoxy((int)(g_enemy[2].fEPosX + 6), (int)(g_enemy[2].fEPosY));
				printf("※");
				gotoxy((int)(g_enemy[2].fEPosX + 6), (int)(g_enemy[2].fEPosY + 1));
				printf("※");
			}
		}
	}

