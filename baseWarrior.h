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
	/// *��������* ����Ĭ��Ѫ�������ã��ǵ�Ϊ�����þ�̬������
	/// </summary>
	/// <returns></returns>
	virtual int& DefaultHealth() = 0;
	/// <summary>
	/// *��������* ����Ĭ�Ϲ����������ã��ǵ�Ϊ�����þ�̬������
	/// </summary>
	/// <returns></returns>
	virtual int& DefaultAttack() = 0;
	/// <summary>
	/// *��������* ��������������һ��ָ����new��warrior�����ָ��
	/// </summary>
	/// <returns>��new��warrior��ָ��</returns>
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
	/// ��ȡ�������ܹ�����
	/// </summary>
	/// <returns></returns>
	int getArmAttack();
	/// <summary>
	/// ���̴ݻ��Լ������Լ������ڳ�����ɾ�����ұ��Ϊ����
	/// </summary>
	void Destroy();

	/// <summary>
	/// ÿ����Ϸ�̵���
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
	/// ÿ��Сʱ��ʼʱ����
	/// </summary>
	virtual void OnHourStart() {}
	/// <summary>
	/// ��ʿ����ʱ����
	/// </summary>
	virtual void Start() {}
	/// <summary>
	/// ��ʿ�ɹ��ƶ����������
	/// </summary>
	virtual void OnMoved() {}
	/// <summary>
	/// ��ʿ������������ǰ����
	/// </summary>
	/// <param name="Ŀ����ʿ"></param>
	virtual void OnAttack(baseWarrior*) {}
	/// <summary>
	/// ��ʿ���ܵ���ʱ����
	/// </summary>
	/// <param name="���ܵ���ʿ"></param>
	virtual void OnKillEnemy(baseWarrior*) {}
	/// <summary>
	/// ��ʿ����ǰ����
	/// </summary>
	/// <param name="����Ŀ����ʿ"></param>
	virtual void OnCounterAttack(baseWarrior*) {}
	/// <summary>
	/// ��ʿ����ʱ����
	/// </summary>
	/// <param name="��ɱ��"></param>
	virtual void OnDead(baseWarrior*) {}
	/// <summary>
	/// ��ʿ��Ͷ�������ʱ����
	/// </summary>
	/// <param name=""></param>
	virtual void OnBeShoot(baseMissile*) {}
	/// <summary>
	/// ��ʿ���ս��ʤ��ʱ����
	/// </summary>
	virtual void OnWinAttack() {}
	/// <summary>
	/// ��ս����������ã�winattack֮��
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

