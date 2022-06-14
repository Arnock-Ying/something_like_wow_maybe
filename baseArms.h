#pragma once
#include <string>
#include "gameObject.h"
class baseWarrior;
class baseArms :public GameObject
{
public:
	/// <summary>
	/// *��������* ��������������һ����new��arms��ʵ��
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
	/// *��������* ���شݻ�����
	/// </summary>
	/// <returns></returns>
	virtual bool ifDestroy() = 0;
	/// <summary>
	/// ���ؽ�ս������
	/// </summary>
	/// <returns></returns>
	virtual int getAttack() { return power; }

	/// <summary>
	/// �����ڽ�ս����ʹ��ʱ����
	/// </summary>
	/// <param name="war"> �������ĵ��� </param>
	virtual void OnUsing(baseWarrior*) {}
	/// <summary>
	/// ÿ���ӣ���Ϸ�̣�����
	/// </summary>
	virtual void Updata() {}

	virtual std::string to_string() { return ""; }
};

