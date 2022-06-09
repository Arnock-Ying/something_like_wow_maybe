#pragma once
/// <summary>
/// ������Ҫ�ӿڵ���ĸ���
/// ���ǡ������࣬������װһЩname��action֮���
/// Ȼ��Ѻ����ӿ�Ҳ�ƹ���
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

