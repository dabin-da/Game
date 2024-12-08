#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20

// GameObject_Triangle ����ü ����
typedef struct {
    int x1, y1; // ù ��° ��
    int x2, y2; // �� ��° ��
    int x3, y3; // �� ��° ��
} GameObject_Triangle;

// drawLine �Լ�: �� ���� �����ϴ� ���� '@' ��ȣ�� ���
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

// �̵ ���ﰢ���� �׸��� �Լ�
void drawTriangle(GameObject_Triangle triangle, char canvas[HEIGHT][WIDTH]) {
    // �� ���� �׸���.
    drawLine(triangle.x1, triangle.y1, triangle.x2, triangle.y2, canvas);
    drawLine(triangle.x2, triangle.y2, triangle.x3, triangle.y3, canvas);
    drawLine(triangle.x3, triangle.y3, triangle.x1, triangle.y1, canvas);
}

// ȭ���� ����ϴ� �Լ�
void printCanvas(char canvas[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", canvas[y][x] == 0 ? ' ' : canvas[y][x]);
        }
        printf("\n");
    }
}

int main() {
    // �� ĵ���� ����
    char canvas[HEIGHT][WIDTH] = { 0 };

    // ���ﰢ���� �� �� (ȭ�� �߾ӿ� �׸��� ���� ��ǥ ���)
    int centerX = WIDTH / 2;
    int centerY = HEIGHT / 2;
    int height = 8;  // ���ﰢ���� ����

    // ���ﰢ���� 3���� �� ��ǥ
    int x1 = centerX;
    int y1 = centerY - height / 2;

    int x2 = centerX - height / 2;
    int y2 = centerY + height / 2;

    int x3 = centerX + height / 2;
    int y3 = centerY + height / 2;

    // GameObject_Triangle ����ü �ʱ�ȭ
    GameObject_Triangle triangle = { x1, y1, x2, y2, x3, y3 };

    // ���ﰢ�� �׸���
    drawTriangle(triangle, canvas);

    // ȭ�� ���
    printCanvas(canvas);

    return 0;
}
