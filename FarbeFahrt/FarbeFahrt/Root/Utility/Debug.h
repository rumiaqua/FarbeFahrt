# pragma once

# include <Dxlib.h>
# include "String.h"
# include <utility>

/// <summary>デバッグ情報</summary>
class Debug
{
private:

	/// <summary>コンストラクタ</summary>
	Debug();

	/// <summary>コピーコンストラクタ削除</summary>
	Debug(const Debug&) = delete;

	/// <summary>代入演算子削除</summary>
	Debug& operator = (const Debug&) = delete;

	/// <summary>単一インスタンスを返す</summary>
	static Debug& Instance();

public:

	/// <summary>デバッグ機能を有効にする</summary>
	static void SetEnabled(bool isEnabled);

	/// <summary>デバッグが有効かどうかを返す</summary>
	static bool IsEnabled();

	/// <summary>画面にデバッグ表示する</summary>
	template <typename ...Args>
	static void Print(const std::string& format, Args&& ...args)
	{
		if (!IsEnabled())
		{
			return;
		}
		printfDx(format.c_str(), std::forward<Args>(args)...);
	}

	/// <summary>画面にデバッグ表示したあと改行する</summary>
	template <typename ...Args>
	static void Println(const std::string& format, Args&& ...args)
	{
		if (!IsEnabled())
		{
			return;
		}
		Print(format, std::forward<Args>(args)...);
		printfDx("\n");
	}

	/// <summary>更新処理</summary>
	static void Update();

	/// <summary>毎フレームクリアするかどうかを設定する</summary>
	static void SetClear(bool isClear);

	/// <summary>毎フレームクリアするかどうかを返す</summary>
	static bool IsClear();

	/// <summary>デバッグ表示をクリアする</summary>
	static void Clear();

	/// <summary>メッセージボックスを表示する</summary>
	static void Show(const char* messsage, const char* caption, UINT style);

	/// <summary>フォントサイズを変更する</summary>
	static void ChangeFontSize(int fontSize);

private:

	bool m_isEnabled;

	bool m_isClear;

	int m_fontSize;
};
