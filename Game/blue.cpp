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
	if (player == nullptr) return; // プレイヤーが見つからない場合は処理を中断

	Vector3 playerPos = player->GetPosition();

	//毎フレーム床の位置を所得
	Matrix worldMatrix = m_modelRender.GetModel().GetWorldMatrix();
	Vector3 floorPos = { worldMatrix.m[3][0], worldMatrix.m[3][1], worldMatrix.m[3][2] };

	//モデルのスケールを使って範囲を計算
	float halfSizex = fabs(m_scale.x) * 5.0f;//x方向の半径
	float halfSizez = fabs(m_scale.z) * 5.0f;//z方向の半径
	float floorY = floorPos.y;

    // プレイヤーが床の上にいるか判定
    bool onFloorNow =
        (playerPos.x > floorPos.x - halfSizex && playerPos.x < floorPos.x + halfSizex &&
            playerPos.z > floorPos.z - halfSizez && playerPos.z < floorPos.z + halfSizez &&
            fabs(playerPos.y - floorY) < 5.0f);

    if (onFloorNow)
    {
        //前フレームは乗っていなかったら→今乗った瞬間
        if (!m_wasOnFloor)
        {
            //操作反転フラグをトグル切り替え  
			player->isControlReversed = !player->isControlReversed;
        }
		m_wasOnFloor = true;
    }
    else
    {
		m_wasOnFloor = false;//降りたらフラグ解除
    }

	
}

void blue::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}