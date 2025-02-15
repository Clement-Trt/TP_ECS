#include <iostream>
#include "GameManager.h"
#include "Scene.h"


int main() {

	GameManager* GM = new GameManager;

	Scene* scene = new Scene;

	GM->Initialize();

	GM->SetScene(scene);
	scene->SetGameManager(GM);

	GM->Run();

	return 0;
}
