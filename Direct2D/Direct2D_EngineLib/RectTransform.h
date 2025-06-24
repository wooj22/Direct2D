#pragma once
#include <d2d1_1.h>
#include "ITransform.h"
#include "TransformSystem.h"

/*[RectTransform Componenet]
* UI ���ӿ�����Ʈ ���� Transform ������Ʈ�� 
* ī�޶��� ������ ���� �ʰ� �׻� ������ ȭ�� ��ǥ�� ����Ѵ�.
* ������Ʈ ������ Transform System�� ��ϵǾ� dirty���Ͽ� ���� matrix�� ��� ����Ѵ�.
* �ϴ� �θ� ���� ����� �ȸ������.
*/

class RectTransform : public ITransform
{
private:
    // rect transform
    D2D1_POINT_2F position = { 0, 0 };     // UI ��ġ (��ũ�� �߽� ����)
    D2D1_SIZE_F size = { 100, 100 };       // UI ũ��
    D2D1_POINT_2F pivot = { 0.5f, 0.5f };  // �ǹ� (0~1)

    // this matrix
    D2D1::Matrix3x2F screenMatrix = D2D1::Matrix3x2F::Identity();
    bool isDirty = true;

public:
    RectTransform() { TransformSystem::Get().Regist(this); }
    ~RectTransform() override { TransformSystem::Get().Unregist(this); }

    // component
    void OnEnable() override;
    void OnDestroy() override;
    void Update() override;

public:
    // set
    void SetPosition(float x, float y);
    void SetSize(float w, float h);
    void SetPivot(float x, float y);

    // get
    D2D1_SIZE_F GetSize() const { return size; }
    D2D1_POINT_2F GetPosition() const { return position; }
    D2D1_POINT_2F GetPivot() const { return pivot; }

    
private:
    // matrix
    void MakeScreenMatrix();

public:
    //  matrix get
    const D2D1::Matrix3x2F& GetScreenMatrix() const { return screenMatrix; }
};
