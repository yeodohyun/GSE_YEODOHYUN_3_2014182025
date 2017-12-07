
#include "Renderer.h"
#include "Object.h"

#define MAX_OBJECTS_COUNT 100

class SceneMgr
{
private:
	Object* m_Objects[MAX_OBJECTS_COUNT];
	Object* m_Bullets[MAX_OBJECTS_COUNT];

	Renderer *m_renderer;

	int m_windowWidth;
	int m_windowHeight;

	GLuint backgronund;
	GLuint Building_texture1, Building_texture2;	//���� �ý���
	GLuint Character_texture1, Character_texture2; //ĳ���� �ý���
	GLuint Particle_texture; //��ƼŬ

	Sound *m_sound;
	
public:
	SceneMgr(int width, int height);
	~SceneMgr();

	int CharacterMove = 0;
	float ParticleTimer = 0.f;

	void DrawAllObjects();
	void UpateSceneMgr(float elapsedTime);

	void AddObject(float x, float y, int type,  int team);
	void ColisionTest();

};

