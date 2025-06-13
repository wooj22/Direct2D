// World = local * parent->world
// Screen = world * camera �����

// Uniny Style Screen position
// ��ǥ�� - �߾� (0,0), ������(-, +), ������ �Ʒ�(+, -)
// D2D���� ����Ƽ ��ǥ��ó�� ����Ϸ��� �ļ��� �ʿ���
// Screen = renderMatrix * world * camera ����� * unity matrix
//  unity matrix�� �߽� �̵��� y ������ ���� ��İ��� ������ �ִ�.
//  renderMatrix�� unity matrix�� �����ϱ� ���� y scale�� -1�� �� ���
//  transform ����� �����ϸ� �ڽı��� ���� ������ ��ġ�� ������ ���꿡�� ����ؾ��Ѵ�.

// Dirty ����
// transform�� ���濡 ���� flag�� Ȱ���Ͽ� 
// �� �����Ӹ��� ���ʿ��ϰ� ����� �ٽ� ������� �ʵ��� �ϴ� ���

#include <d2d1_1.h>
#include <vector>

/* Transform Component*/
class Transform
{
private:
    // transform
    D2D1_POINT_2F position;
    float rotation;
    D2D1_POINT_2F scale;


    // parent, child
    Transform* parent = nullptr;
    //std::vector<Transform*> children;

    // dirty patten
    bool isDirty = true;
    D2D1::Matrix3x2F localMatrix;

public:
    // matrix
    static D2D1::Matrix3x2F cameraInversMatrix;   // screen size �ʿ�
    static D2D1::Matrix3x2F unityMatrix;          // screen size �ʿ�
    static D2D1::Matrix3x2F renderMatrix;

public:
    Transform() : position{ 0.0f, 0.0f }, rotation(0.0f), 
        scale{ 1.0f, 1.0f }, parent(nullptr) { localMatrix = D2D1::Matrix3x2F::Identity(); }

    void SetParent(Transform* newParent);
    void ResetTransform();

    // set
    void SetPosition(float x, float y) { isDirty = true; position = { x, y }; }
    void SetRotation(float angle) { isDirty = true; rotation = angle; }
    void SetScale(float scaleX, float scaleY) { isDirty = true; scale = { scaleX, scaleY }; }
    
    // add
    void AddPosition(float x, float y) { isDirty = true; position.x += x; position.y += y; }
    void AddRotation(float angle) { isDirty = true; rotation += angle; }
    void AddScale(float scaleX, float scaleY) { isDirty = true; scale.x += scaleX; scale.y += scaleY; }
    
    // get
    D2D1_POINT_2F GetPosition() const { return position; }
    float GetRotation() const { return rotation; }
    D2D1_POINT_2F GetScale() const { return scale; }

    // get matrix
    D2D1::Matrix3x2F GetLocalMatrix();
    D2D1::Matrix3x2F GetWorldMatrix();
    D2D1::Matrix3x2F GetScreenMatrix();
};