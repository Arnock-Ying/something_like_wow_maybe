#pragma once
#include "baseArms.h"

class basePlace;
class baseWarrior;

class baseMissile :
	public baseArms
{
protected:
	int durable = 3;
	basePlace* hurtPlace;

public:
	basePlace* getHurtCity();

	void _fire();

	virtual int getAttack() { return 0; }
	virtual bool ifDestroy() { return durable == 0; }

	/// <summary>
	/// 发动远程攻击时调用
	/// </summary>
	/// <param name="city"> 攻击抵达的城市 </param>
	virtual void Fire(basePlace*) {}

	/// <summary>
	/// *必须重载* 返回发动远程攻击的时机
	/// </summary>
	/// <returns></returns>
	virtual int FireTime() = 0;

	/// <summary>
	/// 远程攻击击中敌人时调用
	/// </summary>
	/// <param name="war"> 受攻击者 </param>
	virtual void OnHart(baseWarrior*) {}
};

