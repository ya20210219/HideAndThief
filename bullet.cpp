//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author : TAKASHI AKIYAMA
//
//=============================================================================
#define CONIOEX
#include "main.h"
#include "player.h"
#include "bullet.h"
#include "block.h"
#include "UI.h"
#include "wall.h"
#include "enemy.h"
#include "map.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
BULLET g_Bullet;		// �e�̏��
extern BLOCK g_block;
extern PLAYER g_player;
extern ENEMY g_enemy[10];
extern UI g_ui;
extern WALL g_wall;
extern MAP g_map;

int BGM1 = 0;
//=============================================================================
// �e�̏���������
//=============================================================================
void InitBullet(void)
{
	BGM1 = opensound("BGM/laser3.mp3");
	setvolume(BGM1, 40);
	g_Bullet.fPosX = 0.0f;
	g_Bullet.fPosY = 0.0f;
	g_Bullet.fPosXOld = 0.0f;
	g_Bullet.fPosYOld = 0.0f;
	g_Bullet.fMoveX = 0.0f;
	g_Bullet.fMoveY = 0.0f;
	g_Bullet.flag = 0;
	g_Bullet.bulletcount = 7;
	g_Bullet.bulletsound = 0;
	g_Bullet.type = BULLETTYPE_PLAYER;
	g_Bullet.bUse = false;
}

//=============================================================================
// �e�̏I������
//=============================================================================
void UninitBullet(void)
{
} 

