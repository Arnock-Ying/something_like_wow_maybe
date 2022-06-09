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
	/// Ͷ����ռ�
	/// </summary>
	//std::vector<baseMissile*> missList;

	/// <summary>
	/// ��������ʿ���ģ����з���ռ䣬ϣ����Ҫ��ʶ̧��(��-��-)
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
	/// ��ÿСʱ��ʼʱ����
	/// </summary>
	virtual void OnHourStart() {}
	/// <summary>
	/// ÿ���ӣ���Ϸ�̣�����
	/// </summary>
	virtual void Updata() {}
	/// <summary>
	/// ÿ��Updata����ǰ����
	/// </summary>
	virtual void UpdataStart() {}
	/// <summary>
	/// ÿ��Updata���ú����
	/// </summary>
	virtual void UpdataEnd() {}
	/// <summary>
	/// ÿ��Сʱ����ʱ����
	/// </summary>
	virtual void OnHourEnd() {}
	/// <summary>
	/// �������з���ս��ʱ����
	/// </summary>
	virtual void OnAttack() {}
	/// <summary>
	/// �������е�����Ԫ���˻�ռ��˾�
	/// </summary>
	void BackLiveToHeader();
	

	void _attack();
	//virtual void _getMissile(baseMissile*);
	
	/// <summary>
	/// �ж�warrior�Ƿ��ܹ�������У���ֹ���
	/// </summary>
	/// <param name="campID"> ���������warrior������ӪID </param>
	/// <returns></returns>
	virtual bool ifHaveSeat(int) { return true; }
	/// <summary>
	/// ����ռ����ӪID��û���˻������������Ϸ���-1
	/// </summary>
	/// <returns></returns>
	virtual int getOccupier()const;
	/// <summary>
	/// *��������* ��ʿ���뺯��
	/// </summary>
	/// <param name="war"> ������ʿ </param>
	/// <returns>�ɹ����뷵�ؽ�����ʿ�����򷵻�nullptr</returns>
	virtual baseWarrior* enterWarrior(baseWarrior*) = 0;
	/// <summary>
	/// *��������* ��ʿ�˳�����
	/// </summary>
	/// <param name="war">�˳���ʿ</param>
	/// <returns>�ɹ��˳������˳���ʿ�����򷵻�nullptr</returns>
	virtual baseWarrior* exitWarrior(baseWarrior*) = 0;
	/// <summary>
	/// ����ս��������ʬ���ʬ���ϵ������������
	/// </summary>
	virtual void Clear() {};

	void _clear();
};

