//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : TAKASHI AKYAMA
//
//=============================================================================
#define CONIOEX
#include "conioex.h"
#include "main.h"
#include "player.h"
#include "bullet.h"
#include "wall.h"
#include "enemy.h"
#include "UI.h"
#include "map.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_MOVE_X			(0.5f)		// �n��ł̈ړ��ʂw����   �@���ł̈ړ��ʁ@�@�@//������0.75
#define VALUE_T_MOVE_X          (0.75f)
#define	VALUE_MOVE_Y			(0.25f)		// �n��ł̈ړ��ʂx����   �@���ł̈ړ��ʁ@�@�@//������0.75
#define	VALUE_RESIST_X			(0.50f)		// �n��ł̈ړ����C��R
#define	VALUE_RESIST_Y			(0.50f)		// �n��ł̈ړ����C��R

#define	LIMIT_LEFT1				(3.0f)		// �ړ��͈͍��[             |
#define	LIMIT_RIGHT1			(77.0f)	    // �ړ��͈͉E�[             |--  ��ʒ[�̐ݒ�    ������78
#define	LIMIT_DOWN1				(13.0f)		// �ړ��͈͉��[             |
#define	LIMIT_UP1				(8.0f)		// �ړ��͈͏�[             |

#define	LIMIT_LEFT2				(3.0f)		// �ړ��͈͍��[             |
#define	LIMIT_RIGHT2			(77.0f)	    // �ړ��͈͉E�[             |--  ��ʒ[�̐ݒ�    ������78
#define	LIMIT_DOWN2 			(22.0f)		// �ړ��͈͉��[             |
#define	LIMIT_UP2				(3.0f)		// �ړ��͈͏�[             |

#define	LIMIT_LEFT3				(3.0f)		// �ړ��͈͍��[             |
#define	LIMIT_RIGHT3			(77.0f)	    // �ړ��͈͉E�[             |--  ��ʒ[�̐ݒ�    ������78
#define	LIMIT_DOWN3				(22.0f)		// �ړ��͈͉��[             |
#define	LIMIT_UP3				(3.0f)		// �ړ��͈͏�[             |

#define	LIMIT_LEFT4				(3.0f)		// �ړ��͈͍��[             |
#define	LIMIT_RIGHT4			(47.0f)	    // �ړ��͈͉E�[             |--  ��ʒ[�̐ݒ�    ������78
#define	LIMIT_DOWN4				(14.0f)		// �ړ��͈͉��[             |
#define	LIMIT_UP4				(3.0f)		// �ړ��͈͏�[             |

#define	LIMIT_LEFT5				(3.0f)		// �ړ��͈͍��[             |
#define	LIMIT_RIGHT5			(47.0f)	    // �ړ��͈͉E�[             |--  ��ʒ[�̐ݒ�    ������78
#define	LIMIT_DOWN5				(14.0f)		// �ړ��͈͉��[             |
#define	LIMIT_UP5				(3.0f)		// �ړ��͈͏�[             |




//()���̐��l��������Ό��E�̐��l���ς�� �E�B���h�E�̃T�C�Y����ŕύX����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PLAYER g_player;						// �v���C���[���[�N
extern WALL g_wall;
extern BULLET g_Bullet;
extern UI g_ui;
extern ENEMY g_enemy[10];
extern MAP g_map;

int slowBGM;


//=============================================================================
// �v���C���[�̏���������
//=============================================================================
void InitPlayer(void)
{
	slowBGM = opensound("BGM/magic-charge1.mp3");
	setvolume(slowBGM, 40);

	// �v���C���[���[�N�̃N���A
	g_player.fPosX = 3.0f;       //�v���C���[�̏����ʒu
	g_player.fPosY = 4.0f;
	g_player.fPosXOLD = 0.0f;
	g_player.fPosYOLD = 0.0f;
	g_player.fMoveX = 0.0f;
	g_player.fMoveY = 0.0f;
	g_player.bShot = false;
	g_player.bMove = false;
	g_player.color = 0;
	g_player.life = 1;
	g_player.slow = 0;
	g_player.slowflag = 1;
	g_player.slowtime = 1;
	g_player.slowcooldown = 0;
	g_player.slowcooldownflag = 0;
}

//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void UninitPlayer(void)
{
}

