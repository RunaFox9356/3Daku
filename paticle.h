#pragma once
#ifndef _PARTICLE_H_
#define _PARTICLE_H_


#include "main.h"

//�}�N����`
#define MAX_PARTICLE	(2048)		//�p�[�e�B�N���̍ő吔
#define NUM_PARTICLE	(24)		//�p�[�e�B�N���̎��
#define LIGHTNINGLIFE (120)
#define KITUNELIFE	 (150)
#define OUKANLIFE	 (70)
#define MERALIFE	(50)
//�񋓌^
typedef enum
{
	PARTICLETYPE_LIGHTNING = 0,		//�L���L��
	PARTICLETYPE_KITUNE,	//��
	PARTICLETYPE_OUKAN,		//����
	PARTICLETYPE_MERA,		//�ꖇ�G
	PARTICLETYPE_MAX
}PARTICLETYPE;

//�\����
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 move;			//�ړ���
	D3DXCOLOR col;				//�F
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	PARTICLETYPE type;			//�p�[�e�B�N���̎��
	float fWidth;				//��
	float fHeight;				//����
	float fRadius;				//���a
	float fAngle;				//�p�x
	float fLength;				//����
	float fAttenuation;			//����
	int nLife;					//������܂ł̎���
	int nMaxLife;				//�ő僉�C�t
	int nParticleNumber;		//�p�[�e�B�N���̔ԍ�
	int nCounterAnim;			//�A�j���[�V�����J�E���g
	int nPatternAnim;			//�����̃J�E���g
	int nDivisionMAX;				//���������邩�̃J�E���g
	int nDivisionY;				//Y���������邩�̃J�E���g
	int nDivisionX;				//X���������邩�̃J�E���g
	int speed;					//�A�j���[�V�����̑��x
	bool bUse;					//�g�p���Ă��邩�ǂ���
}PARTICLE;

//�v���g�^�C�v�錾
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fWidth, float fHeight, PARTICLETYPE type, int nLife);
void SubSetParticle(int nSubParticle, PARTICLETYPE type);
void DeleteParticle(int nParticle);
PARTICLE *GetParticle(void);

#endif