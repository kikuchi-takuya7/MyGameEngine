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

	//�_�C�A���O�v���V�[�W��
	BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

	//�e��update�֐�
	void Dlg_Up_Update(int _changeX, int _changeZ);
	void Dlg_Down_Update(int _changeX, int _changeZ);
	void Dlg_Change_Update(int _changeX, int _changeZ);

	//���C���������Ă���isHit��true�ɂȂ��ĕύX�����ʒu��x,z���Ԃ����
	void CheckHitRay(bool &_isHit, int &_changeX, int &_changeZ);

	//�Z�[�u����
	void Save();

	void NameSave();

	void Load();

	void NewCreate();

	void NowFileLoad();


private:
	int hModel_[MAX_COLOR];

	DLGSTATE mode_;	//0:�グ��@1:������@2:��ނ�ς���
	COLOR select_; //���

	char fileName_[MAX_PATH];  //�t�@�C����������ϐ�

};