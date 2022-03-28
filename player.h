//=============================================================================
//
// �v���C���[���� [player.h]
// Author : TAKASHI AKYAMA
//
//=============================================================================

#ifndef _PLAYER_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`
#define _PLAYER_H_

//*************************************
// �v���C���[�\����
//*************************************
typedef struct
{
	float fPosX;		// ���݂̈ʒu�w
	float fPosY;		// ���݂̈ʒu�x
	float fMoveX;		// �ړ��ʂw����
	float fMoveY;
	float fPosXOLD;     //�ߋ�(�Â�)��X�ʒu���
	float fPosYOLD;     //�ߋ�(�Â�)��Y�ʒu���
	int   color;
	int   life;
	int   slow;
	int	  slowflag;
	int   slowtime;
	int   slowcooldown;
	int   slowcooldownflag;

	bool bShot;			// �V���b�g�����ǂ���
	bool bMove;			// �ړ��������ǂ���(�`��X�V�p)
} PLAYER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void Slow(void);

#endif