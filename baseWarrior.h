#pragma once
#include "gameObject.h"
#include "baseArms.h"
#include "baseMissile.h"
#include <string>
#include <list>
#include <vector>

class basePlace;
class Headquarters;

class baseWarrior
	:public GameObject
{
public:
	bool ifWillGetReward = false;
private:
	static std::list<baseWarrior*> Warriors;
public:
	static void foreachUpdata();
	static void foreachHourStart();
	static void foreachHourEnd();
	static void foreachUpdataStart();
	static void foreachUpdataEnd();
	static void ResetMapState();
	static void foreachMove();
	static void foreachGetReward();

	static void Clear();
	static void Delete();
public:
	/// <summary>
	/// *必须重载* 返回默认血量的引用（记得为它设置静态变量）
	/// </summary>
	/// <returns></returns>
	virtual int& DefaultHealth() = 0;
	/// <summary>
	/// *必须重载* 返回默认攻击力的引用（记得为它设置静态变量）
	/// </summary>
	/// <returns></returns>
	virtual int& DefaultAttack() = 0;
	/// <summary>
	/// *必须重载* 工厂函数，返回一个指向新new的warrior对象的指针
	/// </summary>
	/// <returns>新new的warrior的指针</returns>
	virtual baseWarrior* factionWar() = 0;
	baseWarrior* _factionWar(Headquarters*);
	basePlace* getNextCity();
private:
	bool ifMoved = false;
protected:
	int health = 1;
	int power = 1;

	bool ifCounterattack = true;
	int campID = -1;
	int destID = -1;

	int maxArmsNum = 1;
public:
	std::vector<baseArms*> arms;

private:
	void afterHartWar(baseWarrior*);
public:
	basePlace* location;
public:

	baseWarrior() = default;
	~baseWarrior();

	inline void setHealth(int n) { health = n; }
	inline void setAttack(int n) { power = n; }
	inline int getHealth() { return health; }
	inline int getAttack() { return power; }
	inline int getCamp() { return campID; }
	inline int getmaxArmsNum() { return maxArmsNum; }

	/// <summary>
	/// 获取武器的总攻击力
	/// </summary>
	/// <returns></returns>
	int getArmAttack();
	/// <summary>
	/// 立刻摧毁自己（将自己在所在城市中删除并且标记为死亡
	/// </summary>
	void Destroy();

	/// <summary>
	/// 每个游戏刻调用
	/// </summary>
	virtual void Updata() {}
	/// <summary>
	/// 每个Updata调用前调用
	/// </summary>
	virtual void UpdataStart() {}
	/// <summary>
	/// 每个Updata调用后调用
	/// </summary>
	virtual void UpdataEnd() {}
	/// <summary>
	/// 每个小时结束时调用
	/// </summary>
	virtual void OnHourEnd() {}
	/// <summary>
	/// 每个小时开始时调用
	/// </summary>
	virtual void OnHourStart() {}
	/// <summary>
	/// 武士诞生时调用
	/// </summary>
	virtual void Start() {}
	/// <summary>
	/// 武士成功移动结束后调用
	/// </summary>
	virtual void OnMoved() {}
	/// <summary>
	/// 武士主动发动进攻前调用
	/// </summary>
	/// <param name="目标武士"></param>
	virtual void OnAttack(baseWarrior*) {}
	/// <summary>
	/// 武士击败敌人时调用
	/// </summary>
	/// <param name="击败的武士"></param>
	virtual void OnKillEnemy(baseWarrior*) {}
	/// <summary>
	/// 武士反击前调用
	/// </summary>
	/// <param name="反击目标武士"></param>
	virtual void OnCounterAttack(baseWarrior*) {}
	/// <summary>
	/// 武士死亡时调用
	/// </summary>
	/// <param name="击杀者"></param>
	virtual void OnDead(baseWarrior*) {}
	/// <summary>
	/// 武士被投掷物射击时调用
	/// </summary>
	/// <param name=""></param>
	virtual void OnBeShoot(baseMissile*) {}
	/// <summary>
	/// 武士获得战斗胜利时调用
	/// </summary>
	virtual void OnWinAttack() {}
	/// <summary>
	/// 在战斗结束后调用（winattack之后）
	/// </summary>
	virtual void OnAfterAttack() {}

	void _getHart(int, bool ifChangeAction = true);
	void _updata();
	void _move();
	void _attack(baseWarrior*);
	void _countattack(baseWarrior*);
	bool _addArms(baseArms*);
	void _beShoot(baseMissile*);

	void drawPut(std::string);
	std::string to_string();
};

