#include <stdio.h>
#include <math.h>
#include <conio.h>  // _kbhit()와 _getch() 사용을 위해 필요
#include <stdlib.h> // system("cls")를 사용하기 위해 필요
#include <windows.h> // Sleep()을 사용하기 위해 필요

#define PI 3.14159265

// 삼각형의 초기 좌표
float triangle[3][2] = {
    {0.0f, 1.0f},    // 위
    {-1.0f, -1.0f},  // 왼쪽
    {1.0f, -1.0f}    // 오른쪽
};

// 회전 함수 (주어진 각도만큼 삼각형을 회전시킨다)
void rotateTriangle(float angle) {
    // 회전 행렬을 사용하여 각 점을 회전시킴
    for (int i = 0; i < 3; i++) {
        float x = triangle[i][0];
        float y = triangle[i][1];

        // 회전 행렬을 적용
        triangle[i][0] = x * cos(angle * PI / 180.0f) - y * sin(angle * PI / 180.0f);
        triangle[i][1] = x * sin(angle * PI / 180.0f) + y * cos(angle * PI / 180.0f);
    }
}

// 삼각형을 화면에 출력하는 함수 (텍스트 기반)
void printTriangle() {
    // 콘솔 화면 지우기
    system("cls");

    // 화면 크기
    const int width = 40;
    const int height = 20;

    // 화면을 비우기
    char screen[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            screen[i][j] = ' ';
        }
    }

    // 삼각형의 좌표를 정수로 변환하여 화면에 그리기
    for (int i = 0; i < 3; i++) {
        int x = (int)(triangle[i][0] * 10 + width / 2); // X 좌표 변환
        int y = (int)(triangle[i][1] * 10 + height / 2); // Y 좌표 변환

        if (x >= 0 && x < width && y >= 0 && y < height) {
            screen[y][x] = '*';
        }
    }

    // 화면에 출력
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
}

// 메인 함수
int main() {
    float angle = 0.0f;  // 회전 각도 초기값
    char key;

    while (1) {
        if (_kbhit()) {  // 키가 눌렸는지 확인
            key = _getch();  // 눌린 키를 받아옴

            if (key == 'a') {
                angle -= 1.0f;  // 'a' 키: 왼쪽으로 1도 회전
            }
            else if (key == 'd') {
                angle += 1.0f;  // 'd' 키: 오른쪽으로 1도 회전
            }
            else if (key == 'q') {
                break;  // 'q' 키를 누르면 종료
            }

            // 삼각형 회전 함수 호출
            rotateTriangle(angle);

            // 회전된 삼각형 출력
            printTriangle();
        }

        // 30ms 대기
        Sleep(30);
    }

    return 0;
}
