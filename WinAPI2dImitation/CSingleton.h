#pragma once


#define SINGLETON(CLASS)				\
private:								\
	static CLASS* _instance;			\
public:									\
	static CLASS* getInst()				\
	{									\
		if (nullptr == _instance)		\
			_instance = new CLASS;		\
		return _instance;				\
	}									\
	static void release() 				\
	{									\
		if (nullptr != _instance)		\
		{								\
			delete _instance;			\
			_instance = nullptr;		\
		}								\
	}									\
private:								\
	CLASS();							\
	~CLASS();
