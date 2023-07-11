#pragma once

#include "Transform.h"
#include <list>
#include <string>

using std::string;
using std::list;
class GameObject
{
private:
	bool				IsDead_;

protected:
	list<GameObject*>	childList_;
	Transform			transform_;
	GameObject*			pParent_;
	string				objectName_;
	

public:
	GameObject();
	GameObject(GameObject* parent, const string& name);
	~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
	void DrawSub();
	void UpdateSub();
	void ReleaseSub();
	void KillMe();

	template<class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* P;
		P = new T(parent);
		P->Initialize();
		parent->childList_.push_back(P);
		return P;
	}
};