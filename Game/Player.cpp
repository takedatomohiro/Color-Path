#include "stdafx.h"
#include "Player.h"
#include "GameClear.h"

Player::Player()
{
	animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimClip_Idle].SetLoopFlag(true);
	animationClips[enAnimClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimClip_Walk].SetLoopFlag(true);
	animationClips[enAnimClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimClip_Jump].SetLoopFlag(false);
	animationClips[enAnimClip_Run].Load("Assets/animData/run.tka");
	animationClips[enAnimClip_Run].SetLoopFlag(true);

	m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimClip_Num, enModelUpAxisY);
	characterController.Init(25.0f, 75.0f, m_position);
}

Player::~Player()
{

}

void Player::Update()
{
	moveSpeed.x = 0.0f;

	moveSpeed.y -= 0.5f;

	moveSpeed.z = 0.0f;



	m_modelRender.Update();

	Move();

	Rotation();

	ManageState();

	//ManageJumpState();

	PlayAnimation();

	const float fallLimit = -200.0f;  // �������肷�鍂��
	if (m_position.y < fallLimit) {
		// �X�^�[�g�n�_�ɖ߂�
		m_position = startPos;
		moveSpeed = { 0.0f, 0.0f, 0.0f }; // ���������Z�b�g
		characterController.SetPosition(m_position);
		m_modelRender.SetPosition(m_position);
	}
}

void Player::Rotation()
{
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���B
		m_rot.SetRotationYFromDirectionXZ(moveSpeed);
		//�G�`������ɉ�]��������B
		m_modelRender.SetRotation(m_rot);
	}
}


void Player::Move()
{
	//xz�̈ړ����x��0.0f�ɂ���
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ��擾
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	// ���]�t���O�������Ă���ꍇ�A���͂𔽓]
	if (isControlReversed) 
	{
		stickL.x *= -1.0f; // x���̓��͂𔽓]
		stickL.y *= -1.0f; // y���̓��͂𔽓]
	}

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//Y�����ɂ͈ړ����Ȃ�
	forward.y = 0.0f;
	right.y = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ�120.0f����Z
	right *= stickL.x * 10.0f;
	forward *= stickL.y * 10.0f;

	//�ړ����x�ɏ�L�Ōv�Z�����x�N�g���������Ă���
	moveSpeed += right + forward;

	//if (g_pad[0]->IsPress(enButtonB))
	//{
	//	moveSpeed.x *= 2;
	//	moveSpeed.z *= 2;//B�{�^����������Ă��鎞�̓v���C���[�X�e�[�g��3(����)�ɐݒ�
	//}

	//�L�����R���ňړ�
	m_position = characterController.Execute(moveSpeed, 1.0f / 60.0f);

	m_modelRender.SetPosition(m_position);

	if (characterController.IsOnGround() == true)
	{
		moveSpeed.y = 0.0f;
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			if (JumpCount < MaxJumpCount)
				moveSpeed.y = 10.0f;
	/*		JumpCount++;*/
			playerState = 1;
		}
	
		JumpCount = 0; // �n�ʂɂ��鎞�̓W�����v�񐔂����Z�b�g
	}



	m_position = characterController.Execute(moveSpeed, 1.0f);
	if (characterController.IsOnGround() == true)
	{
		playerState = 0;

	}

	m_modelRender.SetPosition(m_position);
}
void Player::ManageState()
{
	//�n�ʂɕt���Ă��Ȃ�������B
	if (characterController.IsOnGround() == false)
	{
		//�X�e�[�g��1(�W�����v��)�ɂ���B
		playerState = 1;
		//������ManageState�̏������I��点��B
		return;
	}

	//�n�ʂɕt���Ă�����B
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		//�X�e�[�g��2(����)�ɂ���B
		playerState = 2;

		if (g_pad[0]->IsPress(enButtonB))
		{
			playerState = 3; // �v���C���[�X�e�[�g��3(����)�ɐݒ�
		}
	}
	//x��z�̈ړ����x������������(�X�e�B�b�N�̓��͂�����������)�B
	else
	{
		//�X�e�[�g��0(�ҋ@)�ɂ���B
		playerState = 0;
	}
}

//void Player::ManageJumpState()
//{
//	if (g_pad[0]->IsTrigger(enButtonA))
//	{
//		if (JumpCount < MaxJumpCount)
//			moveSpeed.y = 10.0f;
//		JumpCount++;
//		playerState = 1;
//	}
//}

void Player::PlayAnimation()
{
	switch (playerState) {
		//�v���C���[�X�e�[�g��0(�ҋ@)��������B
	case 0:
		//�ҋ@�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimClip_Idle);
		break;
		//�v���C���[�X�e�[�g��1(�W�����v��)��������B
	case 1:
		//�W�����v�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimClip_Jump);
		break;
		//�v���C���[�X�e�[�g��2(����)��������B
	case 2:
		//�����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimClip_Walk);
		break;
	case 3:
		//����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimClip_Run);
		break;
	}
}

void Player::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}


