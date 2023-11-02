#pragma once
#include "Engine/GameObject.h"
#include <Windows.h>
#include <stack>

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

	struct BackUpData {
		int x;
		int z;
		int height;
		COLOR color;
		BackUpData(int _x,int _z,int _h,COLOR _c){
			x = _x;
			z = _z;
			height = _h;
			color = _c;
		}
	};

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

	//���O��t���ĕۑ�
	void NameSave();

	//�t�@�C���̃��[�h�A�J��
	void Load();

	//�t�@�C���̐V�K�쐬
	void NewCreate();

	//���̃t�@�C�������[�h����B
	void NowFileLoad();

	//�ۑ��������֐���
	void SaveTheTable(std::ofstream& _ofs);
	void LoadTheTable(std::ifstream& _ofs);

	OPENFILENAME InitOpenFileName();

	//�ύX���ꂽ��ۑ�����
	void BackUpSave(int _x,int _z);

	//�ύX�����ɖ߂�
	void BackUpLoad();

	//�ύX�����ɖ߂��ꂽ�猳�̃f�[�^��ۑ�
	void RedoSave(int _x, int _z);

	//���ɖ߂��ꂽ���̃f�[�^�𕜌�����
	void RedoLoad();

	//redo�̗v�f����ɂ���
	void ClearRedo();

private:
	int hModel_[MAX_COLOR];

	DLGSTATE mode_;	//0:�グ��@1:������@2:��ނ�ς���
	COLOR select_; //���

	char fileName_[MAX_PATH];  //�t�@�C����������ϐ�

	//��߂��p�̃o�b�N�A�b�v
	std::stack<BackUpData> backUp_;

	//���ɖ߂��p�̃o�b�N�A�b�v
	std::stack<BackUpData> redo_;

};