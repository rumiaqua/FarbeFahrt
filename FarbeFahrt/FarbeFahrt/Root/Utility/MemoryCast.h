# pragma once

/// <summary>�������\�����c�����܂܃L���X�g����</summary>
template <typename Cast, typename Base>
Cast& memory_cast(Base& base)
{
	return *reinterpret_cast<Cast*>(&base);
}

/// <summary>�������\�����c�����܂܃L���X�g����</summary>
template <typename Cast, typename Base>
const Cast& memory_cast(const Base& base)
{
	return *reinterpret_cast<const Cast*>(&base);
}

/// <summary>�������\�����c�����܂܃L���X�g����</summary>
template <typename Cast, typename Base>
Cast* memory_cast(Base* base)
{
	return reinterpret_cast<Cast*>(base);
}

/// <summary>�������\�����c�����܂܃L���X�g����</summary>
template <typename Cast, typename Base>
const Cast* memory_cast(const Base* base)
{
	return reinterpret_cast<const Cast*>(base);
}
