#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 30

// 사용자 정보 구조체
typedef struct UserInfo {
    char id[MAX_LEN];
    char passwd[MAX_LEN];
} UserInfo;

// 간단한 로그인 함수
int userLogin(const char *id, const char *passwd) {
    // 실제 시스템에서는 사용자 정보를 데이터베이스나 파일에서 확인할 수 있음
    if (strcmp(id, "admin") == 0 && strcmp(passwd, "1234") == 0) {
        return 1; // 로그인 성공
    }
    return 0; // 로그인 실패
}

// 로그인 창을 그리는 함수
void drawLoginWindow(WINDOW *win, int focus, const char *msg, const char *id, const char *passwd) {
    box(win, 0, 0); // 창 테두리 그리기

    // Welcome 메시지
    mvwprintw(win, 1, 12, "Welcome to Blog!");

    // ID: 텍스트와 입력값 표시
    if (focus == 0) {
        wattron(win, A_REVERSE); // 포커스가 있으면 하이라이트
        mvwprintw(win, 3, 3, "ID:");
        mvwprintw(win, 3, 6, "%s", id); // 입력된 ID 표시
        wattroff(win, A_REVERSE); // 하이라이트 해제
    } else {
        mvwprintw(win, 3, 3, "ID:");
        mvwprintw(win, 3, 6, "%s", id); // 입력된 ID 표시
    }

    // Password: 텍스트와 입력값 표시
    if (focus == 1) {
        wattron(win, A_REVERSE); // 포커스가 있으면 하이라이트
        mvwprintw(win, 5, 3, "Password:");
        mvwprintw(win, 5, 12, "%s", passwd); // 입력된 Password 표시
        wattroff(win, A_REVERSE); // 하이라이트 해제
    } else {
        mvwprintw(win, 5, 3, "Password:");
        mvwprintw(win, 5, 12, "%s", passwd); // 입력된 Password 표시
    }

    // 로그인 메시지 출력
    mvwprintw(win, 7, 1, "                                     "); // 메시지를 지운다
    mvwprintw(win, 7, 3, msg);  // 새로운 메시지 출력

    wrefresh(win);
}

// 로그인 버튼을 그리는 함수 (단순 텍스트)
void drawLoginButton(WINDOW *win, int focus) {
    int buttonStartY = 9;
    int buttonStartX = 17;

    // 포커스가 있을 때만 하이라이트
    if (focus == 2) {
        wattron(win, A_REVERSE); // 포커스가 있을 때 텍스트 하이라이트
    }

    mvwprintw(win, buttonStartY, buttonStartX, "Login"); // 버튼 안에 텍스트

    if (focus == 2) {
        wattroff(win, A_REVERSE); // 포커스를 떼면 하이라이트를 해제
    }

    wrefresh(win);
}

// 배경과 전체 UI를 그리는 함수
void drawBackground(WINDOW *win) {
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 50; x++) {
            if (x == 0 || x == 49 || y == 0 || y == 19) {
                mvwaddch(win, y, x, '#');
            }
        }
    }

    wrefresh(win);
}

// 메인 메뉴
void mainMenu(WINDOW *win) {
    int choice;
    char id[MAX_LEN] = "";
    char passwd[MAX_LEN] = "";
    int focus = 0; // 0: ID, 1: Password, 2: Login Button
    WINDOW *loginWin;

    // 로그인 창 크기 설정
    int loginHeight = 12, loginWidth = 40;
    int loginStartY = 5, loginStartX = 40;
    loginWin = newwin(loginHeight, loginWidth, loginStartY, loginStartX);

    // 배경 크기 설정
    int height = 20, width = 50;
    int start_y = 1, start_x = 1;
    WINDOW *bgWin = newwin(height, width, start_y, start_x);

    // 배경 그리기
    drawBackground(bgWin);

    // 사용자 입력 받기
    char input[MAX_LEN];
    char message[100] = "Please enter your ID and Password.";

    // 로그인 창을 그립니다.
    drawLoginWindow(loginWin, focus, message, id, passwd);
    drawLoginButton(loginWin, focus);

    while (1) {
        int ch = wgetch(loginWin); // 키 입력 받기

        // 'W', 'A', 'S', 'D' 키로 포커스 이동
        if (ch == 'w' || ch == 'W') {
            if (focus == 2) {
                focus = 1;  // Password로 포커스 이동
            } else if (focus == 1) {
                focus = 0;  // ID로 포커스 이동
            }
        } else if (ch == 's' || ch == 'S') {
            if (focus == 0) {
                focus = 1;  // Password로 포커스 이동
            } else if (focus == 1) {
                focus = 2;  // Login 버튼으로 포커스 이동
            }
        } else if (ch == 'a' || ch == 'A') {
            if (focus == 2) {
                focus = 1;  // Password로 포커스 이동
            }
        } else if (ch == 'd' || ch == 'D') {
            if (focus == 1) {
                focus = 2;  // Login 버튼으로 포커스 이동
            }
        } else if (ch == 10) { // Enter 키를 누르면 로그인 시도
            if (focus == 0) {
                // ID 입력 받기
                mvwprintw(loginWin, 3, 6, "                ");  // 이전에 입력한 내용 지우기
                echo();
                mvwgetnstr(loginWin, 3, 6, input, sizeof(input) - 1);
                noecho();
                strcpy(id, input);
            } else if (focus == 1) {
                // Password 입력 받기
                mvwprintw(loginWin, 5, 12, "                ");  // 이전에 입력한 내용 지우기
                echo();
                mvwgetnstr(loginWin, 5, 12, input, sizeof(input) - 1);
                noecho();
                strcpy(passwd, input);
            } else if (focus == 2) {
                // 로그인 버튼을 클릭하면 로그인 시도
                if (userLogin(id, passwd)) {
                    strcpy(message, "        Login successful!");
                } else {
                    strcpy(message, "          Login failed!");
                }
            }

            // 로그인 창 다시 그리기
            drawBackground(bgWin);
            drawLoginWindow(loginWin, focus, message, id, passwd);
            drawLoginButton(loginWin, focus);
        }

        // 로그인 창 다시 그리기
        drawLoginWindow(loginWin, focus, message, id, passwd);
        drawLoginButton(loginWin, focus);
    }
}

int main() {
    // ncurses 초기화
    initscr();
    cbreak();
    noecho();
    curs_set(1);

    // 터미널 크기 고정
    resize_term(30, 80);  // 터미널 크기를 50x20으로 고정

    // 메인 메뉴 실행
    mainMenu(stdscr);

    // ncurses 종료
    endwin();
    return 0;
}