//=============================================================================
// �e�̍X�V����
//=============================================================================
void UpdateBullet(void)
{
	if (g_Bullet.bUse == true)
	{// �e���g�p���

		if (g_Bullet.bulletsound == 0)
		{
			playsound(BGM1, 0);
			g_Bullet.bulletsound = 1;
		}
		// �O��̈ʒu��ۑ�
		g_Bullet.fPosXOld = g_Bullet.fPosX;
		g_Bullet.fPosYOld = g_Bullet.fPosY;
		//���ړ�
		if (g_ui.flag == 1 && g_Bullet.flag == 0)
		{
			g_Bullet.flag = 1;
		}
		if (g_ui.flag == 2 && g_Bullet.flag == 0)
		{
			g_Bullet.flag = 2;
		}
		if (g_ui.flag == 3 && g_Bullet.flag == 0)
		{
			g_Bullet.flag = 3;
		}
		if (g_ui.flag == 4 && g_Bullet.flag == 0)
		{
			g_Bullet.flag = 4;
		}

		// �ʒu���X�V
		if (g_Bullet.flag == 1)
		{		
			g_Bullet.fPosX -= g_Bullet.fMoveX;			
		}
		if (g_Bullet.flag == 2)
		{
			g_Bullet.fPosX += g_Bullet.fMoveX;
		}
		if (g_Bullet.flag == 3)
		{
			g_Bullet.fPosY -= g_Bullet.fMoveY;
		}
		if (g_Bullet.flag == 4)
		{
			g_Bullet.fPosY += g_Bullet.fMoveY;
		}

		if (g_map.mapcount == 1)
		{
			if (g_Bullet.fPosX <= 2.0f         //�ǂƃu���b�N�ɓ���������Ƃ����Ӗ�
				|| g_Bullet.fPosX >= 79.0f     //   ||��or�ł���Aif����or�łȂ��Ă���
				|| g_Bullet.fPosY < 7.0f
				|| g_Bullet.fPosY > 14.0f
				
				)
			{// �e����ʊO�ɏo��
				gotoxy((int)(g_Bullet.fPosXOld), (int)(g_Bullet.fPosYOld));
				printf("�@");
				g_Bullet.bUse = false;		// �e�𖢎g�p��Ԃ�
				g_Bullet.flag = 0;
				g_Bullet.bulletsound = 0;
			}
		}

		if (g_map.mapcount == 2)
		{
			if (g_Bullet.fPosX <= 2.0f         //�ǂƃu���b�N�ɓ���������Ƃ����Ӗ�
				|| g_Bullet.fPosX >= 79.0f     //   ||��or�ł���Aif����or�łȂ��Ă���
				|| g_Bullet.fPosY < 2.0f
				|| g_Bullet.fPosY > 24.0f
				|| g_Bullet.fPosX > g_block.PosX - 1.0f && g_Bullet.fPosX < g_block.PosX + 1.0f && g_Bullet.fPosY >= g_block.PosY - 1.0f && g_Bullet.fPosY <= g_block.PosY + 1.0f
				|| g_Bullet.fPosX >= g_wall.WPosX[0] - 1.0f && g_Bullet.fPosX < g_wall.WPosX[0] + 8.0f && g_Bullet.fPosY >= g_wall.WPosY[0] && g_Bullet.fPosY <= g_wall.WPosY[0] + 4.0f
				|| g_Bullet.fPosX >= g_wall.WPosX[1] - 1.0f && g_Bullet.fPosX < g_wall.WPosX[1] + 8.0f && g_Bullet.fPosY >= g_wall.WPosY[1] && g_Bullet.fPosY <= g_wall.WPosY[1] + 4.0f
				|| g_Bullet.fPosX >= g_wall.WPosX[2] - 1.0f && g_Bullet.fPosX < g_wall.WPosX[2] + 8.0f && g_Bullet.fPosY >= g_wall.WPosY[2] && g_Bullet.fPosY <= g_wall.WPosY[2] + 4.0f
				|| g_Bullet.fPosX >= g_wall.WPosX[3] - 1.0f && g_Bullet.fPosX < g_wall.WPosX[3] + 8.0f && g_Bullet.fPosY >= g_wall.WPosY[3] && g_Bullet.fPosY <= g_wall.WPosY[3] + 4.0f
				)
			{// �e����ʊO�ɏo��
				gotoxy((int)(g_Bullet.fPosXOld), (int)(g_Bullet.fPosYOld));
				printf("�@");
				g_Bullet.bUse = false;		// �e�𖢎g�p��Ԃ�
				g_Bullet.flag = 0;
				g_Bullet.bulletsound = 0;
			}
		}

		if (g_map.mapcount == 3)
		{
			if (g_Bullet.fPosX <= 2.0f         //�ǂƃu���b�N�ɓ���������Ƃ����Ӗ�
				|| g_Bullet.fPosX >= 79.0f     //   ||��or�ł���Aif����or�łȂ��Ă���
				|| g_Bullet.fPosY < 2.0f
				|| g_Bullet.fPosY > 24.0f
				|| g_Bullet.fPosX > g_block.PosX - 1.0f && g_Bullet.fPosX < g_block.PosX + 1.0f && g_Bullet.fPosY >= g_block.PosY - 1.0f && g_Bullet.fPosY <= g_block.PosY + 1.0f
				|| g_Bullet.fPosX >= g_wall.WPosX[4] - 1.0f && g_Bullet.fPosX < g_wall.WPosX[4] + 44.0f && g_Bullet.fPosY >= g_wall.WPosY[4] && g_Bullet.fPosY <= g_wall.WPosY[4] + 1.0f
				|| g_Bullet.fPosX >= g_wall.WPosX[4] - 1.0f && g_Bullet.fPosX < g_wall.WPosX[4] + 8.0f && g_Bullet.fPosY >= g_wall.WPosY[4] && g_Bullet.fPosY <= g_wall.WPosY[4] + 4.0f
				
				)
			{// �e����ʊO�ɏo��
				gotoxy((int)(g_Bullet.fPosXOld), (int)(g_Bullet.fPosYOld));
				printf("�@");
				g_Bullet.bUse = false;		// �e�𖢎g�p��Ԃ�
				g_Bullet.flag = 0;
				g_Bullet.bulletsound = 0;
			}
		}

		if (g_map.mapcount == 4)
		{
			if (g_Bullet.fPosX <= 2.0f         //�ǂƃu���b�N�ɓ���������Ƃ����Ӗ�
				|| g_Bullet.fPosX >= 48.0f     //   ||��or�ł���Aif����or�łȂ��Ă���
				|| g_Bullet.fPosY < 2.0f
				|| g_Bullet.fPosY > 14.0f
				|| g_Bullet.fPosX > 35 && g_Bullet.fPosX < 40 && g_Bullet.fPosY >= 7 && g_Bullet.fPosY <= g_wall.WPosY[4] + 12
				
				)
			{// �e����ʊO�ɏo��
				gotoxy((int)(g_Bullet.fPosXOld), (int)(g_Bullet.fPosYOld));
				printf("�@");
				g_Bullet.bUse = false;		// �e�𖢎g�p��Ԃ�
				g_Bullet.flag = 0;
				g_Bullet.bulletsound = 0;
			}
			if (g_Bullet.fPosX > 35 && g_Bullet.fPosX < 40 && g_Bullet.fPosY >= 7 && g_Bullet.fPosY <= g_wall.WPosY[4] + 12)
			{
				g_enemy[0].cameralife--;
			}
		}

		if (g_map.mapcount == 5)
		{
			if (g_Bullet.fPosX <= 2.0f         //�ǂƃu���b�N�ɓ���������Ƃ����Ӗ�
				|| g_Bullet.fPosX >= 48.0f     //   ||��or�ł���Aif����or�łȂ��Ă���
				|| g_Bullet.fPosY < 2.0f
				|| g_Bullet.fPosY > 14.0f
				
				)
			{// �e����ʊO�ɏo��
				gotoxy((int)(g_Bullet.fPosXOld), (int)(g_Bullet.fPosYOld));
				printf("�@");
				g_Bullet.bUse = false;		// �e�𖢎g�p��Ԃ�
				g_Bullet.flag = 0;
				g_Bullet.bulletsound = 0;
			}
		}

		//�G�Ƀ^�}������������
		if (g_enemy[0].life == 1 && g_map.mapcount == 2)
		{
			if (g_Bullet.fPosX > g_enemy[0].fEPosX - 1.0f && g_Bullet.fPosX < g_enemy[0].fEPosX + 1.0f && g_Bullet.fPosY >= g_enemy[0].fEPosY - 2.0f && g_Bullet.fPosY <= g_enemy[0].fEPosY + 1.0f)
			{// �e����ʊO�ɏo��
				gotoxy((int)(g_Bullet.fPosXOld), (int)(g_Bullet.fPosYOld));
				printf("�@");
				g_Bullet.bUse = false;		// �e�𖢎g�p��Ԃ�
				g_Bullet.flag = 0; //�e�̔��˕��������Z�b�g����
				g_Bullet.bulletsound = 0;
				g_enemy[0].life = 0;  //�G�̕\����0�ɂ��邽��
				g_enemy[0].count++;   //�G��|���������v���X����

			}
		}
		if (g_enemy[1].life == 1 && g_map.mapcount == 2)
		{
			if (g_Bullet.fPosX > g_enemy[1].fEPosX - 1.0f && g_Bullet.fPosX < g_enemy[1].fEPosX + 1.0f && g_Bullet.fPosY >= g_enemy[1].fEPosY - 2.0f && g_Bullet.fPosY <= g_enemy[1].fEPosY + 1.0f)
			{// �e����ʊO�ɏo��
				gotoxy((int)(g_Bullet.fPosXOld), (int)(g_Bullet.fPosYOld));
				printf("�@");
				g_Bullet.bUse = false;		// �e�𖢎g�p��Ԃ�
				g_Bullet.flag = 0; //�e�̔��˕��������Z�b�g����
				g_Bullet.bulletsound = 0;
				g_enemy[1].life = 0;  //�G�̕\����0�ɂ��邽��
				g_enemy[0].count++;   //�G��|���������v���X����

			}
		}

		if (g_enemy[3].life == 1 && g_map.mapcount == 2)
		{
			if (g_Bullet.fPosX > g_enemy[3].fEPosX - 1.0f && g_Bullet.fPosX < g_enemy[3].fEPosX + 1.0f && g_Bullet.fPosY >= g_enemy[3].fEPosY - 2.0f && g_Bullet.fPosY <= g_enemy[3].fEPosY + 1.0f)
			{// �e����ʊO�ɏo��
				gotoxy((int)(g_Bullet.fPosXOld), (int)(g_Bullet.fPosYOld));
				printf("�@");
				g_Bullet.bUse = false;		// �e�𖢎g�p��Ԃ�
				g_Bullet.flag = 0; //�e�̔��˕��������Z�b�g����
				g_Bullet.bulletsound = 0;
				g_enemy[3].life = 0;  //�G�̕\����0�ɂ��邽��
				g_enemy[0].count++;   //�G��|���������v���X����

			}
		}

		if (g_enemy[4].life == 1 && g_map.mapcount == 3)
		{
			if (g_Bullet.fPosX > g_enemy[4].fEPosX - 1.0f && g_Bullet.fPosX < g_enemy[4].fEPosX + 1.0f && g_Bullet.fPosY >= g_enemy[4].fEPosY - 2.0f && g_Bullet.fPosY <= g_enemy[4].fEPosY + 1.0f)
			{// �e����ʊO�ɏo��
				gotoxy((int)(g_Bullet.fPosXOld), (int)(g_Bullet.fPosYOld));
				printf("�@");
				g_Bullet.bUse = false;		// �e�𖢎g�p��Ԃ�
				g_Bullet.flag = 0; //�e�̔��˕��������Z�b�g����
				g_Bullet.bulletsound = 0;
				g_enemy[4].life = 0;  //�G�̕\����0�ɂ��邽��
				g_enemy[0].count++;   //�G��|���������v���X����

			}
		}

		if (g_enemy[5].life == 1 && g_map.mapcount == 5)
		{
			if (g_Bullet.fPosX > g_enemy[5].fEPosX - 1.0f && g_Bullet.fPosX < g_enemy[5].fEPosX + 1.0f && g_Bullet.fPosY >= g_enemy[5].fEPosY - 2.0f && g_Bullet.fPosY <= g_enemy[5].fEPosY + 1.0f)
			{// �e����ʊO�ɏo��
				gotoxy((int)(g_Bullet.fPosXOld), (int)(g_Bullet.fPosYOld));
				printf("�@");
				g_Bullet.bUse = false;		// �e�𖢎g�p��Ԃ�
				g_Bullet.flag = 0; //�e�̔��˕��������Z�b�g����
				g_Bullet.bulletsound = 0;
				g_enemy[5].life = 0;  //�G�̕\����0�ɂ��邽��
				g_enemy[0].count++;   //�G��|���������v���X����

			}
		}

		if (g_enemy[2].life == 1)
		{
			if (g_Bullet.fPosX > g_enemy[2].fEPosX - 1.0f && g_Bullet.fPosX < g_enemy[2].fEPosX + 1.0f && g_Bullet.fPosY >= g_enemy[2].fEPosY - 2.0f && g_Bullet.fPosY <= g_enemy[2].fEPosY + 1.0f)
			{// �e����ʊO�ɏo��
				gotoxy((int)(g_Bullet.fPosXOld), (int)(g_Bullet.fPosYOld));
				printf("�@");
				g_Bullet.bUse = false;		// �e�𖢎g�p��Ԃ�
				g_Bullet.flag = 0; //�e�̔��˕��������Z�b�g����
				g_Bullet.bulletsound = 0;
				g_enemy[2].life = 0;  //�G�̕\����0�ɂ��邽��
				g_enemy[0].count++;   //�G��|���������v���X����

			}
		}
	}
}

