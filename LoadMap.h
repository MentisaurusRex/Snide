#pragma once
#include <string>
class LoadMap
{
public:
	virtual void load() = 0;

	virtual void unload() = 0;
};

