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
	std::shared_ptr<KdSquarePolygon> m_IdlePoly;	// 操作無
	std::shared_ptr<KdSquarePolygon> m_HurtPoly;	// 被弾
	std::shared_ptr<KdSquarePolygon> m_DeathPoly;	// 死亡
	std::shared_ptr<KdSquarePolygon> m_RunPoly;		// 移動
	std::shared_ptr<KdSquarePolygon> m_DashPoly;	// ダッシュ
	std::shared_ptr<KdSquarePolygon> m_JumpPoly;	// ジャンプ
	std::shared_ptr<KdSquarePolygon> m_FallPoly;	// 落下
	std::shared_ptr<KdSquarePolygon> m_Atk1Poly;	// 通常攻撃
	std::shared_ptr<KdSquarePolygon> m_Atk2Poly;	// ダッシュ攻撃
	
	std::shared_ptr<KdSquarePolygon> m_pNowPolygon; // 現在の画像

	// 状態
	State m_state = State::Idle;

	// アニメーション
	int animeX[15] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	float m_anime = 0.0f;

	// 重力
	float m_gravity = 0;

	// ダッシュ入力
	bool m_dush = false;


};