#pragma once
class green : public IGameObject
{
	public:
		green();
		~green();
		/*void Update();*/
		void Render(RenderContext& rc);
		void SetPosition(const Vector3& pos);
private:
		ModelRender m_modelRender;
		PhysicsStaticObject m_physicsStaticObject;
		Vector3 m_position = { 0.0f,0.0f,0.0f };
		Vector3 firstPos;
};

