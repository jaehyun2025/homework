#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_QUESTIONS 10
#define QUIZ_SIZE 5
#define MAX_TRAINEES 4
#define NAME_LEN 50

typedef struct {
    int id;
    char question[100];
    char answer[100];
} Question;

typedef struct {
    char name[NAME_LEN];
    char nickname[NAME_LEN];
    char nationality[NAME_LEN];
    int score;
    int passed;
} Trainee;

typedef struct {
    int questionID;
    char correct;
} AnswerSheet;

Question questionBank[MAX_QUESTIONS] = {
    {1, "What is '안녕하세요' in English?", "Hello"},
    {2, "Translate '사랑' into English.", "Love"},
    {3, "What is the Korean word for 'Thank you'?", "감사합니다"},
    {4, "Translate '행복' into English.", "Happiness"},
    {5, "What does '학교' mean?", "School"},
    {6, "Translate '친구' into English.", "Friend"},
    {7, "What is '물' in English?", "Water"},
    {8, "Translate '시간' into English.", "Time"},
    {9, "What does '배고파요' mean?", "I'm hungry"},
    {10, "Translate '예쁘다' into English.", "Pretty"}
};

Trainee trainees[MAX_TRAINEES] = {
    {"박지연", "Jiyeon", "Korea", 0, 0},
    {"Alex", "Lex", "USA", 0, 0},
    {"Hana", "HanaB", "Japan", 0, 0},
    {"Liam", "Limo", "Canada", 0, 0}
};

AnswerSheet answerSheet[QUIZ_SIZE];

void selectRandomTakers(Trainee **taker) {
    time_t t = time(NULL);
    srand((unsigned int)t);
    int index;
    do {
        index = rand() % MAX_TRAINEES;
    } while (strcmp(trainees[index].nationality, "Korea") == 0);
    *taker = &trainees[index];
    printf("\n{%s}님, 한국어 퀴즈 세션에 오신 걸 환영합니다!\n", trainees[index].name);
}

void serveRandomQuiz(Trainee *taker) {
    int selected[QUIZ_SIZE] = {0};
    int used[MAX_QUESTIONS] = {0};
    char userAnswer[100];
    int totalScore = 0;

    printf("30초 뒤에 퀴즈가 시작됩니다...\n");
    sleep(30);

    srand((unsigned int)time(NULL));
    for (int i = 0; i < QUIZ_SIZE; ) {
        int idx = rand() % MAX_QUESTIONS;
        if (used[idx]) continue;
        used[idx] = 1;
        selected[i] = idx;
        printf("\nQ%d. %s\n> ", i + 1, questionBank[idx].question);
        fgets(userAnswer, sizeof(userAnswer), stdin);
        userAnswer[strcspn(userAnswer, "\n")] = '\0';

        answerSheet[i].questionID = questionBank[idx].id;
        if (strlen(userAnswer) == 0 || strcmp(userAnswer, questionBank[idx].answer) != 0) {
            answerSheet[i].correct = 'X';
        } else {
            answerSheet[i].correct = 'O';
            totalScore += 20;
        }
        i++;
    }

    taker->score = totalScore;
    taker->passed = (totalScore >= 80) ? 1 : 0;

    printf("\n--- 퀴즈 결과 ---\n");
    for (int i = 0; i < QUIZ_SIZE; i++) {
        printf("문제 ID: %d - %c\n", answerSheet[i].questionID, answerSheet[i].correct);
    }
    printf("총점: %d점\n", taker->score);
    printf("합격 여부: %s\n", taker->passed ? "합격" : "불합격");
}

void testKoreanLang() {
    Trainee *taker;
    selectRandomTakers(&taker);
    serveRandomQuiz(taker);
}

int main() {
    int choice;
    while (1) {
        printf("\n[II. 훈련 > 3. 언어 및 발음 훈련 > A. 한국어 퀴즈]\n");
        printf("1. 한국어 퀴즈 시작\n0. 종료\n> ");
        scanf("%d", &choice);
        getchar();
        if (choice == 1) {
            testKoreanLang();
        } else {
            break;
        }
    }
    return 0;
}
