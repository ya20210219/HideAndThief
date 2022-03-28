//=============================================================================
//
// �v���C���[���� [block.h]
// Author : TAKASHI AKYAMA
//
//=============================================================================

#ifndef _UI_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`
#define _UI_H_

//*************************************
// �v���C���[�\����
//*************************************
typedef struct
{
	int UIPosX;		// ���݂̈ʒu�w
	int UIPosY;		// ���݂̈ʒu�x
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
// �v���g�^�C�v�錾
//*****************************************************************************
void InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);
void ending(void);
void title(void);
void tutorial(void);


#endif


