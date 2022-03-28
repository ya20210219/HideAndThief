//= ============================================================================
//
// Author : TAKASHI AKYAMA
//
//=============================================================================
#define CONIOEX
#include "conioex.h"
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "block.h"
#include "wall.h"
#include "UI.h"
#include "map.h"
#include "bullet.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UI_POS_X				(90)		// ��Q���̃|�W�V�����w����
#define UI_POS_Y				(5)	// ��Q���̃|�W�V�����x����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
UI g_ui;
extern PLAYER g_player;
extern ENEMY g_enemy[10];
extern BLOCK g_block;
extern MAP g_map;
extern BULLET g_Bullet;


int gunBGM;
int explosionBGM;

//=============================================================================
// �u���b�N�̏���������
//=============================================================================
void InitUI(void)
{
	gunBGM = opensound("BGM/machinegun.mp3");
	explosionBGM = opensound("BGM/bomb.mp3");
	setvolume(gunBGM, 40);
	setvolume(explosionBGM, 60);

	g_ui.UIcount = 0;
	g_ui.flag = 0;
	g_ui.gameflag = 1;
	g_ui.UIPosX = UI_POS_X;
	g_ui.UIPosY = UI_POS_Y;
	g_ui.score = 0;
	g_ui.scount = 0;
	g_ui.time = 200;
	g_ui.timeflag = 0;
	g_ui.ending = 0;
	g_ui.systemflag = 0;
	g_ui.buttonL = 0;
	g_ui.buttonR = 0;

}
//=============================================================================
// �u���b�N�̏I������
//=============================================================================
void UninitUI(void)
{

}

//=============================================================================
// �u���b�N�̍X�V����
//=============================================================================
void UpdateUI(void)
{
	g_ui.scount++;

	if (g_ui.scount % 60 == 1 && g_ui.gameflag == 1)
	{
		g_ui.score++;
	}

	if (g_ui.scount % 60 == 1 && g_ui.gameflag == 1)
	{
		g_ui.timeflag++;
		
	}
	g_ui.time = 200 - g_ui.timeflag;

	if (inport(PJ_XPOS) == 0 || inport(PK_A))
	{
		g_ui.flag = 1;
	}

	// �E�ړ�
	if (inport(PJ_XPOS) == 65535 || inport(PK_D))
	{
		g_ui.flag = 2;
	}

	// ��ړ�
	if (inport(PJ_YPOS) == 0 || inport(PK_W))
	{
		g_ui.flag = 3;
	}

	// ���ړ�
	if (inport(PJ_YPOS) == 65535 || inport(PK_S))
	{
		g_ui.flag = 4;
	}
	if (g_enemy[0].cameralife == 0)
	{
		g_ui.UIcount++;
	}
	if (g_player.life == 0)
	{
		g_ui.UIcount++;
	}
	if (g_player.life == 0 && g_ui.UIcount % 120 == 0)
	{
		playsound(gunBGM, 0);
	}
}

