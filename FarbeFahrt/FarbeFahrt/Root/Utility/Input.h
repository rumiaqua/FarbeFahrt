// -----------------------------------------------------------
// 作成者：堀
// -----------------------------------------------------------
# pragma once

# include <array>

/// <summary>入力クラス</summary>

class Input
{
private:

	/// <summary>コンストラクタ</summary>
	Input();

	/// <summary>コピーコンストラクタの削除</summary>
	Input(const Input&) = delete;

	/// <summary>コピー演算子の削除</summary>
	Input& operator = (const Input&) = delete;

private:

	/// <summary>単一のインスタンスを返す</summary>
	static Input& Instance();

public:

	/// <summary>キー情報の更新</summary>
	static void Update();

	/// <summary>押した瞬間かどうかを返す</summary>
	/// <param name="keyCode">DxLibのキーコード</param>
	static bool IsClicked(int keyCode);

	/// <summary>押されているかどうかを返す</summary>
	/// <param name="keyCode">DxLibのキーコード</param>
	static bool IsPressed(int keyCode);

	/// <summary>離した瞬間かどうかを返す</summary>
	/// <param name="keyCode">DxLibのキーコード</param>
	static bool IsReleased(int keyCode);

private:

	/// <summary>1フレーム前の入力情報</summary>
	std::array<char, 256> m_previousBuffer;

	/// <summary>現在の入力情報</summary>
	std::array<char, 256> m_currentBuffer;
};
