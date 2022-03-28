//= ============================================================================
//
// �v���C���[���� [block.cpp]
// Author : TAKASHI AKYAMA
//
//=============================================================================
#define CONIOEX
#include "conioex.h"
#include "main.h"
#include "player.h"
#include "block.h"
#include "wall.h"
#include "map.h"
#include "bullet.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WALL_POS_X1				(5)		// ��Q���̃|�W�V�����w����
#define WALL_POS_Y1				(6)		// ��Q���̃|�W�V�����x����
#define WALL_POS_X2				(20)	// ��Q���̃|�W�V�����w����
#define WALL_POS_Y2				(6)		// ��Q���̃|�W�V�����x����
#define WALL_POS_X3				(5)		// ��Q���̃|�W�V�����w����
#define WALL_POS_Y3				(16)	// ��Q���̃|�W�V�����x����
#define WALL_POS_X4				(20)	// ��Q���̃|�W�V�����w����
#define WALL_POS_Y4				(16)	// ��Q���̃|�W�V�����x����
#define WALL_POS_X5				(20)	// ��Q���̃|�W�V�����w����
#define WALL_POS_Y5				(7)		// ��Q���̃|�W�V�����x����
#define WALL_POS_X6				(12)	// ��Q���̃|�W�V�����w����
#define WALL_POS_Y6				(6)		// ��Q���̃|�W�V�����x����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
WALL g_wall;
extern PLAYER g_player;
extern MAP g_map;
extern BULLET g_Bullet;
extern ENEMY g_enemy[10];

//=============================================================================
// �u���b�N�̏���������
//=============================================================================
void InitWall(void)
{
	// �v���C���[���[�N�̃N���A
	g_wall.WPosX[0] = WALL_POS_X1;
	g_wall.WPosY[0] = WALL_POS_Y1;
	g_wall.WPosX[1] = WALL_POS_X2;
	g_wall.WPosY[1] = WALL_POS_Y2;
	g_wall.WPosX[2] = WALL_POS_X3;
	g_wall.WPosY[2] = WALL_POS_Y3;
	g_wall.WPosX[3] = WALL_POS_X4;
	g_wall.WPosY[3] = WALL_POS_Y4;
	g_wall.WPosX[4] = WALL_POS_X5;
	g_wall.WPosY[4] = WALL_POS_Y5;
	g_wall.WPosX[5] = WALL_POS_X6;
	g_wall.WPosY[5] = WALL_POS_Y6;
}
//=============================================================================
// �u���b�N�̏I������
//=============================================================================
void UninitWall(void)
{

}

//=============================================================================
// �u���b�N�̍X�V����
//=============================================================================
void UpdateWall(void)
{
	g_wall.WPosX[0] = WALL_POS_X1;
	g_wall.WPosY[0] = WALL_POS_Y1;
	g_wall.WPosX[1] = WALL_POS_X2;
	g_wall.WPosY[1] = WALL_POS_Y2;
	g_wall.WPosX[2] = WALL_POS_X3;
	g_wall.WPosY[2] = WALL_POS_Y3;
	g_wall.WPosX[3] = WALL_POS_X4;
	g_wall.WPosY[3] = WALL_POS_Y4;
}

