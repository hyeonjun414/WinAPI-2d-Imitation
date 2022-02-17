#pragma once
class CCore
{
	//static CCore* _instance;

	//SINGLETON(CCore);
private:
	static CCore* _instance;
public:
	static CCore* getInst()
	{
		if (nullptr == _instance)
			_instance = new CCore;
		return _instance;
	}
	static void release()
	{
		if (nullptr != _instance)
		{
			delete _instance;
			_instance = nullptr;
		}
	}
private:
	CCore();
	~CCore();

public :
	void update(); // 게임 업데이트
	void render(); // 게임 그리기
};

