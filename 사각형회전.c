#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // _kbhit(), _getch()
#include <windows.h> // Sleep(), system("cls")
#include <math.h> // sin(), cos()

#define WIDTH 11       // 사각형의 너비
#define HEIGHT 5       // 사각형의 높이
#define DELAY 100      // 회전 속도 (100ms)
#define PI 3.14159265358979323846 // 원주율 정의
#define SCREEN_WIDTH 80  // 콘솔 가로 크기
#define SCREEN_HEIGHT 25 // 콘솔 세로 크기
#define ORBIT_RADIUS 10  // 원 궤도 반지름

void clearScreen() {
    // 콘솔 화면을 지웁니다.
    system("cls");
}

void drawFilledRectangle(double angle, int offsetX, int offsetY) {
    int i, j;
    char output[HEIGHT][WIDTH]; // 사각형 출력 버퍼

    // 버퍼 초기화
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            output[i][j] = ' '; // 공백으로 초기화
        }
    }

    // 사각형의 꼭지점을 계산하여 버퍼에 저장
    for (i = -HEIGHT / 2; i <= HEIGHT / 2; i++) {
        for (j = -WIDTH / 2; j <= WIDTH / 2; j++) {
            // 회전된 위치 계산
            int x = (int)(j * cos(angle) - i * sin(angle) + WIDTH / 2);
            int y = (int)(j * sin(angle) + i * cos(angle) + HEIGHT / 2);

            // 출력 버퍼에 '#' 저장
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                output[y][x] = '#';
            }
        }
    }

    // 화면의 중앙에 위치시키기 위한 시작 위치 계산
    int startX = (SCREEN_WIDTH - WIDTH) / 2 + offsetX;
    int startY = (SCREEN_HEIGHT - HEIGHT) / 2 + offsetY;

    // 화면 상단에 여백 추가
    for (i = 0; i < startY; i++) {
        printf("\n");
    }

    // 출력 버퍼를 콘솔에 출력
    for (i = 0; i < HEIGHT; i++) {
        // 시작 위치까지 공백 출력
        for (j = 0; j < startX; j++) {
            printf(" ");
        }
        output[i][WIDTH - 1] = '\0'; // 문자열 끝에 NULL 추가
        printf("%s\n", output[i]); // 출력
    }
}

int main() {
    double angle = 0;
    double orbitAngle = 0; // 궤도 각도
    double orbitIncrement = (2 * PI) / (3000.0 / DELAY); // 3초에 한 바퀴 돌도록 증가량 계산

    while (!_kbhit()) { // 키 입력이 있을 때까지 반복
        clearScreen();

        // 원형 궤도를 따라 움직이는 offset 계산
        int offsetX = (int)(ORBIT_RADIUS * cos(orbitAngle));
        int offsetY = (int)(ORBIT_RADIUS * sin(orbitAngle));

        drawFilledRectangle(angle, offsetX, offsetY);

        // 회전 각도와 궤도 각도 증가
        angle += orbitIncrement;    // 내부 회전 각도
        orbitAngle += orbitIncrement; // 궤도 회전 각도

        Sleep(DELAY); // 회전 속도 조절
    }

    return 0;
}
