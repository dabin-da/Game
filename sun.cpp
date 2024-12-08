#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20
#define SUN_EARTH_DISTANCE 10.0f // �¾����κ��� ���������� �Ÿ�
#define EARTH_MOON_DISTANCE 3.0f   // �����κ��� �ޱ����� �Ÿ�

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    float x, y, w; // 3D ���� (���� ��ǥ)
} vec3;

typedef struct {
    float m[3][3]; // 3x3 ���
} Matrix3x3;

// 3x3 ��� �ʱ�ȭ
void initIdentityMatrix(Matrix3x3* mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                mat->m[i][j] = 1;
            }
            else {
                mat->m[i][j] = 0;
            }
        }
    }
}

// vec3�� ��� ����
vec3 Mul(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = b.m[0][0] * a.x + b.m[0][1] * a.y + b.m[0][2] * a.w;
    result.y = b.m[1][0] * a.x + b.m[1][1] * a.y + b.m[1][2] * a.w;
    result.w = a.w; // ���� ��ǥ�̹Ƿ� w�� �״�� ����
    return result;
}

// ��� ����
Matrix3x3 MulMatrix(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j];
        }
    }
    return result;
}

// �̵� ��� ����
Matrix3x3 createTranslationMatrix(float tx, float ty) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    mat.m[0][2] = tx; // X�� �̵�
    mat.m[1][2] = ty; // Y�� �̵�
    return mat;
}

// ȸ�� ��� ����
Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    float radian = angle * M_PI / 180;
    mat.m[0][0] = cos(radian); // cos(��)
    mat.m[0][1] = -sin(radian); // -sin(��)
    mat.m[1][0] = sin(radian); // sin(��)
    mat.m[1][1] = cos(radian); // cos(��)
    return mat;
}

// �ܼ� ȭ�� �����
void clearScreen() {
    system("cls");
}

// ȭ�� �׸���
void draw(float earthAngle, float moonAngle) {
    clearScreen();

    // �¾� ��ġ (�߾�)
    int sunX = WIDTH / 2;
    int sunY = HEIGHT / 2;

    // �¾� �ʱ� ��ġ (����)
    vec3 sunPos = { 0.0f, 0.0f, 1.0f }; // �¾� ���� ��ǥ
    // ���� �ʱ� ��ġ (�¾����κ����� �Ÿ�)
    vec3 earthPos = { 0.0f, SUN_E\RTH_DISTANCE, 1.0f }; // ���� ���� ��ǥ
    // �� �ʱ� ��ġ (�����κ����� �Ÿ�)
    vec3 moonPos = { 0.0f, EARTH_MOON_DISTANCE, 1.0f }; // �� ���� ��ǥ

    // ���� ȸ��
    Matrix3x3 earthRotation = createRotationMatrix(earthAngle);
    earthPos = Mul(earthPos, earthRotation);

    // ���� ��ġ ��ȯ (�¾� ��ġ�� ����Ͽ�)
    vec3 earthScreenPos = { earthPos.x + sunX, earthPos.y + sunY, 1.0f }; // ȭ����� ���� ��ġ

    // ���� ��ġ�� ������ �������� ȸ���ϰ�, �Ÿ���ŭ ������ �ֵ��� ����
    // �� ȸ�� (������ �߽�����)
    Matrix3x3 moonRotation = createRotationMatrix(moonAngle);
    moonPos = Mul(moonPos, moonRotation);

    // �� ��ġ ��ȯ (���� ��ġ�� ����Ͽ�)
    moonPos = Mul(moonPos, createTranslationMatrix(earthScreenPos.x, earthScreenPos.y));

    // ȭ�� �׸���
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == sunX && y == sunY) {
                printf("S"); // �¾�(S) ���
            }
            else if ((int)earthScreenPos.x == x && (int)earthScreenPos.y == y) {
                printf("E"); // ����(E) ���
            }
            else if ((int)moonPos.x == x && (int)moonPos.y == y) {
                printf("M"); // ��(M) ���
            }
            else {
                printf(" "); // �� ���� ���
            }
        }
        printf("\n");
    }
}

int main() {
    float earthAngle = 0.0f;
    float moonAngle = 0.0f;

    for (int frame = 0; frame < 360; frame += 5) {
        earthAngle += 5.0f; // ���� ȸ��
        moonAngle += 20.0f; // �� ȸ��

        draw(earthAngle, moonAngle); // �ִϸ��̼� �׸���
        Sleep(100); // 0.1�� ���
    }
    return 0;
}
