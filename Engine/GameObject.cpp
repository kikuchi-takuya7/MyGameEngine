#include "GameObject.h"

GameObject::GameObject()
{
	
}

GameObject::GameObject(GameObject* parent, const std::string& name)
{
	childList_ = { nullptr };

	pParent_ = parent;
	objectName_ = name;
}

GameObject::~GameObject()
{
}
