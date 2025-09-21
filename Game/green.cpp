#include "stdafx.h"
#include "green.h"

green::green()
{
	m_modelRender.Init("Assets/stage/green.tkm");
	m_modelRender.SetScale({ 7.5f,-10.0f,7.5f });
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	//m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

green::~green()
{

}

void green::SetPosition(const Vector3& pos)
{
	m_position = pos;
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

void green::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
