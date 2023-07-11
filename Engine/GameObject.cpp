#include "GameObject.h"

GameObject::GameObject() :IsDead_(false)
{
	
}

GameObject::GameObject(GameObject* parent, const std::string& name):IsDead_(false)
{

	pParent_ = parent;
	objectName_ = name;
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->DrawSub();
	}
}

void GameObject::UpdateSub()
{

	for (auto itr = childList_.begin(); itr != childList_.end();) {
		if ((*itr)->IsDead_) {
			(*itr)->ReleaseSub();
			delete* itr;
			itr = childList_.erase(itr);
		}
		else {
			itr++;
		}
	}

	Update();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->UpdateSub();
	}
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->ReleaseSub();
	}
}

void GameObject::KillMe()
{
	IsDead_ = true;
}
