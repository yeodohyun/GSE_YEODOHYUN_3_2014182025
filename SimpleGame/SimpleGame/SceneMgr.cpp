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
	m_Objects[MAX_OBJECTS_COUNT - 1] = new Object(0, 350, OBJECT_BUILDING, 0, 1);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 1]->posX, m_Objects[MAX_OBJECTS_COUNT - 1]->posY, OBJECT_BULLET, 0, 1);
	m_Objects[MAX_OBJECTS_COUNT - 2] = new Object(-200, 350, OBJECT_BUILDING, 0, 1);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 2]->posX, m_Objects[MAX_OBJECTS_COUNT - 1]->posY, OBJECT_BULLET, 0, 1);
	m_Objects[MAX_OBJECTS_COUNT - 3] = new Object(200, 350, OBJECT_BUILDING, 0, 1);
	AddObject(m_Objects[MAX_OBJECTS_COUNT - 3]->posX, m_Objects[MAX_OBJECTS_COUNT - 1]->posY, OBJECT_BULLET, 0, 1);


}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::DrawAllObjects()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			if (m_Objects[i]->ObjectType == OBJECT_BUILDING)
			{
				GLuint texture = m_renderer->CreatePngTexture("./Textures/ClashRoyale.png");

				m_renderer->DrawTexturedRect(
					m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
					m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3], texture);
			}
			else
			{
				m_renderer->DrawSolidRect(
					m_Objects[i]->posX, m_Objects[i]->posY, 0, m_Objects[i]->size,
					m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3]);
			}
		}
	}
}

void SceneMgr::UpateSceneMgr(float elapsedTime)
{

	
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			if (m_Objects[i]->ObjectType == OBJECT_BUILDING && m_Objects[i]->BulletTimer > 0.5f)
			{
				AddObject(m_Objects[i]->posX, m_Objects[i]->posY, OBJECT_BULLET, 0, 1);
				m_Objects[i]->BulletTimer = 0;
			}
			if (m_Objects[i]->ObjectType == OBJECT_CHARACTER && m_Objects[i]->ArrowTimer > 0.5f)
			{
				std::cout << m_Objects[i]->ArrowTimer << std::endl;
				AddObject(m_Objects[i]->posX, m_Objects[i]->posY, OBJECT_ARROW, i, 1);
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


void SceneMgr::AddObject(float x, float y, int type, int index, int team)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (type == OBJECT_CHARACTER && m_Objects[i] == NULL)
		{
			m_Objects[i] = new Object(x, y, type, index, team);
			break;
		}
		else if (type == OBJECT_BULLET && m_Objects[i] == NULL)
		{
			m_Objects[i] = new Object(x, y, type, index, team);
			break;
		}
		else if (type == OBJECT_ARROW && m_Objects[i] == NULL)
		{
			m_Objects[i] = new Object(x, y, type, index, team);
			m_Objects[i]->Life = m_Objects[index]->Life;
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
			if (m_Objects[i]->ObjectType == OBJECT_CHARACTER)
			{
				if (m_Objects[i]->Team == 1)
				{
					m_Objects[i]->color[0] = 1;
					m_Objects[i]->color[1] = 0;
					m_Objects[i]->color[2] = 0;
					m_Objects[i]->color[3] = 1;
				}
				else if (m_Objects[i]->Team == 2)
				{
					m_Objects[i]->color[0] = 0;
					m_Objects[i]->color[1] = 1;
					m_Objects[i]->color[2] = 0;
					m_Objects[i]->color[3] = 1;
				}
			}
			else if (m_Objects[i]->ObjectType == OBJECT_BUILDING)
			{
				if (m_Objects[i]->Team == 1)
				{
					m_Objects[i]->color[0] = 1;
					m_Objects[i]->color[1] = 0;
					m_Objects[i]->color[2] = 0;
					m_Objects[i]->color[3] = 1;
				}
				else if (m_Objects[i]->Team == 2)
				{
					m_Objects[i]->color[0] = 0;
					m_Objects[i]->color[1] = 0;
					m_Objects[i]->color[2] = 0;
					m_Objects[i]->color[3] = 1;
				}
			}
			else if (m_Objects[i]->ObjectType == OBJECT_BULLET)
			{
				if (m_Objects[i]->Team == 1)
				{
					m_Objects[i]->color[0] = 1;
					m_Objects[i]->color[1] = 0;
					m_Objects[i]->color[2] = 0;
					m_Objects[i]->color[3] = 1;
				}
				else if (m_Objects[i]->Team == 2)
				{
					m_Objects[i]->color[0] = 0;
					m_Objects[i]->color[1] = 0;
					m_Objects[i]->color[2] = 1;
					m_Objects[i]->color[3] = 1;
				}
			}
			else if (m_Objects[i]->ObjectType == OBJECT_ARROW)
			{
				if (m_Objects[i]->Team == 1)
				{
					m_Objects[i]->color[0] = 0.5;
					m_Objects[i]->color[1] = 0.2;
					m_Objects[i]->color[2] = 0.7;
					m_Objects[i]->color[3] = 1;
				}
				else if (m_Objects[i]->Team == 2)
				{
					m_Objects[i]->color[0] = 1;
					m_Objects[i]->color[1] = 1;
					m_Objects[i]->color[2] = 0;
					m_Objects[i]->color[3] = 1;
				}
			}

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
						if ((m_Objects[i]->ObjectType == OBJECT_BUILDING &&m_Objects[j]->ObjectType == OBJECT_CHARACTER))
						{
							m_Objects[i]->Life -= m_Objects[j]->Life;
							std::cout << m_Objects[i]->Life << std::endl;
							m_Objects[i]->color[0] = 1;
							m_Objects[i]->color[1] = 0;
							m_Objects[i]->color[2] = 0;
							m_Objects[i]->color[3] = 1;
							m_Objects[j] = NULL;
							delete m_Objects[j];
						}
						else if (m_Objects[i]->ObjectType == OBJECT_CHARACTER &&m_Objects[j]->ObjectType == OBJECT_BULLET)
						{
							m_Objects[i]->Life -= m_Objects[j]->Life;
							std::cout << m_Objects[i]->Life << std::endl;
							m_Objects[i]->color[0] = 1;
							m_Objects[i]->color[1] = 0;
							m_Objects[i]->color[2] = 0;
							m_Objects[i]->color[3] = 1;
							m_Objects[j] = NULL;
							delete m_Objects[j];
						}
						else if ((m_Objects[i]->ObjectType == OBJECT_CHARACTER || m_Objects[i]->ObjectType == OBJECT_BUILDING) && m_Objects[j]->ObjectType == OBJECT_ARROW && i != m_Objects[j]->ShooterIndex)
						{
							m_Objects[i]->Life -= m_Objects[j]->Life;
							std::cout << m_Objects[i]->Life << std::endl;
							m_Objects[i]->color[0] = 1;
							m_Objects[i]->color[1] = 0;
							m_Objects[i]->color[2] = 0;
							m_Objects[i]->color[3] = 1;
							m_Objects[j] = NULL;
							delete m_Objects[j];
						}
					}
				}
			}
		}
	}
}
