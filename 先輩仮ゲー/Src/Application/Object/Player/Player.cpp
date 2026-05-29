#include "Player.h"

void Player::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();

	m_polygon->SetMaterial("Asset/Textures/Object/Player/Idle.png");

	m_pos = { -20,2,0 };

	m_polygon->SetSplit(7, 1);

	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
}

void Player::Update()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_pos.x += 0.1f; }
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { m_pos.x -= 0.1f; }

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;
}

void Player::PostUpdate()
{

}

void Player::DrawSprite()
{
	KdShaderManager::Instance().
		m_StandardShader.DrawPolygon(*m_polygon);
}
