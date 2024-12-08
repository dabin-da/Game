#include <stdio.h>
#include <math.h>
#include <windows.h>

// ȭ�� ũ��� �簢�� ũ�� ����
#define WIDTH 40 // �ܼ� â �ʺ�
#define HEIGHT 20 // �ܼ� â ����
#define RECT_WIDTH 11 // �簢�� �ʺ�
#define RECT_HEIGHT 5 // �簢�� ����

// M_PI�� ���ǵ��� ���� ��� �������� ���� (������)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// �ܼ� ȭ�� ����� �Լ�
void clearScreen() {
    system("cls"); // Windows���� ȭ���� ����� ��ɾ� (�ܼ� ȭ�� �����)
}

// ȭ�� �߾ӿ� ȸ���� �簢���� �׸��� �Լ�
void drawFilledRotatedRectangle(float angle) {
    // ���� ������ ���� ȸ���� �簢���� �׸��� �� �ܼ� ȭ���� ����
    clearScreen();

    // ����� ȭ���� �ʱ�ȭ�� ���� �迭 ����
    char screen[HEIGHT][WIDTH];
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen[y][x] = ' '; // �� ȭ���� ���� ���ڷ� �ʱ�ȭ
        }
    }

    // ȭ�� �߽� ��ǥ
    int centerX = WIDTH / 2; // X�� �߽� ��ǥ (ȭ�� �߾�)
    int centerY = HEIGHT / 2; // Y�� �߽� ��ǥ (ȭ�� �߾�)

    // ����(�� ����)�� �������� ��ȯ
    float rad = angle * M_PI / 180.0f; // ȸ�� ������ ���� ������ ��ȯ
    float cosA = cos(rad); // ������ �ڻ��� �� ���
    float sinA = sin(rad); // ������ ���� �� ���

    // ȸ���� �簢���� �� ��ǥ�� ����ϰ�, ���θ� '*'�� ä���
    for (float y = -RECT_HEIGHT / 2.0f; y <= RECT_HEIGHT / 2.0f; y += 0.25f) {
        for (float x = -RECT_WIDTH / 2.0f; x <= RECT_WIDTH / 2.0f; x += 0.5f) {
            // ȸ�� ��ȯ ������ ����� ȸ�� �� ��ǥ ���
            int rotatedX = (int)(x * cosA - y * sinA + centerX); // ȸ���� X ��ǥ ���
            int rotatedY = (int)(x * sinA + y * cosA + centerY); // ȸ���� Y ��ǥ ���

            // ȭ�� ���� ���� �ִ� ��츸 '*'�� �־� ä���
            if (rotatedX >= 0 && rotatedX < WIDTH && rotatedY >= 0 && rotatedY < HEIGHT) {
                screen[rotatedY][rotatedX] = '*'; // �簢�� ������ '*'�� ä���
            }
        }
    }

    // �ϼ��� ȭ�� �迭�� �ֿܼ� ���
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", screen[y][x]); // ȭ�� �迭�� ���
        }
        printf("\n"); // �ٹٲ� (�� ���� ȭ�鿡 ���)
    }
}

// ���� �Լ�
int main() {
    float angle = 0.0f; // �ʱ� ���� ���� (ȸ�� ����)

    // ���� ������ ���鼭 ȭ���� ����ؼ� �����Ͽ� ȸ�� �ִϸ��̼� ����
    while (1) {
        drawFilledRotatedRectangle(angle); // ���� ������ ���� ȸ���� �簢���� �׸�
        Sleep(100); // 0.1�� ��� (ȸ�� �ӵ� ����)

        angle += 6.0f; // ������ 6���� ���� (ȸ�� �ӵ�)
        if (angle >= 360.0f) {
            angle = 0.0f; // 360�� �̻��� �Ǹ� 0���� �ʱ�ȭ (�� ���� �Ϸ�)
        }
    }

    return 0; // ���α׷� ����
}
