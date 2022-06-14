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
	/// *��������* Ѱ·������ͨ����ǰλ�ú�Ŀ��λ��Ѱ�ҵ���һ��Ӧ���ߵ���λ��
	/// </summary>
	/// <param name="nowPlace"> ָ��ǰλ�õ�ָ�� </param>
	/// <param name="destination"> Ŀ�ĵ�˾� </param>
	/// <returns> ��һ��λ�� </returns>
	virtual basePlace* foundNextPlaceFromTo(basePlace* nowPlace, Headquarters* destination) = 0;
	/// <summary>
	/// Ѱ·������ͨ����ǰλ�ú�Ŀ��˾�IDѰ�ҵ���һ��Ӧ���ߵ���λ��
	/// </summary>
	/// <param name="nowPlace"> ָ��ǰλ�õ�ָ�� </param>
	/// <param name="destination"> Ŀ�ĵ�˾�ID </param>
	/// <returns> ��һ��λ�� </returns>
	virtual basePlace* foundNextPlaceFromTo(basePlace* nowPlace, int destination);

	//virtual void foreachUpdata() = 0;
	//virtual void foreachHourStart() = 0;
	//virtual void foreachUpdataStart() = 0;
	//virtual void foreachUpdataEnd() = 0;
	//virtual void ResetMapState() = 0;
	//virtual void foreachMove() = 0;

	/// <summary>
	/// �ж��Ƿ�ֻʣ��ĳһ��ָ�Ӳ���ĳָ�Ӳ��Ƿ�ʤ����
	/// </summary>
	/// <returns> ��ʤ��ӪID��δ��ʤ����-2��ͬ���ھ�����-1 </returns>
	virtual int onlyOnceHeader();

	void _panelInit();
	void _panelIpdata();

	/// <summary>
	/// �����ʼ��
	/// </summary>
	virtual void PanelInit() {}

	/// <summary>
	/// �������
	/// </summary>
	virtual void PanelUpdata() {}
};

