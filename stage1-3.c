#include <stdio.h>
#include <string.h>

#define MEMBER_COUNT 5
#define DAY_COUNT 6
#define EXERCISE_NAME_LEN 32
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

const char *aerobic[]    = {"러닝", "자전거", "빠른걷기"};
const char *full_body[]  = {"푸시업", "스쿼트"};
const char *lower_body[] = {"레그프레스", "레그컬"};
const char *upper_body[] = {"철봉", "풀업바"};
const char *core[]       = {"플랭크", "크런치"};

char member_routine[MEMBER_COUNT][DAY_COUNT][2][EXERCISE_NAME_LEN];

int get_member_index_by_name(const char *name) {
    for (int i = 0; i < MEMBER_COUNT; ++i) {
        if (strcmp(milliways_members[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// 공통 함수: 멤버 목록 출력
void print_member_list(void) {
    printf("\n[멤버 목록]\n");
    for (int i = 0; i < MEMBER_COUNT; ++i) {
        printf("- %s (%s)\n", milliways_members[i].name, milliways_members[i].nickname);
    }
}

void print_exercise_options(void) {
    printf("\n[운동 종류 목록]\n");

    printf("유산소 운동: ");
    for (int i = 0; i < 3; ++i) printf("%s  ", aerobic[i]);

    printf("\n전신 근력: ");
    for (int i = 0; i < 2; ++i) printf("%s  ", full_body[i]);

    printf("\n하체 근력: ");
    for (int i = 0; i < 2; ++i) printf("%s  ", lower_body[i]);

    printf("\n상체 근력: ");
    for (int i = 0; i < 2; ++i) printf("%s  ", upper_body[i]);

    printf("\n코어 운동: ");
    for (int i = 0; i < 2; ++i) printf("%s  ", core[i]);

    printf("\n");
}

// 운동 루틴 설정
void setExerciseRoutine(void) {
    char name[NAME_LENGTH];
    int member_index;
    char aerobic_input[EXERCISE_NAME_LEN];
    char strength_input[EXERCISE_NAME_LEN];
    int core_day_used = 0;

    print_member_list();
    printf("\n운동 루틴을 설정할 멤버 이름을 입력하세요: ");
    scanf("%s", name);

    member_index = get_member_index_by_name(name);
    if (member_index == -1) {
        printf("❌ 멤버를 찾을 수 없습니다.\n");
        return;
    }

    print_exercise_options();

    for (int day = 0; day < DAY_COUNT; ++day) {
        printf("\n[%d일차] 유산소 운동 선택: ", day + 1);
        scanf("%s", aerobic_input);
        printf("[%d일차] 근력 또는 코어 운동 선택: ", day + 1);
        scanf("%s", strength_input);

        // 코어 운동 하루만 허용
        for (int i = 0; i < 2; ++i) {
            if (strcmp(strength_input, core[i]) == 0) {
                if (core_day_used) {
                    printf("⚠️ 코어 운동은 하루만 가능합니다. 다시 입력하세요.\n");
                    day--;
                    continue;
                }
                core_day_used = 1;
            }
        }

        // 루틴 저장
        strcpy(member_routine[member_index][day][0], aerobic_input);
        strcpy(member_routine[member_index][day][1], strength_input);
    }

    printf("\n✅ %s님의 운동 루틴이 설정되었습니다.\n", name);
}

// 운동 루틴 조회
void getExerciseRoutine(void) {
    char name[NAME_LENGTH];
    int member_index;

    print_member_list();
    printf("\n운동 루틴을 조회할 멤버 이름을 입력하세요: ");
    scanf("%s", name);

    member_index = get_member_index_by_name(name);
    if (member_index == -1) {
        printf("❌ 멤버를 찾을 수 없습니다.\n");
        return;
    }

    printf("\n📋 [%s (%s)의 주간 운동 루틴]\n",
           milliways_members[member_index].name,
           milliways_members[member_index].nickname);

    for (int day = 0; day < DAY_COUNT; ++day) {
        printf("Day %d: %s + %s\n", day + 1,
            member_routine[member_index][day][0],
            member_routine[member_index][day][1]);
    }
}

// 메인 메뉴
int main(void) {
    int choice;

    while (1) {
        printf("\n====== [밀리웨이즈 트레이닝 시스템] ======\n");
        printf("1. 기초 운동 루틴 설정\n");
        printf("2. 기초 운동 루틴 조회\n");
        printf("0. 종료\n");
        printf("선택 > ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                setExerciseRoutine();
                break;
            case 2:
                getExerciseRoutine();
                break;
            case 0:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("❗ 올바른 번호를 입력하세요.\n");
        }
    }
}
