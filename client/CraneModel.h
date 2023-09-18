#pragma once
#include "List.h"
#include "Node.h"
#include "TypeSelected.h"
#include "TypeDirection.h"
#include "Screen.h"
#include "PerspectiveCamera.h"
#include <vector>

class CraneModel
{
public:
	CraneModel(List* renderList);
	~CraneModel();

	TypeSelected getTypeSelected();

	void changeTypeSelcted();
	void changeCamera();

	void moveArm(TypeDirection direction);
	void moveCarriage(TypeDirection direction);
	void moveHook(TypeDirection direction);
	void grabOrDrop();

	void moveCamera(TypeDirection direction);
	void moveViewingPointCamera(int x, int y);

private:
	Screen screen = Screen();
	TypeSelected selected;

	Node* grabbed = nullptr;
	glm::mat4 originalMatrix = glm::mat4(1.0f);
	vector<Node*> grabbable;

	int cntCamera = 0;
	vector<PerspectiveCamera*> cameras;

	// ------------------------------
	//		Movements specifications
	// ------------------------------
	float rotationAngle = 2.0f;
	float speedCarriage = 0.5f;
	float speedHook = 0.5f;
	float maxCarriage = 34.0f;
	float minCarriage = 9.0f;
	float maxHeightHook;
	float minHeightHook;
	float distanceToGrab = 5.0f;
	float distanceToDrop = 5.0f;
	float speedCamera = 0.5f;

	// ------------------------------
	//		Crane objects
	// ------------------------------
	Node* rotaryMotor = nullptr;
	Node* carriage = nullptr;
	Node* delimiter01 = nullptr;
	Node* delimiter02 = nullptr;
	Node* cable = nullptr;
	Node* hookBlock = nullptr;
	Node* hook = nullptr;
	Node* plane = nullptr;
	Node* box01 = nullptr;
	Node* box02 = nullptr;
	Node* box03 = nullptr;
	Node* cabin = nullptr;

	// ------------------------------
	//		Mouse specifications
	// ------------------------------
	float mouseX, mouseY = 0.0f;

	// ------------------------------
	//		Methods
	// ------------------------------
	void initializeCameras();
	void initializeModel(List* renderList);
};

