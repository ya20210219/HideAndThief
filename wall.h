//=============================================================================
//
// �v���C���[���� [block.h]
// Author : TAKASHI AKYAMA
//
//=============================================================================

#ifndef _WALL_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`
#define _WALL_H_

//*************************************
// �v���C���[�\����
//*************************************
typedef struct
{
	int WPosX[4];		// ���݂̈ʒu�w
	int WPosY[4];		// ���݂̈ʒu�x
}WALL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void Wallcollision(void);
#endif
