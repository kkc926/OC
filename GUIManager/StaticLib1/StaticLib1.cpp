// StaticLib1.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include <iostream>

using namespace std;

// TODO: 라이브러리 함수의 예제입니다.
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