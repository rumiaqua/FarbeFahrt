# pragma once

class Point4;
class Vector4;

/// <summary>1バイトを表す</summary>
using Byte = unsigned char;

/// <summary>9ビットサイズを表す(0 ~ 255)</summary>
using Size8 = Byte;

/// <summary>16ビットサイズを表す(0 ~ 65535)</summary>
using Size16 = unsigned short;

/// <summary>サイズを表す</summary>
using Size = unsigned int;

/// <summary>32ビットサイズを表す(0 ~ 4294967295)</summary>
using Size32 = Size;

/// <summary>32ビットサイズを表す(0 ~ 18446744073709551615)</summary>
using Size64 = unsigned long long;

/// <summary>(0~255)のカラーコードを持つRGBAカラーを表す</summary>
using Color = Point4;

/// <summary>(0.0 ~ 1.0)のカラーコードを持つRGBAカラーを表す</summary>
using ColorF = Vector4;
