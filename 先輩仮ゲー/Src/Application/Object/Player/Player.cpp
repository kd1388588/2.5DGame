#include "Player.h"

void Player::Init()
{
	m_IdlePoly = std::make_shared<KdSquarePolygon>();
	m_IdlePoly->SetMaterial("Asset/Textures/Object/Player/Idle.png");

	m_Atk1Poly = std::make_shared<KdSquarePolygon>();
	m_Atk1Poly->SetMaterial("Asset/Textures/Object/Player/Atk1.png");

	m_Atk2Poly = std::make_shared<KdSquarePolygon>();
	m_Atk2Poly->SetMaterial("Asset/Textures/Object/Player/Atk2.png");
	
	m_RunPoly = std::make_shared<KdSquarePolygon>();
	m_RunPoly->SetMaterial("Asset/Textures/Object/Player/Run.png");
	
	m_DashPoly = std::make_shared<KdSquarePolygon>();
	m_DashPoly->SetMaterial("Asset/Textures/Object/Player/Dash.png");

	m_pos = { 0,-1,0 };

	m_IdlePoly->SetSplit(7, 1);
	m_IdlePoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_Atk1Poly->SetSplit(10, 1);
	m_Atk1Poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	
	m_Atk2Poly->SetSplit(15, 1);
	m_Atk2Poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	
	//m_IdlePoly->SetSplit(7, 1);
	//m_IdlePoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);


	m_pNowPolygon = m_IdlePoly;
}

void Player::Update()
{

	// ダッシュ入力
	if(GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		m_dush = true;
	}
	else
	{
		m_dush = false;
	}

	// ダッシュ状態
	if (m_dush == true)
	{
		if (GetAsyncKeyState('W') & 0x8000)
		{
			m_pos.z += 0.01f;
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			m_pos.z -= 0.01f;
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			m_pos.x -= 0.01f;
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			m_pos.x += 0.01f;
		}
	}

	// ダッシュしていない場合
	else
	{
		if (GetAsyncKeyState('W') & 0x8000)
		{
			m_pos.z += 0.01f;
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			m_pos.z -= 0.01f;
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			m_pos.x -= 0.01f;
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			m_pos.x += 0.01f;
		}
	}

	// 攻撃入力
	if (m_state == State::Idle)
	{
		// ダッシュしている場合
		if (m_dush == true)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				m_state = State::Atk1;           // 状態を攻撃に変更
				m_pNowPolygon = m_Atk1Poly;      // 使う画像を攻撃用に切り替え
				m_anime = 0.0f;                    // アニメーションを0コマ目から再生
			}
		}

		// ダッシュしていない場合
		else 
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
			m_state = State::Atk2;           // 状態を攻撃に変更
			m_pNowPolygon = m_Atk2Poly;      // 使う画像を攻撃用に切り替え
			m_anime = 0.0f;                    // アニメーションを0コマ目から再生
			}
		}
	}


	// アニメーション処理
	{
		if (m_state == State::Idle)
		{
			animeX[7];
			m_anime += 0.2f; // アニメーションの再生速度

			// Idle状態：7コマでループ
			if (m_anime >= 7.0f)
			{
				m_anime = 0.0f;
			}
		}
		else if (m_state == State::Atk2)
		{
			animeX[15];
			m_anime += 0.2f; // アニメーションの再生速度

			// Attack状態：10コマ再生し終わったらIdleに戻る
			if (m_anime >= 15.0f)
			{
				m_state = State::Idle;         // 状態を待機に戻す
				m_pNowPolygon = m_IdlePoly;    // 画像を待機用に切り替え
				m_anime = 0.0f;                // アニメーションをリセット
			}
		}
		else if (m_state == State::Atk1)
		{
			animeX[10];
			m_anime += 0.2f; // アニメーションの再生速度

			// Attack状態：10コマ再生し終わったらIdleに戻る
			if (m_anime >= 10.0f)
			{
				m_state = State::Idle;         // 状態を待機に戻す
				m_pNowPolygon = m_IdlePoly;    // 画像を待機用に切り替え
				m_anime = 0.0f;                // アニメーションをリセット
			}
		}

		// アニメーション処理
		m_pNowPolygon->SetUVRect(animeX[(int)m_anime]);

	// ------------------------------------------------------------
	}

	// 行列の更新
	{
		// 拡縮行列
		Math::Matrix m_scale = Math::Matrix::CreateScale(0.5f, 1.0f, 1.0f);

		// 移動行列
		Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

		// 行列合成
		m_mWorld = m_scale * transMat;
	}

}

void Player::PostUpdate()
{

}

void Player::DrawLit()
{
	if (!m_pNowPolygon) return;

	Math::Color color = { 0,1,0,1 };

	KdShaderManager::Instance().
		m_StandardShader.DrawPolygon(*m_pNowPolygon,m_mWorld);
}
