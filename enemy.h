//=============================================================================
//
// Author : TAKASHI AKYAMA
//
//=============================================================================

#ifndef _ENEMY_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`
#define _ENEMY_H_

//*************************************
// �v���C���[�\����
//*************************************
typedef struct
{
	float fEPosX;		// ���݂̈ʒu�w
	float fEPosY;		// ���݂̈ʒu�x
	float fEeyePosX[10];
	float fEeyePosY[10];
	float fEeyePosXOLD[10];
	float fEeyePosYOLD[10];
	float fEMoveX;		// �ړ��ʂw����
	float fEMoveY;
	float fEPosXOLD;     //�ߋ�(�Â�)��X�ʒu���
	float fEPosYOLD;     //�ߋ�(�Â�)��Y�ʒu���
	int   fEcameraPosX;
	int   fEcameraPosY;
	int   cameralife;
	int	  flag;
	int   life;
	int   count;
} ENEMY;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

#endif