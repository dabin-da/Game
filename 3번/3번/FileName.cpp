#include <stdio.h>
#include <windows.h>  // Sleep �Լ� ����� ���� ���

// FPS�� �����ϴ� �Լ�
void setFPS(int fps) {
    int delay = 1000 / fps; // �� �����ӿ� �ɸ��� �ð� (ms ����)
    Sleep(delay);  // ���� �ð� ���
}

int main() {
    int fps = 30;  // FPS�� 30���� ����

    while (1) {
        // ȭ���� ������Ʈ�ϰų� ���� ������ ó���ϴ� �ڵ� �ۼ�
        printf("Frame Updated\n");

        // FPS ���߱�
        setFPS(fps);
    }

    return 0;
}
