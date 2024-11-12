#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // _kbhit(), _getch() : 키 입력 감지와 입력을 위해 사용
#include <windows.h> // Sleep(), system("cls") : 화면 클리어와 대기 기능 제공
#include <math.h> // sin(), cos() : 삼각함수 사용을 위해 포함

// 사각형의 크기와 애니메이션 속도, 화면 크기 및 원주율을 정의
#define WIDTH 11       // 사각형의 너비
#define HEIGHT 5       // 사각형의 높이
#define DELAY 100      // 회전 속도 (밀리초 단위 100ms)
#define PI 3.14159265358979323846 // 원주율 정의
#define SCREEN_WIDTH 80  // 콘솔 창의 가로 크기
#define SCREEN_HEIGHT 25 // 콘솔 창의 세로 크기
#define ORBIT_RADIUS 10  // 사각형이 회전하는 궤도의 반지름

// 콘솔 화면을 지우는 함수
void clearScreen() {
    system("cls"); // 콘솔 화면을 지우기 위해 cls 명령어 사용
}

// 회전하는 사각형을 그리는 함수
void drawFilledRectangle(double angle, int offsetX, int offsetY) {
    int i, j;
    char output[HEIGHT][WIDTH]; // 사각형을 나타낼 출력 버퍼 배열 선언

    // 버퍼 초기화 : 사각형 내부를 공백 문자로 채움
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            output[i][j] = ' '; // 공백 문자로 초기화
        }
    }

    // 사각형의 각 좌표를 회전하여 버퍼에 '#' 문자를 채워 넣음
    for (i = -HEIGHT / 2; i <= HEIGHT / 2; i++) {
        for (j = -WIDTH / 2; j <= WIDTH / 2; j++) {
            // 회전 변환을 적용하여 새로운 좌표 계산
            int x = (int)(j * cos(angle) - i * sin(angle) + WIDTH / 2);
            int y = (int)(j * sin(angle) + i * cos(angle) + HEIGHT / 2);

            // 계산된 좌표가 배열의 범위 내에 있으면 해당 위치에 '#'을 배치
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                output[y][x] = '#'; // 회전된 좌표에 '#'을 채움
                if (x + 1 < WIDTH) output[y][x + 1] = '#';         // 오른쪽에 빈 공간이 없도록 추가로 채움
                if (y + 1 < HEIGHT) output[y + 1][x] = '#';        // 아래쪽에 빈 공간이 없도록 추가로 채움
                if (x + 1 < WIDTH && y + 1 < HEIGHT) output[y + 1][x + 1] = '#'; // 오른쪽 아래 채움
            }
        }
    }

    // 콘솔 화면의 중앙에 사각형이 위치하도록 시작 위치 계산
    int startX = (SCREEN_WIDTH - WIDTH) / 2 + offsetX;
    int startY = (SCREEN_HEIGHT - HEIGHT) / 2 + offsetY;

    // 사각형이 시작하기 전에 화면의 줄 수만큼 개행하여 상단 여백 추가
    for (i = 0; i < startY; i++) {
        printf("\n");
    }

    // 사각형의 각 줄을 콘솔에 출력하여 표시
    for (i = 0; i < HEIGHT; i++) {
        // 사각형이 시작 위치에 오도록 공백 출력
        for (j = 0; j < startX; j++) {
            printf(" ");
        }
        output[i][WIDTH - 1] = '\0'; // 줄 끝에 NULL 문자 추가하여 문자열 종료
        printf("%s\n", output[i]); // 사각형의 각 줄을 콘솔에 출력
    }
}

int main() {
    double angle = 0; // 사각형 자체의 회전 각도 초기화
    double orbitAngle = 0; // 궤도를 따라 도는 각도 초기화
    double orbitIncrement = (2 * PI) / (3000.0 / DELAY); // 사각형이 3초에 한 바퀴 돌도록 각도 증가량 계산

    // 키 입력이 있을 때까지 애니메이션 반복 실행
    while (!_kbhit()) { // 사용자가 키를 입력할 때까지 루프 반복
        clearScreen(); // 화면을 지움

        // 원형 궤도를 따라 사각형의 위치를 결정하는 offset 계산
        int offsetX = (int)(ORBIT_RADIUS * cos(orbitAngle));
        int offsetY = (int)(ORBIT_RADIUS * sin(orbitAngle));

        // 회전된 각도로 사각형을 offset 위치에 그리기
        drawFilledRectangle(angle, offsetX, offsetY);

        // 사각형의 회전 각도와 궤도 회전 각도를 증가시켜 다음 프레임 준비
        angle += orbitIncrement;       // 사각형 자체의 회전 각도 증가
        orbitAngle += orbitIncrement;  // 궤도 회전 각도 증가

        Sleep(DELAY); // DELAY 시간만큼 대기하여 애니메이션 속도를 조절
    }

    return 0; // 프로그램 종료
}
