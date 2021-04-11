#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "Camera.h"

typedef struct platform {
	float tx;
	float ty;
	float tz;
	float sx;
	float sy;
	float sz;
	bool last;
	bool obs_collect = false; // Daca platforma are un obstacol sau obiect colectabil
	int pos;
	glm::vec3 color;
}Platforms;

typedef struct objects {
	float tx1;
	float ty1;
	float tz1;
	float tx2;
	float ty2;
	float tz2;
	float sx1;
	float sy1;
	float sz1;
	float sx2;
	float sy2;
	float sz2;
	bool last;
	int pos;
	int type;
}Objects;

typedef struct obstacles {
	float tx;
	float ty;
	float tz;
	float sx;
	float sy;
	float sz;
	bool type;
	float time = 0;
}Obstacles;

class Tema3 : public SimpleScene
{
	public:
		Tema3();
		~Tema3();

		void Init() override;
		
	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color, bool screen_object, bool random, Texture2D* texture1 = NULL);

		glm::vec3 lightPosition;
		unsigned int materialShininess;
		float materialKd;
		float materialKs;

	protected:
	
		float speed; // Viteza deplasare
		float intial_platform = 1; // Lungimea unei laturi din cubul initial
		float player_tx; // Translatare pe Ox player
		float player_ty; // Translatare pe Oy player
		float player_tz; // Translatare pe Oz player
		float player_speed = 3; // Viteza player deplasare stanga/dreapta
		float length = 10; // Lungime scena pe Ox
		bool jump; // Se verifica daca sare
		float gravity = 9.81f; // Gravitie
		float max_jump = 2.f; // Inaltimea maxima
		float clk = 0; // Timp
		float player_speed_ty = 5.f; // Viteza deplasare Oy
		float spawn_plat = 40.f; // Distanta de spawnare a platformelor
		float var_speed = 4.f; // Variatia vitezei platformelor
		float max_speed = 8.f; // Viteza maxima
		float min_speed = 3.f; // Viteza minima
		float camera_pos_x; // Pozitie camera x
		float camera_pos_y; // Pozitie camera y
		float camera_pos_z; // Pozitie camera z
		float camera_center_x; // Centru camera x
		float camera_center_y; // Centru camera y
		float camera_center_z; // Centru camera z
		bool first_person; // Seteaza first person
		float fuel; // Combustibil curent
		float max_fuel; // Combustibil maxim
		float fuel_tx; // Translatare fuel bar Ox
		float fuel_ty; // Translatare fuel bar Oy
		float fuel_sx; // Scalare fuel bar Ox
		float fuel_sy; // Scalare fuel bar Oy
		float speed_ability; // Viteza abilitate
		float last_speed; // Ultima viteza inainte de abilitate;
		bool ability; // Abilitatte activa
		float clock_ability = 0; // Timp abilitate
		float time_ability; // Timpul cat dureaza abilitatea
		float is_death; // Stare player
		float clk_death = 0; // Contorizare timp death
		float time_player = 3; // Timp translatare player final
		float time_camera = 6; // Timp translatare camera final
		float time_exit = 9; // Timp termina joc
		float light_position_y; // Pozitie lumina pe y
		float rad = 0; // Raza spiralei de la final de joc
		float fuel_speed = 0.5f; // Viteza de scadere a combustibilului
		float time_render = 1; // Timp utilizat render
		int score = 0; // Scor
		float score_tx; // score tx
		float score_ty; // score ty
		float score_sx;	// score sx
		float score_sy; // score sy
		float score_max; // scorul maxim

		TemaCamera::Camera *camera;
		glm::mat4 projectionMatrix;
		glm::mat4 projectionMatrixInitial;

		std::vector<Platforms> platforms; // Platformele din ecran
		std::vector<Objects> objects; // Elemente decorative
		std::vector<Obstacles> obstacles; // Elemente decorative
		void InitialPlatform(); // Generare platforma initiala
		void InitialObjects(); // Generare platforma initiala
		void ShowPlatforms(float deltaTimeSeconds); // Afisare platforme
		void RemovePlatform(); // Se elimina platformele care au iesit din ecran
		void SpawnPlayer(); // Generare player
		void ShowPlayer(float deltaTime); // Afisare player
		void SpawnPlatform(); // Functia genereaza platforme
		void PlayerOnPlatform(); // Verificare player pe platforma
		int Random(int a, int b); // Functie de generare random
		void ChangeView(); // Functia de modificare in first person 
		Mesh* CreateFuelBar(std::string name, glm::vec4 leftBottomCorner, 
			glm::vec3 color); // Generare fuelbar
		Mesh* CreateChristmasTree(std::string name, glm::vec3 leftBottomCorner,
			glm::vec3 color); // Generare pom de craciun
		Mesh* CreateCube(std::string name, glm::vec3 leftBottomCorner,
			glm::vec3 color); // Generare felinar
		void ShowFuelBar(); // Se afiseaza combustibilul
		void CheckFuel(); // Se verifica combustibilul
		void CheckAbility(float deltaTimeSeconds); // Verifica abilitatea
		void ShowDeathPlatforms(float deltaTimeSeconds); // Afisare platforme terminare joc
		void ShowDeathPlayer(float deltaTimeSeconds); // Afisare player final joc
		std::unordered_map<std::string, Texture2D*> mapTextures; // Texturi
		void SpawnObjects(); // Functie de generare obiecte
		void RemoveObjects(); // Se elimina obiectele care ies din ecran
		void ShowObjects(float deltaTimeSeconds); // Afisare obiecte decor
		void SpawnObstacle(); // Generare obstacole
		void RemoveObstacles(); // Se elimina obstacolele care ies din ecran
		void ShowObstacles(float deltaTimeSeconds); // Afisare obstacole
		bool CollisionTest(float boxminX, float boxminY, float boxminZ,
			float boxmaxX, float boxmaxY, float boxmaxZ, float spherex, float spherey,
			float spherez, float radius); //Verificare coliziune
		void PlayervsObstacle(); //Coliziune player - obstacol
		void ShowScore(); // Afisare scor
};	


