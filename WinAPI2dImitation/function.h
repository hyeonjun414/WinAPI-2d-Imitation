#pragma once

class CGameObject;

void CreateObject(CGameObject* _pObj);
void DeleteObject(CGameObject* _pObj);
void ChangeScene(SCENE_TYPE _eSceneType);

template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}
	_vec.clear();
}