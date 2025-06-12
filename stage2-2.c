#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_MEMBERS 5
#define MAX_QUESTIONS 5
#define MAX_SESSIONS 50
#define MAX_ANSWER_LEN 100

typedef struct {
    char nickname[20];
    int age;
    char trauma[100];
} Trauma;

typedef struct {
    int id;
    char content[150];
} Question;

typedef struct {
    char nickname[20];
    char question[150];
    char answer[MAX_ANSWER_LEN + 1];
} Counseling;

Trauma traumaList[MAX_MEMBERS] = {
    {"Mina", 21, ""},
    {"Jisoo", 22, ""},
    {"Hana", 20, ""},
    {"Yuna", 23, ""},
    {"Sora", 19, ""}
};

const Question questionList[MAX_QUESTIONS] = {
    {1, "어떤 상황에서 그 트라우마를 경험하셨나요?"},
    {2, "해당 상황이 어떻게 당신의 일상생활과 감정에 어떤 영향을 미치고 있는지 말씀해주세요."},
    {3, "이 트라우마를 어떻게 극복하려고 노력하셨나요?"},
    {4, "트라우마와 관련하여 어떤 감정을 느끼고 계신가요?"},
    {5, "트라우마를 극복하기 위해 어떤 지원이 필요한 것으로 생각하시나요?"}
};

Counseling sessionList[MAX_SESSIONS];
int sessionCount = 0;

int findMemberIndex(char *nickname);
void inputTrauma();
void startCounseling();
void showResults();
void traumaSubMenu();
void overcomeTrauma();

int findMemberIndex(char *nickname) {
    int i;
    for (i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(traumaList[i].nickname, nickname) == 0) {
            return i;
        }
    }
    return -1;
}

void inputTrauma() {
    char nickname[20];
    char trauma[100];
    int index;
    while (1) {
        printf("\n닉네임 입력 (종료는 X): ");
        scanf("%s", nickname);
        if (toupper(nickname[0]) == 'X') break;

        index = findMemberIndex(nickname);

        index != -1 ?
            (printf("트라우마 입력: "),
             getchar(), // flush
             fgets(traumaList[index].trauma, sizeof(traumaList[index].trauma), stdin),
             traumaList[index].trauma[strcspn(traumaList[index].trauma, "\n")] = '\0') :
            printf("존재하지 않는 닉네임입니다.\n");
    }
}

// 상담 세션 시작
void startCounseling() {
    char nickname[20];
    int i, j;
    int questionUsed[5] = {0};
    int qindex;
    char answer[MAX_ANSWER_LEN + 1];

    printf("\n[상담 가능한 멤버 목록]\n");
    for (i = 0; i < MAX_MEMBERS; i++) {
        if (strlen(traumaList[i].trauma) > 0) {
            printf("- %s\n", traumaList[i].nickname);
        }
    }

    printf("\n상담할 닉네임 입력: ");
    scanf("%s", nickname);
    int index = findMemberIndex(nickname);
    if (index == -1 || strlen(traumaList[index].trauma) == 0) {
        printf("해당 멤버는 존재하지 않거나 트라우마 정보가 없습니다.\n");
        return;
    }

    srand(time(NULL));
    for (i = 0; i < 3; i++) {
        do {
            qindex = rand() % MAX_QUESTIONS;
        } while (questionUsed[qindex]);
        questionUsed[qindex] = 1;

        printf("\n질문 %d: %s\n", i + 1, questionList[qindex].content);
        printf("답변: ");
        getchar();
        fgets(answer, sizeof(answer), stdin);
        answer[strcspn(answer, "\n")] = '\0';

        while (strlen(answer) == 0 || strlen(answer) > MAX_ANSWER_LEN) {
            printf("유효하지 않은 답변입니다. 다시 입력하세요: ");
            fgets(answer, sizeof(answer), stdin);
            answer[strcspn(answer, "\n")] = '\0';
        }

        strcpy(sessionList[sessionCount].nickname, nickname);
        strcpy(sessionList[sessionCount].question, questionList[qindex].content);
        strcpy(sessionList[sessionCount].answer, answer);
        sessionCount++;
    }

    printf("상담이 완료되었습니다.\n");
}

void showResults() {
    char nickname[20];
    int found = 0;

    printf("\n답변한 멤버 목록:\n");
    for (int i = 0; i < sessionCount; i++) {
        printf("- %s\n", sessionList[i].nickname);
    }

    printf("\n상세 보기 닉네임 입력: ");
    scanf("%s", nickname);

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(traumaList[i].nickname, nickname) == 0) {
            printf("\n[%s님의 트라우마] %s\n", nickname, traumaList[i].trauma);
            break;
        }
    }

    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessionList[i].nickname, nickname) == 0) {
            printf("Q: %s\n", sessionList[i].question);
            printf("A: %s\n", sessionList[i].answer);
            found = 1;
        }
    }

    if (!found) {
        printf("상담 기록이 없습니다.\n");
    }
}

void traumaSubMenu() {
    char choice;
    while (1) {
        printf("\n[트라우마 관리 메뉴]\n");
        printf("1. 트라우마 입력\n");
        printf("2. 상담 세션 시작\n");
        printf("3. 상담 결과 보기\n");
        printf("X. 이전으로\n");
        printf("선택: ");
        scanf(" %c", &choice);

        switch (toupper(choice)) {
            case '1': inputTrauma(); break;
            case '2': startCounseling(); break;
            case '3': showResults(); break;
            case 'X': return;
            default: printf("잘못된 선택입니다.\n");
        }
    }
}

void overcomeTrauma() {
    traumaSubMenu();
}

int main() {
    overcomeTrauma();
    return 0;
}
