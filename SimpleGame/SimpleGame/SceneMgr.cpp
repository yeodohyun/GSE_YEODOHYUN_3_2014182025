#include "stdafx.h"
#include "SceneMgr.h"

#define  TextColor GLUT_BITMAP_9_BY_15   


SceneMgr::SceneMgr(int width, int height)
{
	m_renderer = new Renderer(width, height);

	m_windowWidth = width;
	m_windowHeight = height;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		m_Objects[i] = NULL;
	}
	m_Objects[MAX_OBJECTS_COUNT] = new Object(-1000,-1000, Steering, 1);


	m_Objects[MAX_OBJECTS_COUNT - 1] = new Object(-50, 350, OBJECT_BUILDING, 1);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 1]->posX, m_Objects[MAX_OBJECTS_COUNT - 1]->posY, OBJECT_BULLET, 1);
	m_Objects[MAX_OBJECTS_COUNT - 2] = new Object(-200, 350, OBJECT_BUILDING, 1);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 2]->posX, m_Objects[MAX_OBJECTS_COUNT - 2]->posY, OBJECT_BULLET, 1);
	m_Objects[MAX_OBJECTS_COUNT - 3] = new Object(100, 350, OBJECT_BUILDING, 1);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 3]->posX, m_Objects[MAX_OBJECTS_COUNT - 3]->posY, OBJECT_BULLET, 1);
	
	m_Objects[MAX_OBJECTS_COUNT - 4] = new Object(-50, -350, OBJECT_BUILDING, 2);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 4]->posX, m_Objects[MAX_OBJECTS_COUNT - 4]->posY, OBJECT_BULLET, m_Objects[MAX_OBJECTS_COUNT - 4]->Team);
	m_Objects[MAX_OBJECTS_COUNT - 5] = new Object(-200, -350, OBJECT_BUILDING, 2);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 5]->posX, m_Objects[MAX_OBJECTS_COUNT - 5]->posY, OBJECT_BULLET, m_Objects[MAX_OBJECTS_COUNT - 5]->Team);
	m_Objects[MAX_OBJECTS_COUNT - 6] = new Object(100, -350, OBJECT_BUILDING, 2);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 6]->posX, m_Objects[MAX_OBJECTS_COUNT - 6]->posY, OBJECT_BULLET, m_Objects[MAX_OBJECTS_COUNT - 6]->Team);

	CreateUiData();

	backgroundeffect = m_renderer->CreatePngTexture("./Textures/background.png");
	backgronund = m_renderer->CreatePngTexture("./Textures/background2.png");

	Building_texture1 = m_renderer->CreatePngTexture("./Textures/door.png");
	Building_texture2 = m_renderer->CreatePngTexture("./Textures/door2.png");
	Character1_texture1 = m_renderer->CreatePngTexture("./Textures/character1_1.png");
	Character1_texture2 = m_renderer->CreatePngTexture("./Textures/character1_2.png");
	Character2_texture1 = m_renderer->CreatePngTexture("./Textures/character2_1.png");
	Character2_texture2 = m_renderer->CreatePngTexture("./Textures/character2_2.png");
	Character3_texture1 = m_renderer->CreatePngTexture("./Textures/character3_1.png");
	Character3_texture2 = m_renderer->CreatePngTexture("./Textures/character3_2.png");
	Character4_texture1 = m_renderer->CreatePngTexture("./Textures/head.png");
	Character4_texture2 = m_renderer->CreatePngTexture("./Textures/head.png");
	Particle_texture = m_renderer->CreatePngTexture("./Textures/Particle2.png");
	Rain_texture = m_renderer->CreatePngTexture("./Textures/Rain.png");
	m_sound = new Sound();
	int soundBG = m_sound->CreateSound("./Dependencies/SoundSamples/Isaac.mp3");
	m_sound->PlaySound(soundBG, true, 0.4f);
	Select = 1;
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::DrawAllObjects()
{

	if ((m_Objects[MAX_OBJECTS_COUNT - 1] == NULL && m_Objects[MAX_OBJECTS_COUNT - 2] == NULL && m_Objects[MAX_OBJECTS_COUNT - 3] == NULL))
	{
		m_renderer->DrawText1(0, 0, TextColor, 1, 1, 1, "Player Win !! ");
	}
	else if ((m_Objects[MAX_OBJECTS_COUNT - 4] == NULL &&m_Objects[MAX_OBJECTS_COUNT - 5] == NULL &&m_Objects[MAX_OBJECTS_COUNT - 6] == NULL))
	{

		m_renderer->DrawText1(0, 0, TextColor, 1, 1, 1, "Computer Win !! ");
	}
	else
	{
		m_renderer->DrawTexturedRect(0, 0, 0, 800, 1, 1, 1, 1, backgronund, 0.6);

		//눈 배경
		for (int i = 0; i < 3; i++)
			m_renderer->DrawTexturedRect(-50, i * 100 - 250, 0, 450, 1, 1, 1, 1, backgroundeffect, 0.6);


		//선택창 가리기
		m_renderer->DrawSolidRect(0, 0, 0, 800, 1, 1, 0, 0, -0.025);

		// 캐릭터 선택 표시
		for (int i = 0; i < 70; i++)
		{
			m_renderer->DrawSolidRect(m_CharacterUI[Select + 3]->posX - 35 + i, m_CharacterUI[Select + 3]->posY + 35, 0, 5, 1, 1, 1, 1, 0.004);
			m_renderer->DrawSolidRect(m_CharacterUI[Select + 3]->posX - 35 + i, m_CharacterUI[Select + 3]->posY - 35, 0, 5, 1, 1, 1, 1, 0.004);
			m_renderer->DrawSolidRect(m_CharacterUI[Select + 3]->posX - 35, m_CharacterUI[Select + 3]->posY + 35 - i, 0, 5, 1, 1, 1, 1, 0.004);
			m_renderer->DrawSolidRect(m_CharacterUI[Select + 3]->posX + 35, m_CharacterUI[Select + 3]->posY + 35 - i, 0, 5, 1, 1, 1, 1, 0.004);
		}
		// 캐릭터 유아이
		for (int i = 0; i < 8; i++) {

			if (m_CharacterUI[i]->ObjectType == OBJECT_CHARACTER)
			{

				if (m_CharacterUI[i]->Team == 3)
				{

					m_renderer->DrawTexturedRectSeq(
						m_CharacterUI[i]->posX, m_CharacterUI[i]->posY, 0, 50, m_CharacterUI[i]->color[0], m_CharacterUI[i]->color[1], m_CharacterUI[i]->color[2], m_CharacterUI[i]->color[3],
						Character1_texture1, 1, 1, 2, 1, 0.015);

					m_renderer->DrawSolidRectGauge(m_CharacterUI[i]->posX, m_CharacterUI[i]->posY, 0,
						100, 100, 1, 0, 0, 1, m_CharacterUI[i]->PlayerTimer / 5, 0.016);

				}
				else if (m_CharacterUI[i]->Team == 4)
				{
					m_renderer->DrawTexturedRectSeq(
						m_CharacterUI[i]->posX, m_CharacterUI[i]->posY, 0, 50, m_CharacterUI[i]->color[0], m_CharacterUI[i]->color[1], m_CharacterUI[i]->color[2], m_CharacterUI[i]->color[3],
						Character1_texture2, 1, 1, 2, 1, 0.015);

					m_renderer->DrawSolidRectGauge(m_CharacterUI[i]->posX, m_CharacterUI[i]->posY, 0,
						100, 100, 0, 0, 1, 1, m_CharacterUI[i]->PlayerTimer / 5, 0.016);
				}

			}
			if (m_CharacterUI[i]->ObjectType == OBJECT_CHARACTER2)
			{

				if (m_CharacterUI[i]->Team == 3)
				{

					m_renderer->DrawTexturedRectSeq(
						m_CharacterUI[i]->posX, m_CharacterUI[i]->posY, 0, m_CharacterUI[i]->size, m_CharacterUI[i]->color[0], m_CharacterUI[i]->color[1], m_CharacterUI[i]->color[2], m_CharacterUI[i]->color[3],
						Character2_texture1, 0, 1, 5, 1, 0.015);

					m_renderer->DrawSolidRectGauge(m_CharacterUI[i]->posX, m_CharacterUI[i]->posY, 0,
						100, 100, 1, 0, 0, 1, m_CharacterUI[i]->PlayerTimer / 7, 0.016);

				}
				else if (m_CharacterUI[i]->Team == 4)
				{
					m_renderer->DrawTexturedRectSeq(
						m_CharacterUI[i]->posX, m_CharacterUI[i]->posY, 0, m_CharacterUI[i]->size, m_CharacterUI[i]->color[0], m_CharacterUI[i]->color[1], m_CharacterUI[i]->color[2], m_CharacterUI[i]->color[3],
						Character2_texture2, 4, 1, 5, 1, 0.015);

					m_renderer->DrawSolidRectGauge(m_CharacterUI[i]->posX, m_CharacterUI[i]->posY, 0,
						100, 100, 0, 0, 1, 1, m_CharacterUI[i]->PlayerTimer / 7, 0.016);
				}

			}
			if (m_CharacterUI[i]->ObjectType == OBJECT_CHARACTER3)
			{

				if (m_CharacterUI[i]->Team == 3)
				{

					m_renderer->DrawTexturedRectSeq(
						m_CharacterUI[i]->posX, m_CharacterUI[i]->posY + 0, 0, 60, m_CharacterUI[i]->color[0], m_CharacterUI[i]->color[1], m_CharacterUI[i]->color[2], m_CharacterUI[i]->color[3],
						Character3_texture1, 0, 0, 2, 1, 0.015);
					m_renderer->DrawSolidRectGauge(m_CharacterUI[i]->posX, m_CharacterUI[i]->posY, 0,
						100, 100, 1, 0, 0, 1, m_CharacterUI[i]->PlayerTimer / 10, 0.016);

				}
				else if (m_CharacterUI[i]->Team == 4)
				{
					m_renderer->DrawTexturedRectSeq(
						m_CharacterUI[i]->posX, m_CharacterUI[i]->posY - 10, 0, 60, m_CharacterUI[i]->color[0], m_CharacterUI[i]->color[1], m_CharacterUI[i]->color[2], m_CharacterUI[i]->color[3],
						Character3_texture2, 0, 0, 2, 1, 0.015);

					m_renderer->DrawSolidRectGauge(m_CharacterUI[i]->posX, m_CharacterUI[i]->posY, 0,
						100, 100, 0, 0, 1, 1, m_CharacterUI[i]->PlayerTimer / 10, 0.016);
				}

			}
			if (m_CharacterUI[i]->ObjectType == OBJECT_CHARACTER4)
			{

				if (m_CharacterUI[i]->Team == 3)
				{

					m_renderer->DrawTexturedRectSeq(
						m_CharacterUI[i]->posX, m_CharacterUI[i]->posY, 0, 80, m_CharacterUI[i]->color[0], m_CharacterUI[i]->color[1], m_CharacterUI[i]->color[2], m_CharacterUI[i]->color[3],
						Character4_texture1, 2, 0, 4, 1, 0.015);
					m_renderer->DrawSolidRectGauge(m_CharacterUI[i]->posX, m_CharacterUI[i]->posY, 0,
						100, 100, 1, 0, 0, 1, m_CharacterUI[i]->PlayerTimer / 30, 0.016);

				}
				else if (m_CharacterUI[i]->Team == 4)
				{
					m_renderer->DrawTexturedRectSeq(
						m_CharacterUI[i]->posX, m_CharacterUI[i]->posY, 0, 80, m_CharacterUI[i]->color[0], m_CharacterUI[i]->color[1], m_CharacterUI[i]->color[2], m_CharacterUI[i]->color[3],
						Character4_texture2, 2, 0, 4, 1, 0.015);

					m_renderer->DrawSolidRectGauge(m_CharacterUI[i]->posX, m_CharacterUI[i]->posY, 0,
						100, 100, 0, 0, 1, 1, m_CharacterUI[i]->PlayerTimer / 30, 0.016);
				}

			}
		}

		m_renderer->DrawText1(-50, 0, TextColor, 1, 1, 1, "Play !! ");


		for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
		{
			if (m_Objects[i] != NULL)
			{
				if (m_Objects[i]->ObjectType == OBJECT_BUILDING)
				{

					if (m_Objects[i]->Team == 1)
					{

						m_renderer->DrawTexturedRectSeq(
							m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size, m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
							Building_texture1, 0, 0, 2, 1, 0.016);

						m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
							m_Objects[i]->posY + m_Objects[i]->size / 2, 0, m_Objects[i]->size, 5, 1, 0, 0, 1, m_Objects[i]->Life / 500, 0.1);
					}
					if (m_Objects[i]->Team == 2)
					{
						m_renderer->DrawTexturedRectSeq(
							m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size, m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
							Building_texture2, 0, 0, 2, 1, 0.016);

						m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
							m_Objects[i]->posY - m_Objects[i]->size / 2, 0, m_Objects[i]->size, 5, 0, 0, 1, 1, m_Objects[i]->Life / 500, 0.1);
					}

					m_renderer->DrawText1(-50, 0, TextColor, 1, 1, 1, "Play !! ");
				}

				if (m_Objects[i]->ObjectType == OBJECT_CHARACTER)
				{

					if (m_Objects[i]->Team == 1)
					{

						m_renderer->DrawTexturedRectSeq(
							m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size, m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
							Character1_texture1, CharacterMove / 200, 1, 2, 1, 0.016);

						m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
							m_Objects[i]->posY + m_Objects[i]->size / 1.5, 0, m_Objects[i]->size, 5, 1, 0, 0, 1, m_Objects[i]->Life / 20, 0.1);
					}
					else if (m_Objects[i]->Team == 2)
					{
						m_renderer->DrawTexturedRectSeq(
							m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size, m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
							Character1_texture2, CharacterMove / 100, 1, 2, 1, 0.016);

						m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
							m_Objects[i]->posY + m_Objects[i]->size / 1.5, 0, m_Objects[i]->size, 5, 0, 0, 1, 1, m_Objects[i]->Life / 20, 0.1);
					}
				}
				if (m_Objects[i]->ObjectType == OBJECT_CHARACTER2)
				{

					if (m_Objects[i]->Team == 1)
					{

						m_renderer->DrawTexturedRectSeq(
							m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size, m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
							Character2_texture1, CharacterMove / 70, 0, 5, 1, 0.016);

						m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
							m_Objects[i]->posY + m_Objects[i]->size / 1.5, 0, m_Objects[i]->size, 5, 1, 0, 0, 1, m_Objects[i]->Life / 100, 0.1);
					}
					else if (m_Objects[i]->Team == 2)
					{
						m_renderer->DrawTexturedRectSeq(
							m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size, m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
							Character2_texture2, CharacterMove / 70, 0, 5, 1, 0.016);


						m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
							m_Objects[i]->posY + m_Objects[i]->size / 1.5, 0, m_Objects[i]->size, 5, 0, 0, 1, 1, m_Objects[i]->Life / 100, 0.1);
					}
				}

				if (m_Objects[i]->ObjectType == OBJECT_CHARACTER3)
				{

					if (m_Objects[i]->Team == 1)
					{

						m_renderer->DrawTexturedRectSeq(
							m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size, m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
							Character3_texture1, CharacterMove / 80, 0, 2, 1, 0.016);

						m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
							m_Objects[i]->posY + m_Objects[i]->size / 1.5, 0, m_Objects[i]->size, 5, 1, 0, 0, 1, m_Objects[i]->Life / 50, 0.1);
					}
					else if (m_Objects[i]->Team == 2)
					{
						m_renderer->DrawTexturedRectSeq(
							m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size, m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
							Character3_texture2, CharacterMove / 80, 0, 2, 1, 0.016);

						m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
							m_Objects[i]->posY + m_Objects[i]->size / 1.5, 0, m_Objects[i]->size, 5, 0, 0, 1, 1, m_Objects[i]->Life / 50, 0.1);
					}
				}

				if (m_Objects[i]->ObjectType == OBJECT_CHARACTER4)
				{

					if (m_Objects[i]->Team == 1)
					{

						m_renderer->DrawTexturedRectSeq(
							m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size, m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
							Character4_texture1, CharacterMove / 80, 0, 4, 1, 0.016);

						m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
							m_Objects[i]->posY + m_Objects[i]->size / 1.5, 0, m_Objects[i]->size, 5, 1, 0, 0, 1, m_Objects[i]->Life / 50, 0.1);
					}
					else if (m_Objects[i]->Team == 2)
					{
						m_renderer->DrawTexturedRectSeq(
							m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size, m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
							Character4_texture1, CharacterMove / 80, 0, 4, 1, 0.016);

						m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
							m_Objects[i]->posY + m_Objects[i]->size / 1.5, 0, m_Objects[i]->size, 5, 0, 0, 1, 1, m_Objects[i]->Life / 50, 0.1);
					}
				}

				if (m_Objects[i]->ObjectType == OBJECT_BULLET)
				{
					if (m_Objects[i]->Team == 1)
					{
						m_renderer->DrawSolidRect(
							m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
							m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3], 0.3);

						m_renderer->DrawParticle(
							m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
							m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
							-((m_Objects[i]->vX - (int)m_Objects[i]->vX*(-1)) / 200.f), 1, Particle_texture, m_Objects[i]->ParticleTimer, 0.5);

					}
					else if (m_Objects[i]->Team == 2)
					{
						m_renderer->DrawSolidRect(
							m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
							m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3], 0.3);

						m_renderer->DrawParticle(
							m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
							m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
							-((m_Objects[i]->vX - (int)m_Objects[i]->vX*(-1)) / 200.f), -1, Particle_texture, m_Objects[i]->ParticleTimer, 0.5);
					}
				}

				if (m_Objects[i]->ObjectType == OBJECT_ARROW)
				{
					m_renderer->DrawSolidRect(
						m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
						m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3], 0.3);
				}

				m_renderer->DrawParticleClimate(0, 0, 0, 0.7, 1, 1, 1, 1, -0.1, -0.1, Rain_texture, m_Objects[MAX_OBJECTS_COUNT]->ParticleTimer, 0.01);

			}
		}
	}
}

