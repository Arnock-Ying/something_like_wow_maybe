#pragma once
#include <string>
#include "gameObject.h"
class baseWarrior;
class baseArms :public GameObject
{
public:
	/// <summary>
	/// *必须重载* 工厂函数，返回一个新new的arms的实例
	/// </summary>
	/// <returns></returns>
	virtual baseArms* FactionArm() = 0;
	baseArms* _factionArm(baseWarrior* w);

protected:
	int power = 0;
public:
	baseWarrior* Holder;
	baseArms() = default;

	/// <summary>
	/// *必须重载* 返回摧毁条件
	/// </summary>
	/// <returns></returns>
	virtual bool ifDestroy() = 0;
	/// <summary>
	/// 返回近战攻击力
	/// </summary>
	/// <returns></returns>
	virtual int getAttack() { return power; }

	/// <summary>
	/// 武器在近战被被使用时调用
	/// </summary>
	/// <param name="war"> 被攻击的敌人 </param>
	virtual void OnUsing(baseWarrior*) {}
	/// <summary>
	/// 每分钟（游戏刻）调用
	/// </summary>
	virtual void Updata() {}

	virtual std::string to_string() { return ""; }
};

