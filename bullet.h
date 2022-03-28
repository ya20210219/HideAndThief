//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : TAKASHI AKIYAMA
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//*************************************
// �e�̎��
//*************************************
typedef enum
{
	BULLETTYPE_PLAYER = 0,		// �v���C���[�̒e
	BULLETTYPE_ENEMY,			// �G�̒e
	BULLETTYPE_MAX
} BULLETTYPE;

//*************************************
// �e�̍\����
//*************************************
typedef struct
{
	float fPosX;		// ���݂̈ʒu(�w���W)
	float fPosY;		// ���݂̈ʒu(�x���W)
	float fPosXOld;		// �O��̈ʒu(�w���W)
	float fPosYOld;		// �O��̈ʒu(�x���W)
	float fMoveX;		// �ړ���(�w����)
	float fMoveY;		// �ړ���(�x����)
	int   flag;
	int bulletcount;
	int bulletsound;
	BULLETTYPE type;	// �e�̎��
	bool bUse;			// �g�p�����ǂ���
} BULLET;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(float fPosX, float fPosY, float fMoveX, float fMoveY, BULLETTYPE type);

#endif
