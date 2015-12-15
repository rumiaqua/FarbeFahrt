#include "Renderer.h"
#include <algorithm>
#include "Actor\Camera\Camera.h"

# include "Point2.h"
# include "Vector2.h"
# include "Math.h"

# include "Collision/IShape.h"

# include "Debug.h"

Renderer::Renderer()
{
	initDepthBuffer();
	loadShader();
	setFont();
}

Renderer::~Renderer()
{
	RemoveFontResourceEx("Resources/Font/cinecaption2.28.ttf", FR_PRIVATE, NULL);
}
void Renderer::setFont()
{
	if (AddFontResourceEx("Resources/Font/cinecaption2.28.ttf", FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理s
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
	m_fontData.fontHandle = CreateFontToHandle("しねきゃぷしょん", fontSize, 3, DX_FONTTYPE_ANTIALIASING_EDGE, -1, 2);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);

	ChangeFont("しねきゃぷしょん", DX_CHARSET_DEFAULT);

}
void Renderer::drawPrimitive(const IShape& shape) const
{
	if (!Debug::IsEnabled())
	{
		return;
	}
	m_primitives.push_back([&shape] () { shape.draw(); });
}
void Renderer::initDepthBuffer()
{
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_NOT_SEMITRANS_ONLY);
	SetDrawValidFloatTypeGraphCreateFlag(TRUE);
	SetCreateDrawValidGraphChannelNum(1);

	m_buffer.depthBuffer = MakeScreen(2048, 2048, FALSE);

	SetDrawValidFloatTypeGraphCreateFlag(FALSE);
	SetCreateDrawValidGraphChannelNum(4);
	SetCreateGraphColorBitDepth(32);
}
void Renderer::loadShader()
{
	m_shaderHandle.depthRecord_normal = LoadVertexShader("Resources/Shader/depthRecord_normal.vso");
	m_shaderHandle.depthRecord_skin = LoadVertexShader("Resources/Shader/depthRecord_skin.vso");
	m_shaderHandle.depthRecord_pixel = LoadPixelShader("Resources/Shader/depthRecord_pixel.pso");
	m_shaderHandle.render_normal = LoadVertexShader("Resources/Shader/render_normal.vso");
	m_shaderHandle.render_skin = LoadVertexShader("Resources/Shader/render_skin.vso");
	m_shaderHandle.render_pixel = LoadPixelShader("Resources/Shader/render_pixel.pso");

}
void Renderer::setModelData(const ContentMap& modelData)
{
	for (auto &data : modelData)
	{
		m_modelData.emplace(std::piecewise_construct,
			std::forward_as_tuple(data.first),
			std::forward_as_tuple(data.second.handle, -1, -1, 0.0f, 0.0f));
	}

}
void Renderer::setTextureData(const ContentMap& textureData)
{
	for (auto &data : textureData)
	{
		m_textureData.emplace(data.first, data.second.handle);
	}
}