//=============================================================================
// �u���b�N�̕`�揈��
//=============================================================================
void DrawWall(void)
{
	if (g_player.life == 1 && g_map.mapcount == 2)
	{
		textbackground(0x6);
		textcolor(0010);
		//�@�I�u�W�F�N�g�̔z�u
		gotoxy(g_wall.WPosX[0], g_wall.WPosY[0]);
		printf("��������");
		gotoxy(g_wall.WPosX[0], g_wall.WPosY[0] + 1);
		printf("��������");
		gotoxy(g_wall.WPosX[0], g_wall.WPosY[0] + 2);
		printf("��������");
		gotoxy(g_wall.WPosX[0], g_wall.WPosY[0] + 3);
		printf("��������");

		gotoxy(g_wall.WPosX[1], g_wall.WPosY[1]);
		printf("��������");
		gotoxy(g_wall.WPosX[1], g_wall.WPosY[1] + 1);
		printf("��������");
		gotoxy(g_wall.WPosX[1], g_wall.WPosY[1] + 2);
		printf("��������");
		gotoxy(g_wall.WPosX[1], g_wall.WPosY[1] + 3);
		printf("��������");

		gotoxy(g_wall.WPosX[2], g_wall.WPosY[2]);
		printf("��������");
		gotoxy(g_wall.WPosX[2], g_wall.WPosY[2] + 1);
		printf("��������");
		gotoxy(g_wall.WPosX[2], g_wall.WPosY[2] + 2);
		printf("��������");
		gotoxy(g_wall.WPosX[2], g_wall.WPosY[2] + 3);
		printf("��������");

		gotoxy(g_wall.WPosX[3], g_wall.WPosY[3]);
		printf("��������");
		gotoxy(g_wall.WPosX[3], g_wall.WPosY[3] + 1);
		printf("��������");
		gotoxy(g_wall.WPosX[3], g_wall.WPosY[3] + 2);
		printf("��������");
		gotoxy(g_wall.WPosX[3], g_wall.WPosY[3] + 3);
		printf("��������");
	}

	if (g_player.life == 1 && g_map.mapcount == 3)
	{
		textbackground(7);
		textcolor(1000);
		gotoxy(g_wall.WPosX[4], g_wall.WPosY[4]); 
		printf("��������������������������������������������");
		gotoxy(g_wall.WPosX[4], g_wall.WPosY[4] + 11);
		printf("��������������������������������������������");
		gotoxy(g_wall.WPosX[4], g_wall.WPosY[4] + 1);
		printf("��");
		gotoxy(g_wall.WPosX[4] + 42, g_wall.WPosY[4] + 1);
		printf("��");
		gotoxy(g_wall.WPosX[4], g_wall.WPosY[4] + 2);
		printf("��");
		gotoxy(g_wall.WPosX[4] + 42, g_wall.WPosY[4] + 2);
		printf("��");
		gotoxy(g_wall.WPosX[4], g_wall.WPosY[4] + 3);
		printf("��");
		gotoxy(g_wall.WPosX[4] + 42, g_wall.WPosY[4] + 3);
		printf("��");
		gotoxy(g_wall.WPosX[4], g_wall.WPosY[4] + 4);
		printf("��");
		
		gotoxy(g_wall.WPosX[4], g_wall.WPosY[4] + 5);
		printf("��");
		
		gotoxy(g_wall.WPosX[4], g_wall.WPosY[4] + 6);
		printf("��");
		
		gotoxy(g_wall.WPosX[4], g_wall.WPosY[4] + 7);
		printf("��");
		
		gotoxy(g_wall.WPosX[4], g_wall.WPosY[4] + 8);
		printf("��");
		gotoxy(g_wall.WPosX[4] + 42, g_wall.WPosY[4] + 8);
		printf("��");
		gotoxy(g_wall.WPosX[4], g_wall.WPosY[4] + 9);
		printf("��");
		gotoxy(g_wall.WPosX[4] + 42, g_wall.WPosY[4] + 9);
		printf("��");
		gotoxy(g_wall.WPosX[4], g_wall.WPosY[4] + 10);
		printf("��");
		gotoxy(g_wall.WPosX[4] + 42, g_wall.WPosY[4] + 10);
		printf("��");
	}

	if (g_player.life == 1 && g_map.mapcount == 4 && g_enemy[0].cameralife >= 1)
	{
		textbackground(3);
		textcolor(1000);
		gotoxy(g_wall.WPosX[4] + 30, g_wall.WPosY[4]);
		printf("����������");
		gotoxy(g_wall.WPosX[4] + 30, g_wall.WPosY[4] + 1);
		printf("����������");
		gotoxy(g_wall.WPosX[4] + 30, g_wall.WPosY[4] + 2);
		printf("����������");
		gotoxy(g_wall.WPosX[4] + 30, g_wall.WPosY[4] + 3);
		printf("����������");
		gotoxy(g_wall.WPosX[4] + 30, g_wall.WPosY[4] + 4);
		printf("����������");
		gotoxy(g_wall.WPosX[4] + 30, g_wall.WPosY[4] + 5);
		printf("����������");
	}

	if (g_player.life == 1 && g_map.mapcount == 4 && g_enemy[0].cameralife <= 0)
	{
		textbackground(6);
		textcolor(RED);
		gotoxy(g_wall.WPosX[4] + 30, g_wall.WPosY[4]);
		printf("����������");
		gotoxy(g_wall.WPosX[4] + 30, g_wall.WPosY[4] + 1);
		printf("����������");
		gotoxy(g_wall.WPosX[4] + 30, g_wall.WPosY[4] + 2);
		printf("����������");
		gotoxy(g_wall.WPosX[4] + 30, g_wall.WPosY[4] + 3);
		printf("����������");
		gotoxy(g_wall.WPosX[4] + 30, g_wall.WPosY[4] + 4);
		printf("����������");
		gotoxy(g_wall.WPosX[4] + 30, g_wall.WPosY[4] + 5);
		printf("����������");
	}

	if (g_player.life == 1 && g_map.mapcount == 5)
	{
		textbackground(7);
		textcolor(1000);

		gotoxy(3, 6);
		printf("��������������");
	}

	textbackground(0);
}