//=============================================================================
// �u���b�N�̕`�揈��
//=============================================================================
void DrawUI(void)
{
	textbackground(0x0);
	
	gotoxy(g_ui.UIPosX + 2, g_ui.UIPosY + 11);
	textcolor(1111);
	printf("�G�Ɍ����炸");
	gotoxy(g_ui.UIPosX, g_ui.UIPosY + 12);
	textcolor(1011);
	printf("��");
	gotoxy(g_ui.UIPosX + 2, g_ui.UIPosY + 12);
	textcolor(1111);
	printf("�̏���"); 
	textcolor(1110);	
	gotoxy(g_ui.UIPosX + 8, g_ui.UIPosY + 12);
	printf("��");
	gotoxy(g_ui.UIPosX + 10, g_ui.UIPosY + 12);
	textcolor(1111);
	printf("�������ċA�낤�I");

	gotoxy(g_ui.UIPosX + 10, g_ui.UIPosY + 14);
	textcolor(1111);
	printf("%d", g_map.mapcount);


	gotoxy(81, 1);
	textcolor(BLACK);
	printf("������������");


	if (g_player.life == 1)
	{
		textcolor(0011);
		gotoxy(g_ui.UIPosX + 14, g_ui.UIPosY - 3);
		printf("�X���[�A�r���e�B");

		gotoxy(g_ui.UIPosX + 14, g_ui.UIPosY - 1);

		if (g_player.slow == 1)
		{
			textcolor(1110);
			gotoxy(g_ui.UIPosX + 14, g_ui.UIPosY - 1);
			printf("�A�r���e�B�����I");
		}
		if (g_player.slowcooldownflag == 1 && g_player.slow == 0 && g_player.slowflag == 0)
		{
			textcolor(LIGHTBLUE);
			gotoxy(g_ui.UIPosX + 14, g_ui.UIPosY - 1);
			printf("�N�[���_�E����  ");
		}
		if (g_player.slowflag == 1)
		{
			textcolor(LIGHTGREEN);
			gotoxy(g_ui.UIPosX + 14, g_ui.UIPosY - 1);
			printf("��������        ");
		}
		

		textcolor(1100);
		gotoxy(g_ui.UIPosX, g_ui.UIPosY - 3);
		printf("�����Ă����");

		gotoxy(g_ui.UIPosX + 1, g_ui.UIPosY - 1);
		{
			printf("  �P�P");
		}

		gotoxy(g_ui.UIPosX + 4, g_ui.UIPosY + 1);
		{
			printf("�Q�Q");
		}
		gotoxy(g_ui.UIPosX + 2, g_ui.UIPosY - 1);
		{
			printf("|");
		}
		gotoxy(g_ui.UIPosX + 2, g_ui.UIPosY );
		{
			printf("|");
		}
		gotoxy(g_ui.UIPosX + 2, g_ui.UIPosY + 1);
		{
			printf("|");
		}
		gotoxy(g_ui.UIPosX + 8, g_ui.UIPosY - 1);
		{
			printf("|");
		}
		gotoxy(g_ui.UIPosX + 8, g_ui.UIPosY);
		{
			printf("|");
		}
		gotoxy(g_ui.UIPosX + 8, g_ui.UIPosY + 1);
		{
			printf("|");
		}



		if (g_ui.flag == 1)
		{
			gotoxy(g_ui.UIPosX + 4, g_ui.UIPosY);
			printf("��");
		}
		if (g_ui.flag == 2)
		{
			gotoxy(g_ui.UIPosX + 4, g_ui.UIPosY);
			printf("��");
		}
		if (g_ui.flag == 3)
		{
			gotoxy(g_ui.UIPosX + 4, g_ui.UIPosY);
			printf("��");
		}
		if (g_ui.flag == 4)
		{
			gotoxy(g_ui.UIPosX + 4, g_ui.UIPosY);
			printf("��");
		}

		gotoxy(g_ui.UIPosX, g_ui.UIPosY + 4);
		printf("�c�e��:%d", g_Bullet.bulletcount);

		gotoxy(g_ui.UIPosX, g_ui.UIPosY + 5);
		printf("�|�����G�̐�:%d", g_enemy[0].count);

		gotoxy(g_ui.UIPosX, g_ui.UIPosY + 7);
		printf("�c�莞��:%d", g_ui.time);

		if (g_ui.time <= 9)
		{
			gotoxy(g_ui.UIPosX + 10, g_ui.UIPosY + 7);
			printf(" ");
		}

		if (g_Bullet.bulletcount <= 9)
		{
			gotoxy(g_ui.UIPosX + 8, g_ui.UIPosY + 4);
			printf(" ");
		}

		textcolor(DARKGRAY);
		gotoxy(65, 25);
		printf("�\���L�[");
		textcolor(WHITE);
		gotoxy(73, 25);
		printf("�F�L�����ړ�");

		textcolor(LIGHTRED);
		gotoxy(65, 26);
		printf("A");
		textcolor(WHITE);
		gotoxy(66, 26);
		printf("�{�^���F�e����");

		textcolor(LIGHTGREEN);
		gotoxy(65, 27);
		printf("Y");
		textcolor(WHITE);
		gotoxy(66, 27);
		printf("�{�^���F�A�r���e�B����");

	}

	if (g_player.life == 0 )
	{
		textcolor(1100);
		gotoxy(10, 26);
		printf("�N����!!");
		msleep(100);

		textcolor(1100);
		gotoxy(10, 26);
		printf("�������ꂽ�I");
		gotoxy(10, 28);
		printf("�Q�[���I�[�o�[�I");
		g_ui.ending = 1;
		g_ui.gameflag = 0;
	}

	if (g_ui.time < 0.1)
	{
		textcolor(1100);
		gotoxy(10, 26);
		printf("���Ԑ؂ꂾ...");
		gotoxy(10, 28);
		printf("�Q�[���I�[�o�[�I");
		g_ui.ending = 1;
		g_ui.gameflag = 0;
	}

	if ((int)g_player.fPosX > 2 && (int)g_player.fPosX < 5 && (int)g_player.fPosY >= 9 && (int)g_player.fPosY <= 10 && g_block.thief == 0 && g_map.mapcount == 1)
	{
		g_ui.ending = 1;
		g_ui.gameflag = 0;
	}
	if (g_map.mapcount == 1)
	{
		gotoxy(38, 16);
		printf("�ʘH");
	}
	if (g_map.mapcount == 2)
	{
		gotoxy(38, 24);
		printf("��L��");
	}
	if (g_map.mapcount == 3)
	{
		gotoxy(30, 24);
		printf("����");

		if (g_enemy[0].cameralife >= 1)
		{
			gotoxy(30, 25);
			printf("�Ď��J�����������ĕ󂪂Ƃ�Ȃ�");
			gotoxy(30, 26);
			printf("�Ď��J�����̓d�������Ƃ���΁E�E�E");
		}
	}
	if (g_map.mapcount == 4)
	{
		gotoxy(30, 16);
		printf("�Ď��J�����p�d����");
		if (g_enemy[0].cameralife >= 1)
		{
			gotoxy(30, 26);
			printf("�Ď��J�����̓d����");
			gotoxy(30, 27);
			printf("�󂵂Ă������ق���������������Ȃ�");
			gotoxy(30, 28);
			printf("�������ĂΉ��邩�E�E�E�H");
		}
	}
	if (g_enemy[0].cameralife == 0 && g_ui.UIcount <= 180)
	{
		gotoxy(30, 25);
		printf("�Ď��J�����̓d�����󂵂��I");
		playsound(explosionBGM, 0);
		gotoxy(30, 26);
		printf("                                         ");
		gotoxy(30, 27);
		printf("                                         ");
		gotoxy(30, 28);
		printf("                                         ");
		g_ui.UIcount = 0;
		g_enemy[0].cameralife = -1;
	}

	if (g_map.mapcount == 5)
	{
		gotoxy(25, 16);
		printf("�e���");
	}
}

