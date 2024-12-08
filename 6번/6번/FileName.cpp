#include <stdio.h>
#include <math.h>
#include <conio.h>  // _kbhit()�� _getch() ����� ���� �ʿ�
#include <stdlib.h> // system("cls")�� ����ϱ� ���� �ʿ�
#include <windows.h> // Sleep()�� ����ϱ� ���� �ʿ�

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

// ���� �Լ�
int main() {
    float angle = 0.0f;  // ȸ�� ���� �ʱⰪ
    char key;

    while (1) {
        if (_kbhit()) {  // Ű�� ���ȴ��� Ȯ��
            key = _getch();  // ���� Ű�� �޾ƿ�

            if (key == 'a') {
                angle -= 1.0f;  // 'a' Ű: �������� 1�� ȸ��
            }
            else if (key == 'd') {
                angle += 1.0f;  // 'd' Ű: ���������� 1�� ȸ��
            }
            else if (key == 'q') {
                break;  // 'q' Ű�� ������ ����
            }

            // �ﰢ�� ȸ�� �Լ� ȣ��
            rotateTriangle(angle);

            // ȸ���� �ﰢ�� ���
            printTriangle();
        }

        // 30ms ���
        Sleep(30);
    }

    return 0;
}
