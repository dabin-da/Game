#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20

// GameObject_Triangle 구조체 정의
typedef struct {
    int x1, y1; // 첫 번째 점
    int x2, y2; // 두 번째 점
    int x3, y3; // 세 번째 점
} GameObject_Triangle;

// drawLine 함수: 두 점을 연결하는 선을 '@' 기호로 출력
void drawLine(int x1, int y1, int x2, int y2, char canvas[HEIGHT][WIDTH]) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    while (1) {
        if (x1 >= 0 && x1 < WIDTH && y1 >= 0 && y1 < HEIGHT) {
            canvas[y1][x1] = '@';
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

// 이등변 정삼각형을 그리는 함수
void drawTriangle(GameObject_Triangle triangle, char canvas[HEIGHT][WIDTH]) {
    // 세 선을 그린다.
    drawLine(triangle.x1, triangle.y1, triangle.x2, triangle.y2, canvas);
    drawLine(triangle.x2, triangle.y2, triangle.x3, triangle.y3, canvas);
    drawLine(triangle.x3, triangle.y3, triangle.x1, triangle.y1, canvas);
}

// 화면을 출력하는 함수
void printCanvas(char canvas[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", canvas[y][x] == 0 ? ' ' : canvas[y][x]);
        }
        printf("\n");
    }
}

int main() {
    // 빈 캔버스 생성
    char canvas[HEIGHT][WIDTH] = { 0 };

    // 정삼각형의 세 점 (화면 중앙에 그리기 위한 좌표 계산)
    int centerX = WIDTH / 2;
    int centerY = HEIGHT / 2;
    int height = 8;  // 정삼각형의 높이

    // 정삼각형의 3개의 점 좌표
    int x1 = centerX;
    int y1 = centerY - height / 2;

    int x2 = centerX - height / 2;
    int y2 = centerY + height / 2;

    int x3 = centerX + height / 2;
    int y3 = centerY + height / 2;

    // GameObject_Triangle 구조체 초기화
    GameObject_Triangle triangle = { x1, y1, x2, y2, x3, y3 };

    // 정삼각형 그리기
    drawTriangle(triangle, canvas);

    // 화면 출력
    printCanvas(canvas);

    return 0;
}