void ending(void)
{
	if (g_ui.time < 1)
	{
		g_ui.ending = 1;
		g_ui.gameflag = 0;
	}

	if (g_ui.ending == 1 && g_player.life == 0)
	{
		playsound(gunBGM, 0);
	}

	if (g_ui.ending == 1 && g_player.life != 0 && g_block.thief == 0)
	{
		gotoxy(g_ui.UIPosX, g_ui.UIPosY + 15);
		textcolor(1110);
		printf("���ݏo�����I");
		g_ui.gameflag = 0;
		gotoxy(g_ui.UIPosX, g_ui.UIPosY + 17);

		if (200 - g_ui.score >= 1)
		{
			printf("�X�R�A:%d", 200 - g_ui.score + g_enemy->count);
		}

		if (200 - g_ui.score+ g_enemy->count < 1)
		{
			printf("�X�R�A:%d", 0);
			Sleep(3500);
			return;
		}

		if (200 - g_ui.score + g_enemy->count >= 160)
		{
			gotoxy(g_ui.UIPosX, g_ui.UIPosY + 19);
			printf("�����NS");
			gotoxy(g_ui.UIPosX, g_ui.UIPosY + 20);
			printf("Excellent!!");
			Sleep(3500);
			return;
		}
		if (200 - g_ui.score + g_enemy->count >= 140 && 100 - g_ui.score + g_enemy->count < 90)
		{
			gotoxy(g_ui.UIPosX, g_ui.UIPosY + 19);
			printf("�����NA");
			gotoxy(g_ui.UIPosX, g_ui.UIPosY + 20);
			printf("�f���炵���I");
			Sleep(3500);
			return;
		}

		if (200 - g_ui.score + g_enemy->count >= 120 && 100 - g_ui.score + g_enemy->count < 70)
		{
			gotoxy(g_ui.UIPosX, g_ui.UIPosY + 19);
			printf("�����NB");
			gotoxy(g_ui.UIPosX, g_ui.UIPosY + 20);
			printf("��o����");
			Sleep(3500);
			return;
		}


		if (200 - g_ui.score + g_enemy->count < 100)
		{
			gotoxy(g_ui.UIPosX, g_ui.UIPosY + 19);
			printf("�����NC");
			gotoxy(g_ui.UIPosX, g_ui.UIPosY + 20);
			printf("���Ƃ�������...");
			Sleep(3500);
			return;
		}

		
	}

	if (g_player.life == 0)
	{
		Sleep(3500);
		return;
	}
}

