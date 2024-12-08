#include <stdio.h>
#include <windows.h>  // Sleep 함수 사용을 위한 헤더

// FPS를 설정하는 함수
void setFPS(int fps) {
    int delay = 1000 / fps; // 한 프레임에 걸리는 시간 (ms 단위)
    Sleep(delay);  // 일정 시간 대기
}

int main() {
    int fps = 30;  // FPS를 30으로 설정

    while (1) {
        // 화면을 업데이트하거나 게임 로직을 처리하는 코드 작성
        printf("Frame Updated\n");

        // FPS 맞추기
        setFPS(fps);
    }

    return 0;
}
