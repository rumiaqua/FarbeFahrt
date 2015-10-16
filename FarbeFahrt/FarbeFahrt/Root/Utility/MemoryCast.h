# pragma once

/// <summary>メモリ構成を残したままキャストする</summary>
template <typename Cast, typename Base>
Cast& memory_cast(Base& base)
{
	return *reinterpret_cast<Cast*>(&base);
}

/// <summary>メモリ構成を残したままキャストする</summary>
template <typename Cast, typename Base>
const Cast& memory_cast(const Base& base)
{
	return *reinterpret_cast<const Cast*>(&base);
}

/// <summary>メモリ構成を残したままキャストする</summary>
template <typename Cast, typename Base>
Cast* memory_cast(Base* base)
{
	return reinterpret_cast<Cast*>(base);
}

/// <summary>メモリ構成を残したままキャストする</summary>
template <typename Cast, typename Base>
const Cast* memory_cast(const Base* base)
{
	return reinterpret_cast<const Cast*>(base);
}