// 深度描画？
void Renderer::drawDepth()
{
	Vector3 lightPosition = { 20.0f,120.0f,-70.0f };
	Vector3 lightTarget{ -45.0f,-30.0f,0.0f };
	SetDrawScreen(m_buffer.depthBuffer);
	SetBackgroundColor(255, 255, 255);
	// 描画ターゲットをクリア
	ClearDrawScreen();
	// 背景色を黒でクリア
	SetBackgroundColor(0, 0, 0);

	SetupCamera_Ortho(500.0f);
	SetCameraNearFar(1.0f, 500.0f);
	SetCameraPositionAndTarget_UpVecY(lightPosition, lightTarget);

	// 現在の設定を保持
	m_lightCamera.viewMatrix = GetCameraViewMatrix();
	m_lightCamera.projectionMatrix = GetCameraProjectionMatrix();

	// 自作シェーダーの使用開始
	MV1SetUseOrigShader(TRUE);
	// ピクセルシェーダーを指定
	SetUsePixelShader(m_shaderHandle.depthRecord_pixel);
	// 全モデルデータの表示
	for (auto&& model : m_modelData)
	{
		if (model.second.Use == false)
		{
			continue;
		}
		if (model.second.isSkinMesh)//スキンメッシュの影描画用
		{
			// スキンメッシュ用の頂点シェーダーを使用
			SetUseVertexShader(m_shaderHandle.depthRecord_skin);
		}
		//剛体メッシュの影描画用
		// そうでなければ
		else
		{
			// 剛体メッシュ用の頂点シェーダーを使用
			SetUseVertexShader(m_shaderHandle.depthRecord_normal);
		}
		// モデルの描画
		MV1DrawModel(model.second.modelHandle);
	}
	// 自作シェーダーの使用終了
	MV1SetUseOrigShader(FALSE);
	// 描画ターゲットを背面に変更
	SetDrawScreen(DX_SCREEN_BACK);
}
// モデルを影と一緒に描画
void Renderer::drawModelWithDepthShadow()
{
	// クリップ面の指定
	SetCameraNearFar(1.0f, 600.0f);
	// カメラのビュー行列を保存した行列に変更
	SetCameraPositionAndTarget_UpVecY(m_cameraData.pos, m_cameraData.terget);
	// 自作シェーダーの使用開始
	MV1SetUseOrigShader(TRUE);
	// ピクセルシェーダーを指定
	SetUsePixelShader(m_shaderHandle.render_pixel);
	// ビュー行列をシェーダーにセット
	SetVSConstFMtx(43, m_lightCamera.viewMatrix);
	// 透視射影行列をシェーダーにセット
	SetVSConstFMtx(47, m_lightCamera.projectionMatrix);

	// 影用深度記録画像をテクスチャ１にセット
	SetUseTextureToShader(1, m_buffer.depthBuffer);
	// 全モデルデータの描画
	for (auto& model : m_modelData)
	{
		if (model.second.Use == false)
		{
			continue;
		}
		if (model.second.isSkinMesh)//スキンメッシュの影描画用
		{
			// 
			// スキンメッシュ用の頂点シェーダーを使用
			SetUseVertexShader(m_shaderHandle.render_skin);
		}
		//剛体メッシュの影描画用
		// そうでなければ
		else
		{
			// 剛体メッシュ用の頂点シェーダーを使用
			SetUseVertexShader(m_shaderHandle.render_normal);
		}
		// モデルの描画
		MV1DrawModel(model.second.modelHandle);
		model.second.Use = false;
	}
	// 自作シェーダーの使用終了
	MV1SetUseOrigShader(FALSE);
	// テクスチャ１を無効にする
	SetUseTextureToShader(1, -1);
	// スロット43を初期化？
	ResetVSConstF(43, 8);
}
void Renderer::setDrawList(const std::string& name, int handle)
{
	drawList.push_back(std::make_pair(name, handle));
}
void Renderer::draw()
{
	// 現在の設定を保持
	m_cameraData.pos = GetCameraPosition();
	m_cameraData.terget = GetCameraTarget();
	// 深度の描画
	drawDepth();
	// 影の描画
	drawModelWithDepthShadow();

	// プリミティブの描画
	for (auto&& func : m_primitives)
	{
		func();
	}
	m_primitives.clear();

	// フォントの描画
	drawFont();
}
void Renderer::drawFont()
{
	// フォントハンドル
	int handle = m_fontData.fontHandle;
	// 文字色
	unsigned int color = GetColor(255, 255, 255);
	// 縁色
	int edge = GetColor(0, 0, 0);

	// 画面幅
	int windowWidth = getWindowSize().x;
	// 画面高さ
	int windowHeight = getWindowSize().y;

	for (auto&& data : m_fontData.buffer)
	{
		// テキストの長さ
		std::string::size_type size = data.length;
		// テキストの横幅
		int textWidth = GetDrawStringWidthToHandle(data.text.c_str(), data.text.length(), handle);
		// テキストの縦幅
		int textHeight = fontSize + 6;

		// x座標
		int x;
		switch (data.widthPlacement)
		{
		case WidthPlacement::Left:
			x = 0;
			break;
		case WidthPlacement::Right:
			x = windowWidth - textWidth;
			break;
		case WidthPlacement::Center:
			x = (windowWidth - textWidth) / 2.0f;
			break;
		}

		// y座標
		int y;
		switch (data.heightPlacement)
		{
		case HeightPlacement::Top:
			y = 0;
			break;
		case HeightPlacement::Bottom:
			y = windowHeight - textHeight;
			break;
		case HeightPlacement::Center:
			y = (windowHeight - textHeight) / 2.0f;
			break;
		}

		// 描画
		std::string renderingText = String::ToNarrow(String::ToWide(data.text).substr(0, data.length));
		DrawStringToHandle(x + data.x, y + data.y, renderingText.c_str(), color, handle, edge);
	}
	m_fontData.buffer.clear();
}
void Renderer::drawNormalModel(const std::string& name, const Vector3& position, const Matrix& rotation)
{
	const int &handle = m_modelData.at(name).modelHandle;
	MV1SetPosition(handle, position);
	MV1SetRotationMatrix(handle, rotation);
	m_modelData.at(name).Use = true;
}
void Renderer::refreshAnimParam(const std::string& name)
{
	auto& modeldata = m_modelData.at(name);
	modeldata.playAnim1 = -1;
	modeldata.playAnim2 = -1;
	modeldata.animPlayCount1 = 0.0f;
	modeldata.animPlayCount2 = 0.0f;

}
void Renderer::refreshAnimParam()
{
	for (auto&& model : m_modelData)
	{
		refreshAnimParam(model.first);
	}
}
void Renderer::drawSkinModel(const std::string& name, const Vector3& position,
	const Matrix& rotation, int animNumber, float frame, bool isBlend)
{
	//見辛いから後々関数分けする予定
	//サンプル丸パクリスペクト
	float animTotalTime;
	auto& modelData = m_modelData.at(name);
	modelData.isSkinMesh = true;

	if (animNumber != modelData.animNumber)//アニメーションが切り替わった時
	{
		modelData.animNumber = animNumber;
		if (modelData.playAnim2 != -1)
		{
			int result = MV1DetachAnim(modelData.modelHandle, modelData.playAnim2);
			modelData.playAnim2 = -1;
		}
		modelData.playAnim2 = modelData.playAnim1;
		modelData.animPlayCount2 = modelData.animPlayCount1;

		modelData.playAnim1 = MV1AttachAnim(modelData.modelHandle, modelData.animNumber);
		modelData.animPlayCount1 = 0.0f;
		modelData.animBlendRate = modelData.playAnim2 == -1 ? 1.0f : 0.0f;

	}

	if (modelData.animBlendRate < 1.0f)
	{
		modelData.animBlendRate += ANIM_BLEND_SPEED;
		if (modelData.animBlendRate > 1.0f)
		{
			modelData.animBlendRate = 1.0f;
		}
	}

	if (modelData.playAnim1 != -1)
	{
		animTotalTime = MV1GetAttachAnimTotalTime(modelData.modelHandle, modelData.playAnim1);
		modelData.animPlayCount1 = frame;
		if (modelData.animPlayCount1 >= animTotalTime)
		{
			modelData.animPlayCount1 = fmod(modelData.animPlayCount1, animTotalTime);
		}
		MV1SetAttachAnimTime(modelData.modelHandle, modelData.playAnim1, modelData.animPlayCount1);
		MV1SetAttachAnimBlendRate(modelData.modelHandle, modelData.playAnim1, modelData.animBlendRate);
	}
	if (modelData.playAnim2 != -1)
	{
		animTotalTime = MV1GetAttachAnimTotalTime(modelData.modelHandle, modelData.playAnim2);
		modelData.animPlayCount2 = frame;
		if (modelData.animPlayCount2 >= animTotalTime)
		{
			modelData.animPlayCount2 = fmod(modelData.animPlayCount2, animTotalTime);
		}
		MV1SetAttachAnimTime(modelData.modelHandle, modelData.playAnim2, modelData.animPlayCount2);
		MV1SetAttachAnimBlendRate(modelData.modelHandle, modelData.playAnim2, 1.0f - modelData.animBlendRate);
	}


	//現在のアニメーションを再生

	drawNormalModel(name, position, rotation);
}

