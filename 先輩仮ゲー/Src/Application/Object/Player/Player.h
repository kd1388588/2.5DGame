#pragma once

class Player : public KdGameObject
{

public:
	// プレイヤーの状態を管理する列挙型
	enum class State
	{
		Idle,		// 操作無
		Hurt,		// 被弾
		Death,		// 死亡
		Run,		// 移動
		Dash,		// ダッシュ
		Jump,		// ジャンプ
		Fall,		// 落下
		Atk1,		// 通常攻撃
		Atk2,		// ダッシュ攻撃
	};

	Player() { Init(); }
	~Player() override {}

	void Init()			override;
	
	void Update()		override;
	void PostUpdate()	override;
	
	void DrawLit()	override;

private:

	// 位置
	Math::Vector3 m_pos;

	// 画像
	std::shared_ptr<KdSquarePolygon> m_PlayerPolygon; // 現在の画像

	// 状態
	State m_state = State::Idle;

	// アニメーション
	float m_anime = 0.0f;

	// 重力
	float m_gravity = 0;

	// ダッシュ入力
	bool m_dush = false;


};