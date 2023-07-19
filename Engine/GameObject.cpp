#include "GameObject.h"

GameObject::GameObject() :IsDead_(false),pParent_(nullptr)
{
	
}

GameObject::GameObject(GameObject* parent, const std::string& name) :IsDead_(false),pParent_(parent),objectName_(name)
{

	//pParent_ = parent;
	//objectName_ = name;
	if (pParent_ != nullptr) {
		this->transform_.pParent_ = &(parent->transform_);
	}
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
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else {
			itr++;
		}
	}
}

void GameObject::ReleaseSub()
{
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->ReleaseSub();
	}
	Release();
}

void GameObject::KillMe()
{
	IsDead_ = true;
}

GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_) {
		return(this); //自分が_objNameのオブジェクトだった
	}
	else {
		//for (auto itr = childList_.begin(); itr != childList_.end(); itr++) { //こっちはポインタアスタリスクが必要
		for(auto itr:childList_){ //こっちはアドレスそのまま行くからおっけ
			GameObject* obj = itr->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}
	}

	return nullptr;
}

/// <summary>
/// 再起呼び出しでRootJobを探してそのアドレスを返す関数
/// </summary>
/// <returns>RootJobのアドレス</returns>
GameObject* GameObject::GetRootJob()
{
	if(pParent_ == nullptr)
		return this;
	
	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string _objName)
{
	return GetRootJob()->FindChildObject(_objName);
}