void Renderer::setScale(const std::string& name, const Vector3& scale)
{
	MV1SetScale(m_modelData.at(name).modelHandle, scale);
}

void Renderer::drawSkinModel(const std::string& name, const Pose& pose, int animNumber, float t)
{
	//見辛いから後々関数分けする予定
	//サンプル丸パクリスペクト
	float animTotalTime;
	auto& modelData = m_modelData.at(name);
	modelData.isSkinMesh = true;
	if (animNumber != modelData.animNumber)//アニメーションが切り替わった時
	{
		modelData.animNumber = animNumber;
		if (modelData.playAnim2 != -1)
		{
			int result = MV1DetachAnim(modelData.modelHandle, modelData.playAnim2);
			modelData.playAnim2 = -1;
		}
		modelData.playAnim2 = modelData.playAnim1;
		modelData.animPlayCount2 = modelData.animPlayCount1;

		modelData.playAnim1 = MV1AttachAnim(modelData.modelHandle, modelData.animNumber);
		modelData.animPlayCount1 = 0.0f;
		modelData.animBlendRate = modelData.playAnim2 == -1 ? 1.0f : 0.0f;

	}

	float totalTime = MV1GetAttachAnimTotalTime(m_modelData.at(name).modelHandle, modelData.playAnim1);
	float frame = totalTime * t;

	if (modelData.animBlendRate < 1.0f)
	{
		modelData.animBlendRate += ANIM_BLEND_SPEED;
		if (modelData.animBlendRate > 1.0f)
		{
			modelData.animBlendRate = 1.0f;
		}
	}
	if (modelData.playAnim1 != -1)
	{
		animTotalTime = MV1GetAttachAnimTotalTime(modelData.modelHandle, modelData.playAnim1);
		modelData.animPlayCount1 = frame;
		if (modelData.animPlayCount1 >= animTotalTime)
		{
			modelData.animPlayCount1 = fmod(modelData.animPlayCount1, animTotalTime);
		}
		MV1SetAttachAnimTime(modelData.modelHandle, modelData.playAnim1, modelData.animPlayCount1);
		MV1SetAttachAnimBlendRate(modelData.modelHandle, modelData.playAnim1, modelData.animBlendRate);
	}
	if (modelData.playAnim2 != -1)
	{
		animTotalTime = MV1GetAttachAnimTotalTime(modelData.modelHandle, modelData.playAnim2);
		modelData.animPlayCount2 = frame;
		if (modelData.animPlayCount2 >= animTotalTime)
		{
			modelData.animPlayCount2 = fmod(modelData.animPlayCount2, animTotalTime);
		}
		MV1SetAttachAnimTime(modelData.modelHandle, modelData.playAnim2, modelData.animPlayCount2);
		MV1SetAttachAnimBlendRate(modelData.modelHandle, modelData.playAnim2, 1.0f - modelData.animBlendRate);
	}
	//現在のアニメーションを再生

	drawNormalModel(name, pose.position, pose.rotation);
}

