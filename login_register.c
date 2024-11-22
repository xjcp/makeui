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

int userLogin(const char *id, const char *passwd);
int userRegister(char *id, char *passwd);
void drawLoginButton(WINDOW *win, int focus);
void drawRegisterButton(WINDOW *win, int focus);
void drawLoginWindow(WINDOW *win, int focus, const char *msg, const char *id, const char *passwd);
void drawRegisterWindow(WINDOW *win, int focus, const char *msg, const char *id, const char *passwd);
void handleLogin(WINDOW *win);
void handleRegister(WINDOW *win);

// 간단한 로그인 함수
int userLogin(const char *id, const char *passwd) {
    if (strcmp(id, "admin") == 0 && strcmp(passwd, "1234") == 0) {
        return 1; // 로그인 성공
    }
    return 0; // 로그인 실패
}

// 간단한 회원가입 함수
int userRegister(char *id, char *passwd) {
    if (strcmp(id, "admin") == 0) {
        return 0; // 이미 존재하는 아이디
    }
    return 1; // 회원가입 성공
}

// 로그인 버튼을 그리는 함수
void drawLoginButton(WINDOW *win, int focus) {
    int buttonStartY = 9;
    int buttonStartX = 18;

    if (focus == 2) {
        wattron(win, A_REVERSE);
    }

    mvwprintw(win, buttonStartY, buttonStartX, "Login");

    if (focus == 2) {
        wattroff(win, A_REVERSE);
    }

    wrefresh(win);
}

// 회원가입 버튼을 그리는 함수
void drawRegisterButton(WINDOW *win, int focus) {
    int buttonStartY = 11;
    int buttonStartX = 14;

    if (focus == 3) {
        wattron(win, A_REVERSE);
    }

    mvwprintw(win, buttonStartY, buttonStartX, "Go To Register");

    if (focus == 3) {
        wattroff(win, A_REVERSE);
    }

    wrefresh(win);
}

// 로그인 창을 그리는 함수
void drawLoginWindow(WINDOW *win, int focus, const char *msg, const char *id, const char *passwd) {
    box(win, 0, 0);
    mvwprintw(win, 1, 13, "Welcome to Blog!");

    if (focus == 0) {
        wattron(win, A_REVERSE);
        mvwprintw(win, 3, 3, "ID:");
        mvwprintw(win, 3, 6, "%s", id);
        wattroff(win, A_REVERSE);
    } else {
        mvwprintw(win, 3, 3, "ID:");
        mvwprintw(win, 3, 6, "%s", id);
    }

    if (focus == 1) {
        wattron(win, A_REVERSE);
        mvwprintw(win, 5, 3, "Password:");
        mvwprintw(win, 5, 12, "%s", passwd);
        wattroff(win, A_REVERSE);
    } else {
        mvwprintw(win, 5, 3, "Password:");
        mvwprintw(win, 5, 12, "%s", passwd);
    }

    mvwprintw(win, 7, 1, "                                     ");
    mvwprintw(win, 7, 3, msg);

    drawLoginButton(win, focus);
    drawRegisterButton(win, focus);

    wrefresh(win);
}

// 로그인 버튼을 그리는 함수
void drawRegisterButton2(WINDOW *win, int focus) {
    int buttonStartY = 9;
    int buttonStartX = 16;

    if (focus == 2) {
        wattron(win, A_REVERSE);
    }

    mvwprintw(win, buttonStartY, buttonStartX, "Register");

    if (focus == 2) {
        wattroff(win, A_REVERSE);
    }

    wrefresh(win);
}

// 회원가입 버튼을 그리는 함수
void drawLoginButton2(WINDOW *win, int focus) {
    int buttonStartY = 11;
    int buttonStartX = 15;

    if (focus == 3) {
        wattron(win, A_REVERSE);
    }

    mvwprintw(win, buttonStartY, buttonStartX, "Go To Login");

    if (focus == 3) {
        wattroff(win, A_REVERSE);
    }

    wrefresh(win);
}

// 회원가입 창을 그리는 함수
void drawRegisterWindow(WINDOW *win, int focus, const char *msg, const char *id, const char *passwd) {
    box(win, 0, 0);
    mvwprintw(win, 1, 9, "Register a New Account");

    if (focus == 0) {
        wattron(win, A_REVERSE);
        mvwprintw(win, 3, 3, "ID:");
        mvwprintw(win, 3, 6, "%s", id);
        wattroff(win, A_REVERSE);
    } else {
        mvwprintw(win, 3, 3, "ID:");
        mvwprintw(win, 3, 6, "%s", id);
    }

    if (focus == 1) {
        wattron(win, A_REVERSE);
        mvwprintw(win, 5, 3, "Password:");
        mvwprintw(win, 5, 12, "%s", passwd);
        wattroff(win, A_REVERSE);
    } else {
        mvwprintw(win, 5, 3, "Password:");
        mvwprintw(win, 5, 12, "%s", passwd);
    }

    mvwprintw(win, 7, 1, "                                     ");
    mvwprintw(win, 7, 3, msg);

    drawLoginButton2(win, focus);
    drawRegisterButton2(win, focus);

    wrefresh(win);
}


