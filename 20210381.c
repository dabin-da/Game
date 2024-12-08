#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

#define WIDTH 40
#define HEIGHT 24
#define SUN_POSITION_X 20.0f       // �¾��� X ��ǥ
#define SUN_POSITION_Y 12.0f       // �¾��� Y ��ǥ
#define SUN_EARTH_DISTANCE 12.0f
#define EARTH_MOON_DISTANCE 4.0f

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    float x, y, w;
} vec3;

typedef struct {
    float m[3][3];
} Matrix3x3;

// �ܼ� Ŀ�� �̵� �Լ�
void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// ȭ�� �����
void clearScreen() {
    system("cls");
}

// �޽��� ���
void showMessage(const char* message) {
    clearScreen();
    int centerX = WIDTH / 2 - (int)(strlen(message) / 2);
    int centerY = HEIGHT / 2;
    setCursorPosition(centerX, centerY);
    printf("%s", message);
}

// ���� ��� �ʱ�ȭ
void initIdentityMatrix(Matrix3x3* mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat->m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

// ���Ϳ� ��� ����
vec3 Mul(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = b.m[0][0] * a.x + b.m[0][1] * a.y + b.m[0][2] * a.w;
    result.y = b.m[1][0] * a.x + b.m[1][1] * a.y + b.m[1][2] * a.w;
    result.w = 1.0f;
    return result;
}

// ȸ�� ��� ����
Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    float radian = angle * M_PI / 180.0f;
    mat.m[0][0] = cos(radian);
    mat.m[0][1] = -sin(radian);
    mat.m[1][0] = sin(radian);
    mat.m[1][1] = cos(radian);
    return mat;
}

// �̵� ��� ����
Matrix3x3 createTranslationMatrix(float tx, float ty) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    mat.m[0][2] = tx;
    mat.m[1][2] = ty;
    return mat;
}

// ���� �׸���
void drawSquare(int centerX, int centerY, int size, const char* symbol) {
    for (int y = -size / 2; y <= size / 2; y++) {
        for (int x = -size / 2; x <= size / 2; x++) {
            setCursorPosition(centerX + x, centerY + y);
            printf("%s", symbol);
        }
    }
}

void drawCircle(int centerX, int centerY, int radius, const char* symbol) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                setCursorPosition(centerX + x, centerY + y);
                printf("%s", symbol);
            }
        }
    }
}

void drawRotatingTriangle(int centerX, int centerY, int size, float angle, const char* symbol) {
    vec3 vertices[3] = {
        {0.0f, -size, 1.0f},  // ���� ������
        {-size, size, 1.0f},  // ���� �Ʒ� ������
        {size, size, 1.0f}    // ������ �Ʒ� ������
    };

    Matrix3x3 rotation = createRotationMatrix(angle);

    // �ﰢ���� ������ ���
    for (int i = 0; i < 3; i++) {
        vertices[i] = Mul(vertices[i], rotation);
        vertices[i] = Mul(vertices[i], createTranslationMatrix(centerX, centerY));
    }

    // �ﰢ���� �����ϴ� ���� ��� (���� ���� ���)
    for (int i = 0; i < 3; i++) {
        int x1 = (int)vertices[i].x;
        int y1 = (int)vertices[i].y;
        int x2 = (int)vertices[(i + 1) % 3].x;
        int y2 = (int)vertices[(i + 1) % 3].y;

        // �� �� ���̸� ������ ����
        int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
        int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
        int err = dx + dy, e2;

        while (1) {
            setCursorPosition(x1, y1);
            printf("%s", symbol);
            if (x1 == x2 && y1 == y2) break;
            e2 = 2 * err;
            if (e2 >= dy) { err += dy; x1 += sx; }
            if (e2 <= dx) { err += dx; y1 += sy; }
        }
    }
}


// ȭ�� �׸���
void draw(float sunAngle, float earthAngle, float moonAngle, int state) {
    clearScreen();

    int sunX = WIDTH / 2;
    int sunY = HEIGHT / 2;

    vec3 sunPos = { sunX, sunY, 1.0f }; // �¾� ��ġ

    vec3 earthPos = { 0.0f, SUN_EARTH_DISTANCE, 1.0f };
    vec3 moonPos = { 0.0f, EARTH_MOON_DISTANCE, 1.0f };

    if (state == 2) {
        Matrix3x3 earthRotation = createRotationMatrix(earthAngle);
        earthPos = Mul(earthPos, earthRotation);
        earthPos = Mul(earthPos, createTranslationMatrix(sunX, sunY));

        Matrix3x3 moonRotation = createRotationMatrix(moonAngle);
        moonPos = Mul(moonPos, moonRotation);
        moonPos = Mul(moonPos, createTranslationMatrix(earthPos.x, earthPos.y));
    }
    else if (state == 1) { // 1�� ��ġ ����
        earthPos.x = sunX;
        earthPos.y = sunY + SUN_EARTH_DISTANCE;
        moonPos.x = sunX;
        moonPos.y = earthPos.y + EARTH_MOON_DISTANCE;
    }
    else {
        return; // �޽��� ���¿����� ȭ���� �׸��� ����
    }

    drawRotatingTriangle(sunX, sunY, 5, sunAngle, "SS");
    drawSquare((int)earthPos.x, (int)earthPos.y, 3, "EE");
    drawCircle((int)moonPos.x, (int)moonPos.y, 1, "MM");
}

int main() {
    float sunAngle = 0.0f;
    float earthAngle = 0.0f;
    float moonAngle = 0.0f;
    int state = 0; // 0: �޽��� ����, 1: 1�� ��ġ ����, 2: ����/���� ����

    while (1) {
        if (_kbhit()) { // Ű �Է��� ���� ��
            char key = _getch();
            if (key == 27) { // ESC Ű
                break; // ���α׷� ����
            }
            else if (key == ' ') { // �����̽���
                state = (state + 1) % 3; // ���� ����
            }
        }

        if (state == 0) {
            showMessage("20210381 �̴ٺ�");
        }
        else if (state == 1 || state == 2) {
            draw(sunAngle, earthAngle, moonAngle, state);
            if (state == 2) { // ����/���� ���¿����� ���� ����
                sunAngle += 2.0f;
                earthAngle += 1.0f;
                moonAngle += 5.0f;
            }
        }

        Sleep(100);
    }

    return 0;
}
