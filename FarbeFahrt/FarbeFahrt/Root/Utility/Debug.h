# pragma once

# include <Dxlib.h>

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
	static Debug& instance();

public:

	/// <summary>画面にデバッグ表示する</summary>
	template <typename ...Args>
	inline static void print(const char* format, Args&& ...args)
	{
		printfDx(format, std::forward<Args>(args)...);
	}

	/// <summary>画面にデバッグ表示したあと改行する</summary>
	template <typename ...Args>
	inline static void println(const char* format, Args&& ...args)
	{
		print(format, std::forward<Args>(args)...);
		printfDx("\n");
	}

	/// <summary>更新処理</summary>
	static void update();

	/// <summary>毎フレームクリアするかどうかを設定する</summary>
	static void setClear(bool isClear);

	/// <summary>毎フレームクリアするかどうかを返す</summary>
	static bool isClear();

	/// <summary>デバッグ表示をクリアする</summary>
	static void clear();

	/// <summary>メッセージボックスを表示する</summary>
	static void show(const char* messsage, const char* caption, UINT style);

	/// <summary>フォントサイズを変更する</summary>
	static void changeFontSize(int fontSize);

private:

	bool m_isClear;

	int m_fontSize;
};
