#pragma once

class Player : public KdGameObject
{

public:

	Player() { Init(); }
	~Player() override {}

	void Init()			override;
	
	void Update()		override;
	void PostUpdate()	override;
	
	void DrawSprite()	override;

private:

	// 位置
	Math::Vector3 m_pos;

	// 画像
	std::shared_ptr<KdSquarePolygon> m_polygon;
	
	// アニメーション
	float m_anime = 0.0f;

	// 重力
	float m_gravity = 0;
};