#pragma once
#include "Engine/GameObject.h"

namespace {
	const int XSIZE{ 15 };
	const int ZSIZE{ 15 };
	enum COLOR {
		DEFAULT,
		BRINK,
		GRASS,
		SAND,
		WATER,
		MAX_COLOR
	};

	struct BrockType
	{
		COLOR color;
		int height;
	}table_[XSIZE][ZSIZE];

}



//�����V�[�����Ǘ�����N���X
class Stage : public GameObject
{
public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�u���b�N�̃Z�b�g
	void SetBlock(int _x, int _z, COLOR _type);

	void SetBlockHeght(int _x, int _z, int _height);

private:
	int hModel_[MAX_COLOR];

	//���̍��W�̈ʒu�̃^�C�v
	
	

};