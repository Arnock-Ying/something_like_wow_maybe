#pragma once
/// <summary>
/// 所有需要接口的类的父类
/// 就是……父类，往里面装一些name，action之类的
/// 然后把函数接口也移过来
/// TODO->
/// </summary>

#include <iostream>
#include "faction.h"

class GameObject
{
public:
	static void Clear();
private:
	int action = true;
public:
	std::string name;

	inline void SetAction(bool a) { action = a; }
	inline bool Action() { return action; }

	virtual void show() {}

	void Log(std::string);
};

