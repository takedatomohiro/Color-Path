#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{

	m_modelRender.Init("Assets/stage/start.tkm");
	m_modelRender.SetScale({ 20.0f,0.0f,20.0f });
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

BackGround::~BackGround()
{

}

//void BackGround::Update()
//{
//	
//}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
