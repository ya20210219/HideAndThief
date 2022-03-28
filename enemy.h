//=============================================================================
//
// Author : TAKASHI AKYAMA
//
//=============================================================================

#ifndef _ENEMY_H_	// ２重インクルード防止のマクロ定義
#define _ENEMY_H_

//*************************************
// プレイヤー構造体
//*************************************
typedef struct
{
	float fEPosX;		// 現在の位置Ｘ
	float fEPosY;		// 現在の位置Ｙ
	float fEeyePosX[10];
	float fEeyePosY[10];
	float fEeyePosXOLD[10];
	float fEeyePosYOLD[10];
	float fEMoveX;		// 移動量Ｘ方向
	float fEMoveY;
	float fEPosXOLD;     //過去(古い)のX位置情報
	float fEPosYOLD;     //過去(古い)のY位置情報
	int   fEcameraPosX;
	int   fEcameraPosY;
	int   cameralife;
	int	  flag;
	int   life;
	int   count;
} ENEMY;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

#endif