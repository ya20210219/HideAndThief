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
#include "enemy.h"
#include "map.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BLOCK_POS_X				(13)		// ��Q���̃|�W�V�����w����
#define BLOCK_POS_Y				(12)		// ��Q���̃|�W�V�����x����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
BLOCK g_block;
extern MAP g_map;
extern PLAYER g_player;
extern BULLET g_Bullet;

int BGM5;
int BGM6;
//=============================================================================
// �u���b�N�̏���������
//=============================================================================
void InitBlock(void)
{
	// �v���C���[���[�N�̃N���A
	g_block.PosX = BLOCK_POS_X;
	g_block.PosY = BLOCK_POS_Y;
	g_block.thief = 1;
	g_block.blocktime = 0;
	g_block.ammoblock = 1;
	BGM5 = opensound("BGM/decision4.mp3");
	BGM6 = opensound("BGM/pistolready.mp3");
}
//=============================================================================
// �u���b�N�̏I������
//=============================================================================
void UninitBlock(void)
{

}

//=============================================================================
// �u���b�N�̍X�V����
//=============================================================================
void UpdateBlock(void)
{
	g_block.PosX = BLOCK_POS_X;
	g_block.PosY = BLOCK_POS_Y;
	if (g_block.thief == 0)
	{
		g_block.blocktime++;
	}
}

//=============================================================================
// �u���b�N�̕`�揈��
//=============================================================================
void DrawBlock(void)
{
	if (g_player.life == 1 && g_block.thief == 1 && g_map.mapcount == 3)
	{
		//�@�I�u�W�F�N�g�̔z�u
		textcolor(1110);
		gotoxy(g_block.PosX, g_block.PosY);
		printf("��");
	}

	if (g_map.mapcount == 5 && g_block.ammoblock == 1)
	{
		gotoxy(5, 3);
		textcolor(GREEN);
		printf("��");
	}
}

//=============================================================================
// �����蔻����K
//=============================================================================
void collision(void)
{
	//�A�����蔻��̐ݒ�
	if (g_block.thief == 1 && (int)(g_player.fPosX) > g_block.PosX - 2.0f && (int)(g_player.fPosX) < g_block.PosX + 2.0f && (int)(g_player.fPosY) >= g_block.PosY - 1.0f && (int)(g_player.fPosY) <= g_block.PosY + 1.0f && g_map.mapcount == 3)
	{

		gotoxy(10, 27);
		textcolor(WHITE);
		printf("�C�����I");
		playsound(BGM5, 0);
		g_block.thief = 0;
		msleep(20);
		clrscr();
		gotoxy(10, 27);
		textcolor(WHITE);
		printf("���񂾁I");
	
	}
	if (g_block.blocktime == 100)
	{
		gotoxy(10, 27);
		textcolor(0000);
		printf("������������");
	}

	if (g_block.ammoblock == 1 && (int)(g_player.fPosX) > 5 - 1.0f && (int)(g_player.fPosX) < 5 + 1.0f && (int)(g_player.fPosY) >= 3 - 1.0f && (int)(g_player.fPosY) <= 3 + 1.0f && g_map.mapcount == 5)
	{
		gotoxy(10, 27);
		textcolor(WHITE);
		printf("�e���⋋����!");
		playsound(BGM6, 0);
		g_block.ammoblock = 0;
		g_Bullet.bulletcount = g_Bullet.bulletcount + 5;
		msleep(20);
		clrscr();
		gotoxy(10, 27);
		textcolor(WHITE);
		printf("�e���⋋����!");
	}

	if (g_block.blocktime == 100)
	{
		gotoxy(10, 27);
		textcolor(0000);
		printf("����������������");
	}
}