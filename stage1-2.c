#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEMBER_COUNT 5
#define TEST_ITEM_COUNT 7
#define NAME_LENGTH 32
#define NICKNAME_LENGTH 16

typedef struct {
    char name[NAME_LENGTH];
    char nickname[NICKNAME_LENGTH];
} Member;

Member milliways_members[MEMBER_COUNT] = {
    {"고은", "goeun"},
    {"원철", "wonchul"},
    {"영진", "youngjin"},
    {"혜경", "hyekyung"},
    {"아서", "arthur"}
};

float health_scores[MEMBER_COUNT][TEST_ITEM_COUNT];

const char *test_items[TEST_ITEM_COUNT] = {
    "1마일 러닝", "스피드 스프린트", "푸시업", "스쿼트",
    "팔굽혀펴기", "수영", "무게 들기"
};

int get_member_index_by_nickname(const char *nickname) {
    for (int i = 0; i < MEMBER_COUNT; ++i) {
        if (strcmp(milliways_members[i].nickname, nickname) == 0) {
            return i;
        }
    }
    return -1;
}

// 체력 입력 함수
void setHealth(void) {
    char nickname[NICKNAME_LENGTH];
    char input[128];
    int index;

    printf("닉네임을 입력하세요: ");
    scanf("%s", nickname);
    index = get_member_index_by_nickname(nickname);

    if (index == -1) {
        printf("해당 닉네임의 멤버를 찾을 수 없습니다.\n");
        return;
    }

    printf("체력 데이터를 쉼표로 구분하여 입력하세요:\n");
    printf("(예: 10.5,12.2,3.5,4.0,5.5,9.3,1.2)\n> ");
    scanf(" %[^\n]", input);

    char *token = strtok(input, ",");
    int i = 0;
    while (token != NULL && i < TEST_ITEM_COUNT) {
        health_scores[index][i] = atof(token);
        token = strtok(NULL, ",");
        i++;
    }

    if (i != TEST_ITEM_COUNT) {
        printf("입력 항목 수가 부족합니다.\n");
    } else {
        printf("체력 정보가 저장되었습니다.\n");
    }
}

// 체력 조회 함수
void getHealth(void) {
    char option[16];
    char nickname[NICKNAME_LENGTH];
    int index;

    printf("조회 옵션을 선택하세요 (all | nickname | item): ");
    scanf("%s", option);

    if (strcmp(option, "all") == 0) {
        for (int i = 0; i < MEMBER_COUNT; ++i) {
            printf("\n[%s (%s)]\n", milliways_members[i].name, milliways_members[i].nickname);
            for (int j = 0; j < TEST_ITEM_COUNT; ++j) {
                printf("%s: %.2f\n", test_items[j], health_scores[i][j]);
            }
        }
    } else if (strcmp(option, "nickname") == 0) {
        printf("멤버 닉네임 입력: ");
        scanf("%s", nickname);
        index = get_member_index_by_nickname(nickname);
        if (index == -1) {
            printf("해당 멤버가 없습니다.\n");
            return;
        }
        printf("\n[%s (%s)]\n", milliways_members[index].name, nickname);
        for (int j = 0; j < TEST_ITEM_COUNT; ++j) {
            printf("%s: %.2f\n", test_items[j], health_scores[index][j]);
        }
    } else if (strcmp(option, "item") == 0) {
        printf("항목 인덱스를 입력하세요 (0~6): ");
        int item;
        scanf("%d", &item);
        if (item < 0 || item >= TEST_ITEM_COUNT) {
            printf("유효하지 않은 항목 인덱스입니다.\n");
            return;
        }
        printf("\n[%s 항목 전체 보기]\n", test_items[item]);
        for (int i = 0; i < MEMBER_COUNT; ++i) {
            printf("%s (%s): %.2f\n", milliways_members[i].name, milliways_members[i].nickname, health_scores[i][item]);
        }
    } else {
        printf("유효하지 않은 옵션입니다.\n");
    }
}

void menu(void) {
    int choice;
    while (1) {
        printf("\n=== 체력 트레이닝 시스템 ===\n");
        printf("1. 체력 상태 입력\n");
        printf("2. 체력 상태 조회\n");
        printf("0. 종료\n");
        printf("선택 > ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                setHealth();
                break;
            case 2:
                getHealth();
                break;
            case 0:
                return;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
}

int main(void) {
    menu();
    return 0;
}
