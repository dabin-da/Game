#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// ȭ�� ũ��
#define WIDTH 40
#define HEIGHT 24

// 1�ȼ��� 2���� ���ڷ� ������ ���ڿ��̹Ƿ�, ���� ũ��� WIDTH * HEIGHT * 2
void Elf2DDrawLine(int x1, int y1, int x2, int y2, char* Buffer, int width, int height) {
    // ������ �׸��� �⺻���� �˰����� �극���� �˰����� ���
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1, sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        // �ȼ� ��ġ�� '00'���� ä��� (2���ھ� �ʿ�)
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
    // �ε� �Ҽ����� ����Ͽ� ������ �׸��� �Լ� (���������� Bresenham �˰��� ���)
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = sqrt(dx * dx + dy * dy);
    float step = 1.0f;

    // �ε��Ҽ������� �����ϸ� ������ ���
    for (float t = 0; t <= length; t += step) {
        int x = (int)(x1 + dx * t / length);
        int y = (int)(y1 + dy * t / length);

        // �ȼ� ��ġ�� '00'���� ä��� (2���ھ� �ʿ�)
        if (x >= 0 && x < width && y >= 0 && y < height) {
            Buffer[(y * width + x) * 2] = '0';
            Buffer[(y * width + x) * 2 + 1] = '0';
        }
    }
}

// ȭ���� ����ϴ� �Լ�
void printBuffer(char* buffer, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%c%c", buffer[(y * width + x) * 2], buffer[(y * width + x) * 2 + 1]);
        }
        printf("\n");
    }
}

int main() {
    // ȭ�� ũ��
    char buffer[WIDTH * HEIGHT * 2]; // �� �ȼ����� 2���� ���� ����

    // ���� �ʱ�ȭ
    for (int i = 0; i < WIDTH * HEIGHT * 2; i++) {
        buffer[i] = ' '; // �� �������� �ʱ�ȭ
    }

    // ���� �׸��� ����
    Elf2DDrawLine2(1.0f, 1.0f, 38.0f, 23.0f, buffer, WIDTH, HEIGHT);

    // ȭ�� ���
    printBuffer(buffer, WIDTH, HEIGHT);

    return 0;
}
