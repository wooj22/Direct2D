#pragma once
#include <d2d1_1.h>
#include "ITransform.h"
#include "TransformSystem.h"

/*[RectTransform Componenet]
* UI ���ӿ�����Ʈ ���� Transform ������Ʈ��,  
* ī�޶��� ������ ���� �ʰ� �׻� ������ ȭ�� ��ǥ�� ����Ѵ�.
* ������Ʈ ������ Transform System�� ��ϵǾ� dirty���Ͽ� ���� matrix�� ��� ����Ѵ�.
* �ϴ� �θ� ���� ����� �ȸ������.
*/

class RectTransform : public ITransform
{
private:
    // rect transform
    D2D1_POINT_2F position = { 0, 0 };     // center
    D2D1_SIZE_F size = { 100, 100 };       // width, height
    D2D1_POINT_2F pivot = { 0.5f, 0.5f };  // rect�� �߽��� (left top = 0,0) -> offset ó��

    // this matrix
    D2D1::Matrix3x2F screenMatrix;
    bool isDirty = true;

public:
    // matrix
    static D2D1::Matrix3x2F unityMatrix;          // ����, screen size �ʿ�
    static D2D1::Matrix3x2F renderMatrix;         // ����

public:
    // component cycle
    RectTransform() { TransformSystem::Get().Regist(this); }
    ~RectTransform() override { TransformSystem::Get().Unregist(this); }

    void OnEnable() override;
    void Update() override;
    void OnDestroy() override;

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
    const D2D1::Matrix3x2F& GetScreenMatrix() const 
    { 
        // d2d
        return screenMatrix; 

        // unity
        //return renderMatrix * screenMatrix * unityMatrix;
    }
};
