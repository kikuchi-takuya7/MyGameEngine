#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

//�e�X�g�V�[�����Ǘ�����N���X
class Enemy : public GameObject
{
	Fbx* pFbx_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Enemy(GameObject* parent);
	~Enemy();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};