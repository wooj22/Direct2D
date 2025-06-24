#pragma once
#include <d2d1_1.h>
#include <vector>
#include "ITransform.h"
#include "TransformSystem.h"

/* [Transform Component]
* D2D1::MATRIX_3X2_F : 2D ��ȯ(�̵�, ȸ��, ������, ����)�� ǥ���ϴ� 3*2 ���
* �� ����� �̿��Ͽ� ������Ʈ�� ��ȯ�� ����ϴ� ������Ʈ�̴�.
* ������Ʈ ������ Transform System�� ��ϵǾ� dirty���Ͽ� ���� matrix�� ��� ����Ѵ�.

// position ��� ���
* World = local * parent->world
* Screen = world * camera �����

// Uniny Style Screen position
* ��ǥ�� - �߾� (0,0), ������(-, +), ������ �Ʒ�(+, -)
* D2D���� ����Ƽ ��ǥ��ó�� ����Ϸ��� �ļ��� �ʿ���
* Screen = renderMatrix * world * camera ����� * unity matrix
* unity matrix�� �߽� �̵��� y ������ ���� ��İ��� ������ �ִ�.
* renderMatrix�� unity matrix�� �����ϱ� ���� y scale�� -1�� �� ���
* transform ����� �����ϸ� �ڽı��� ���� ������ ��ġ�� ������ ���꿡�� ����ؾ��Ѵ�.

// Dirty ����
* transform�� ���濡 ���� flag�� Ȱ���Ͽ�
* �� �����Ӹ��� ���ʿ��ϰ� ����� �ٽ� ������� �ʵ��� �ϴ� ���
*/

class Transform : public ITransform
{
private:
    // transform
    D2D1_POINT_2F position;
    float rotation;
    D2D1_POINT_2F scale;

    // parent, 
    Transform* parent = nullptr;
    std::vector<Transform*> children;

    // this matrix
    D2D1::Matrix3x2F localMatrix;
    D2D1::Matrix3x2F worldMatrix;
    D2D1::Matrix3x2F screenMatrix;

    bool isLocalDirty = true;
    bool isWorldDirty = true;

public:
    // matrix
    static D2D1::Matrix3x2F cameraInversMatrix;   // ����, screen size �ʿ�
    static D2D1::Matrix3x2F unityMatrix;          // ����, screen size �ʿ�
    static D2D1::Matrix3x2F renderMatrix;         // ����

    // camera ����� set
    static void SetCameraMatrix(const D2D1::Matrix3x2F& cameraMatrix)
    {
        D2D1::Matrix3x2F invert = cameraMatrix;
        invert.Invert();
        cameraInversMatrix = invert;
    }

public:
    Transform() : position{ 0.0f, 0.0f }, rotation(0.0f), scale{ 1.0f, 1.0f }, parent(nullptr) 
    {
        localMatrix = D2D1::Matrix3x2F::Identity();
        TransformSystem::Get().Regist(this);
    }
    ~Transform() override { TransformSystem::Get().Unregist(this); }

    // component
    void OnEnable() override;
    void OnDestroy() override;
    void Update() override;

public:
    // parent, children
    void SetParent(Transform* newParent);
    void RemoveChild(Transform* child);
    void MarkWorldDirty();

    // set
    void SetPosition(float x, float y);
    void SetRotation(float angle);
    void SetScale(float scaleX, float scaleY);
    void ResetTransform();

    // add
    void AddPosition(float x, float y);
    void AddRotation(float angle);
    void AddScale(float scaleX, float scaleY);

    // get
    D2D1_POINT_2F GetPosition() const { return position; }
    float GetRotation() const { return rotation; }
    D2D1_POINT_2F GetScale() const { return scale; }

    //  matrix
    void MakeLocalMatrix();
    void MakeWorldMatrix();
    void MakeScreenMatrix();

    //  matrix get
    const D2D1::Matrix3x2F& GetLocalMatrix() { return localMatrix; }
    const D2D1::Matrix3x2F& GetWorldMatrix(){ return worldMatrix; }
    const D2D1::Matrix3x2F& GetScreenMatrix() { return screenMatrix; }
};