#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // _kbhit(), _getch() : 키 입력 감지와 입력을 위해 사용
#include <windows.h> // Sleep(), system("cls") : 화면 클리어와 대기 기능 제공
#include <math.h> // sin(), cos() : 삼각함수 사용을 위해 포함

#define WIDTH 11       // 사각형의 너비
#define HEIGHT 5       // 사각형의 높이
#define DELAY 100      // 회전 속도 (100ms)
#define PI 3.14159265358979323846 // 원주율 정의
#define SCREEN_WIDTH 80  // 콘솔 가로 크기
#define SCREEN_HEIGHT 25 // 콘솔 세로 크기
#define ORBIT_RADIUS 10  // 원 궤도 반지름

void clearScreen() {
    system("cls"); // 콘솔 화면을 지우기 위해 cls 명령어 사용
}

void drawFilledRectangle(double angle, int offsetX, int offsetY) {
    int i, j;
    char output[HEIGHT][WIDTH]; // 사각형 출력 버퍼를 선언

    // 버퍼 초기화 : 모든 위치에 공백 문자를 채워줌
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            output[i][j] = ' '; // 공백으로 초기화
        }
    }

    // 사각형의 각 좌표를 회전 변환하여 버퍼에 저장
    for (i = -HEIGHT / 2; i <= HEIGHT / 2; i++) {
        for (j = -WIDTH / 2; j <= WIDTH / 2; j++) {
            int x = (int)(j * cos(angle) - i * sin(angle) + WIDTH / 2);
            int y = (int)(j * sin(angle) + i * cos(angle) + HEIGHT / 2);

            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                output[y][x] = '#';
                if (x + 1 < WIDTH) output[y][x + 1] = '#';
                if (y + 1 < HEIGHT) output[y + 1][x] = '#';
                if (x + 1 < WIDTH && y + 1 < HEIGHT) output[y + 1][x + 1] = '#';
            }
        }
    }

    int startX = (SCREEN_WIDTH - WIDTH) / 2 + offsetX;
    int startY = (SCREEN_HEIGHT - HEIGHT) / 2 + offsetY;

    for (i = 0; i < startY; i++) {
        printf("\n");
    }

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < startX; j++) {
            printf(" ");
        }
        output[i][WIDTH - 1] = '\0'; // 문자열의 끝에 NULL 추가
        printf("%s\n", output[i]); // 각 줄을 출력하여 사각형 표시
    }
}

int main() {
    double angle = 0; // 사각형의 회전 각도 초기화
    double orbitAngle = 0; // 궤도 회전 각도 초기화
    double orbitIncrement = (2 * PI) / (3000.0 / DELAY); // 3초에 한 바퀴 돌도록 각도 증가량 계산

    while (!_kbhit()) {
        clearScreen();

        int offsetX = (int)(ORBIT_RADIUS * cos(orbitAngle));
        int offsetY = (int)(ORBIT_RADIUS * sin(orbitAngle));

        drawFilledRectangle(angle, offsetX, offsetY);

        angle += orbitIncrement;
        orbitAngle += orbitIncrement;

        Sleep(DELAY);
    }

    return 0;
}