void title(void)
{
	textcolor(0111);
	gotoxy(5,1);
	printf("��          ��    ��    ����������        ������������");
	gotoxy(5, 2);
	printf("��          ��    ��    ��        ��      ��");
	gotoxy(5, 3);
	printf("��          ��    ��    ��          ��    ��");
	gotoxy(5, 4);
	printf("��          ��    ��    ��          ��    ��");
	gotoxy(5, 5);
	printf("��������������    ��    ��          ��    ����������                                         �@�@���Q_��");
	gotoxy(5, 6);
	printf("��          ��    ��    ��          ��    ��                                                   �i �E�ցE�j");
	gotoxy(5, 7);
	printf("��          ��    ��    ��          ��    ��                          �ȁQ��     ���P�P�P�R  �@���@�@�@�R");
	gotoxy(5, 8);
	printf("��          ��    ��    ��        ��      ��                        �i�@�E�́j   |        |  �@ |   �@| |");
	gotoxy(5, 9);
	printf("��          ��    ��    ����������        ������������            ���P�R  ��     |   ��   |  �@��Ɂ@,,ɤ_)");
	gotoxy(5, 10);
	printf("                                                               �@�@� r�_���     |        |    �@|�@|�@| ");
	gotoxy(5, 11);
	printf("                                                              �@�i /�@ /�@/      |        |    �@|�@|�@| ");

	gotoxy(7, 12);
	printf("      ����        ����          ��    ����������             �@ �T�Q,�j__�j    |        |  �@ �i__)�Q�j");
	gotoxy(7, 13);
	printf("      ����        ������        ��    ��        ��");
	gotoxy(7, 14);
	printf("    ��  ��        ��  ��        ��    ��          ��");
	gotoxy(7, 15);
	printf("    ��    ��      ��    ��      ��    ��          ��");
	gotoxy(7, 16);
	printf("    ��    ��      ��    ����    ��    ��          ��");
	gotoxy(7, 17);
	printf("  ����������      ��      ��    ��    ��          ��");
	gotoxy(7, 18);
	printf("  ��        ��    ��        ��  ��    ��          ��");
	gotoxy(7, 19);
	printf("����        ��    ��        ������    ��        ��");
	gotoxy(7, 20);
	printf("��          ��    ��            ��    ����������");

	gotoxy(1, 22);
	printf("��������������    ��          ��    ��    ������������    ������������               PRESS START");
	gotoxy(1, 23);
	printf("      ��          ��          ��    ��    ��              ��");
	gotoxy(1, 24);
	printf("      ��          ��          ��    ��    ��              ��");
	gotoxy(1, 25);
	printf("      ��          ��          ��    ��    ��              ��");
	gotoxy(1, 26);
	printf("      ��          ��������������    ��    ����������      ����������");
	gotoxy(1, 27);
	printf("      ��          ��          ��    ��    ��              ��");
	gotoxy(1, 28);
	printf("      ��          ��          ��    ��    ��              ��");
	gotoxy(1, 29);
	printf("      ��          ��          ��    ��    ��              ��");
	gotoxy(1, 30);
	printf("      ��          ��          ��    ��    ������������    ��");
}

