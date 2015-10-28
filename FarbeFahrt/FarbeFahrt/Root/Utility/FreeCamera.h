# pragma once

# include "Vector3.h"

/// <summary>自由なカメラ移動をサポートするカメラクラス</summary>
class FreeCamera
{
public:

	FreeCamera();

public:

	/// <summary>カメラの座標を指定する</summary>
	/// <param name="position">座標</param>
	void setPosition(const Vector3& position);

	/// <summary>カメラの方向を指定する</summary>
	/// <param name="direction">方向</param>
	void setDirection(const Vector3& direction);

	/// <summary>カメラを移動させる</summary>
	/// <param name="translation">移動量</param>
	void move(const Vector3& translation);

	/// <summary>カメラを回転させる</summary>
	/// <param name="axis">回転軸</param>
	/// <param name="angle">回転量</param>
	void rotate(const Vector3& axis, double angle);

	/// <summary>カメラに指定座標を見させる</summary>
	/// <param name="target">注視点</param>
	void lookAt(const Vector3& target);

	/// <summary>設定を反映する</summary>
	void apply() const;

public:

	/// <summary>カメラから見た右方向ベクトルを返す</summary>
	Vector3 right() const;

	/// <summary>カメラから見た上方向ベクトルを返す</summary>
	Vector3 up() const;

	/// <summary>カメラから見た前方向ベクトルを返す</summary>
	Vector3 forward() const;

private:

	Vector3 m_position;

	Vector3 m_direction;
};
