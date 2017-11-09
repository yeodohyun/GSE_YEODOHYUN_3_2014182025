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
		m_Objects[MAX_OBJECTS_COUNT - 1] = new Object(0, 0, OBJECT_BUILDING);
		std::cout <<std::endl<< m_Objects[MAX_OBJECTS_COUNT - 1]->Life << std::endl;

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
			m_renderer->DrawSolidRect(
				m_Objects[i]->posX, m_Objects[i]->posY ,0,m_Objects[i]->size, 
				m_Objects[i]->color[0], m_Objects[i]->color[1], m_Objects[i]->color[2], m_Objects[i]->color[3]);
		}
	}
}

void SceneMgr::UpateSceneMgr(float elapsedTime)
{
	ColisionTest();

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_Objects[i] != NULL)
		{
			if (m_Objects[i]->GetTime() <= 0.0f)
			{
				m_Objects[i] = NULL;
				delete m_Objects[i];
			}
			else
				m_Objects[i]->Update(elapsedTime);

			if (m_Objects[i]->Life == 0)
			{
				m_Objects[i] = NULL;
				delete m_Objects[i];
			}
		}
	}
}

void SceneMgr::AddObject(float x, float y)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_Objects[i] == NULL)
		{
			m_Objects[i] = new Object(x, y, OBJECT_CHARACTER);
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
				m_Objects[i]->color[0] = 1;
				m_Objects[i]->color[1] = 1;
				m_Objects[i]->color[2] = 1;
				m_Objects[i]->color[3] = 1;
			}
			else if (m_Objects[i]->ObjectType == OBJECT_BUILDING)
			{
				m_Objects[i]->color[0] = 1;
				m_Objects[i]->color[1] = 1;
				m_Objects[i]->color[2] = 0;
				m_Objects[i]->color[3] = 1;
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
					if (m_Objects[i]->ObjectType == OBJECT_BUILDING)
					{
						m_Objects[i]->Life -= m_Objects[j]->Life;
						m_Objects[i]->color[0] = 1;
						m_Objects[i]->color[1] = 0;
						m_Objects[i]->color[2] = 0;
						m_Objects[i]->color[3] = 1;
						std::cout << m_Objects[i]->Life << std::endl;
						m_Objects[j] = NULL;
						delete m_Objects[j];
					}
				}
			}
		}
	}
}
