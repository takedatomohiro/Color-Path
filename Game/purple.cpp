#include "stdafx.h"
#include "purple.h"
#include "Player.h"

purple::purple()
{
	m_scale = { 7.5f,-10.0f,7.5f };
	//m_pos = { 75.0f,0.0f,-721.0f };
	m_modelRender.Init("Assets/stage/purple.tkm");
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	//m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_onFloor = false;
}

purple::~purple()
{

}

void purple::SetRandomDirection()
{
	//�����_���p�x
	float angle = (rand() % 360) * (3.14159f / 180.0f);

	//xz���ʂ̒P�ʃx�N�g�����v�Z
	m_moveDir = { cosf(angle), 0.0f, sinf(angle) };

	//�Œ葬�x
	m_moveDir *= 20.0f;
}

void purple::SetPosition(const Vector3& pos)
{
	m_position = pos;
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

void purple::Update()
{
	Player* player = FindGO<Player>("player");
	Vector3 playerPos = player->GetPosition();

	//���t���[�����̈ʒu������
	Matrix worldMatrix = m_modelRender.GetModel().GetWorldMatrix();
	Vector3 floorPos = { worldMatrix.m[3][0], worldMatrix.m[3][1], worldMatrix.m[3][2] };

	//����T�C�Y
	float halfSizex = fabs(m_scale.x) * 5.0f;//x�����̔��a
	float halfSizez = fabs(m_scale.z) * 5.0f;//z�����̔��a
	float floorY = floorPos.y;

	//�v���C���[�����̏�ɂ��邩�ǂ���
	bool OnFloorNow=
		(playerPos.x > floorPos.x - halfSizex && playerPos.x < floorPos.x + halfSizex &&
		playerPos.z > floorPos.z - halfSizez && playerPos.z < floorPos.z + halfSizez &&
			fabs(playerPos.y - floorY) < 5.0f);

	if (OnFloorNow)
	{
		if (!m_onFloor)
		{
			//������u�ԃ����_���ȕ����ɓ����o��
			SetRandomDirection();
			m_onFloor = true;
		}
		//������铮��
		playerPos += m_moveDir;
		player->SetPosition(playerPos);
	}
	else
	{
		//������~�肽��t���O���Z�b�g
		m_onFloor = false;
	}
}

void purple::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