// 로그인 및 회원가입 메인 화면을 관리하는 함수
void handleLogin(WINDOW *win) {
    int focus = 0; // 0: ID, 1: Password, 2: Login Button, 3: Register Button
    char id[MAX_LEN] = "";
    char passwd[MAX_LEN] = "";
    char message[100] = "Please enter your ID and Password.";

    // 로그인 창 크기 설정
    int loginHeight = 14, loginWidth = 40;
    int loginStartY = 5, loginStartX = 40;
    WINDOW *loginWin = newwin(loginHeight, loginWidth, loginStartY, loginStartX);

    // 로그인 창을 그립니다.
    drawLoginWindow(loginWin, focus, message, id, passwd);

    // 포커스 이동과 입력을 처리하는 루프
    while (1) {
        int ch = wgetch(loginWin); // 키 입력 받기

        if (ch == 'w' || ch == 'W') {
            focus = (focus == 3) ? 2 : (focus == 2) ? 1 : (focus == 1) ? 0 : focus;
        } else if (ch == 's' || ch == 'S') {
            focus = (focus == 0) ? 1 : (focus == 1) ? 2 : (focus == 2) ? 3 : focus;
        } else if (ch == 10) { // Enter 키를 누르면
            if (focus == 0) {
                // ID 입력 받기
                wattroff(loginWin, A_REVERSE);
                mvwprintw(loginWin, 3, 3, "ID:");
                mvwprintw(loginWin, 3, 6, "                ");
                wrefresh(loginWin);
                echo();
                mvwgetnstr(loginWin, 3, 6, id, sizeof(id) - 1);
                noecho();
            } else if (focus == 1) {
                // Password 입력 받기
                wattroff(loginWin, A_REVERSE);
                mvwprintw(loginWin, 5, 3, "Password:");
                mvwprintw(loginWin, 5, 12, "                ");
                wrefresh(loginWin);
                echo();
                mvwgetnstr(loginWin, 5, 12, passwd, sizeof(passwd) - 1);
                noecho();
            } else if (focus == 2) {
                // 로그인 버튼을 클릭하면 로그인 시도
                if (userLogin(id, passwd)) {
                    strcpy(message, "        Login successful!");
                    // 로그인 성공 후 다음 단계로 이동
                    break;
                } else {
                    strcpy(message, "           Login failed!");
                }
            } else if (focus == 3) {
                // 회원가입 버튼 클릭 시 회원가입 창으로 이동
                clear();  // 화면을 지우고
                refresh(); // 화면을 새로 고침
                handleRegister(win); // 회원가입 창으로 이동
                return;
            }
        }

        drawLoginWindow(loginWin, focus, message, id, passwd);
    }
}

void handleRegister(WINDOW *win) {
    int registerFocus = 0; // 0: ID, 1: Password, 2: Register Button, 3: Back to Login Button
    char id[MAX_LEN] = "";
    char passwd[MAX_LEN] = "";
    char registerMessage[100] = "  Enter your new ID and Password.";

    // 회원가입 창 크기 설정
    int registerHeight = 14, registerWidth = 40;
    int registerStartY = 5, registerStartX = 40;
    WINDOW *registerWin = newwin(registerHeight, registerWidth, registerStartY, registerStartX);

    // 회원가입 창을 그립니다.
    drawRegisterWindow(registerWin, registerFocus, registerMessage, id, passwd);

    // 포커스 이동과 입력을 처리하는 루프
    while (1) {
        int ch = wgetch(registerWin); // 키 입력 받기

        if (ch == 'w' || ch == 'W') {
            registerFocus = (registerFocus == 3) ? 2 : (registerFocus == 2) ? 1 : (registerFocus == 1) ? 0 : registerFocus;
        } else if (ch == 's' || ch == 'S') {
            registerFocus = (registerFocus == 0) ? 1 : (registerFocus == 1) ? 2 : (registerFocus == 2) ? 3 : registerFocus;
        } else if (ch == 10) { // Enter 키를 누르면
            if (registerFocus == 0) {
                // ID 입력 받기
                wattroff(registerWin, A_REVERSE);
                mvwprintw(registerWin, 3, 3, "ID:");
                mvwprintw(registerWin, 3, 6, "                ");
                wrefresh(registerWin);
                echo();
                mvwgetnstr(registerWin, 3, 6, id, sizeof(id) - 1);
                noecho();
            } else if (registerFocus == 1) {
                // Password 입력 받기
                wattroff(registerWin, A_REVERSE);
                mvwprintw(registerWin, 5, 3, "Password:");
                mvwprintw(registerWin, 5, 12, "                ");
                wrefresh(registerWin);
                echo();
                mvwgetnstr(registerWin, 5, 12, passwd, sizeof(passwd) - 1);
                noecho();
            } else if (registerFocus == 3) {
                // "Back to Login" 버튼 클릭 시 로그인 화면으로 돌아감
                clear();  // 화면을 지우고
                refresh(); // 화면을 새로 고침
                handleLogin(win); // 로그인 화면으로 돌아가는 함수 호출
                return;
            } else if (registerFocus == 2) {
                // 회원가입 버튼 클릭 시
                if (userRegister(id, passwd)) {
                    strcpy(registerMessage, "Registration successful!");
                    clear();  // 화면을 지우고
                    refresh(); // 화면을 새로 고침
                    handleLogin(win); // 로그인 화면으로 돌아가기
                    return;
                } else {
                    strcpy(registerMessage, "ID already exists.");
                }
            }
        }
        drawRegisterWindow(registerWin, registerFocus, registerMessage, id, passwd);
    }
}