//=============================================================================
// �e�̕`�揈��
//=============================================================================
void DrawBullet(void)
{
	if (g_player.life == 1)
	{
		if (g_Bullet.bUse == true)
		{// �e���g�p���

			// �O��̈ʒu�ł̒e������
			gotoxy((int)(g_Bullet.fPosXOld), (int)(g_Bullet.fPosYOld));
			printf("�@");

			// ���݂̈ʒu�ɒe��\��
			if (g_Bullet.fPosX >= 3.0f && g_Bullet.fPosX <= 79.0f)
			{
				textcolor(1110);
				gotoxy((int)(g_Bullet.fPosX), (int)(g_Bullet.fPosY));
				printf("�� ");
			}
		}
	}
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
void SetBullet(float fPosX, float fPosY, float fMoveX, float fMoveY, BULLETTYPE type)
{

	if (g_Bullet.bUse == false)
	{// �e�����g�p���
		g_Bullet.fPosX = fPosX;
		g_Bullet.fPosY = fPosY;
		g_Bullet.fPosXOld = fPosX;
		g_Bullet.fPosYOld = fPosY;
		g_Bullet.fMoveX = fMoveX;
		g_Bullet.fMoveY = fMoveY;
		g_Bullet.type = type;
		g_Bullet.bUse = true;		// �e���g�p��Ԃ�
	}
}

