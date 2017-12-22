
#include "Renderer.h"
#include "Object.h"


#define MAX_OBJECTS_COUNT 100

class SceneMgr
{
private:
	Object* m_Objects[MAX_OBJECTS_COUNT+1];
	Object* m_CharacterUI[8];
	Renderer *m_renderer;

	int m_windowWidth;
	int m_windowHeight;

	GLuint backgronund, backgroundeffect;
	GLuint Building_texture1, Building_texture2;	//빌딩 택스쳐
	GLuint Character1_texture1, Character1_texture2; //캐릭터 택스쳐
	GLuint Character1_head1, Character1_head2; //캐릭터 택스쳐
	GLuint Character2_texture1, Character2_texture2; //캐릭터 택스쳐
	GLuint Character3_texture1, Character3_texture2; //캐릭터 택스쳐
	GLuint Character4_texture1, Character4_texture2; //캐릭터 택스쳐
	GLuint Particle_texture; //파티클
	GLuint Rain_texture; //파티클

	Sound *m_sound;
	
public:
	SceneMgr(int width, int height);
	~SceneMgr();

	int CharacterMove = 0;
	float ParticleTimer = 0.f;
	void DrawAllObjects();
	void UpateSceneMgr(float elapsedTime);

	void AddObject(float x, float y, int type, int team); 
	void CreateUiData();
	void ColisionTest();
	void MouseClick(int x, int y);
	int Select;
};

