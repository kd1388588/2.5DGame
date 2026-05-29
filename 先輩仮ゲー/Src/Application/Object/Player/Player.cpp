#include "Player.h"

void Player::Init()
{
	// 1.ポインタのままだと使えないので実体化
	m_PlayerPolygon = std::make_shared<KdSquarePolygon>();

	// 2.Texture設定
	m_PlayerPolygon->SetMaterial("Asset/Textures/Object/Player/Sword.png");

	m_pos = { 0,0,0 };

	// 画像分割 (横14, 縦8)
	m_PlayerPolygon->SetSplit(14, 8);

	// プレイヤーの原点変更
	m_PlayerPolygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_mWorld = Math::Matrix::Identity;
}

void Player::Update()
{
	// ------------------------------------------------------------
	// 移動と状態の更新
	// ------------------------------------------------------------

	// 攻撃中でなければ、とりあえず一旦 Idle 状態にする
	if (m_state != State::Atk1 && m_state != State::Atk2)
	{
		m_state = State::Idle;
	}

	// ダッシュ入力
	if(GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		m_dush = true;
	}

	// 攻撃中でない時だけ移動を許可
	if (m_state != State::Atk1 && m_state != State::Atk2)
	{
		float moveSpd = m_dush ? 0.02f : 0.01f;
		State moveState = m_dush ? State::Dash : State::Run;
		bool isMoved = false;

		if (GetAsyncKeyState('W') & 0x8000) { m_pos.z += moveSpd; isMoved = true; }
		if (GetAsyncKeyState('S') & 0x8000) { m_pos.z -= moveSpd; isMoved = true; }
		if (GetAsyncKeyState('A') & 0x8000) { m_pos.x -= moveSpd; isMoved = true; }
		if (GetAsyncKeyState('D') & 0x8000) { m_pos.x += moveSpd; isMoved = true; }

		// 移動キーが押されていたら状態を更新
		if (isMoved)
		{
			m_state = moveState;
		}
	}

	// ------------------------------------------------------------
	// 攻撃入力
	// ------------------------------------------------------------
	if (m_state != State::Atk1 && m_state != State::Atk2)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			// ダッシュ中ならAtk1、通常時はAtk2（元のコードの仕様）
			m_state = m_dush ? State::Atk1 : State::Atk2;
			m_anime = 0.0f; // アニメーションを0から再生
		}
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_state = State::Hurt;
		m_anime = 0.0f;
	}

	// ------------------------------------------------------------
	// アニメーション処理
	// ------------------------------------------------------------
	int currentFrameNumber = 0; // 今回表示するコマ番号を格納する変数
	m_anime += 0.2f;            // アニメーションの進行

	if (m_state == State::Idle)
	{
		int animeX[] = { 0, 1, 2, 3, 4, 5, 6 };
		if (m_anime >= 7.0f) { m_anime = 0.0f; } // 7コマでループ
		currentFrameNumber = animeX[(int)m_anime];
	}

	else if (m_state == State::Run)
	{
		int animeX[] = { 14, 15, 16, 17, 18, 19, 20 };
		if (m_anime >= 4.0f) { m_anime = 0.0f; } // 7コマでループ
		currentFrameNumber = animeX[(int)m_anime];
	}

	else if (m_state == State::Dash)
	{
		int animeX[] = { 70,71,72,73 };
		if (m_anime >= 4.0f) { m_anime = 0.0f;m_dush = false; }
		currentFrameNumber = animeX[(int)m_anime];
		
	}
	
	else if (m_state == State::Atk2)
	{
		int animeX[] = { 74, 75, 76 };
		if (m_anime >= 3.0f)
		{
			m_state = State::Idle;
			m_anime = 0.0f;
		}

		int idx = (int)m_anime;
		currentFrameNumber = animeX[idx];
	}

	else if (m_state == State::Atk1)
	{
		int animeX[] = { 56 ,57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67 }; // 7コマ
		if (m_anime >= 12.0f)
		{
			m_state = State::Idle; // 再生完了でIdleに戻る
			m_anime = 0.0f;
		}

		// Idleに戻る瞬間に配列外アクセスしないための安全対策
		int idx = (int)m_anime;
		currentFrameNumber = animeX[idx];
	}

	else if (m_state == State::Hurt)
	{
		int animeX[] = { 78,79 };
		if (m_anime >= 0.4f)
		{
			m_state = State::Idle;
			m_anime = 0.0f;
		}

		int idx = (int)m_anime;
		currentFrameNumber = animeX[idx];
	}

	// 決定したコマ番号をポリゴンにセット
	m_PlayerPolygon->SetUVRect(currentFrameNumber);

	// ------------------------------------------------------------
	// 行列の更新
	// ------------------------------------------------------------

	// 拡縮行列
	Math::Matrix m_scale = Math::Matrix::CreateScale(0.5f, 0.5f, 1.0f);

	// 移動行列
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	// 行列合成
	m_mWorld = m_scale * transMat;
}

void Player::PostUpdate()
{
}

void Player::DrawLit()
{
	if (!m_PlayerPolygon) return;

	KdShaderManager::Instance().
		m_StandardShader.DrawPolygon(*m_PlayerPolygon, m_mWorld);
}