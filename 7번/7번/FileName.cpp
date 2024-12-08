#include <stdio.h>
#include <math.h>
#include <stdlib.h>  // system("cls")�� ����ϱ� ���� �ʿ�
#include <windows.h> // Sleep()�� ����ϱ� ���� �ʿ�
#include <conio.h>    // _kbhit()�� _getch() ����� ���� �ʿ�

#define PI 3.14159265

// �ﰢ���� �ʱ� ��ǥ
float triangle[3][2] = {
    {0.0f, 1.0f},    // ��
    {-1.0f, -1.0f},  // ����
    {1.0f, -1.0f}    // ������
};

// ȸ�� �Լ� (�־��� ������ŭ �ﰢ���� ȸ����Ų��)
void rotateTriangle(float angle) {
    // ȸ�� ����� ����Ͽ� �� ���� ȸ����Ŵ
    for (int i = 0; i < 3; i++) {
        float x = triangle[i][0];
        float y = triangle[i][1];

        // ȸ�� ����� ����
        triangle[i][0] = x * cos(angle * PI / 180.0f) - y * sin(angle * PI / 180.0f);
        triangle[i][1] = x * sin(angle * PI / 180.0f) + y * cos(angle * PI / 180.0f);
    }
}

// �ﰢ���� ȭ�鿡 ����ϴ� �Լ� (�ؽ�Ʈ ���)
void printTriangle() {
    // �ܼ� ȭ�� �����
    system("cls");

    // ȭ�� ũ��
    const int width = 40;
    const int height = 20;

    // ȭ���� ����
    char screen[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            screen[i][j] = ' ';
        }
    }

    // �ﰢ���� ��ǥ�� ������ ��ȯ�Ͽ� ȭ�鿡 �׸���
    for (int i = 0; i < 3; i++) {
        int x = (int)(triangle[i][0] * 10 + width / 2); // X ��ǥ ��ȯ
        int y = (int)(triangle[i][1] * 10 + height / 2); // Y ��ǥ ��ȯ

        if (x >= 0 && x < width && y >= 0 && y < height) {
            screen[y][x] = '*';
        }
    }

    // ȭ�鿡 ���
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
}

// �ﰢ���� '++' �������� ���� �Ǵ� ������Ű�� �Լ�
void moveTriangle(float direction, float step) {
    // �̵� ���� ��� (���⿡ ����)
    float moveX = step * cos(direction * PI / 180.0f);
    float moveY = step * sin(direction * PI / 180.0f);

    // �ﰢ���� �� ���� �̵���Ŵ
    for (int i = 0; i < 3; i++) {
        triangle[i][0] += moveX;
        triangle[i][1] += moveY;
    }
}

// ���� �Լ�
int main() {
    float angle = 0.0f;  // ȸ�� ���� �ʱⰪ
    char key;
    int moveFlag = 0; // �̵� ���θ� �����ϴ� ���� (�ʱⰪ 0)

    while (1) {
        if (_kbhit()) {  // Ű�� ���ȴ��� Ȯ��
            key = _getch();  // ���� Ű�� �޾ƿ�

            if (key == 'w') {
                // 'w' Ű: '++' �������� ���� (frame�� 0.05px) -> �ӵ� ����
                moveTriangle(angle, 0.05f);  // �̵� �ӵ��� ����
                moveFlag = 1; // �̵� �� ���·� ����
            }
            else if (key == 's') {
                // 's' Ű: '++' ���� �ݴ�(����)���� �̵� (frame�� 0.05px) -> �ӵ� ����
                moveTriangle(angle, -0.05f);  // �̵� �ӵ��� ����
                moveFlag = 1; // �̵� �� ���·� ����
            }
            else if (key == 'q') {
                break;  // 'q' Ű�� ������ ����
            }
        }

        if (moveFlag > 0) {  // �̵��� ���۵Ǿ��� ���� ȸ�� �� ���
            // �ﰢ�� ȸ�� �Լ� ȣ�� (�ڵ����� 1���� ȸ��)
            rotateTriangle(angle);

            // ȸ���� �ﰢ�� ���
            printTriangle();

            // ������ 1���� �������Ѽ� ��� ȸ��
            angle += 1.0f;

            // 100ms ��� (ȭ�� ���� �ӵ� ����, ���� 50ms���� 2�� ������)
            Sleep(100);  // ȭ�� ���� ������ �÷��� �̵� �ӵ� ���߱�
        }
    }

    return 0;
}
