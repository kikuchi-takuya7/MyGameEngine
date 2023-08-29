#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller")
{
}

//�f�X�g���N�^
Controller::~Controller()
{
}

//������
void Controller::Initialize()
{
    //Camera::SetPosition(transform_.position_);
}

//�X�V
void Controller::Update()
{

    if (Input::IsKey(DIK_LEFTARROW)) {
        transform_.rotate_.y -= 1.0f;
    }
    if (Input::IsKey(DIK_RIGHTARROW)) {
        transform_.rotate_.y += 1.0f;
    }

    //���݂̈ʒu���x�N�g���^�ɕϊ�
    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    //1�t���[���̈ړ��x�N�g��
    XMVECTOR moveZ = { 0.0f, 0.0f, 0.1f, 0.0f }; //����0.1m

    //1�t���[���̈ړ��x�N�g��
    XMVECTOR moveX = { 0.1f, 0.0f, 0.0f, 0.0f }; //����0.1m

    //transform.rotate_.y�x��]������s����쐬
    XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //�ړ��x�N�g����ό` (��ԂƓ��������ɉ�]) ������
    moveZ = XMVector3TransformCoord(moveZ, rotY);

    //W�L�[�������ꂽ��ړ�
    if (Input::IsKey(DIK_W)) {
        //�ړ�
        pos += moveZ;

        //���ݒn���x�N�g�����炢����transform.position�ɖ߂�
        XMStoreFloat3(&transform_.position_, pos);

    }

    if (Input::IsKey(DIK_S)) {

        pos -= moveZ;

        XMStoreFloat3(&transform_.position_, pos);

    }
    
    if (Input::IsKey(DIK_A)) {

        //transform_.position_.x -= 0.1f;

        pos -= moveX;

        XMStoreFloat3(&transform_.position_, pos);
    }

    if (Input::IsKey(DIK_D)) {

        //transform_.position_.x += 0.1f;

        pos += moveX;

        XMStoreFloat3(&transform_.position_, pos);

    }

    //XMFLOAT3 camPos = transform_.position_;

    //Camera::SetPosition(camPos);
    Camera::SetTarget(transform_.position_);

    XMVECTOR vCam = { 0,5,-10,0 };
    //vCam = XMVector3TransformCoord(vCam, rotY);
    XMFLOAT3 camPos;
    XMFLOAT3 camTag;
    XMStoreFloat3(&camPos, pos + vCam);
    Camera::SetPosition(camPos);
}

//�`��
void Controller::Draw()
{
}

//�J��
void Controller::Release()
{
}