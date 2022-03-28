//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : TAKASHI AKYAMA
//
//=============================================================================

#ifndef _PLAYER_H_	// ２重インクルード防止のマクロ定義
#define _PLAYER_H_

//*************************************
// プレイヤー構造体
//*************************************
typedef struct
{
	float fPosX;		// 現在の位置Ｘ
	float fPosY;		// 現在の位置Ｙ
	float fMoveX;		// 移動量Ｘ方向
	float fMoveY;
	float fPosXOLD;     //過去(古い)のX位置情報
	float fPosYOLD;     //過去(古い)のY位置情報
	int   color;
	int   life;
	int   slow;
	int	  slowflag;
	int   slowtime;
	int   slowcooldown;
	int   slowcooldownflag;

	bool bShot;			// ショット中かどうか
	bool bMove;			// 移動したかどうか(描画更新用)
} PLAYER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void Slow(void);

#endif