#include "Tema3.h"

#include <vector>
#include <string>
#include <iostream>
#include <time.h> 

#include <Core/Engine.h>
#include "Camera.h"
#include "Transform3D.h"

using namespace std;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
	speed = min_speed;
	jump = false;
	max_fuel = 20;
	fuel = max_fuel;
	fuel_tx = -0.95f;
	fuel_ty = 0.8f;
	fuel_sx = 0.2f;
	fuel_sy = 0.15f;
	score_tx = 0.95f;
	score_ty = 0.8f;
	score_sx = 1.f;
	score_sy = 0.15f;
	score_max = 120;
	speed_ability = 11.f;
	time_ability = 3.f;
	is_death = false;
	first_person = false;

	// Pentru a nu se modifica camera dupa miscarea mouse-ului
	GetCameraInput()->SetActive(false);

	// Pentru generarea valorilor random
	srand((unsigned int)time(NULL));

	camera = new TemaCamera::Camera();
	
	// Creare platforma
	{
		Mesh* mesh1 = new Mesh("platform");
		mesh1->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh1->GetMeshID()] = mesh1;
	}
	
	// Creare player
	{
		Mesh* mesh2 = new Mesh("player");
		mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh2->GetMeshID()] = mesh2;
	}

	// Creare fuelbar
	{
		Mesh* fuelBar = CreateFuelBar("fuelbar", glm::vec4(0,0,0,0), glm::vec3(0, 1, 0));
		AddMeshToList(fuelBar);
	}

	// Creare pom
	{
		Mesh* tree = CreateChristmasTree("tree", glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		AddMeshToList(tree);
	}

	// Creare obstacol
	{
		Mesh* box = CreateCube("box", glm::vec4(0, 0, 0, 0), glm::vec3(1, 1, 1));
		AddMeshToList(box);
	}

	const string textureLoc = "Source/Laboratoare/Tema3/Textures/";

	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "tree.png").c_str(), GL_REPEAT);
		mapTextures["tree"] = texture;
	}

	{
		Texture2D* stone = new Texture2D();
		stone->Load2D((textureLoc + "stone.jpg").c_str(), GL_REPEAT);
		mapTextures["stone"] = stone;
	}

	{
		Texture2D* box = new Texture2D();
		box->Load2D((textureLoc + "box.jpg").c_str(), GL_REPEAT);
		mapTextures["box"] = box;
	}

	{
		Texture2D* lamp = new Texture2D();
		lamp->Load2D((textureLoc + "metal.jpg").c_str(), GL_REPEAT);
		mapTextures["metal"] = lamp;
	}

	{
		Texture2D* coin = new Texture2D();
		coin->Load2D((textureLoc + "coin.jpg").c_str(), GL_REPEAT);
		mapTextures["coin"] = coin;
	}

	// Adaugare shader
	{
		Shader *shader = new Shader("Tema3");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// Setare pozitia lumina si caracteristici
	{
		light_position_y = 4;
		lightPosition = glm::vec3(5, light_position_y,3);
		materialShininess = 30;
		materialKd = 0.8f;
		materialKs = 0.8f;
	}

	// Setare perspectiva
	projectionMatrixInitial = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	// Se genereaza platforma initiala
	InitialPlatform();

	//Generare player
	SpawnPlayer();

	// Se genereaza obiectele decorative initiale
	InitialObjects();
}

void Tema3::FrameStart()
{
	// Se curata bufferul de culori si adancime
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Se seteaza aria de desenare
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::Update(float deltaTimeSeconds)
{

	//Initial, deltaTimeSeconds are o valoare foarte mare
	if (deltaTimeSeconds > 0.2f) {
		return;
	}

	time_render++;

	// Se modifica modul de vizualizare
	ChangeView();

	// Daca este mort
	if (is_death) {
		clk_death += deltaTimeSeconds;
		first_person = false;

		// Translate finala jucator
		if (clk_death <= time_player) {
			// Afisare platforme final joc
			ShowDeathPlatforms(deltaTimeSeconds);
			// Afisare player final joc
			ShowDeathPlayer(deltaTimeSeconds);
		// Traslatare camera finala
		} else if (time_player < clk_death && clk_death <= time_camera) {
			// Afisare platforme final joc
			ShowDeathPlatforms(deltaTimeSeconds);
			// Se modifica lumina 
			light_position_y += deltaTimeSeconds*8.f;
			materialKd -= deltaTimeSeconds*0.1f;
			materialKs -= deltaTimeSeconds*0.1f;

			lightPosition = glm::vec3(5, light_position_y, 3);
		
		// Translatare platforme finala
		} else if (time_camera < clk_death && clk_death <= time_exit) {

			// Afisare platforme final joc
			ShowDeathPlatforms(deltaTimeSeconds);

			// Se modifica lumina 
			light_position_y += deltaTimeSeconds * 10.f;
			materialKd -= deltaTimeSeconds * 0.2f;
			materialKs -= deltaTimeSeconds * 0.2f;

			lightPosition = glm::vec3(5, light_position_y, 3);
		
			// Terminare joc
		} else if (time_exit < clk_death) {
			Exit();
		}	
		return;
	}

	// Daca abilitatea este activata, combustibilul scade de 2 ori mai repede
	if (ability) {
		fuel -= 2.f * deltaTimeSeconds * fuel_speed;
	} else {
		fuel -= deltaTimeSeconds * fuel_speed;
	}

	// Se genereaza platformele
	SpawnPlatform();

	//Se elimina platformele
	RemovePlatform();

	//Se afiseaza platformele
	ShowPlatforms(deltaTimeSeconds);

	// Se genereaza obiectele
	SpawnObjects();

	// Se elimina obiectele
	RemoveObjects();

	// Se afiseaza obiectele
	ShowObjects(deltaTimeSeconds);

	// Se genereaza obstacole
	SpawnObstacle();

	//Se elimina obstacole
	RemoveObstacles();

	//Se afiseaza obstacole
	ShowObstacles(deltaTimeSeconds);

	//Se afiseaza player
	ShowPlayer(deltaTimeSeconds);

	//Se verifica daca player este pe platforma
	PlayerOnPlatform();

	//Se verifica coliziunea player-obstacol
	PlayervsObstacle();

	//Se afiseaza combustibilul
	ShowFuelBar();

	// Se verifica combustibilul
	CheckFuel();

	// Se afiseaza scorul
	ShowScore();

	// Se verifica abilitatea
	if (ability) {
		CheckAbility(deltaTimeSeconds);
	}

}

void Tema3::FrameEnd()
{
}

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
	//Creste viteza platforme
	if (window->KeyHold(GLFW_KEY_W) && ability == false) {
		speed += deltaTime * var_speed;
		if (speed > max_speed) {
			speed = max_speed;
		}
	}

	//Scade viteza platforme
	if (window->KeyHold(GLFW_KEY_S) && ability == false) {
		speed -= deltaTime * var_speed;
		if (speed < min_speed) {
			speed = min_speed;
		}
	}

	//Mutare player la stanga
	if (window->KeyHold(GLFW_KEY_A) && is_death == false) {
		player_tx += deltaTime * player_speed;
	}

	//Mutare player la dreapta
	if (window->KeyHold(GLFW_KEY_D) && is_death == false) {
		player_tx -= deltaTime * player_speed;
	}
}

