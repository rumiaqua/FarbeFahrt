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

	/// <summary>画面にデバッグ表示する</summary>
	template <typename ...Args>
	inline static void Print(const String& format, Args&& ...args)
	{
		printfDx(format.toNarrow().c_str(), std::forward<Args>(args)...);
	}

	/// <summary>画面にデバッグ表示したあと改行する</summary>
	template <typename ...Args>
	inline static void Println(const String& format, Args&& ...args)
	{
		Print(format.toNarrow().c_str(), std::forward<Args>(args)...);
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

	bool m_isClear;

	int m_fontSize;
};
