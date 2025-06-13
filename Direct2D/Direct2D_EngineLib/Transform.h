#include <d2d1.h>
#include <vector>

/* Transform Component*/
// World = this->local * parent->world
// Screen = this->world * camera �����

// Uniny Style Screen position
// ��ǥ�� - �߾� (0,0), ������(-, +), ������ �Ʒ�(+, -)
// D2D���� ����Ƽ ��ǥ��ó�� ����Ϸ��� �ļ��� �ʿ���
// Screen position = renderMatrix * this->world * camera ����� * unity matrix
//  renderMatrix�� unity matrix�� �����ϱ� ���� y scale�� -1�� �� ���
//  transform����� �����ϸ� �ڽı��� ���� ������ ��ġ�� ������ World ��� ������ ���길 �ؾ��Ѵ�.

class Transform
{
private:
    // transform
    D2D1_POINT_2F position;
    float rotation;
    D2D1_POINT_2F scale;

    // parent, child
    Transform* parent = nullptr;
    std::vector<Transform*> children;

public:
    // matrix
    static D2D1_MATRIX_3X2_F cameraInversMatrix;
    static D2D1_MATRIX_3X2_F unityMatrix;
    static D2D1_MATRIX_3X2_F renderMatrix;

public:
    Transform() : position{ 0.0f, 0.0f }, rotation(0.0f), 
        scale{ 1.0f, 1.0f }, parent(nullptr) {}

    void SetPosition(float x, float y) { position = { x, y }; }
    void SetRotation(float angle) { rotation = angle; }
    void SetScale(float scaleX, float scaleY) { scale = { scaleX, scaleY }; }
    D2D1_POINT_2F GetPosition() const { return position; }
    float GetRotation() const { return rotation; }
    D2D1_POINT_2F GetScale() const { return scale; }

    void SetParent(Transform* newParent);
    D2D1_MATRIX_3X2_F GetLocalMatrix() const;
    D2D1_MATRIX_3X2_F GetWorldMatrix() const;
    D2D1_MATRIX_3X2_F GetScreenMatrix() const;
};