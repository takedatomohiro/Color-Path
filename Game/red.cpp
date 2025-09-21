#include "stdafx.h"
#include "red.h"
#include "Player.h"

red::red()
{
	//m_position = { 150.0f,0.0f,-721.0f };
	m_scale = { 7.5f,-10.0f,7.5f };
	m_modelRender.Init("Assets/stage/red.tkm");
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	//m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

red::~red()
{

}

void red::SetPosition(const Vector3& pos)
{
	m_position = pos;
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

void red::Update()
{
	Player* player = FindGO<Player>("player");
	Vector3 playerPos = player->GetPosition();

	//毎フレーム床の位置を所得
	Matrix worldMatrix = m_modelRender.GetModel().GetWorldMatrix();
	Vector3 floorPos = { worldMatrix.m[3][0], worldMatrix.m[3][1], worldMatrix.m[3][2]};

	//モデルのスケールを使って範囲を計算
	float halfSizex = fabs(m_scale.x) * 5.0f;//x方向の半径
	float halfSizez = fabs(m_scale.z) * 10.0f;//z方向の半径

    // Zマイナス方向に奥行きを倍広げる
    float minX = floorPos.x - halfSizex;
    float maxX = floorPos.x + halfSizex;
    float minZ = floorPos.z - halfSizez * 2.0f; // ★奥行きだけ倍
    float maxZ = floorPos.z + halfSizez;        // ＋方向はそのまま
    float floorY = floorPos.y;

    // プレイヤーが範囲内に入ったら強制的に戻す
    if (playerPos.x > minX && playerPos.x < maxX &&
        playerPos.z > minZ && playerPos.z < maxZ &&
        playerPos.y <= floorY)
    {
        player->SetPosition(player->firstPos);
    }
}

void red::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
