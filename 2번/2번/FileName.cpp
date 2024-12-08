#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// 화면 크기
#define WIDTH 40
#define HEIGHT 24

// 1픽셀은 2개의 문자로 구성된 문자열이므로, 버퍼 크기는 WIDTH * HEIGHT * 2
void Elf2DDrawLine(int x1, int y1, int x2, int y2, char* Buffer, int width, int height) {
    // 직선을 그리는 기본적인 알고리즘인 브레젠햄 알고리즘을 사용
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1, sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        // 픽셀 위치에 '00'으로 채우기 (2문자씩 필요)
        if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
            Buffer[(y1 * width + x1) * 2] = '0';
            Buffer[(y1 * width + x1) * 2 + 1] = '0';
        }

        if (x1 == x2 && y1 == y2) break;

        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void Elf2DDrawLine2(float x1, float y1, float x2, float y2, char* Buffer, int width, int height) {
    // 부동 소수점을 사용하여 직선을 그리는 함수 (선택적으로 Bresenham 알고리즘 사용)
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = sqrt(dx * dx + dy * dy);
    float step = 1.0f;

    // 부동소수점으로 진행하며 점들을 계산
    for (float t = 0; t <= length; t += step) {
        int x = (int)(x1 + dx * t / length);
        int y = (int)(y1 + dy * t / length);

        // 픽셀 위치에 '00'으로 채우기 (2문자씩 필요)
        if (x >= 0 && x < width && y >= 0 && y < height) {
            Buffer[(y * width + x) * 2] = '0';
            Buffer[(y * width + x) * 2 + 1] = '0';
        }
    }
}

// 화면을 출력하는 함수
void printBuffer(char* buffer, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%c%c", buffer[(y * width + x) * 2], buffer[(y * width + x) * 2 + 1]);
        }
        printf("\n");
    }
}

int main() {
    // 화면 크기
    char buffer[WIDTH * HEIGHT * 2]; // 각 픽셀마다 2개의 문자 저장

    // 버퍼 초기화
    for (int i = 0; i < WIDTH * HEIGHT * 2; i++) {
        buffer[i] = ' '; // 빈 공백으로 초기화
    }

    // 직선 그리기 예시
    Elf2DDrawLine2(1.0f, 1.0f, 38.0f, 23.0f, buffer, WIDTH, HEIGHT);

    // 화면 출력
    printBuffer(buffer, WIDTH, HEIGHT);

    return 0;
}
