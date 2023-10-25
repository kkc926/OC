#pragma once

using namespace std;
#include <Windows.h>
#include <iostream>
// Windows에서만 동작하는 예제입니다.

// C#에서 정의한 콜백 함수 형식을 정의합니다.
typedef void(__stdcall* CallbackFunc)(int);

// C++에서 호출할 함수입니다.
void CallCSharpCallback(CallbackFunc callback) {
    std::cout << "Calling C# callback from C++" << std::endl;
    // 콜백 함수 호출
    callback(42);
}

int main() {
    // C#에서 정의한 콜백 함수를 전달합니다.
    CallbackFunc callback = [](int value) {
        std::cout << "C# callback invoked with value: " << value << std::endl;
    };

    // C++에서 C# 콜백 호출
    CallCSharpCallback(callback);

    return 0;
}

