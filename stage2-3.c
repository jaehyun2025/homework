#include <stdio.h>
#include <string.h>

#define MAX_KEYWORD_LEN 20
#define MAX_MESSAGE_LEN 400

typedef struct {
    char keyword[MAX_KEYWORD_LEN];
    char message[MAX_MESSAGE_LEN];
} EasterEgg;

void print_binary_reverse(const char *str) {
    int len = strlen(str);
    for (int i = len - 1; i >= 0; i--) {
        unsigned char ch = str[i];
        for (int bit = 7; bit >= 0; bit--) {
            printf("%d", (ch >> bit) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

int isEasterEgg(const char *input, const char *keyword) {
    return strcmp(input, keyword) == 0;
}

void bonus_scramble_keyword(const char *keyword) {
    int len = strlen(keyword);
    char reversed[20];
    for (int i = 0; i < len; i++) {
        reversed[i] = keyword[len - 1 - i];
    }
    reversed[len] = '\0';

    char odd[20], even[20];
    int oddIdx = 0, evenIdx = 0;
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0)
            odd[oddIdx++] = reversed[i];
        else
            even[evenIdx++] = reversed[i];
    }
    odd[oddIdx] = '\0';
    even[evenIdx] = '\0';

    char scrambled[20];
    strcpy(scrambled, odd);
    strcat(scrambled, even);

    print_binary_reverse(scrambled);
}

void find_easter_egg() {
    EasterEgg egg;
    strcpy(egg.keyword, "specter");
    strncpy(egg.message,
        "나는 고백한다. 대학 졸업 후 스타트업 창업이라는 허세에 빠져 치기 어린 행동으로 친구들의 앞길을 막았다. "
        "나는 나의 아이디어가 설득되는 사람이 나 뿐일 때 파괴적인 결과를 보게 된다는 것을 뼈저리게 경험했다. "
        "과거의 아서는 독선과 아집의 망령이다.", MAX_MESSAGE_LEN - 1);
    egg.message[MAX_MESSAGE_LEN - 1] = '\0';

    char name_input[30];
    printf("이름을 입력하세요: ");
    scanf("%s", name_input);

    if (strcmp(name_input, "Arthur") != 0) return;

    printf("\n<<아서의 이스터에그>>\n");
    print_binary_reverse(egg.keyword);

    char user_input[30];
    while (1) {
        printf("각 이진수에 해당하는 문자를 차례대로 입력하세요: ");
        scanf("%s", user_input);

        if (isEasterEgg(user_input, egg.keyword)) {
            printf("##이스터에그 발견!$$\n");
            printf("%s\n", egg.message);
            break;
        } else {
            printf("틀렸습니다. 다시 시도하세요.\n");
        }
    }

    printf("\n[보너스] 단어를 섞은 후의 이진수 출력:\n");
    bonus_scramble_keyword(egg.keyword);
}

void show_submenu() {
    printf("\n[II. 훈련 > 2. 자기관리와 팀워크]\n");
    printf(" - 목표 설정 및 실천\n");
    printf(" - 감정 관리\n");
    printf(" - Arthur (숨겨진 항목)\n");
    printf("하위 메뉴를 선택하세요: ");
}

int main() {
    int main_choice;

    while (1) {
        printf("\n[메인 메뉴]\n");
        printf("1. 훈련\n");
        printf("0. 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf("%d", &main_choice);

        if (main_choice == 0) {
            break;
        } else if (main_choice == 1) {
            int sub_choice;
            printf("\n[II. 훈련]\n");
            printf("1. 의사소통\n");
            printf("2. 자기관리와 팀워크\n");
            printf("메뉴를 선택하세요: ");
            scanf("%d", &sub_choice);

            if (sub_choice == 2) {
                char submenu_input[30];
                show_submenu();
                scanf("%s", submenu_input);

                if (strcmp(submenu_input, "Arthur") == 0) {
                    find_easter_egg();
                }
            }
        }
    }

    return 0;
}
