//=============================================================================
//
// プレイヤー処理 [block.h]
// Author : TAKASHI AKYAMA
//
//=============================================================================

#ifndef _UI_H_	// ２重インクルード防止のマクロ定義
#define _UI_H_

//*************************************
// プレイヤー構造体
//*************************************
typedef struct
{
	int UIPosX;		// 現在の位置Ｘ
	int UIPosY;		// 現在の位置Ｙ
	int flag;
	int gameflag;
	int score;
	int scount;
	int time;
	int timeflag;	
	int ending;
	int systemflag;
	int buttonR;
	int buttonL;
	int UIcount;

}UI;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);
void ending(void);
void title(void);
void tutorial(void);


#endif


