#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANDIDATES 6
#define MAX_LEN 100

struct Candidate {
    char name[MAX_LEN];
    char birthday[11];
    char gender;
    char email[MAX_LEN];
    char nationality[MAX_LEN];
    float bmi;
    char main_skill[MAX_LEN];
    char sub_skill[MAX_LEN];
    int topik;
    char mbti[5];
    char intro[300];
};

int get_age(char *birth) {
    int year, month, day;
    sscanf(birth, "%d/%d/%d", &year, &month, &day);

    int current_year = 2025, current_month = 6, current_day = 11;
    int age = current_year - year;

    if (current_month < month || (current_month == month && current_day < day)) {
        age--;
    }
    return age;
}

int main() {
    struct Candidate candidates[CANDIDATES];
    char group_name[MAX_LEN];

    printf("지원하는 오디션 그룹명을 입력하세요: ");
    fgets(group_name, MAX_LEN, stdin);
    group_name[strcspn(group_name, "\n")] = 0; // 개행 제거

    printf("\n####################################\n");
    printf("[%s] 오디션 후보자 데이터 입력\n", group_name);
    printf("####################################\n");

    int i = 0;
    while (i < CANDIDATES) {
        printf("\n%d번째 후보자의 정보를 입력합니다.\n", i + 1);
        printf("---------------------------------\n");

        printf("1. 성명: ");
        fgets(candidates[i].name, MAX_LEN, stdin);
        candidates[i].name[strcspn(candidates[i].name, "\n")] = 0;

        printf("2. 생일(YYYY/MM/DD 형식): ");
        fgets(candidates[i].birthday, 11, stdin);
        getchar(); // 엔터키 처리

        printf("3. 성별(F 또는 M): ");
        scanf(" %c", &candidates[i].gender);
        getchar();

        printf("4. 메일 주소: ");
        fgets(candidates[i].email, MAX_LEN, stdin);
        candidates[i].email[strcspn(candidates[i].email, "\n")] = 0;

        printf("5. 국적: ");
        fgets(candidates[i].nationality, MAX_LEN, stdin);
        candidates[i].nationality[strcspn(candidates[i].nationality, "\n")] = 0;

        printf("6. BMI: ");
        scanf("%f", &candidates[i].bmi);
        getchar();

        printf("7. 주 스킬: ");
        fgets(candidates[i].main_skill, MAX_LEN, stdin);
        candidates[i].main_skill[strcspn(candidates[i].main_skill, "\n")] = 0;

        printf("8. 보조 스킬: ");
        fgets(candidates[i].sub_skill, MAX_LEN, stdin);
        candidates[i].sub_skill[strcspn(candidates[i].sub_skill, "\n")] = 0;

        printf("9. 한국어 등급(TOPIK): ");
        scanf("%d", &candidates[i].topik);
        getchar();

        printf("10. MBTI: ");
        fgets(candidates[i].mbti, 5, stdin);
        candidates[i].mbti[strcspn(candidates[i].mbti, "\n")] = 0;
        getchar();

        printf("11. 소개: ");
        fgets(candidates[i].intro, 300, stdin);
        candidates[i].intro[strcspn(candidates[i].intro, "\n")] = 0;

        i++;
    }

    printf("\n####################################\n");
    printf("[%s] 오디션 후보자 데이터 조회\n", group_name);
    printf("####################################\n");

    printf("=============================================================================================\n");
    printf("성   명(나이) | 생   일     | 성별 | 메   일              | 국적 | BMI | 주스킬 | 보조스킬 | TOPIK | MBTI |\n");
    printf("=============================================================================================\n");

    for (int j = 0; j < CANDIDATES; j++) {
        int age = get_age(candidates[j].birthday);
        printf("%-12s(%2d)| %-10s |  %c  | %-20s | %-5s| %.1f | %-6s | %-8s | %-5s | %-4s |\n",
            candidates[j].name, age, candidates[j].birthday, candidates[j].gender,
            candidates[j].email, candidates[j].nationality, candidates[j].bmi,
            candidates[j].main_skill, candidates[j].sub_skill,
            (candidates[j].topik == 0) ? "원어민" : (candidates[j].topik == 1) ? "1급" : (candidates[j].topik == 2) ? "2급" : (candidates[j].topik == 3) ? "3급" : (candidates[j].topik == 4) ? "4급" : "5급",
            candidates[j].mbti);

        printf("---------------------------------------------------------------------------------------------\n");
        printf("%s\n", candidates[j].intro);
        printf("---------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
