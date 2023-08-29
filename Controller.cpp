#include "Controller.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//コンストラクタ
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller")
{
}

//デストラクタ
Controller::~Controller()
{
}

//初期化
void Controller::Initialize()
{
    //Camera::SetPosition(transform_.position_);
}

//更新
void Controller::Update()
{

    if (Input::IsKey(DIK_LEFTARROW)) {
        transform_.rotate_.y -= 1.0f;
    }
    if (Input::IsKey(DIK_RIGHTARROW)) {
        transform_.rotate_.y += 1.0f;
    }

    //現在の位置をベクトル型に変換
    XMVECTOR pos = XMLoadFloat3(&transform_.position_);

    //1フレームの移動ベクトル
    XMVECTOR moveZ = { 0.0f, 0.0f, 0.1f, 0.0f }; //奥に0.1m

    //1フレームの移動ベクトル
    XMVECTOR moveX = { 0.1f, 0.0f, 0.0f, 0.0f }; //横に0.1m

    //transform.rotate_.y度回転させる行列を作成
    XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //移動ベクトルを変形 (洗車と同じ向きに回転) させる
    moveZ = XMVector3TransformCoord(moveZ, rotY);

    //Wキーが押されたら移動
    if (Input::IsKey(DIK_W)) {
        //移動
        pos += moveZ;

        //現在地をベクトルからいつものtransform.positionに戻す
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

//描画
void Controller::Draw()
{
}

//開放
void Controller::Release()
{
}