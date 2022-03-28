//=============================================================================
//
// �A�N�V�����Q�[���T���v�� [main.cpp]
// Author : TAKASHI AKIYAMA
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "block.h"
#include "wall.h"
#include "map.h"
#include "UI.h"
//#include "system.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DEBUG

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void Init(void);
void Uninit(void);
void Update(void);
void Draw(void);
void titleback(void);
extern UI g_ui;
extern PLAYER g_player;

#ifdef DEBUG
void DispFPS(void);
#endif

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int g_nCountFPS;				// FPS�J�E���^
int gamereset = 1;
int BGM2 = 0;
int BGM3 = 0;
int BGM4 = 0;

//=============================================================================
// ���C���֐�
//=============================================================================
void main(void)
{

	DWORD dwExecLastTime;	//���s�p������
	DWORD dwFPSLastTime;	//FPS�p������
	DWORD dwCurrentTime;	//���ݎ���
	int nCountFrame;

	//int BGM1 = 0;
	//int BGM2 = 0;
	BGM2 = opensound("BGM/bgm_maoudamashii_cyber44.mp3");
	BGM3 = opensound("BGM/n139.mp3");
	BGM4 = opensound("BGM/n100(2).mp3");


	setvolume(BGM2, 40);
	setvolume(BGM3, 40);
	setvolume(BGM4, 40);

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �e��l�̏�����
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();//�V�X�e���������~���b�P�ʂŕԂ�֐�
	dwCurrentTime =
		nCountFrame = 0;

	// ����������
	Init();

	// �J�[�\���\���n�e�e
	setcursortype(NOCURSOR);

	playsound(BGM4, 1);
	do
	{
		title();
		if (inport(PJ_BTNS) == 128 || inport(PK_ENTER))
		{
			g_ui.systemflag = 1;
		}

		if (inport(PK_ESC))
		{
			g_ui.systemflag = 2;
		}

	} while (g_ui.systemflag == 0);


	clrscr();
	// �Q�[�����C������
	stopsound(BGM4);

	if (g_ui.systemflag == 1)
	{
		do
		{
			tutorial();
			if (inport(PJ_BTNS) == 16 || inport(PK_O))
			{
				g_ui.buttonL = 1;
			}
			if (inport(PJ_BTNS) == 32 || inport(PK_K))
			{
				g_ui.buttonR = 1;
			}
			if (inport(PJ_BTNS) == 48)
			{
				g_ui.buttonR = 1;
				g_ui.buttonL = 1;
			}
		} while (!g_ui.buttonL == 1 || !g_ui.buttonR == 1);
	}
		clrscr();

		if (g_ui.systemflag == 1)
		{
			playsound(BGM3, 1);
			do
			{
				dwCurrentTime = timeGetTime();
				if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
				{
					g_nCountFPS = nCountFrame * 1000 / (dwCurrentTime - dwFPSLastTime);
					dwFPSLastTime = dwCurrentTime;
					nCountFrame = 0;
				}

				if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
				{
					dwExecLastTime = dwCurrentTime;




					// �X�V����
					Update();
					// �`�揈��
					Draw();

					nCountFrame++;

	#ifdef DEBUG
					// FPS�\��
					DispFPS();
	#endif
				}
			} while (!inport(PK_ESC) && g_ui.gameflag == 1);

			stopsound(BGM3);
			ending();
		}
		// �J�[�\���\���n�m
		setcursortype(NORMALCURSOR);

		// �I������
		Uninit();
	

		// ����\��߂�
		timeEndPeriod(1);
}


//=============================================================================
// ����������
//=============================================================================
void Init(void)
{
	// �v���C���[�̏���������
	InitPlayer();
	InitEnemy();
	InitBullet();
	InitBlock();
	InitWall();
	InitUI();
	InitMap();
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	// �v���C���[�̏I������
	UninitPlayer();
	UninitEnemy();
	UninitBlock();
	UninitWall();
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// �v���C���[�̍X�V����
	UpdatePlayer();
	Slow();
	UpdateEnemy();
	UpdateBullet();
	UpdateBlock();
	UpdateWall();
	collision();
	Wallcollision();
	mapcollision();
	UpdateUI();
	if (g_player.life == 0)
	{
		stopsound(BGM3);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �v���C���[�ȂǊe��`�揈��
	DrawPlayer();
	DrawEnemy();
	DrawBullet();
	DrawBlock();
	DrawWall();
	DrawMap();
	DrawUI();
}

void titleback(void)
{
	clrscr();
	gotoxy(40, 20);
	printf("�^�C�g���ɖ߂�܂�");
	msleep(3000);
	return;
}

#ifdef DEBUG
//=============================================================================
// FPS�\��
//=============================================================================
void DispFPS(void)
{
	// �F�ݒ�
	textcolor(LIGHTGREEN);

	/*gotoxy(1, 1);
	printf("X:%5d", inport(PJ_XPOS));

	gotoxy(10, 1);
	printf("Y:%5d", inport(PJ_YPOS));

	gotoxy(20, 1);
	printf("B:%5d", inport(PJ_BTNS));
*/
	gotoxy(1, 30);
	printf("FPS:%d", g_nCountFPS);
}
#endif
