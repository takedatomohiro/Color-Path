#pragma once
class blue : public IGameObject
{
	public:
		blue();
		~blue();
		void Update();
		void Render(RenderContext& rc);

		void SetPosition(const Vector3& pos);
private:
		ModelRender m_modelRender;
		PhysicsStaticObject m_physicsStaticObject;
		Vector3 firstPos;
		Vector3 m_position = { 0.0f,0.0f,0.0f };
		Vector3 m_scale;
		bool m_wasOnFloor;// ëOÉtÉåÅ[ÉÄÇ≈è∞ÇÃè„Ç…Ç¢ÇΩÇ©Ç«Ç§Ç©
};

