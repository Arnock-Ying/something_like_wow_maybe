#pragma once
#include <vector>
#include "basePlace.h"
#include "Headquarters.h"

class CityMap
{
private:
	bool onInit = false;
protected:
	std::vector<basePlace*> placeList;
	std::vector<Headquarters*> headquarters;
public:
	CityMap(int n);
	~CityMap();
	inline Headquarters* Header(int i) { return headquarters[i]; }

	/// <summary>
	/// *必须重载* 寻路函数，通过当前位置和目标位置寻找到下一步应该走到的位置
	/// </summary>
	/// <param name="nowPlace"> 指向当前位置的指针 </param>
	/// <param name="destination"> 目的地司令部 </param>
	/// <returns> 下一个位置 </returns>
	virtual basePlace* foundNextPlaceFromTo(basePlace* nowPlace, Headquarters* destination) = 0;
	/// <summary>
	/// 寻路函数，通过当前位置和目标司令部ID寻找到下一步应该走到的位置
	/// </summary>
	/// <param name="nowPlace"> 指向当前位置的指针 </param>
	/// <param name="destination"> 目的地司令部ID </param>
	/// <returns> 下一个位置 </returns>
	virtual basePlace* foundNextPlaceFromTo(basePlace* nowPlace, int destination);

	//virtual void foreachUpdata() = 0;
	//virtual void foreachHourStart() = 0;
	//virtual void foreachUpdataStart() = 0;
	//virtual void foreachUpdataEnd() = 0;
	//virtual void ResetMapState() = 0;
	//virtual void foreachMove() = 0;

	/// <summary>
	/// 判断是否只剩下某一个指挥部（某指挥部是否胜利）
	/// </summary>
	/// <returns> 获胜阵营ID，未获胜返回-2，同归于尽返回-1 </returns>
	virtual int onlyOnceHeader();

	void _panelInit();
	void _panelIpdata();

	/// <summary>
	/// 画板初始化
	/// </summary>
	virtual void PanelInit() {}

	/// <summary>
	/// 画板更新
	/// </summary>
	virtual void PanelUpdata() {}
};