void SceneMgr::UpateSceneMgr(float elapsedTime)
{
	CharacterMove++;
	//std::cout << ParticleTimer << std::endl;



	for (int i = 0; i < 8; i++)
	{
		if (m_CharacterUI[i]->PlayerTimer < 40.0f)
			m_CharacterUI[i]->PlayerTimer += elapsedTime / 1000.f;
		if (m_CharacterUI[i]->ObjectType == OBJECT_CHARACTER)
		{
			if (m_CharacterUI[i]->PlayerTimer > 5.0f)
			{
				if (m_CharacterUI[i]->Team == 3)
				{
					AddObject(rand() % 400 - 200, rand() % 400, OBJECT_CHARACTER, m_CharacterUI[i]->Team - 2);
					m_CharacterUI[i]->PlayerTimer = 0.0f;
				}
				else if (m_CharacterUI[i]->Team == 4)
				{
					m_CharacterUI[i]->CharacterReady = true;
					//std::cout << m_CharacterUI[i]->PlayerTimer << std::endl;
				}
			}
		}
		if (m_CharacterUI[i]->ObjectType == OBJECT_CHARACTER2)
		{
			if (m_CharacterUI[i]->PlayerTimer > 7.0f)
			{
				if (m_CharacterUI[i]->Team == 3)
				{
					for (int j =1; j < 7; j++)
					{
						if (m_Objects[MAX_OBJECTS_COUNT-j] != NULL)
						{
							if (m_Objects[MAX_OBJECTS_COUNT - j]->Team == 2 && m_Objects[MAX_OBJECTS_COUNT - j]->ObjectType == OBJECT_BUILDING)
							{
								AddObject(m_Objects[MAX_OBJECTS_COUNT - j]->posX, rand() % 400, OBJECT_CHARACTER2, m_CharacterUI[i]->Team - 2);
								break;
							}
						}
					}
					m_CharacterUI[i]->PlayerTimer = 0.0f;
				}
				else if (m_CharacterUI[i]->Team == 4)
				{
					m_CharacterUI[i]->CharacterReady = true;
				}
			}
		}
		if (m_CharacterUI[i]->ObjectType == OBJECT_CHARACTER3)
		{
			if (m_CharacterUI[i]->PlayerTimer > 10.0f)
			{
				if (m_CharacterUI[i]->Team == 3)
				{
					for (int j = 1; j < 7; j++)
					{
						if (m_Objects[MAX_OBJECTS_COUNT - j] != NULL)
						{
							if (m_Objects[MAX_OBJECTS_COUNT - j]->Team == 1 && m_Objects[MAX_OBJECTS_COUNT - j]->ObjectType == OBJECT_BUILDING)
							{
								AddObject(m_Objects[MAX_OBJECTS_COUNT - j]->posX, rand() % 400, OBJECT_CHARACTER3, m_CharacterUI[i]->Team - 2);
								break;
							}
						}
					}
					m_CharacterUI[i]->PlayerTimer = 0.0f;
				}
				else if (m_CharacterUI[i]->Team == 4)
				{
					m_CharacterUI[i]->CharacterReady = true;
				}
			}
		}
		if (m_CharacterUI[i]->ObjectType == OBJECT_CHARACTER4)
		{
			if (m_CharacterUI[i]->PlayerTimer > 30.0f)
			{
				if (m_CharacterUI[i]->Team == 3)
				{
					AddObject(rand() % 400 - 200, rand() % 400, OBJECT_CHARACTER4, m_CharacterUI[i]->Team - 2);
					m_CharacterUI[i]->PlayerTimer = 0.0f;
				}
				else if (m_CharacterUI[i]->Team == 4)
				{
					m_CharacterUI[i]->CharacterReady = true;
				}
			}
		}
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT+1; i++)
	{
		if (m_Objects[i] != NULL)
		{
			
			if (m_Objects[i]->ObjectType == OBJECT_BUILDING && m_Objects[i]->BulletTimer > 2.f)
			{
				AddObject(m_Objects[i]->posX, m_Objects[i]->posY, OBJECT_BULLET,m_Objects[i]->Team);
				m_Objects[i]->BulletTimer = 0;
			}
			if (m_Objects[i]->ObjectType == OBJECT_CHARACTER && m_Objects[i]->ArrowTimer > 3.0f)
			{
				AddObject(m_Objects[i]->posX, m_Objects[i]->posY, OBJECT_ARROW, m_Objects[i]->Team);
				m_Objects[i]->ArrowTimer = 0;
			}
			m_Objects[i]->Update(elapsedTime);

			if (m_Objects[i]->Life <= 0)
			{
				m_Objects[i] = NULL;
				delete m_Objects[i];
			}
		}
	}
	ColisionTest();
}


