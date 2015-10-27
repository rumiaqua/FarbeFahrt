#pragma once
#include "Utility/Vector3.h"

struct CameraMatrix
{
	Vector3 targetPos;
	Vector3 currentPos;
	Vector3 targetRot;
	Vector3 currentRot;
};