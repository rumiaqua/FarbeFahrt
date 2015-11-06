#include "CameraMatrix.h"
#include "Utility/Math.h"

namespace
{
	// ‰½•b‚©‚¯‚Ä‘JˆÚ‚·‚é‚©
	static const float Second = 1.0f;
}

CameraMatrix::CameraMatrix()
{
}

void CameraMatrix::update()
{
	t += 1 / (60.0f * Second);
	t = t > 1.0f ? 1.0f : t;
}

void CameraMatrix::setCameraMatrix(Vector3 targetPos, Vector3 targetRot)
{
	m_currentPos = targetPos;
	timeReset();
	m_currentRot = targetRot;
	m_targetPos = targetPos;
	m_targetRot = targetRot;

	m_pos.SetBegin(m_currentPos);
	m_pos.SetEnd(m_targetPos);
	m_rot.SetBegin(m_currentRot);
	m_rot.SetEnd(m_targetRot);
}

void CameraMatrix::setCameraMatrix(Vector3 targetPos, Vector3 targetRot, Vector3 currentPos, Vector3 currentRot, bool resetFlag)
{
	m_currentPos = currentPos;
	if (resetFlag)
	{
		timeReset();
	}
	m_currentRot = currentRot;
	m_targetPos = targetPos;
	m_targetRot = targetRot;

	m_pos.SetBegin(m_currentPos);
	m_pos.SetEnd(m_targetPos);
	m_rot.SetBegin(m_currentRot);
	m_rot.SetEnd(m_targetRot);
}

Vector3 CameraMatrix::getTargetPos()
{
	return m_targetPos;
}

Vector3 CameraMatrix::getTargetRot()
{
	return m_targetRot;
}

Vector3 CameraMatrix::getPos()
{
	return m_pos.Lerp(static_cast<float>(Math::sin(Math::HalfPi * t)));
}

Vector3 CameraMatrix::getCurrentPos()
{
	return m_currentPos;
}

Vector3 CameraMatrix::getCurrentRot()
{
	return m_currentRot;
}

Vector3 CameraMatrix::getRot()
{
	return m_rot.Lerp(static_cast<float>(::sin(Math::HalfPi * t)));
}

bool CameraMatrix::hadFinished()
{
	return t >= 1;
}

float CameraMatrix::getTime()
{
	return t;
}

void CameraMatrix::timeReset()
{
	t = 0;
}