void tutorial(void)
{
	gotoxy(44, 2);
	printf("�`�`�`�`���[�g���A���`�`�`");


	textcolor(1111);
	gotoxy(10, 5);
	printf("��");
	gotoxy(10, 6);
	printf("��");
	gotoxy(8, 8);
	printf("���L����");

	textcolor(0001);
	gotoxy(20, 5);
	printf("��");
	gotoxy(20, 6);
	printf("��");
	gotoxy(20, 8);
	printf("�G�L����");

	textcolor(0xAA);
	gotoxy(22, 5);
	printf("��");
	gotoxy(24, 4);
	printf("��");
	gotoxy(24, 5);
	printf("��");
	gotoxy(24, 6);
	printf("��");
	gotoxy(26, 3);
	printf("��");
	gotoxy(26, 4);
	printf("��");
	gotoxy(26, 5);
	printf("��");
	gotoxy(26, 6);
	printf("��");
	gotoxy(26, 7);
	printf("��");
	gotoxy(30, 5);
	printf("��:�G��Ď��J�����̎��E");

	textcolor(0001);
	gotoxy(20, 12);
	printf("��");
	textcolor(0xAA);
	gotoxy(22, 11);
	printf("����������������");
	gotoxy(22, 12);
	printf("����������������");
	gotoxy(22, 13);
	printf("����������������");
	gotoxy(20, 15);
	textcolor(0001);
	printf("�Ď��J����");

	textcolor(4);
	gotoxy(8, 17);
	printf("��");
	textcolor(1111);
	gotoxy(10, 17);
	printf(":�}�b�v�ړ��̃e���|�[�g��");

	textcolor(GREEN);
	gotoxy(8, 19);
	printf("��");
	textcolor(1111);
	gotoxy(10, 19);
	printf(":�e��BOX");

	textcolor(DARKGRAY);
	gotoxy(8, 21);
	printf("�\");

	textcolor(1111);
	gotoxy(10, 21);
	printf("���L�[�Ŏ��L�����𑀍�I");
	textcolor(1100);
	gotoxy(8, 23);
	printf("A");
	textcolor(1111);
	gotoxy(9, 23);
	printf("�{�^��:�e�𔭎ˁI");
	textcolor(GREEN);
	gotoxy(8, 25);
	printf("Y");

	textcolor(1111);
	gotoxy(9, 25);
	printf("�{�^��:3�b�Ԃ����G�̓������X���[�ɂ��邱�Ƃ��ł���");
	gotoxy(8, 26);
	printf("�������A�g�p��ɂ͐��b�Ԃ̃N�[���_�E���^�C��������");

	gotoxy(60, 10);
	printf("�G�Ɍ����炸");
	textcolor(1110);
	gotoxy(74, 10);
	printf("��");
	textcolor(1111);
	gotoxy(76,10);
	printf("�𓐂����I");

	textcolor(1111);
	gotoxy(60, 20);
	printf("�������ł�����R���g���[���[��");
	gotoxy(61,21);
	printf("�g���K�[��");
	gotoxy(72, 21);
	printf("�g���K�[");
	textcolor(LIGHTCYAN);
	gotoxy(60, 21);
	printf("L");
	gotoxy(71, 21);
	printf("R");
	textcolor(1111);
	gotoxy(60, 22);
	printf("������");
	gotoxy(60, 23);
	printf("�������̓L�[�{�[�h�́uO�v�ƁuK�v�������Ă�������");
}
