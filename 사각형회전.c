#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // _kbhit(), _getch()
#include <windows.h> // Sleep(), system("cls")
#include <math.h> // sin(), cos()

#define WIDTH 11       // �簢���� �ʺ�
#define HEIGHT 5       // �簢���� ����
#define DELAY 100      // ȸ�� �ӵ� (100ms)
#define PI 3.14159265358979323846 // ������ ����
#define SCREEN_WIDTH 80  // �ܼ� ���� ũ��
#define SCREEN_HEIGHT 25 // �ܼ� ���� ũ��
#define ORBIT_RADIUS 10  // �� �˵� ������

void clearScreen() {
    // �ܼ� ȭ���� ����ϴ�.
    system("cls");
}

void drawFilledRectangle(double angle, int offsetX, int offsetY) {
    int i, j;
    char output[HEIGHT][WIDTH]; // �簢�� ��� ����

    // ���� �ʱ�ȭ
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            output[i][j] = ' '; // �������� �ʱ�ȭ
        }
    }

    // �簢���� �������� ����Ͽ� ���ۿ� ����
    for (i = -HEIGHT / 2; i <= HEIGHT / 2; i++) {
        for (j = -WIDTH / 2; j <= WIDTH / 2; j++) {
            // ȸ���� ��ġ ���
            int x = (int)(j * cos(angle) - i * sin(angle) + WIDTH / 2);
            int y = (int)(j * sin(angle) + i * cos(angle) + HEIGHT / 2);

            // ��� ���ۿ� '#' ����
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                output[y][x] = '#';
            }
        }
    }

    // ȭ���� �߾ӿ� ��ġ��Ű�� ���� ���� ��ġ ���
    int startX = (SCREEN_WIDTH - WIDTH) / 2 + offsetX;
    int startY = (SCREEN_HEIGHT - HEIGHT) / 2 + offsetY;

    // ȭ�� ��ܿ� ���� �߰�
    for (i = 0; i < startY; i++) {
        printf("\n");
    }

    // ��� ���۸� �ֿܼ� ���
    for (i = 0; i < HEIGHT; i++) {
        // ���� ��ġ���� ���� ���
        for (j = 0; j < startX; j++) {
            printf(" ");
        }
        output[i][WIDTH - 1] = '\0'; // ���ڿ� ���� NULL �߰�
        printf("%s\n", output[i]); // ���
    }
}

int main() {
    double angle = 0;
    double orbitAngle = 0; // �˵� ����
    double orbitIncrement = (2 * PI) / (3000.0 / DELAY); // 3�ʿ� �� ���� ������ ������ ���

    while (!_kbhit()) { // Ű �Է��� ���� ������ �ݺ�
        clearScreen();

        // ���� �˵��� ���� �����̴� offset ���
        int offsetX = (int)(ORBIT_RADIUS * cos(orbitAngle));
        int offsetY = (int)(ORBIT_RADIUS * sin(orbitAngle));

        drawFilledRectangle(angle, offsetX, offsetY);

        // ȸ�� ������ �˵� ���� ����
        angle += orbitIncrement;    // ���� ȸ�� ����
        orbitAngle += orbitIncrement; // �˵� ȸ�� ����

        Sleep(DELAY); // ȸ�� �ӵ� ����
    }

    return 0;
}
