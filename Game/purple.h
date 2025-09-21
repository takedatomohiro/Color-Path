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
		Vector3 m_scale;//床のスケール
		Vector3 m_position = { 0.0f,0.0f,0.0f };
		Vector3 m_moveDir;//床の移動方向と速度
		bool m_onFloor; //プレイヤーが床の上にいるかどうか

		void SetRandomDirection();//乗った瞬間にランダム方向を設定
};

