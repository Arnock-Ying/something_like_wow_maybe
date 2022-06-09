#pragma once

#include <list>
#include <vector>

#include "gameObject.h"
#include "baseWarrior.h"
#include "baseMissile.h"

typedef baseWarrior* (*FactionWar)(Headquarters*);

class CityMap;

class basePlace
	:public GameObject
{
private:
	static std::list<basePlace*> Places;

public:
	static void foreachUpdata();
	static void foreachHourStart();
	static void foreachUpdataStart();
	static void foreachUpdataEnd();
	static void foreachHourEnd();
	static void foreachGetifAttack();
	static void ResetMapState();
	static void foreachAttack();
	static void foreachBackLive();
	static void foreachClear();

protected:
	int life = 0;
	int campfig = -1;

	int id;
	int ifAttack = false;
	int lastWinnerCamp = -1;
	/// <summary>
	/// 投掷物空间
	/// </summary>
	//std::vector<baseMissile*> missList;

	/// <summary>
	/// 拿来给存士兵的，自行分配空间，希望不要不识抬举(☆-ｖ-)
	/// </summary>*
	std::vector<baseWarrior*> warriors;

public:
	//static CityMap* cityMap;

public:
	basePlace();
	~basePlace();

	inline int getID()const { return id; }
	inline int getCamp()const { return campfig;; }
	inline std::vector<baseWarrior*>& Warriors() { return warriors; }
	inline int getLive()const { return life; }
	inline void addLive(int n) { life += n; }

	/// <summary>
	/// 在每小时开始时调用
	/// </summary>
	virtual void OnHourStart() {}
	/// <summary>
	/// 每分钟（游戏刻）调用
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
	/// 当城市中发生战斗时调用
	/// </summary>
	virtual void OnAttack() {}
	/// <summary>
	/// 将城市中的生命元搬运回占领司令部
	/// </summary>
	void BackLiveToHeader();
	

	void _attack();
	//virtual void _getMissile(baseMissile*);
	
	/// <summary>
	/// 判断warrior是否能够进入城市，防止溢出
	/// </summary>
	/// <param name="campID"> 即将进入的warrior所在阵营ID </param>
	/// <returns></returns>
	virtual bool ifHaveSeat(int) { return true; }
	/// <summary>
	/// 返回占领阵营ID，没有人或者有两方以上返回-1
	/// </summary>
	/// <returns></returns>
	virtual int getOccupier()const;
	/// <summary>
	/// *必须重载* 武士进入函数
	/// </summary>
	/// <param name="war"> 进入武士 </param>
	/// <returns>成功进入返回进入武士，否则返回nullptr</returns>
	virtual baseWarrior* enterWarrior(baseWarrior*) = 0;
	/// <summary>
	/// *必须重载* 武士退出函数
	/// </summary>
	/// <param name="war">退出武士</param>
	/// <returns>成功退出返回退出武士，否则返回nullptr</returns>
	virtual baseWarrior* exitWarrior(baseWarrior*) = 0;
	/// <summary>
	/// 清理战场（销毁尸体和尸体上的武器）后调用
	/// </summary>
	virtual void Clear() {};

	void _clear();
};