void Renderer::drawTexture(const std::string& name, int x, int y, int cx, int cy, float width, float height, float angle) const
{
	DrawRotaGraph3(x, y, cx, cy, width, height,
		(double)angle, m_textureData.at(name), FALSE, FALSE);
}
void Renderer::drawTexture(const std::string& name, int x, int y)
{
	DrawGraph(x, y, m_textureData.at(name), TRUE);
}

void Renderer::drawTexture(const std::string& name, const AspectType& type)
{
	drawTexture(name, type, Vector2::Zero(), { 0.5f, 0.5f });
}
void Renderer::drawTexture(const std::string& name, const AspectType& type, const Vector2& position, const Vector2& center)
{
	int handle = m_textureData.at(name);
	Point2 size;
	GetGraphSize(handle, &size.x, &size.y);
	Vector2 textureSize = (Vector2)size;
	GetWindowSize(&size.x, &size.y);
	Vector2 windowSize = (Vector2)size;

	Vector2 ext;

	// 何もしない
	if (type == AspectType::None)
	{
		ext = Vector2::One();
	}
	// 画面に合わせて伸縮
	if (type == AspectType::Fit)
	{
		ext = windowSize / textureSize;
	}
	// 黒帯
	if (type == AspectType::LetterBox)
	{
		ext = windowSize / textureSize;
		ext.x = ext.y = Math::Min({ ext.x, ext.y });
	}
	// 拡大
	if (type == AspectType::Expand)
	{
		ext = windowSize / textureSize;
		ext.x = ext.y = Math::Max({ ext.x, ext.y });
	}

	Vector2 correctionSize = textureSize * ext;
	Vector2 pos = (windowSize - correctionSize) * center + position;

	DrawRotaGraph3F(pos.x, pos.y, 0.0f, 0.0f, ext.x, ext.y, 0.0, handle, TRUE, FALSE);
}
void Renderer::drawFont(const std::string& text)
{
	m_fontData.buffer.emplace_back(
		text,
		String::ToWide(text).length(),
		0, WidthPlacement::Left,
		0, HeightPlacement::Top);
}

void Renderer::drawFont(const std::string& text, int x, int y)
{
	m_fontData.buffer.emplace_back(
		text,
		String::ToWide(text).length(),
		x, WidthPlacement::Left,
		y, HeightPlacement::Top);
}

void Renderer::drawFontCenter(const std::string& text, int y)
{
	m_fontData.buffer.emplace_back(
		text,
		String::ToWide(text).length(),
		0, WidthPlacement::Center,
		y, HeightPlacement::Top);
}

void Renderer::drawFont(const std::string& text, int length, int x, const WidthPlacement& width, int y, const HeightPlacement& height)
{
	m_fontData.buffer.emplace_back(
		text,
		length,
		x, width,
		y, height);
}

Point2 Renderer::getTextureSize(const std::string& name)
{
	Point2 size;
	GetGraphSize(m_textureData.at(name), &size.x, &size.y);
	return size;
}

Point2 Renderer::getWindowSize()
{
	Point2 size;
	GetWindowSize(&size.x, &size.y);
	return size;
}

Vector2 Renderer::getCorrectionSize(const std::string& name, const AspectType& type)
{
	Vector2 textureSize(getTextureSize(name));
	Vector2 windowSize(getWindowSize());

	Vector2 ext;

	// 何もしない
	if (type != AspectType::None)
	{
		ext = Vector2::One();
	}
	// 画面に合わせて伸縮
	if (type == AspectType::Fit)
	{
		ext = windowSize / textureSize;
	}
	// 黒帯
	if (type == AspectType::LetterBox)
	{
		ext = windowSize / textureSize;
		ext.x = ext.y = Math::Min({ ext.x, ext.y });
	}
	// 拡大
	if (type == AspectType::Expand)
	{
		ext = windowSize / textureSize;
		ext.x = ext.y = Math::Max({ ext.x, ext.y });
	}

	return textureSize * ext;
}
