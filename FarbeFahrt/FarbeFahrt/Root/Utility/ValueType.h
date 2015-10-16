# pragma once

class Point4;
class Vector4;

/// <summary>1�o�C�g��\��</summary>
using Byte = unsigned char;

/// <summary>9�r�b�g�T�C�Y��\��(0 ~ 255)</summary>
using Size8 = Byte;

/// <summary>16�r�b�g�T�C�Y��\��(0 ~ 65535)</summary>
using Size16 = unsigned short;

/// <summary>�T�C�Y��\��</summary>
using Size = unsigned int;

/// <summary>32�r�b�g�T�C�Y��\��(0 ~ 4294967295)</summary>
using Size32 = Size;

/// <summary>32�r�b�g�T�C�Y��\��(0 ~ 18446744073709551615)</summary>
using Size64 = unsigned long long;

/// <summary>(0~255)�̃J���[�R�[�h������RGBA�J���[��\��</summary>
using Color = Point4;

/// <summary>(0.0 ~ 1.0)�̃J���[�R�[�h������RGBA�J���[��\��</summary>
using ColorF = Vector4;
