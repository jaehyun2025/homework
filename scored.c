#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CANDIDATES 6
#define NUM_FIELDS 5

// 후보자 이름과 ID
char *candidate_names[NUM_CANDIDATES] = {
    "박지연", "Ethan Smith", "Helena Silva",
    "Liam Wilson", "김민준", "Sophie Lee"
};

int candidate_ids[NUM_CANDIDATES] = {
    100001, 100002, 100003, 100004, 100005, 100006
};

int scoring_sheet[NUM_CANDIDATES][7] = {0};


char *fields[NUM_FIELDS] = {"음악 소양", "댄스", "보컬", "비주얼", "전달력"};

int get_valid_score(const char *field) {
    int score;
    while (1) {
        printf("%s: ", field);
        scanf("%d", &score);
        if (score >= 10 && score <= 100) break;
        printf("잘못된 점수입니다. 10~100 사이로 다시 입력하세요.\n");
    }
    return score;
}

// 한 후보자 점수 입력
void input_scores(int field_index) {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("후보자: %s\n", candidate_names[i]);
        scoring_sheet[i][0] = candidate_ids[i];
        scoring_sheet[i][field_index + 1] = get_valid_score(fields[field_index]);
        printf("------------------------------------\n");
    }
}

void calculate_totals() {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        int sum = 0;
        for (int j = 1; j <= NUM_FIELDS; j++) {
            sum += scoring_sheet[i][j];
        }
        scoring_sheet[i][6] = sum;
    }
}

void print_scores(int field_index) {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("%s: %d\n", candidate_names[i], scoring_sheet[i][field_index + 1]);
    }
}

void modify_scores(int field_index) {
    while (1) {
        int id, found = -1;
        printf("수정할 후보자 ID를 입력하세요 (종료: 0): ");
        scanf("%d", &id);
        if (id == 0) break;

        for (int i = 0; i < NUM_CANDIDATES; i++) {
            if (candidate_ids[i] == id) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            printf("해당 ID의 후보자를 찾을 수 없습니다.\n");
        } else {
            printf("후보자 %s의 %s 점수를 수정합니다.\n", candidate_names[found], fields[field_index]);
            scoring_sheet[found][field_index + 1] = get_valid_score(fields[field_index]);
        }
    }
}

void show_final_results() {
    for (int i = 0; i < NUM_CANDIDATES - 1; i++) {
        for (int j = i + 1; j < NUM_CANDIDATES; j++) {
            if (scoring_sheet[i][6] < scoring_sheet[j][6]) {
                int temp[7];
                memcpy(temp, scoring_sheet[i], sizeof(temp));
                memcpy(scoring_sheet[i], scoring_sheet[j], sizeof(temp));
                memcpy(scoring_sheet[j], temp, sizeof(temp));

                char *tmp_name = candidate_names[i];
                candidate_names[i] = candidate_names[j];
                candidate_names[j] = tmp_name;

                int tmp_id = candidate_ids[i];
                candidate_ids[i] = candidate_ids[j];
                candidate_ids[j] = tmp_id;
            }
        }
    }

    printf("\n=======================================\n");
    printf("후보 선발 결과 집계 중 ...\n");
    printf("=======================================\n");
    printf("#######################################\n");
    printf("# 밀리웨이즈의 멤버가 된 걸축하합니다!  #\n");
    printf("#######################################\n");

    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, candidate_names[i]);
    }
}

int main() {
    char evaluator[50], specialty[20];
    char confirm;

    for (int field_index = 0; field_index < NUM_FIELDS; field_index++) {
        while (1) {
            printf("####################################\n");
            printf("#       오디션 심사 결과 입력       #\n");
            printf("####################################\n");

            printf("> 심사위원 이름: ");
            scanf("%s", evaluator);
            printf("> 전문 분야: ");
            scanf("%s", specialty);

            printf("++++++++++++++++++++++++++++++++++++\n");
            input_scores(field_index);

            printf("입력을 모두 완료했습니다.\n입력하신 내용을 검토하세요!\n");
            printf("------------------------------------\n");
            print_scores(field_index);

            printf("제출하시겠습니까? (Y/N): ");
            scanf(" %c", &confirm);

            if (confirm == 'Y' || confirm == 'y') {
                break;
            } else {
                modify_scores(field_index);
            }
        }
    }

    calculate_totals();
    show_final_results();

    return 0;
}
