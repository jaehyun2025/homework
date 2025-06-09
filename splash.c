#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  

int main() {
    char name[50];
    char date[20];
    int year, month, day;

    printf("현재 날짜를 'yyyy-mm-dd' 형식으로 입력하세요: ");
    scanf("%s", date);
    printf("당신의 이름을 입력하세요: ");
    scanf(" %[^\n]", name);  

    sscanf(date, "%d-%d-%d", &year, &month, &day);

    printf("**입력이 정상적으로 처리되었습니다.**\n");

    sleep(3);

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

    for (int i = 1; i <= 5; i++) {
        for (int j = 0; j < i; j++) {
            printf("*");
        }

        // 메시지
        switch (i) {
            case 1:
                printf("                         [마그라테아 ver 0.1]                               ");
                break;
            case 2:
                printf("   풀 한 포기 없는 황무지에서 반짝이는 행성을 만들내는 곳 마그라테아,         ");
                break;
            case 3:
                printf(" 사람들이 보지 못하는 잠재력을 찾고 전문가의 손길을 더해 보석을 빗는 곳,    ");
                break;
            case 4:
                printf("   마그라테아에 오신걸 환영합니다.                                        ");
                break;
            case 5:
                printf("                                                                          ");
                break;
        }

        for (int j = 0; j < 6 - i; j++) {
            printf("*");
        }

        printf("\n");
    }

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[사용자]: %-40s [실행 시간]:%04d년 %02d월 %02d일\n", name, year, month, day);
    printf("================================================================================\n");

    return 0;
}
