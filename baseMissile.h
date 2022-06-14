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
	/// ����Զ�̹���ʱ����
	/// </summary>
	/// <param name="city"> �����ִ�ĳ��� </param>
	virtual void Fire(basePlace*) {}

	/// <summary>
	/// *��������* ���ط���Զ�̹�����ʱ��
	/// </summary>
	/// <returns></returns>
	virtual int FireTime() = 0;

	/// <summary>
	/// Զ�̹������е���ʱ����
	/// </summary>
	/// <param name="war"> �ܹ����� </param>
	virtual void OnHart(baseWarrior*) {}
};

