#include "stdafx.h"
#include "SceneMgr.h"


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


}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::DrawAllObjects()
{
	GLuint texture1, texture2;
	texture1 = m_renderer->CreatePngTexture("./Textures/ClashRoyale.png");
	texture2 = m_renderer->CreatePngTexture("./Textures/ClashRoyale2.png");
	
	// Áß¾Ó¼±
	for (int i = 0; i < 350; i++)
		m_renderer->DrawSolidRect(i*2 - 350, 0, 0, 1, 0, 0, 0, 1,0.4);
	
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
						m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3], texture1, 0.1);

					m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
						m_Objects[i]->posY + m_Objects[i]->size / 1.5, 0, m_Objects[i]->size, 5, 1, 0, 0, 1, m_Objects[i]->Life / 500, 0.1);
				}
				if (m_Objects[i]->Team == 2)
				{
					m_renderer->DrawTexturedRect(
						m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
						m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3], texture2, 0.1);

					m_renderer->DrawSolidRectGauge(m_Objects[i]->posX,
						m_Objects[i]->posY + m_Objects[i]->size / 1.5, 0, m_Objects[i]->size, 5, 0, 0, 1, 1, m_Objects[i]->Life / 500, 0.1);
					std::cout << m_Objects[i]->Life / 500 << std::endl;
				}
			}
			else
			{
				if (m_Objects[i]->ObjectType == OBJECT_CHARACTER)
				{
					m_renderer->DrawSolidRect(
						m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
						m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3], 0.2);

					if (m_Objects[i]->Team == 1)
					{
						m_renderer->DrawSolidRectGauge(m_Objects[i]->posX, 
							m_Objects[i]->posY + m_Objects[i]->size/1.5, 0, m_Objects[i]->size, 5, 1, 0, 0, 1, m_Objects[i]->Life / 100, 0.1);
					}
					else if (m_Objects[i]->Team == 2)
					{
						m_renderer->DrawSolidRectGauge(m_Objects[i]->posX, 
							m_Objects[i]->posY + m_Objects[i]->size/1.5, 0, m_Objects[i]->size, 5, 0, 0, 1, 1, m_Objects[i]->Life / 100, 0.1);
					}
				}
				if (m_Objects[i]->ObjectType != OBJECT_CHARACTER)
				{
					m_renderer->DrawSolidRect(
						m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
						m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3], 0.3);
				}

			}
		}
	}
}

void SceneMgr::UpateSceneMgr(float elapsedTime)
{

	
	if (m_Objects[MAX_OBJECTS_COUNT - 1]->ObjectType == OBJECT_BUILDING && m_Objects[MAX_OBJECTS_COUNT - 1]->PlayerTimer > 3.0f)
	{
		AddObject(rand() % 400 - 200, rand() % 400, OBJECT_CHARACTER, m_Objects[MAX_OBJECTS_COUNT - 1]->Team);
		m_Objects[MAX_OBJECTS_COUNT - 1]->PlayerTimer = 0.0f;
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_Objects[i] != NULL)
		{

			if (m_Objects[i]->ObjectType == OBJECT_BUILDING && m_Objects[i]->BulletTimer > 10.f)
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
							std::cout << m_Objects[i]->Life << std::endl;
							m_Objects[j] = NULL;
							delete m_Objects[j];
						}
						else if ((m_Objects[i]->ObjectType == OBJECT_CHARACTER || m_Objects[i]->ObjectType == OBJECT_BUILDING) && m_Objects[j]->ObjectType == OBJECT_ARROW)
						{
							m_Objects[i]->Life -= m_Objects[j]->Life;
							std::cout << m_Objects[i]->Life << std::endl;
							m_Objects[j] = NULL;
							delete m_Objects[j];
						}
					}
				}
			}
		}
	}
}