//=============================================================================
// �v���C���[�̍X�V����
//=============================================================================
void UpdatePlayer(void)
{
	if (g_player.life == 1)
	{
		g_player.fPosXOLD = g_player.fPosX;
		g_player.fPosYOLD = g_player.fPosY;


		// ���ړ�
		if (inport(PJ_XPOS) == 0 || inport(PK_A))
		{
			// �������l����
			g_player.fMoveX -= VALUE_MOVE_X;
			g_player.bMove = true;
		}

		// �E�ړ�
		if (inport(PJ_XPOS) == 65535 || inport(PK_D))
		{
			// �������l����
			g_player.fMoveX += VALUE_MOVE_X;
			g_player.bMove = true;
		}

		// ��ړ�
		if (inport(PJ_YPOS) == 0 || inport(PK_W))
		{
			// �������l����
			g_player.fMoveY -= VALUE_MOVE_Y;
			g_player.bMove = true;
		}

		// ���ړ�
		if (inport(PJ_YPOS) == 65535 || inport(PK_S))
		{
			// �������l����
			g_player.fMoveY += VALUE_MOVE_Y;
			g_player.bMove = true;
		}

		
		if (inport(PJ_BTNS) == 1 && g_Bullet.bulletcount > 0 || inport(PK_SP) && g_Bullet.bulletcount > 0)
		{// �U��
			if (!g_player.bShot)    //�e�����˂���ĂȂ�������Ƃ����Ӗ�
			{
				g_Bullet.bulletcount--;
				if (g_player.fPosX >= 3.0f && g_player.fPosX <= 77.0f)     //�v���C���[����ʓ�(�͈͓�)�ł̂ݔ���
				{

					if (g_ui.flag == 1)
					{
						// �e�̐ݒ�
						SetBullet(g_player.fPosX - 2.0f + g_player.fMoveX, g_player.fPosY, 1.0f, 0.0f, BULLETTYPE_PLAYER);   //���ˈʒu(�e�̔����ʒu)
						//                                                            x���� y����      ���e�̔��˂̍\����
						g_player.bShot = true;     //�e�������Ă邩�ǂ����̔���
					
					}
					if (g_ui.flag == 2)
					{
						// �e�̐ݒ�
						SetBullet(g_player.fPosX + 2.0f + g_player.fMoveX, g_player.fPosY, 1.0f, 0.0f, BULLETTYPE_PLAYER);   //���ˈʒu(�e�̔����ʒu)
						//                                                            x���� y����      ���e�̔��˂̍\����
						g_player.bShot = true;     //�e�������Ă邩�ǂ����̔���
				
					}
					if (g_ui.flag == 3)
					{
						// �e�̐ݒ�
						SetBullet(g_player.fPosX, g_player.fPosY + g_player.fMoveY + 1.0f, 0.0f, 1.0f, BULLETTYPE_PLAYER);   //���ˈʒu(�e�̔����ʒu)
						//                                                            x���� y����      ���e�̔��˂̍\����
						g_player.bShot = true;     //�e�������Ă邩�ǂ����̔���
					
					}
					if (g_ui.flag == 4)
					{
						// �e�̐ݒ�
						SetBullet(g_player.fPosX, g_player.fPosY + g_player.fMoveY - 1.0f, 0.0f, 1.0f, BULLETTYPE_PLAYER);   //���ˈʒu(�e�̔����ʒu)
						//                                                            x���� y����      ���e�̔��˂̍\����
						g_player.bShot = true;     //�e�������Ă邩�ǂ����̔���
					
					}
				}
				
			}
		}
		else
		{
			if (g_player.bShot)
			{       // �V���b�g��
				g_player.bShot = false;
			}
		}


		// ��R��������
		g_player.fMoveX += (0.0f - g_player.fMoveX) * VALUE_RESIST_X;  //�t�����ɗ͂������Ă���
		g_player.fMoveY += (0.0f - g_player.fMoveY) * VALUE_RESIST_Y;


		// �ʒu�X�V

		g_player.fPosX += g_player.fMoveX;
		g_player.fPosY += g_player.fMoveY;

		if (g_map.mapcount == 1)
		{
			// ��ʒ[�̏���
			if (g_player.fPosX < LIMIT_LEFT1)
			{
				g_player.fPosX = LIMIT_LEFT1;       //��ʂ̌��E��LIMIT_LEFT�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosY > LIMIT_DOWN1)
			{
				g_player.fPosY = LIMIT_DOWN1;       //��ʂ̌��E��LIMIT_DOWN�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosX > LIMIT_RIGHT1)
			{
				g_player.fPosX = LIMIT_RIGHT1;      //��ʂ̌��E��LIMIT_RIGHT�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosY < LIMIT_UP1)
			{

				g_player.fPosY = LIMIT_UP1;         //��ʂ̌��E��LIMIT_UP�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
		}

		if (g_map.mapcount == 2)
		{

			if (g_player.fPosX < LIMIT_LEFT2)
			{
				g_player.fPosX = LIMIT_LEFT2;       //��ʂ̌��E��LIMIT_LEFT�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosY > LIMIT_DOWN2)
			{
				g_player.fPosY = LIMIT_DOWN2;       //��ʂ̌��E��LIMIT_DOWN�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosX > LIMIT_RIGHT2)
			{
				g_player.fPosX = LIMIT_RIGHT2;      //��ʂ̌��E��LIMIT_RIGHT�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosY < LIMIT_UP2)
			{
				g_player.fPosY = LIMIT_UP2;         //��ʂ̌��E��LIMIT_UP�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
		}

		if (g_map.mapcount == 3)
		{
			if (g_player.fPosX < LIMIT_LEFT3)
			{
				g_player.fPosX = LIMIT_LEFT3;       //��ʂ̌��E��LIMIT_LEFT�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosY > LIMIT_DOWN3)
			{
				g_player.fPosY = LIMIT_DOWN3;       //��ʂ̌��E��LIMIT_DOWN�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosX > LIMIT_RIGHT3)
			{
				g_player.fPosX = LIMIT_RIGHT3;      //��ʂ̌��E��LIMIT_RIGHT�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosY < LIMIT_UP3)
			{
				g_player.fPosY = LIMIT_UP3;         //��ʂ̌��E��LIMIT_UP�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
		}

		if (g_map.mapcount == 4)
		{
			if (g_player.fPosX < LIMIT_LEFT4)
			{
				g_player.fPosX = LIMIT_LEFT4;       //��ʂ̌��E��LIMIT_LEFT�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosY > LIMIT_DOWN4)
			{
				g_player.fPosY = LIMIT_DOWN4;       //��ʂ̌��E��LIMIT_DOWN�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosX > LIMIT_RIGHT4)
			{
				g_player.fPosX = LIMIT_RIGHT4;      //��ʂ̌��E��LIMIT_RIGHT�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosY < LIMIT_UP4)
			{
				g_player.fPosY = LIMIT_UP4;         //��ʂ̌��E��LIMIT_UP�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
		}

		if (g_map.mapcount == 5)
		{
			if (g_player.fPosX < LIMIT_LEFT5)
			{
				g_player.fPosX = LIMIT_LEFT5;       //��ʂ̌��E��LIMIT_LEFT�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosY > LIMIT_DOWN5)
			{
				g_player.fPosY = LIMIT_DOWN5;       //��ʂ̌��E��LIMIT_DOWN�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosX > LIMIT_RIGHT5)
			{
				g_player.fPosX = LIMIT_RIGHT5;      //��ʂ̌��E��LIMIT_RIGHT�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
			if (g_player.fPosY < LIMIT_UP5)
			{
				g_player.fPosY = LIMIT_UP5;         //��ʂ̌��E��LIMIT_UP�Ȃ̂ňړ��������l�����E�̐��l�ɂ��Ĉړ����ĂȂ��悤�Ɍ�����
			}
		}

		if (g_enemy[0].life == 1 && g_enemy[0].flag == 0 && g_map.mapcount == 2)
		{
			if ((int)g_player.fPosX > g_enemy[0].fEeyePosX[0] - 2.0f && (int)g_player.fPosX < g_enemy[0].fEeyePosX[0] + 2.0f && (int)g_player.fPosY >= g_enemy[0].fEeyePosY[0] && (int)g_player.fPosY <= g_enemy[0].fEeyePosY[0] + 1.0f)
			{
				g_player.life = 0;
			}
			
			if ((int)g_player.fPosX > g_enemy[0].fEeyePosX[2] - 2.0f && (int)g_player.fPosX < g_enemy[0].fEeyePosX[2] + 2.0f && (int)g_player.fPosY >= g_enemy[0].fEeyePosY[2] && (int)g_player.fPosY <= g_enemy[0].fEeyePosY[2] + 1.0f)
			{
				g_player.life = 0;
			}
			
			if ((int)g_player.fPosX >= g_enemy[0].fEeyePosX[6] - 4.0f && (int)g_player.fPosX <= g_enemy[0].fEeyePosX[6] + 4.0f && (int)g_player.fPosY >= g_enemy[0].fEeyePosY[6] && (int)g_player.fPosY <= g_enemy[0].fEeyePosY[6] + 1.0f)
			{
				g_player.life = 0;
			}
			
		}
		if (g_enemy[0].life == 1 && g_enemy[0].flag == 1 && g_map.mapcount == 2)
		{
			if ((int)g_player.fPosX > g_enemy[0].fEeyePosX[0] - 1.0f && (int)g_player.fPosX < g_enemy[0].fEeyePosX[0] + 1.0f && (int)g_player.fPosY <= g_enemy[0].fEeyePosY[0] && (int)g_player.fPosY >= g_enemy[0].fEeyePosY[0] - 2.0f)
			{
				g_player.life = 0;
			}
			
			if ((int)g_player.fPosX > g_enemy[0].fEeyePosX[2] - 2.0f && (int)g_player.fPosX < g_enemy[0].fEeyePosX[2] + 2.0f && (int)g_player.fPosY <= g_enemy[0].fEeyePosY[2] && (int)g_player.fPosY >= g_enemy[0].fEeyePosY[2] - 2.0f)
			{
				g_player.life = 0;
			}
			
			if ((int)g_player.fPosX > g_enemy[0].fEeyePosX[6] - 4.0f && (int)g_player.fPosX < g_enemy[0].fEeyePosX[6] + 4.0f && (int)g_player.fPosY <= g_enemy[0].fEeyePosY[6] && (int)g_player.fPosY >= g_enemy[0].fEeyePosY[6] - 2.0f)
			{
				g_player.life = 0;
			}
			
		}

		if (g_enemy[1].life == 1 && g_enemy[1].flag == 0 && g_map.mapcount == 2)
		{
			if ((int)g_player.fPosX > g_enemy[1].fEeyePosX[0] - 2.0f && (int)g_player.fPosX < g_enemy[1].fEeyePosX[0] + 2.0f && (int)g_player.fPosY >= g_enemy[1].fEeyePosY[0] && (int)g_player.fPosY <= g_enemy[1].fEeyePosY[0] + 1.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[1].fEeyePosX[2] - 2.0f && (int)g_player.fPosX < g_enemy[1].fEeyePosX[2] + 2.0f && (int)g_player.fPosY >= g_enemy[1].fEeyePosY[2] && (int)g_player.fPosY <= g_enemy[1].fEeyePosY[2] + 1.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX >= g_enemy[1].fEeyePosX[6] - 4.0f && (int)g_player.fPosX <= g_enemy[1].fEeyePosX[6] + 4.0f && (int)g_player.fPosY >= g_enemy[1].fEeyePosY[6] && (int)g_player.fPosY <= g_enemy[1].fEeyePosY[6] + 1.0f)
			{
				g_player.life = 0;
			}

		}
		if (g_enemy[1].life == 1 && g_enemy[1].flag == 1 && g_map.mapcount == 2)
		{
			if ((int)g_player.fPosX > g_enemy[1].fEeyePosX[0] - 1.0f && (int)g_player.fPosX < g_enemy[1].fEeyePosX[0] + 1.0f && (int)g_player.fPosY <= g_enemy[1].fEeyePosY[0] && (int)g_player.fPosY >= g_enemy[1].fEeyePosY[0] - 2.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[1].fEeyePosX[2] - 2.0f && (int)g_player.fPosX < g_enemy[1].fEeyePosX[2] + 2.0f && (int)g_player.fPosY <= g_enemy[1].fEeyePosY[2] && (int)g_player.fPosY >= g_enemy[1].fEeyePosY[2] - 2.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[1].fEeyePosX[6] - 4.0f && (int)g_player.fPosX < g_enemy[1].fEeyePosX[6] + 4.0f && (int)g_player.fPosY <= g_enemy[1].fEeyePosY[6] && (int)g_player.fPosY >= g_enemy[1].fEeyePosY[6] - 2.0f)
			{
				g_player.life = 0;
			}

		}
		if (g_enemy[3].life == 1 && g_enemy[3].flag == 0 && g_map.mapcount == 2)
		{
			if ((int)g_player.fPosX > g_enemy[3].fEeyePosX[0] - 2.0f && (int)g_player.fPosX < g_enemy[3].fEeyePosX[0] + 2.0f && (int)g_player.fPosY >= g_enemy[3].fEeyePosY[0] && (int)g_player.fPosY <= g_enemy[3].fEeyePosY[0] + 1.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[3].fEeyePosX[2] - 2.0f && (int)g_player.fPosX < g_enemy[3].fEeyePosX[2] + 2.0f && (int)g_player.fPosY >= g_enemy[3].fEeyePosY[2] && (int)g_player.fPosY <= g_enemy[3].fEeyePosY[2] + 1.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX >= g_enemy[3].fEeyePosX[6] - 4.0f && (int)g_player.fPosX <= g_enemy[3].fEeyePosX[6] + 4.0f && (int)g_player.fPosY >= g_enemy[3].fEeyePosY[6] && (int)g_player.fPosY <= g_enemy[3].fEeyePosY[6] + 1.0f)
			{
				g_player.life = 0;
			}

		}
		if (g_enemy[3].life == 1 && g_enemy[3].flag == 1 && g_map.mapcount == 2)
		{
			if ((int)g_player.fPosX > g_enemy[3].fEeyePosX[0] - 1.0f && (int)g_player.fPosX < g_enemy[3].fEeyePosX[0] + 1.0f && (int)g_player.fPosY <= g_enemy[3].fEeyePosY[0] && (int)g_player.fPosY >= g_enemy[3].fEeyePosY[0] - 2.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[3].fEeyePosX[2] - 2.0f && (int)g_player.fPosX < g_enemy[3].fEeyePosX[2] + 2.0f && (int)g_player.fPosY <= g_enemy[3].fEeyePosY[2] && (int)g_player.fPosY >= g_enemy[3].fEeyePosY[2] - 2.0f)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[3].fEeyePosX[6] - 4.0f && (int)g_player.fPosX < g_enemy[3].fEeyePosX[6] + 4.0f && (int)g_player.fPosY <= g_enemy[3].fEeyePosY[6] && (int)g_player.fPosY >= g_enemy[3].fEeyePosY[6] - 2.0f)
			{
				g_player.life = 0;
			}

		}
		if (g_enemy[4].life == 1 && g_enemy[4].flag == 0 && g_map.mapcount == 3)
		{
			if ((int)g_player.fPosX > g_enemy[4].fEeyePosX[0] - 1.0f && (int)g_player.fPosX < g_enemy[4].fEeyePosX[0] + 1.0f && (int)g_player.fPosY >= g_enemy[4].fEeyePosY[0] && (int)g_player.fPosY <= g_enemy[4].fEeyePosY[0])
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[4].fEeyePosX[2] - 2.0f && (int)g_player.fPosX < g_enemy[4].fEeyePosX[2] - 1.0f && (int)g_player.fPosY >= g_enemy[4].fEeyePosY[2] - 1 && (int)g_player.fPosY <= g_enemy[4].fEeyePosY[2] + 1)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX >= g_enemy[4].fEeyePosX[6] - 3.0f && (int)g_player.fPosX <= g_enemy[4].fEeyePosX[6] - 2.0f && (int)g_player.fPosY >= g_enemy[4].fEeyePosY[6] - 2 && (int)g_player.fPosY <= g_enemy[4].fEeyePosY[6] + 2)
			{
				g_player.life = 0;
			}

		}

		if (g_enemy[4].life == 1 && g_enemy[4].flag == 1 && g_map.mapcount == 3)
		{
			if ((int)g_player.fPosX > g_enemy[4].fEeyePosX[0] + 1.0f && (int)g_player.fPosX < g_enemy[4].fEeyePosX[0] + 2.0f && (int)g_player.fPosY >= g_enemy[4].fEeyePosY[0] && (int)g_player.fPosY <= g_enemy[4].fEeyePosY[0] )
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[4].fEeyePosX[2] + 1.0f && (int)g_player.fPosX < g_enemy[4].fEeyePosX[2] + 2.0f && (int)g_player.fPosY >= g_enemy[4].fEeyePosY[2] - 1 && (int)g_player.fPosY <= g_enemy[4].fEeyePosY[2] + 1)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[4].fEeyePosX[6] + 1.0f && (int)g_player.fPosX < g_enemy[4].fEeyePosX[6] + 2.0f && (int)g_player.fPosY >= g_enemy[4].fEeyePosY[6] - 2 && (int)g_player.fPosY <= g_enemy[4].fEeyePosY[6] + 2)
			{
				g_player.life = 0;
			}

		}

		if (g_enemy[5].life == 1 && g_enemy[5].flag == 1 && g_map.mapcount == 5)
		{
			if ((int)g_player.fPosX > g_enemy[5].fEeyePosX[0] + 1.0f && (int)g_player.fPosX < g_enemy[5].fEeyePosX[0] + 2.0f && (int)g_player.fPosY >= g_enemy[5].fEeyePosY[0] && (int)g_player.fPosY <= g_enemy[5].fEeyePosY[0])
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[5].fEeyePosX[2] + 1.0f && (int)g_player.fPosX < g_enemy[5].fEeyePosX[2] + 2.0f && (int)g_player.fPosY >= g_enemy[5].fEeyePosY[2] - 1 && (int)g_player.fPosY <= g_enemy[5].fEeyePosY[2] + 1)
			{
				g_player.life = 0;
			}

			if ((int)g_player.fPosX > g_enemy[5].fEeyePosX[6] + 1.0f && (int)g_player.fPosX < g_enemy[5].fEeyePosX[6] + 2.0f && (int)g_player.fPosY >= g_enemy[5].fEeyePosY[6] - 2 && (int)g_player.fPosY <= g_enemy[5].fEeyePosY[6] + 2)
			{
				g_player.life = 0;
			}

		}


		if (g_enemy[0].cameralife >= 1)
		{
			if (g_map.mapcount == 2)
			{
				if ((int)g_player.fPosX > g_enemy[0].fEcameraPosX && (int)g_player.fPosX < g_enemy[0].fEcameraPosX + 18 && (int)g_player.fPosY < g_enemy[0].fEcameraPosY + 2 && (int)g_player.fPosY > g_enemy[0].fEcameraPosY - 2)
				{
					g_player.life = 0;
				}
			}

			if (g_map.mapcount == 3)
			{
				if ((int)g_player.fPosX > 40 && (int)g_player.fPosX < 48 && (int)g_player.fPosY < 15 && (int)g_player.fPosY > 8)
				{
					g_player.life = 0;
				}
			}

			if (g_map.mapcount == 5)
			{
				if ((int)g_player.fPosX > 19 && (int)g_player.fPosX < 27 && (int)g_player.fPosY < 12 && (int)g_player.fPosY > 2)
				{
					g_player.life = 0;
				}
			}

			if (g_map.mapcount == 4)
			{
				if ((int)g_player.fPosX > 19 && (int)g_player.fPosX < 27 && (int)g_player.fPosY < 12 && (int)g_player.fPosY > 2)
				{
					g_player.life = 0;
				}
			}
		}

		if (g_enemy[2].life == 1 && g_map.mapcount == 1)
		{
			if ((int)g_player.fPosX > g_enemy[2].fEPosX + 1.0f && (int)g_player.fPosX < g_enemy[2].fEPosX + 7.0f && (int)g_player.fPosY >= g_enemy[2].fEPosY - 2.0f && (int)g_player.fPosY <= g_enemy[2].fEPosY + 2.0f)
			{
				g_player.life = 0;
			}
		}
	}
}

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void DrawPlayer(void)
{	// ���݂̈ʒu
	if (g_player.life == 1 && g_ui.gameflag == 1)
	{
		textbackground(0);
		textcolor(0000);
		gotoxy((int)(g_player.fPosXOLD), (int)(g_player.fPosYOLD - 1.0f));      //��ɏ���
		printf("  ");
		gotoxy((int)(g_player.fPosXOLD), (int)(g_player.fPosYOLD));
		printf("  ");

		
			if (g_player.color == 0)
			{
				textcolor(1111);
				gotoxy((int)(g_player.fPosX), (int)(g_player.fPosY - 1.0f));
				printf("��");
				gotoxy((int)(g_player.fPosX), (int)(g_player.fPosY));
				printf("��");
			}
			if (g_player.color == 1)
			{
				textcolor(CYAN);
				gotoxy((int)(g_player.fPosX), (int)(g_player.fPosY - 1.0f));
				printf("��");
				gotoxy((int)(g_player.fPosX), (int)(g_player.fPosY));
				printf("��");
			}
	}
	
}

void Slow(void)
{
	if (inport(PJ_BTNS) == 8 && g_player.slowflag == 1 || inport(PK_G) && g_player.slowflag == 1)
	{
		playsound(slowBGM, 0);
		g_player.slow = 1;
		g_player.slowflag = 0;
	}

	if (g_player.slow == 1)
	{
		g_player.slowtime++;
	}

	if (g_player.slowtime % 180 == 0)
	{
		g_player.slow = 0;
		g_player.slowtime = 1;
		g_player.slowcooldownflag = 1;

	}
	if (g_player.slowcooldownflag == 1)
	{
		g_player.slowcooldown++;
		
	}
	if (g_player.slowcooldown % 600 == 0)
	{
		g_player.slowcooldown = 1;
		g_player.slowcooldownflag = 0;
		g_player.slowflag = 1;
	}
}
