#pragma once

using namespace std;
#include <Windows.h>
#include <iostream>
// Windows������ �����ϴ� �����Դϴ�.

// C#���� ������ �ݹ� �Լ� ������ �����մϴ�.
typedef void(__stdcall* CallbackFunc)(int);

// C++���� ȣ���� �Լ��Դϴ�.
void CallCSharpCallback(CallbackFunc callback) {
    std::cout << "Calling C# callback from C++" << std::endl;
    // �ݹ� �Լ� ȣ��
    callback(42);
}

int main() {
    // C#���� ������ �ݹ� �Լ��� �����մϴ�.
    CallbackFunc callback = [](int value) {
        std::cout << "C# callback invoked with value: " << value << std::endl;
    };

    // C++���� C# �ݹ� ȣ��
    CallCSharpCallback(callback);

    return 0;
}

