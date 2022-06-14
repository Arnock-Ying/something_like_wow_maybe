#pragma once
#include<easyx.h>
#include<windows.h>
#include<fstream>
#include<time.h>

namespace api {

	extern int Gui_x, Gui_y;
	extern float DPIx, DPIy;


	bool inipretreatment();

	class Image//图片 含蒙版
	{
	public:
		int state;			//状态
		IMAGE image, imageMask;			//图片 蒙版图片
		friend class Model;

		void GetImage(std::fstream& Message)//从文件中获取图片
		{
			int hight, weight, size;
			std::string midAddress;
			wchar_t* buffer;
			Message >> state;
			Message >> midAddress >> weight >> hight;
			size = midAddress.length();
			buffer = new wchar_t[size + 1];
			MultiByteToWideChar(CP_ACP, 0, midAddress.c_str(), size, buffer, size * 2);
			buffer[size] = 0;
			loadimage(&image, buffer, weight, hight);
			delete[] buffer;
			if (state == 1)
			{
				Message >> midAddress >> weight >> hight;
				size = midAddress.length();
				buffer = new wchar_t[size + 1];
				MultiByteToWideChar(CP_ACP, 0, midAddress.c_str(), size, buffer, size * 2);
				buffer[size] = 0;
				loadimage(&imageMask, buffer, weight, hight);
				delete[] buffer;
			}
		}

		void Put(int x, int y)
		{
			if (state == 1)
			{
				putimage(x, y, &imageMask, NOTSRCERASE);
				putimage(x, y, &image, SRCINVERT);
			}
			else
			{
				putimage(x, y, &image);
			}
		}
	};

	class Model//模型
	{
	private:
		int ImageNumber;		//组成模型的图片
		Image** model;
		int* x, * y;			//在模型中的偏移值
	public:
		void GetImage(std::fstream& in, Image* i)//获取图片指针
		{
			int midI, midX;
			in >> ImageNumber;
			model = new Image * [ImageNumber];
			x = new int[ImageNumber];
			y = new int[ImageNumber];
			for (midI = 0; midI < ImageNumber; midI++)
			{
				in >> midX >> x[midI] >> y[midI];
				model[midI] = &i[midX];
			}
		}
		void PutModel(int& PCx, int& PCy)//绘制图片
		{
			int midI;
			for (midI = 0; midI < ImageNumber; midI++)
			{
				model[midI]->Put(PCx + x[midI], PCy + y[midI]);
			}
		}
		~Model()
		{
			if (ImageNumber > 0)
			{
				delete[] model;
				delete[] x;
				delete[] y;
			}
		}
	};

	class Animation
	{			//动画
	private:
		int ModelNumber;		//模型
		Model** model;
	public:
		friend class assistAnimation;
		Model* GetModel(int i)//返回单个模型
		{
			return model[i];
		}
		int GetLong()//获取模型数量
		{
			return ModelNumber;
		}
		void GetAni(std::fstream& in, Model* mod)//获取动画
		{
			int midI, midX;
			in >> ModelNumber;
			model = new Model * [ModelNumber];
			for (midI = 0; midI < ModelNumber; midI++)
			{
				in >> midX;
				model[midI] = &mod[midX];
			}
		}
		~Animation()
		{
			if (ModelNumber > 0)
			{
				delete[] model;
			}
		}
	};
	class assistAnimation//辅助管理动画
	{
	private:
		Animation* ani;
		int state;
		int* x, * y;
	public:
		assistAnimation()
		{
			ani = 0;
			state = 0;
			x = y = 0;
		}
		Animation* GetAni()
		{
			return ani;
		}
		void SetAnimation(Animation* animation)//建立动画
		{
			if (x != 0)
			{
				delete[] x;
			}
			if (y != 0)
			{
				delete[] y;
			}
			int midI = animation->GetLong();
			ani = animation;
			x = new int[midI];
			y = new int[midI];
		}
		void ReAnimation()//重置动画
		{
			state = 0;
		}
		void NewXY(int* midX = 0, int* midY = 0)//重新设置XY参数
		{
			int midJ = ani->GetLong();
			if (midX == 0 && midY == 0)
			{
				memset(x, 0, 4 * midJ);
				memset(y, 0, 4 * midJ);
				return;
			}
			for (int midI = 0; midI < midJ; midI++)
			{
				x[midI] = midX[midI];
				y[midI] = midY[midI];
			}
		}
		void PutAnimation()//绘制动画
		{
			if (state == ani->GetLong())
			{
				state = 0;
			}
			(ani->GetModel(state))->PutModel(x[state], y[state]);
			state++;
		}
	};

	class BackImageMan//背景图片管理
	{
	private:
		int BackImageNumber;
		IMAGE* Images;

		int state;
	public:
		void SetImage(std::string na)//获取所有图片
		{
			std::string midName;
			wchar_t* buffer;
			int size, midI;
			std::fstream in;
			in.open(na);
			in >> BackImageNumber;
			Images = new IMAGE[BackImageNumber];
			for (midI = 0; midI < BackImageNumber; midI++)
			{
				in >> midName;
				size = midName.length();
				buffer = new wchar_t[size + 1];
				MultiByteToWideChar(CP_ACP, 0, midName.c_str(), size, buffer, size * 2);
				buffer[size] = 0;
				loadimage(&Images[midI], buffer, Gui_x, Gui_y);
				Resize(&Images[midI], Gui_x, Gui_y);
				delete[] buffer;
			}
		}
		void SetName(const char* na)//重载 获取
		{
			SetImage(na);
		}
		void SetName(std::string na)//重载 获取
		{
			SetImage(na);
		}
		void SetState(int sta = 0)//设置状态
		{
			state = sta;
		}
		void PutImage()//打印背景
		{
			putimage(0, 0, &Images[state]);
		}
		~BackImageMan()
		{
			if (BackImageNumber > 0)
			{
				delete[] Images;
			}
		}
	};

	extern BackImageMan BackImageManage;

	extern char midCharAdd[512];
	extern std::string midStringAdd;
}