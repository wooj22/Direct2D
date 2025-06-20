#pragma once
#include <windows.h>

class Time
{
private:
    static LARGE_INTEGER frequency;
    static LARGE_INTEGER initCounter;
    static LARGE_INTEGER prevCounter;
    static LARGE_INTEGER currentCounter;
    static float deltaTime;

public:
    static void Init();
    static void Update();

    static float GetDeltaTime(); // �̹� ������ ��� �ð�
    static float GetTotalTime(); // ��ü ��� �ð�
};