void Tema3::OnKeyPress(int key, int mods)
{
	// Se incepe saritura
	// Jucatorul nu este deja in saritura
	if (key == GLFW_KEY_SPACE && jump != true) {
		clk = 0;
		jump = true;
	}

	// Se modifica modul de vizualizare
	if (key == GLFW_KEY_C && is_death == false) {
		first_person = !first_person;
	}
}

void Tema3::OnKeyRelease(int key, int mods)
{
}

void Tema3::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix,
	const glm::vec3 &color, bool screen_object, bool random, Texture2D* texture1)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// Se specifica shaderul utilizat
	glUseProgram(shader->program);

	// Se seteaza light_position
	glUniform3fv(glGetUniformLocation(shader->program, "light_position"), 1, glm::value_ptr(lightPosition));

	// Se seteaza eye_position
	glm::vec3 eyePosition = camera->GetTargetPosition();
	glUniform3fv(glGetUniformLocation(shader->program, "eye_position"), 1, glm::value_ptr(eyePosition));

	// Se seteaza propietatile materialului
	glUniform1uiv(glGetUniformLocation(shader->program, "material_shinines"), 1, &materialShininess);
	glUniform1fv(glGetUniformLocation(shader->program, "material_kd"), 1, &materialKd);
	glUniform1fv(glGetUniformLocation(shader->program, "material_ks"), 1, &materialKs);
	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));
	
	unsigned int v_random;
	
	// Se verifica random
	if (random) {
		v_random = 1;
	}
	else {
		v_random = 0;
	}

	// Se seteaza random
	glUniform1i(glGetUniformLocation(shader->program, "random"), v_random);

	// Se seteaza time
	glUniform1i(glGetUniformLocation(shader->program, "time"), time_render);

	// Se obtine locatia din shader pt Model
	int location1 = glGetUniformLocation(shader->program, "Model");

	// Se seteaza Model
	glUniformMatrix4fv(location1, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Se obtine locatia din shader pt View
	int location2 = glGetUniformLocation(shader->program, "View");

	// Se alege View, in functie de tipul de obiect(scena sau ecran)
	glm::mat4 viewMatrix;
	if (screen_object) {
		viewMatrix = glm::mat4(1);
		int so = 1;
		// Este un obiect de ecran
		glUniform1i(glGetUniformLocation(shader->program, "screen_object"), so);
	} else {
		viewMatrix = camera->GetViewMatrix();
		int so = 0;
		// Este un obiect din scena
		glUniform1i(glGetUniformLocation(shader->program, "screen_object"), so);
	}
	// Se seteaza View
	glUniformMatrix4fv(location2, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Se obtine locatia pt Projection
	int location3 = glGetUniformLocation(shader->program, "Projection");
	
	// Se alege Projection, in functie de tipul de obiect(scena sau ecran)
	if (screen_object) {
		projectionMatrix = glm::mat4(1);
	}
	else {
		projectionMatrix = projectionMatrixInitial;
	}
	unsigned int texture;
	if (texture1 != NULL)
	{
		// Se activeaza textura 0
		glActiveTexture(GL_TEXTURE0);

		// Se atribuie id texturii
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

		// Se seteaza textura
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
		texture = 1;
	}
	else {
		texture = 0;
	}

	glUniform1i(glGetUniformLocation(shader->program, "texture"), texture);
	
	// Se seteaza Projection
	glUniformMatrix4fv(location3, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Se deseneaza obiectul
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}


void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}

// Functie de generare a unui numar aleator din intervalul [a,b]
int Tema3::Random(int a, int b) {
	return a + (rand() % (b - a + 1));
}
