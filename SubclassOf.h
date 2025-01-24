#pragma once
#include "Macro.h"

template <typename Type>
class SubclassOf
{
	Type* objectRef;

public:
	FORCEINLINE Type GetObject() const
	{
		return *objectRef;
	}

public:
	SubclassOf(const Type& _objectRef)
	{
		objectRef = new Type(_objectRef);
	}
	SubclassOf(const Type* _objectRef)
	{
		objectRef = new Type(*_objectRef);
	}
	SubclassOf(const SubclassOf<Type>& _other)
	{
		objectRef = new Type(*_other.objectRef);
	}
	~SubclassOf()
	{
		delete objectRef;
	}
};