void SceneMgr::AddObject(float x, float y, int type, int team)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_Objects[i] == NULL)
		{
			m_Objects[i] = new Object(x, y, type, team);
			break;
		}
	}

}

void SceneMgr::CreateUiData()
{
	
	for (int i = 0; i < 8; i++)
	{
		m_CharacterUI[i] = new Object(250, -(i * 100) + 350, i % 4+1, i / 4 +3);
	}

}

void SceneMgr::ColisionTest()
{

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_Objects[i] != NULL)
		{

		}
		for (int j = 0; j < MAX_OBJECTS_COUNT; j++)
		{
			if (i == j)
				continue;
			float min_iX, max_iX, min_jX, max_jX;
			float min_iY, max_iY, min_jY, max_jY;

			if (m_Objects[i] != NULL&&m_Objects[j] != NULL)
			{
				min_iX = (m_Objects[i]->posX) - (m_Objects[i]->size / 2);
				max_iX = (m_Objects[i]->posX) + (m_Objects[i]->size / 2);
				min_iY = (m_Objects[i]->posY) - (m_Objects[i]->size / 2);
				max_iY = (m_Objects[i]->posY) + (m_Objects[i]->size / 2);

				min_jX = (m_Objects[j]->posX) - (m_Objects[j]->size / 2);
				max_jX = (m_Objects[j]->posX) + (m_Objects[j]->size / 2);
				min_jY = (m_Objects[j]->posY) - (m_Objects[j]->size / 2);
				max_jY = (m_Objects[j]->posY) + (m_Objects[j]->size / 2);

				if (min_iX<max_jX && max_iX>min_jX && min_iY<max_jY&&max_iY>min_jY)
				{
					if (m_Objects[i]->Team != m_Objects[j]->Team)
					{
						if (m_Objects[i]->ObjectType == OBJECT_BUILDING)
						{
							if (m_Objects[j]->ObjectType == OBJECT_BULLET)
							{
								m_Objects[i]->Life -= m_Objects[j]->damage;
								m_Objects[j] = NULL;
								delete m_Objects[j];
							}
							else if (m_Objects[j]->ObjectType == OBJECT_ARROW)
							{
								m_Objects[i]->Life -= m_Objects[j]->damage;
								m_Objects[j] = NULL;
								delete m_Objects[j];
							}
							else if (m_Objects[j]->ObjectType == OBJECT_CHARACTER2)
							{
								m_Objects[i]->Life -= m_Objects[j]->damage;
								m_Objects[j] = NULL;
								delete m_Objects[j];
							}
						}
						else if (m_Objects[i]->ObjectType == OBJECT_CHARACTER)
						{
							if (m_Objects[j]->ObjectType == OBJECT_BULLET)
							{
								m_Objects[i]->Life -= m_Objects[j]->damage;
								m_Objects[j] = NULL;
								delete m_Objects[j];
							}
						}
						else if (m_Objects[i]->ObjectType == OBJECT_CHARACTER3)
						{
							if (m_Objects[j]->ObjectType == OBJECT_CHARACTER2)
							{
								m_Objects[i]->Life -= 25;
								m_Objects[j] = NULL;
								delete m_Objects[j];
							}
							else if (m_Objects[j]->ObjectType == OBJECT_ARROW)
							{
								m_Objects[i]->Life -= m_Objects[j]->damage;
								m_Objects[j] = NULL;
								delete m_Objects[j];
							}
							else if (m_Objects[j]->ObjectType == OBJECT_BULLET)
							{
								m_Objects[i]->Life -= m_Objects[j]->damage;
								m_Objects[j] = NULL;
								delete m_Objects[j];
							}
						}
						else if (m_Objects[i]->ObjectType == OBJECT_CHARACTER4)
						{
							if (m_Objects[j]->ObjectType == OBJECT_BULLET)
							{
								m_Objects[j] = NULL;
								delete m_Objects[j];
							}
							else if (m_Objects[j]->ObjectType == OBJECT_ARROW)
							{
								m_Objects[j] = NULL;
								delete m_Objects[j];
							}
							else if (m_Objects[j]->ObjectType == OBJECT_CHARACTER)
							{
								m_Objects[j] = NULL;
								delete m_Objects[j];
							}
							else if (m_Objects[j]->ObjectType == OBJECT_CHARACTER2)
							{
								m_Objects[j] = NULL;
								delete m_Objects[j];
							}
							else if (m_Objects[j]->ObjectType == OBJECT_CHARACTER3)
							{
								m_Objects[j] = NULL;
								delete m_Objects[j];
							}
						}
					}
				}
			}
		}
	}
}



void SceneMgr::MouseClick(int x, int y)
{
	for (int i = 0; i < 8; i++)
	{
		if (m_CharacterUI[i]->Team == 4 && m_CharacterUI[i]->CharacterReady == true && m_CharacterUI[i]->ObjectType==Select)
		{

			AddObject(x, y, Select, 2);

			m_CharacterUI[i]->PlayerTimer = 0;
			std::cout << m_CharacterUI[i]->PlayerTimer << std::endl;
			m_CharacterUI[i]->CharacterReady = false;
		}
	}

}