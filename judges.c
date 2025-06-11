#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_LENGTH 512
#define INFO_FIELDS 7

char judges_array[MAX_JUDGES][MAX_LENGTH];

int count_commas(const char *str) {
    int count = 0;
    while (*str) {
        if (*str == ',') count++;
        str++;
    }
    return count;
}

void trim_newline(char *str) {
    char *pos;
    if ((pos = strchr(str, '\n')) != NULL)
        *pos = '\0';
}

void display_judge_info(const char *json, int index) {
    char buffer[MAX_LENGTH];
    strcpy(buffer, json);

    printf("[심사위원 %d]\n", index + 1);
    char *token = strtok(buffer, ",");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }
    printf("-----------------------------------\n");
}

int main() {
    char project_name[100];
    int total_judges, selected_members;
    int current_count = 0;

    printf("####################################\n");
    printf("#      심사위원 명단 데이터 입력       #\n");
    printf("####################################\n");

    printf("> 참여 프로젝트: ");
    fgets(project_name, sizeof(project_name), stdin);
    trim_newline(project_name);

    printf("> 심사 총 인원: ");
    scanf("%d", &total_judges);

    printf("> 선발 멤버 수: ");
    scanf("%d", &selected_members);
    getchar(); // consume newline

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("%d명의 심사위원 정보 입력을 시작합니다.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    while (current_count < total_judges) {
        printf("*심사위원 %d: ", current_count + 1);
        fgets(judges_array[current_count], MAX_LENGTH, stdin);
        trim_newline(judges_array[current_count]);

        if (count_commas(judges_array[current_count]) != INFO_FIELDS - 1) {
            printf("입력 항목이 정확하지 않습니다. 다시 입력해주세요.\n");
            continue;
        }

        current_count++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("심사위원 정보 입력이 끝났습니다.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    char confirm;
    printf("\"%s 심사위원 정보를 확인할까요? (Y/N): \"", project_name);
    scanf(" %c", &confirm);

    if (confirm == 'Y') {
        printf("####################################\n");
        printf("#        심사위원 데이터 출력        #\n");
        printf("####################################\n");
        for (int i = 0; i < total_judges; i++) {
            display_judge_info(judges_array[i], i);
        }
    } else {
        printf("프로그램을 종료합니다.\n");
    }

    return 0;
}
