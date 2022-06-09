#include "gameObject.h"
#include "basePlace.h"
#include "baseWarrior.h"

void GameObject::Clear()
{
	basePlace::foreachClear();
	baseWarrior::Clear();
}

void GameObject::Log(std::string s)
{
	wow::debug.Log(name + " : " + s);
}
