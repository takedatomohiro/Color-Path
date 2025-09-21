#pragma once
class purple : public IGameObject
{
	public:
		purple();
		~purple();
		void Update();
		void Render(RenderContext& rc);
		void SetPosition(const Vector3& pos);
private:
		ModelRender m_modelRender;
		PhysicsStaticObject m_physicsStaticObject;
		Vector3 m_scale;//���̃X�P�[��
		Vector3 m_position = { 0.0f,0.0f,0.0f };
		Vector3 m_moveDir;//���̈ړ������Ƒ��x
		bool m_onFloor; //�v���C���[�����̏�ɂ��邩�ǂ���

		void SetRandomDirection();//������u�ԂɃ����_��������ݒ�
};

