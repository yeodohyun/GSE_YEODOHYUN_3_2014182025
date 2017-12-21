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
	m_Objects[MAX_OBJECTS_COUNT - 1] = new Object(0, 300, OBJECT_BUILDING, 1);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 1]->posX, m_Objects[MAX_OBJECTS_COUNT - 1]->posY, OBJECT_BULLET, 1);
	m_Objects[MAX_OBJECTS_COUNT - 2] = new Object(-180, 330, OBJECT_BUILDING, 1);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 2]->posX, m_Objects[MAX_OBJECTS_COUNT - 2]->posY, OBJECT_BULLET, 1);
	m_Objects[MAX_OBJECTS_COUNT - 3] = new Object(180, 330, OBJECT_BUILDING, 1);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 3]->posX, m_Objects[MAX_OBJECTS_COUNT - 3]->posY, OBJECT_BULLET, 1);
	
	m_Objects[MAX_OBJECTS_COUNT - 4] = new Object(0, -300, OBJECT_BUILDING, 2);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 4]->posX, m_Objects[MAX_OBJECTS_COUNT - 4]->posY, OBJECT_BULLET, m_Objects[MAX_OBJECTS_COUNT - 4]->Team);
	m_Objects[MAX_OBJECTS_COUNT - 5] = new Object(-180, -330, OBJECT_BUILDING, 2);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 5]->posX, m_Objects[MAX_OBJECTS_COUNT - 5]->posY, OBJECT_BULLET, m_Objects[MAX_OBJECTS_COUNT - 5]->Team);
	m_Objects[MAX_OBJECTS_COUNT - 6] = new Object(180, -330, OBJECT_BUILDING, 2);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 6]->posX, m_Objects[MAX_OBJECTS_COUNT - 6]->posY, OBJECT_BULLET, m_Objects[MAX_OBJECTS_COUNT - 6]->Team);


	backgronund = m_renderer->CreatePngTexture("./Textures/background2.png");

	Building_texture1 = m_renderer->CreatePngTexture("./Textures/ClashRoyale.png");
	Building_texture2 = m_renderer->CreatePngTexture("./Textures/ClashRoyale2.png");
	Character_texture1 = m_renderer->CreatePngTexture("./Textures/character1.png");
	Character_texture2 = m_renderer->CreatePngTexture("./Textures/character2.png");
	Particle_texture = m_renderer->CreatePngTexture("./Textures/Particle2.png");
	Rain_texture = m_renderer->CreatePngTexture("./Textures/Rain.png");
	backgroundeffect = m_renderer->CreatePngTexture("./Textures/background.png");

	m_sound = new Sound();
	int soundBG = m_sound->CreateSound("./Dependencies/SoundSamples/Time Is Running Out.mp3");
	m_sound->PlaySound(soundBG, true, 0.4f);
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::DrawAllObjects()
{
	m_renderer->DrawTexturedRect(
		0, 0, 0, 800,
		1, 1, 1, 1, backgronund, 0.6);
	// Áß¾Ó¼±
	for (int i = 1; i < 8; i++)
	m_renderer->DrawTexturedRect(0, i * 100 - 550, 0, 500, 1, 1, 1, 1, backgroundeffect, 0.6);

	for (int i = 0; i < 350; i++)
		m_renderer->DrawSolidRect(i * 2 - 350, 0, 0, 1, 0, 0, 0, 1, 0.4);

	m_renderer->DrawText1(-20, 0, TextColor, 1, 1, 1, "Play !! ");
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			if (m_Objects[i]->ObjectType == OBJECT_BUILDING)
			{


				if (m_Objects[i]->Team == 1)
				{
					m_renderer->DrawTexturedRect(
						m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
						m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3], Building_texture1, 0.1);

					m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
						m_Objects[i]->posY + m_Objects[i]->size / 1.5, 0, m_Objects[i]->size, 5, 1, 0, 0, 1, m_Objects[i]->Life / 500, 0.1);
				}
				if (m_Objects[i]->Team == 2)
				{
					m_renderer->DrawTexturedRect(
						m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
						m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3], Building_texture2, 0.1);

					m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
						m_Objects[i]->posY + m_Objects[i]->size / 1.5, 0, m_Objects[i]->size, 5, 0, 0, 1, 1, m_Objects[i]->Life / 500, 0.1);
				}
			}

			if (m_Objects[i]->ObjectType == OBJECT_CHARACTER)
			{

				if (m_Objects[i]->Team == 1)
				{

					m_renderer->DrawTexturedRectSeq(
						m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size, m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
						Character_texture1, CharacterMove/16, 0, 16, 1, 0.2);

					m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
						m_Objects[i]->posY + m_Objects[i]->size / 1.5, 0, m_Objects[i]->size, 5, 1, 0, 0, 1, m_Objects[i]->Life / 100, 0.1);
				}
				else if (m_Objects[i]->Team == 2)
				{
					m_renderer->DrawTexturedRectSeq(
						m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size, m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
						Character_texture2, CharacterMove/16, 0, 16, 1, 0.2);

					m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
						m_Objects[i]->posY + m_Objects[i]->size / 1.5, 0, m_Objects[i]->size, 5, 0, 0, 1, 1, m_Objects[i]->Life / 100, 0.1);
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
						-((m_Objects[i]->vX-(int)m_Objects[i]->vX*(-1))/200.f), 1, Particle_texture, m_Objects[i]->ParticleTimer,0.5);

				}
				else if (m_Objects[i]->Team == 2)
				{
					m_renderer->DrawSolidRect(
						m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
						m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3], 0.3);
					m_renderer->DrawParticle(
						m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
						m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3],
						-((m_Objects[i]->vX - (int)m_Objects[i]->vX*(-1)) / 200.f), -1, Particle_texture, m_Objects[i]->ParticleTimer,0.5);
				}
			}

			if (m_Objects[i]->ObjectType == OBJECT_ARROW)
			{
				m_renderer->DrawSolidRect(
					m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
					m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3], 0.3);
			}

			m_renderer->DrawParticleClimate(0, 0, 0, 0.7, 1, 1, 1, 1, -0.1, -0.1, Rain_texture, ParticleTimer, 0.01);
		}
	}
}

