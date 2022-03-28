//=============================================================================
//
// �v���C���[���� [block.h]
// Author : TAKASHI AKYAMA
//
//=============================================================================

#ifndef _BLOCK_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`
#define _BLOCK_H_

//*************************************
// �v���C���[�\����
//*************************************
typedef struct
{
	int PosX;		// ���݂̈ʒu�w
	int PosY;		// ���݂̈ʒu�x
	int thief;
	int blocktime;
	int ammoblock;
} BLOCK;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void collision(void);
#endif