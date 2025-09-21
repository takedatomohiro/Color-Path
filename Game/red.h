#pragma once

class red : public IGameObject
{
	public:
		red();
		~red();
		void Update();
		void Render(RenderContext& rc);

		// �O����ʒu�E�X�P�[����ݒ�ł���悤�ɂ���
		void SetPosition(const Vector3& pos);
private:
		ModelRender m_modelRender;
		PhysicsStaticObject m_physicsStaticObject;
		Vector3 firstPos;
		Vector3 m_position = { 0.0f,0.0f,0.0f };
		Vector3 m_scale;
		float m_minX, m_maxX;
		float m_minZ, m_maxZ;
		float m_floorY;
};

