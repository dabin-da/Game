#include <stdio.h>
#include <string.h>

// GameObject_Dot 구조체 정의
typedef struct {
    int x, y;        // 점의 좌표
    char symbol[3];  // 점을 표시할 기호
} GameObject_Dot;

// 콘솔 화면에 삼각형을 그리는 함수
void draw_triangle(int base_width, int height) {
    for (int i = 0; i < height; i++) {
        // 왼쪽 공백 출력
        for (int j = 0; j < height - i - 1; j++) {
            printf(" ");
        }
        // 삼각형의 별 출력
        for (int k = 0; k < (2 * i + 1); k++) {
            printf("*");
        }
        printf("\n");
    }
}

// 점을 출력하는 함수
void draw_dot(GameObject_Dot dot) {
    // y 좌표만큼 줄 바꾸기
    for (int i = 0; i < dot.y; i++) {
        printf("\n");
    }
    // x 좌표만큼 공백 출력
    for (int i = 0; i < dot.x; i++) {
        printf(" ");
    }
    // 점 출력
    printf("%s\n", dot.symbol);
}

int main() {
    // 삼각형의 높이와 밑변 설정
    int triangle_height = 5;
    int triangle_base = triangle_height * 2 - 1;

    // 삼각형 그리기
    draw_triangle(triangle_base, triangle_height);

    // 삼각형의 상단 꼭지점에 점 그리기
    GameObject_Dot dot;
    dot.x = triangle_height;                    // 삼각형 꼭지점의 x 좌표
    dot.y = 1;                                  // 삼각형 꼭지점의 y 좌표
    strcpy_s(dot.symbol, sizeof(dot.symbol), "++");  // "++" 기호로 점 설정

    // 삼각형 꼭지점에 점 그리기
    draw_dot(dot);

    // 프로그램 종료 대기
    printf("\nPress Enter to exit...");
    char temp;
    temp = getchar();  // 반환값을 변수에 저장

    return 0;
}
