//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : TAKASHI AKIYAMA
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//*************************************
// 弾の種類
//*************************************
typedef enum
{
	BULLETTYPE_PLAYER = 0,		// プレイヤーの弾
	BULLETTYPE_ENEMY,			// 敵の弾
	BULLETTYPE_MAX
} BULLETTYPE;

//*************************************
// 弾の構造体
//*************************************
typedef struct
{
	float fPosX;		// 現在の位置(Ｘ座標)
	float fPosY;		// 現在の位置(Ｙ座標)
	float fPosXOld;		// 前回の位置(Ｘ座標)
	float fPosYOld;		// 前回の位置(Ｙ座標)
	float fMoveX;		// 移動量(Ｘ方向)
	float fMoveY;		// 移動量(Ｙ方向)
	int   flag;
	int bulletcount;
	int bulletsound;
	BULLETTYPE type;	// 弾の種類
	bool bUse;			// 使用中かどうか
} BULLET;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(float fPosX, float fPosY, float fMoveX, float fMoveY, BULLETTYPE type);

#endif
