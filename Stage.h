#pragma once
#include "Engine/GameObject.h"
#include <Windows.h>

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

	enum DLGSTATE {
		DLG_UP,
		DLG_DOWN,
		DLG_CHANGE,
		DLG_END
	};

	struct BrockType
	{
		COLOR color;
		int height;
	}table_[XSIZE][ZSIZE];

	struct DistList
	{
		float hitDist;
		int hitX;
		int hitZ;
	}distlist_;

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

	BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

	void Dlg_Up_Update(XMVECTOR vMouseFront, XMVECTOR vMouseBack);

	void Dlg_Down_Update(XMVECTOR vMouseFront, XMVECTOR vMouseBack);

	void Dlg_Change_Update(XMVECTOR vMouseFront, XMVECTOR vMouseBack);

private:
	int hModel_[MAX_COLOR];

	DLGSTATE mode_;	//0:�グ��@1:������@2:��ނ�ς���
	COLOR select_; //���

	//���̍��W�̈ʒu�̃^�C�v
};