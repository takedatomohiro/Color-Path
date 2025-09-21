#include "stdafx.h"
#include "blue.h"
#include "Player.h"

blue::blue()
{
	m_scale = { 7.5f,-10.0f,7.5f };
	m_modelRender.Init("Assets/stage/blue.tkm");
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	//m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_wasOnFloor = false;
}

blue::~blue()
{

}

void blue::SetPosition(const Vector3& pos)
{
	m_position = pos;
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

void blue::Update()
{
	Player* player = FindGO<Player>("player");
	if (player == nullptr) return; // �v���C���[��������Ȃ��ꍇ�͏����𒆒f

	Vector3 playerPos = player->GetPosition();

	//���t���[�����̈ʒu������
	Matrix worldMatrix = m_modelRender.GetModel().GetWorldMatrix();
	Vector3 floorPos = { worldMatrix.m[3][0], worldMatrix.m[3][1], worldMatrix.m[3][2] };

	//���f���̃X�P�[�����g���Ĕ͈͂��v�Z
	float halfSizex = fabs(m_scale.x) * 5.0f;//x�����̔��a
	float halfSizez = fabs(m_scale.z) * 5.0f;//z�����̔��a
	float floorY = floorPos.y;

    // �v���C���[�����̏�ɂ��邩����
    bool onFloorNow =
        (playerPos.x > floorPos.x - halfSizex && playerPos.x < floorPos.x + halfSizex &&
            playerPos.z > floorPos.z - halfSizez && playerPos.z < floorPos.z + halfSizez &&
            fabs(playerPos.y - floorY) < 5.0f);

    if (onFloorNow)
    {
        //�O�t���[���͏���Ă��Ȃ������灨��������u��
        if (!m_wasOnFloor)
        {
            //���씽�]�t���O���g�O���؂�ւ�  
			player->isControlReversed = !player->isControlReversed;
        }
		m_wasOnFloor = true;
    }
    else
    {
		m_wasOnFloor = false;//�~�肽��t���O����
    }

	
}

void blue::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}