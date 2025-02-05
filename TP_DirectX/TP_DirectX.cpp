// TP_DirectX.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <DirectXMath.h>
#include <vector>

#include "Entity.h"
#include "Transform.h"
#include "Component.h"





int main()
{
	std::cout << "Hello World!\n";

	std::vector<Entity> vecEntity;

	//TransformComponent TC;

	Entity firstEntity;
	firstEntity.SetID(1);

	vecEntity.push_back(firstEntity);

	for (auto& entity : vecEntity)
	{
		/*std::unique_ptr<Component> newComp = std::make_unique<TransformComponent>();
		entity.AddComponent(std::move(newComp));*/

		TransformComponent* newTC = new TransformComponent();
		entity.AddComponent(newTC);
	}


	for (auto& entity : vecEntity)
	{
		std::cout << "Entity " << entity.GetID() << " : \n";
		entity.GetComponent<TransformComponent>()->GetPosition();
	}

	std::cout << "\n ---------------------------------------------------------------------------------------------------------------------  \n\n";

	for (auto& entity : vecEntity)
	{
		//std::cout << "Entity " << entity.GetID() << " : \n";
		entity.GetComponent<TransformComponent>()->Move(4,6,2);
	}

	std::cout << "\n *********************************************************************************************************************  \n\n";

	for (auto& entity : vecEntity)
	{
		std::cout << "Entity " << entity.GetID() << " : \n";
		entity.GetComponent<TransformComponent>()->GetPosition();
	}
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