void SceneMgr::UpateSceneMgr(float elapsedTime)
{
	CharacterMove++;
	ParticleTimer +=0.002f;
	std::cout << ParticleTimer << std::endl;
	if (m_Objects[MAX_OBJECTS_COUNT - 1] != NULL && m_Objects[MAX_OBJECTS_COUNT - 1]->ObjectType == OBJECT_BUILDING && m_Objects[MAX_OBJECTS_COUNT - 1]->PlayerTimer > 3.0f)
	{
		AddObject(rand() % 400 - 200, rand() % 400, OBJECT_CHARACTER, m_Objects[MAX_OBJECTS_COUNT - 1]->Team);
		m_Objects[MAX_OBJECTS_COUNT - 1]->PlayerTimer = 0.0f;
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
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
			if (m_Objects[i]->GetTime() <= 0.0f)
			{
				m_Objects[i] = NULL;
				delete m_Objects[i];
				continue;
			}
			else
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
		if (type == OBJECT_CHARACTER && m_Objects[i] == NULL)
		{
			m_Objects[i] = new Object(x, y, type, team);
			break;
		}
		else if (type == OBJECT_BULLET && m_Objects[i] == NULL)
		{
			m_Objects[i] = new Object(x, y, type, team);
			break;
		}
		else if (type == OBJECT_ARROW && m_Objects[i] == NULL)
		{
			m_Objects[i] = new Object(x, y, type, team);
			break;
		}
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
			if (i == j )
				continue;
			float min_iX, max_iX, min_jX, max_jX;
			float min_iY, max_iY, min_jY, max_jY;

			if (m_Objects[i] != NULL&&m_Objects[j] != NULL)
			{
				if (m_Objects[i]->ObjectType == m_Objects[j]->ObjectType)
					continue;
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
						if ((m_Objects[i]->ObjectType == OBJECT_BUILDING &&m_Objects[j]->ObjectType == OBJECT_BULLET))
						{
							m_Objects[i]->Life -= m_Objects[j]->Life;
							m_Objects[j] = NULL;
							delete m_Objects[j];
						}
						else if ((m_Objects[i]->ObjectType == OBJECT_BUILDING &&m_Objects[j]->ObjectType == OBJECT_CHARACTER))
						{
							m_Objects[i]->Life -= m_Objects[j]->Life;
							m_Objects[j] = NULL;
							delete m_Objects[j];
						}
						else if (m_Objects[i]->ObjectType == OBJECT_CHARACTER &&m_Objects[j]->ObjectType == OBJECT_BULLET)
						{
							m_Objects[i]->Life -= m_Objects[j]->Life;
							m_Objects[j] = NULL;
							delete m_Objects[j];
						}
						else if ((m_Objects[i]->ObjectType == OBJECT_CHARACTER || m_Objects[i]->ObjectType == OBJECT_BUILDING) && m_Objects[j]->ObjectType == OBJECT_ARROW)
						{
							m_Objects[i]->Life -= m_Objects[j]->Life;
							m_Objects[j] = NULL;
							delete m_Objects[j];
						}
					}
				}
			}
		}
	}
}
