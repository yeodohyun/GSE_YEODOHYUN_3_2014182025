
#include "Renderer.h"
#include "Object.h"

#define MAX_OBJECTS_COUNT 51

class SceneMgr
{
private:
	Object* m_Objects[MAX_OBJECTS_COUNT];
	Object* m_Bullets[MAX_OBJECTS_COUNT];

	Renderer *m_renderer;

	int m_windowWidth;
	int m_windowHeight;
public:
	SceneMgr(int width, int height);
	~SceneMgr();

	void DrawAllObjects();
	void UpateSceneMgr(float elapsedTime);
	void AddObject(float x, float y, int type);
<<<<<<< HEAD
=======
	void AddObject(float x, float y, int type, int index);
	void AddObject(float x, float y, int type, int index, int team);
>>>>>>> parent of 4ebcafe... Lecture 7
	void ColisionTest();
};

