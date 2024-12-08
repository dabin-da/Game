#include <stdio.h>
#include <string.h>

// GameObject_Dot ����ü ����
typedef struct {
    int x, y;        // ���� ��ǥ
    char symbol[3];  // ���� ǥ���� ��ȣ
} GameObject_Dot;

// �ܼ� ȭ�鿡 �ﰢ���� �׸��� �Լ�
void draw_triangle(int base_width, int height) {
    for (int i = 0; i < height; i++) {
        // ���� ���� ���
        for (int j = 0; j < height - i - 1; j++) {
            printf(" ");
        }
        // �ﰢ���� �� ���
        for (int k = 0; k < (2 * i + 1); k++) {
            printf("*");
        }
        printf("\n");
    }
}

// ���� ����ϴ� �Լ�
void draw_dot(GameObject_Dot dot) {
    // y ��ǥ��ŭ �� �ٲٱ�
    for (int i = 0; i < dot.y; i++) {
        printf("\n");
    }
    // x ��ǥ��ŭ ���� ���
    for (int i = 0; i < dot.x; i++) {
        printf(" ");
    }
    // �� ���
    printf("%s\n", dot.symbol);
}

int main() {
    // �ﰢ���� ���̿� �غ� ����
    int triangle_height = 5;
    int triangle_base = triangle_height * 2 - 1;

    // �ﰢ�� �׸���
    draw_triangle(triangle_base, triangle_height);

    // �ﰢ���� ��� �������� �� �׸���
    GameObject_Dot dot;
    dot.x = triangle_height;                    // �ﰢ�� �������� x ��ǥ
    dot.y = 1;                                  // �ﰢ�� �������� y ��ǥ
    strcpy_s(dot.symbol, sizeof(dot.symbol), "++");  // "++" ��ȣ�� �� ����

    // �ﰢ�� �������� �� �׸���
    draw_dot(dot);

    // ���α׷� ���� ���
    printf("\nPress Enter to exit...");
    char temp;
    temp = getchar();  // ��ȯ���� ������ ����

    return 0;
}
