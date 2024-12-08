#include <stdio.h>
#include <math.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20
#define SUN_EARTH_DISTANCE 10.0f // 태양으로부터 지구까지의 거리
#define EARTH_MOON_DISTANCE 3.0f   // 지구로부터 달까지의 거리

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    float x, y, w; // 3D 벡터 (동차 좌표)
} vec3;

typedef struct {
    float m[3][3]; // 3x3 행렬
} Matrix3x3;

// 3x3 행렬 초기화
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

// vec3와 행렬 곱셈
vec3 Mul(vec3 a, Matrix3x3 b) {
    vec3 result;
    result.x = b.m[0][0] * a.x + b.m[0][1] * a.y + b.m[0][2] * a.w;
    result.y = b.m[1][0] * a.x + b.m[1][1] * a.y + b.m[1][2] * a.w;
    result.w = a.w; // 동차 좌표이므로 w는 그대로 유지
    return result;
}

// 행렬 곱셈
Matrix3x3 MulMatrix(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j];
        }
    }
    return result;
}

// 이동 행렬 생성
Matrix3x3 createTranslationMatrix(float tx, float ty) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    mat.m[0][2] = tx; // X축 이동
    mat.m[1][2] = ty; // Y축 이동
    return mat;
}

// 회전 행렬 생성
Matrix3x3 createRotationMatrix(float angle) {
    Matrix3x3 mat;
    initIdentityMatrix(&mat);
    float radian = angle * M_PI / 180;
    mat.m[0][0] = cos(radian); // cos(θ)
    mat.m[0][1] = -sin(radian); // -sin(θ)
    mat.m[1][0] = sin(radian); // sin(θ)
    mat.m[1][1] = cos(radian); // cos(θ)
    return mat;
}

// 콘솔 화면 지우기
void clearScreen() {
    system("cls");
}

// 화면 그리기
void draw(float earthAngle, float moonAngle) {
    clearScreen();

    // 태양 위치 (중앙)
    int sunX = WIDTH / 2;
    int sunY = HEIGHT / 2;

    // 태양 초기 위치 (원점)
    vec3 sunPos = { 0.0f, 0.0f, 1.0f }; // 태양 동차 좌표
    // 지구 초기 위치 (태양으로부터의 거리)
    vec3 earthPos = { 0.0f, SUN_E\RTH_DISTANCE, 1.0f }; // 지구 동차 좌표
    // 달 초기 위치 (지구로부터의 거리)
    vec3 moonPos = { 0.0f, EARTH_MOON_DISTANCE, 1.0f }; // 달 동차 좌표

    // 지구 회전
    Matrix3x3 earthRotation = createRotationMatrix(earthAngle);
    earthPos = Mul(earthPos, earthRotation);

    // 지구 위치 변환 (태양 위치에 기반하여)
    vec3 earthScreenPos = { earthPos.x + sunX, earthPos.y + sunY, 1.0f }; // 화면상의 지구 위치

    // 달의 위치는 지구를 기준으로 회전하고, 거리만큼 떨어져 있도록 설정
    // 달 회전 (지구를 중심으로)
    Matrix3x3 moonRotation = createRotationMatrix(moonAngle);
    moonPos = Mul(moonPos, moonRotation);

    // 달 위치 변환 (지구 위치에 기반하여)
    moonPos = Mul(moonPos, createTranslationMatrix(earthScreenPos.x, earthScreenPos.y));

    // 화면 그리기
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == sunX && y == sunY) {
                printf("S"); // 태양(S) 출력
            }
            else if ((int)earthScreenPos.x == x && (int)earthScreenPos.y == y) {
                printf("E"); // 지구(E) 출력
            }
            else if ((int)moonPos.x == x && (int)moonPos.y == y) {
                printf("M"); // 달(M) 출력
            }
            else {
                printf(" "); // 빈 공간 출력
            }
        }
        printf("\n");
    }
}

int main() {
    float earthAngle = 0.0f;
    float moonAngle = 0.0f;

    for (int frame = 0; frame < 360; frame += 5) {
        earthAngle += 5.0f; // 지구 회전
        moonAngle += 20.0f; // 달 회전

        draw(earthAngle, moonAngle); // 애니메이션 그리기
        Sleep(100); // 0.1초 대기
    }
    return 0;
}
