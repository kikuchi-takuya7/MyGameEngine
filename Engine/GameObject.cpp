#include "GameObject.h"

GameObject::GameObject() :IsDead_(false),pParent_(nullptr)
{
	
}

GameObject::GameObject(GameObject* parent, const std::string& name) :IsDead_(false), pParent_(nullptr)
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

	Update();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->UpdateSub();
	}

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
