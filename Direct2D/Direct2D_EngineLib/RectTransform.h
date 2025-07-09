#pragma once
#include <d2d1_1.h>
#include "Vector2.h"
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
    Vector2 position = { 0, 0 };
    D2D1_SIZE_F size = { 100, 100 };
    D2D1_POINT_2F pivot = { 0.5f, 0.5f };  // rect�� �߽��� (unity ��ǥ�� ���� left down = 0,0) -> offset ó��

    // this matrix
    D2D1::Matrix3x2F screenMatrix;
    bool isDirty = true;

public:
    // matrix
    static D2D1::Matrix3x2F unityMatrix;          // ����, screen size �ʿ�
    static D2D1::Matrix3x2F renderMatrix;         // ����

public:
    // component cycle
    RectTransform() 
    { 
        TransformSystem::Get().Regist(this); 
        OutputDebugStringA("RectTransform()\n");
    }
    ~RectTransform() override 
    { 
        TransformSystem::Get().Unregist(this); 
        OutputDebugStringA("~RectTransform()\n");
    }

    void OnEnable() override;
    void Update() override;
    void OnDestroy() override;

public:
    // set
    void SetPosition(const Vector2& position);
    void SetPosition(const float& x, const float& y);
    void SetSize(const float& w, const float& h);
    void SetPivot(const float& x, const float& y);

    // get
    D2D1_SIZE_F GetSize() const { return size; }
    Vector2 GetPosition() const { return position; }
    D2D1_POINT_2F GetPivot() const { return pivot; }

    
private:
    // matrix
    void MakeScreenMatrix();

public:
    //  matrix get
    const D2D1::Matrix3x2F& GetScreenMatrix() const 
    { 
        // d2d
        //return screenMatrix;

        // unity
        return renderMatrix * screenMatrix * unityMatrix;
    }
};
