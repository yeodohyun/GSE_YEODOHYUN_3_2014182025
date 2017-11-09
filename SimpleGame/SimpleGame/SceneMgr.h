
#include "Renderer.h"
#include "Object.h"

#define MAX_OBJECTS_COUNT 11

class SceneMgr
{
private:
	Object* m_Objects[MAX_OBJECTS_COUNT];

	Renderer *m_renderer;

	int m_windowWidth;
	int m_windowHeight;
public:
	SceneMgr(int width, int height);
	~SceneMgr();

	void DrawAllObjects();
	void UpateSceneMgr(float elapsedTime);
	void AddObject(float x, float y);
	void ColisionTest();
};

