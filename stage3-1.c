#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CARDS 24
#define MAX_SCORES 100
#define QUIZ_COUNT 5

typedef struct {
    char kor[10];
    char eng_letter[5];
    char eng_pron[20];
} HangulCard;

typedef struct {
    char name[20];
    char type[3];
    int scores[3];
    int attempts;
} Score;

HangulCard consonants[] = {
    {"ㄱ", "g", "giyeok"}, {"ㄴ", "n", "nieun"}, {"ㄷ", "d", "digeut"}, {"ㄹ", "r", "rieul"},
    {"ㅁ", "m", "mieum"}, {"ㅂ", "b", "bieup"}, {"ㅅ", "s", "siot"}, {"ㅇ", "-", "ieung"},
    {"ㅈ", "j", "jieut"}, {"ㅊ", "ch", "chieut"}, {"ㅋ", "k", "kieuk"}, {"ㅌ", "t", "tieut"},
    {"ㅍ", "p", "pieup"}, {"ㅎ", "h", "hieut"}
};

HangulCard vowels[] = {
    {"ㅏ", "a", "a"}, {"ㅑ", "ya", "ya"}, {"ㅓ", "eo", "eo"}, {"ㅕ", "yeo", "yeo"},
    {"ㅗ", "o", "o"}, {"ㅛ", "yo", "yo"}, {"ㅜ", "u", "u"}, {"ㅠ", "yu", "yu"},
    {"ㅡ", "eu", "eu"}, {"ㅣ", "i", "i"}
};

Score results[MAX_SCORES];
int resultCount = 0;

void shuffle(int *arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

Score* findOrCreateScore(const char *name, const char *type) {
    for (int i = 0; i < resultCount; i++) {
        if (strcmp(results[i].name, name) == 0 && strcmp(results[i].type, type) == 0)
            return &results[i];
    }
    if (resultCount < MAX_SCORES) {
        strcpy(results[resultCount].name, name);
        strcpy(results[resultCount].type, type);
        results[resultCount].attempts = 0;
        return &results[resultCount++];
    }
    return NULL;
}

void playGame(HangulCard *cards, int cardCount, const char *name, const char *type, int mode) {
    int indices[cardCount];
    for (int i = 0; i < cardCount; i++) indices[i] = i;
    shuffle(indices, cardCount);

    int score = 0;
    char input[50];

    for (int i = 0; i < QUIZ_COUNT; i++) {
        int idx = indices[i];
        if (mode == 1) {
            printf("Q%d. %s: ", i + 1, cards[idx].kor);
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;
            char answer[50];
            sprintf(answer, "%s,%s", cards[idx].eng_letter, cards[idx].eng_pron);
            if (strcmp(input, answer) == 0) score += 10;
        } else {
            printf("Q%d. %s (%s): ", i + 1, cards[idx].eng_letter, cards[idx].eng_pron);
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;
            if (strcmp(input, cards[idx].kor) == 0) score += 10;
        }
    }

    Score *s = findOrCreateScore(name, type);
    if (s != NULL && s->attempts < 3) {
        s->scores[s->attempts] = score;
        s->attempts++;
    }
    printf("총점: %d점\n", score);
}

int compareAvgScore(const void *a, const void *b) {
    const Score *s1 = (const Score *)a;
    const Score *s2 = (const Score *)b;
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < s1->attempts; i++) sum1 += s1->scores[i];
    for (int i = 0; i < s2->attempts; i++) sum2 += s2->scores[i];
    int avg1 = s1->attempts ? sum1 / s1->attempts : 0;
    int avg2 = s2->attempts ? sum2 / s2->attempts : 0;
    return avg1 - avg2;
}

void showResult() {
    for (int t = 0; t < 2; t++) {
        char *type = (t == 0) ? "KE" : "EK";
        Score filtered[MAX_SCORES];
        int count = 0;

        for (int i = 0; i < resultCount; i++) {
            if (strcmp(results[i].type, type) == 0) {
                filtered[count++] = results[i];
            }
        }

        qsort(filtered, count, sizeof(Score), compareAvgScore);

        printf("=== %s 결과 ===\n", type);
        for (int i = 0; i < count; i++) {
            int total = 0;
            for (int j = 0; j < filtered[i].attempts; j++) total += filtered[i].scores[j];
            int avg = filtered[i].attempts ? total / filtered[i].attempts : 0;
            printf("%d등: %s, 평균: %d점\n", i + 1, filtered[i].name, avg);
        }
    }
}

void learnHangul() {
    char name[20], menu[5], sub[5];
    srand((unsigned)time(NULL));

    printf("학습자 이름: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    while (1) {
        printf("\n1. 한글 표시 영어 입력\n2. 영어 표시 한글 입력\n3. 결과 확인\n0. 돌아가기\n선택: ");
        fgets(menu, sizeof(menu), stdin);
        menu[strcspn(menu, "\n")] = 0;

        if (strcmp(menu, "0") == 0) break;
        else if (strcmp(menu, "1") == 0 || strcmp(menu, "2") == 0) {
            printf("1. 자음 학습\n2. 모음 학습\n선택: ");
            fgets(sub, sizeof(sub), stdin);
            sub[strcspn(sub, "\n")] = 0;

            int isConsonant = strcmp(sub, "1") == 0;
            HangulCard *cards = isConsonant ? consonants : vowels;
            int count = isConsonant ? sizeof(consonants) / sizeof(HangulCard) : sizeof(vowels) / sizeof(HangulCard);
            char type[3];

            if (strcmp(menu, "1") == 0) {
                strcpy(type, "KE");
                playGame(cards, count, name, type, 1);
            } else {
                strcpy(type, "EK");
                playGame(cards, count, name, type, 2);
            }
        } else if (strcmp(menu, "3") == 0) {
            showResult();
        }
    }
}

int main() {
    learnHangul();
    return 0;
}