//=============================================================================
// �����蔻����K
//=============================================================================
void Wallcollision(void)
{

	if (g_map.mapcount == 2)
	{
		//�A�����蔻��̐ݒ�
		if ((int)(g_player.fPosX) >= g_wall.WPosX[0] - 1.0f && (int)(g_player.fPosX) < g_wall.WPosX[0] + 8.0f && (int)(g_player.fPosY) >= g_wall.WPosY[0] && (int)(g_player.fPosY) <= g_wall.WPosY[0] + 4.0f)
		{
			textcolor(0010);
			g_player.fPosY = g_player.fPosYOLD;
			g_player.fPosX = g_player.fPosXOLD;
		}

		if ((int)(g_player.fPosX) >= g_wall.WPosX[1] - 1.0f && (int)(g_player.fPosX) < g_wall.WPosX[1] + 8.0f && (int)(g_player.fPosY) >= g_wall.WPosY[1] && (int)(g_player.fPosY) <= g_wall.WPosY[1] + 4.0f)
		{
			textcolor(0010);
			g_player.fPosY = g_player.fPosYOLD;
			g_player.fPosX = g_player.fPosXOLD;
		}

		if ((int)(g_player.fPosX) >= g_wall.WPosX[2] - 1.0f && (int)(g_player.fPosX) < g_wall.WPosX[2] + 8.0f && (int)(g_player.fPosY) >= g_wall.WPosY[2] && (int)(g_player.fPosY) <= g_wall.WPosY[2] + 4.0f)
		{
			textcolor(0010);
			g_player.fPosY = g_player.fPosYOLD;
			g_player.fPosX = g_player.fPosXOLD;
		}

		if ((int)(g_player.fPosX) >= g_wall.WPosX[3] - 1.0f && (int)(g_player.fPosX) < g_wall.WPosX[3] + 8.0f && (int)(g_player.fPosY) >= g_wall.WPosY[3] && (int)(g_player.fPosY) <= g_wall.WPosY[3] + 4.0f)
		{
			textcolor(0010);
			g_player.fPosY = g_player.fPosYOLD;
			g_player.fPosX = g_player.fPosXOLD;
		}
	}

	if (g_map.mapcount == 3)
	{
		textbackground(7);

		textcolor(1000);
		if ((int)(g_player.fPosX) >= g_wall.WPosX[4] - 1.0f && (int)(g_player.fPosX) < g_wall.WPosX[4] + 44.0f && (int)(g_player.fPosY) >= g_wall.WPosY[4] && (int)(g_player.fPosY) <= g_wall.WPosY[4] + 1.0f)
		{		
			g_player.fPosY = g_player.fPosYOLD;
			g_player.fPosX = g_player.fPosXOLD;
		}

		if ((int)(g_player.fPosX) >= g_wall.WPosX[4] - 1.0f && (int)(g_player.fPosX) < g_wall.WPosX[4] + 44.0f && (int)(g_player.fPosY) >= g_wall.WPosY[4] + 11.0f && (int)(g_player.fPosY) <= g_wall.WPosY[4] + 12.0f)
		{
			g_player.fPosY = g_player.fPosYOLD;
			g_player.fPosX = g_player.fPosXOLD;
		}
		if ((int)(g_player.fPosX) >= g_wall.WPosX[4] - 1.0f && (int)(g_player.fPosX) < g_wall.WPosX[4] + 2.0f && (int)(g_player.fPosY) >= g_wall.WPosY[4] + 1.0f && (int)(g_player.fPosY) <= g_wall.WPosY[4] + 12.0f)
		{
			g_player.fPosY = g_player.fPosYOLD;
			g_player.fPosX = g_player.fPosXOLD;
		}
		if ((int)(g_player.fPosX) >= g_wall.WPosX[4] + 41.0f && (int)(g_player.fPosX) < g_wall.WPosX[4] + 44.0f && (int)(g_player.fPosY) >= g_wall.WPosY[4] + 1.0f && (int)(g_player.fPosY) <= g_wall.WPosY[4] + 4.0f)
		{
     		g_player.fPosY = g_player.fPosYOLD;
			g_player.fPosX = g_player.fPosXOLD;
		}
		if ((int)(g_player.fPosX) >= g_wall.WPosX[4] + 41.0f && (int)(g_player.fPosX) < g_wall.WPosX[4] + 44.0f && (int)(g_player.fPosY) >= g_wall.WPosY[4] + 8.0f && (int)(g_player.fPosY) <= g_wall.WPosY[4] + 12.0f)
		{
			g_player.fPosY = g_player.fPosYOLD;
			g_player.fPosX = g_player.fPosXOLD;
		}
	}

	if (g_map.mapcount == 4)
	{
		if ((int)(g_player.fPosX) > g_wall.WPosX[4] + 28 && (int)(g_player.fPosX) < g_wall.WPosX[4] + 40 && (int)(g_player.fPosY) >= g_wall.WPosY[4] && (int)(g_player.fPosY) <= g_wall.WPosY[4] + 6)
		{
			g_player.fPosY = g_player.fPosYOLD;
			g_player.fPosX = g_player.fPosXOLD;
		}
		if (g_Bullet.fPosX > g_wall.WPosX[4] + 28 && g_Bullet.fPosX < g_wall.WPosX[4] + 40 && g_Bullet.fPosX >= g_wall.WPosY[4] && g_Bullet.fPosX <= g_wall.WPosY[4] + 6)
		{
			g_enemy[0].cameralife--;
		}
	}

	if (g_map.mapcount == 5)
	{
		if ((int)(g_player.fPosX) > 1 && (int)(g_player.fPosX) < 17 && (int)(g_player.fPosY) >= 6 && (int)(g_player.fPosY) <=  7)
		{
			g_player.fPosY = g_player.fPosYOLD;
			g_player.fPosX = g_player.fPosXOLD;
		}
		
	}

}