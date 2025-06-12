#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 100
#define MAX_MENTORS 8
#define NAME_LEN 50

typedef struct {
    char nickname[NAME_LEN];
    int id;
    int ability;
} Trainee;

typedef struct {
    int id;
    char name[NAME_LEN];
    int matchedTraineeID;
} Mentor;

int parseIntMember(const char* nickname) {
    int sum = 0;
    for (int i = 0; nickname[i] != '\0'; i++) {
        sum += (int)nickname[i];
    }
    return sum;
}

int getRandomAbility() {
    return 100 + rand() % 901;
}

void initializeTrainees(Trainee trainees[], int count) {
    for (int i = 0; i < count; i++) {
        printf("Enter nickname for trainee #%d: ", i + 1);
        scanf("%s", trainees[i].nickname);
        trainees[i].id = parseIntMember(trainees[i].nickname);
        trainees[i].ability = getRandomAbility();
    }
}

void initializeMentors(Mentor mentors[], int count) {
    for (int i = 0; i < count; i++) {
        mentors[i].id = i + 1;
        mentors[i].matchedTraineeID = -1;
        printf("Enter name for mentor #%d: ", i + 1);
        scanf("%s", mentors[i].name);
    }
}

void matchMentoring(Trainee trainees[], int tCount, Mentor mentors[], int mCount) {
    int usedMentors[MAX_MENTORS] = {0};
    for (int i = 0; i < tCount; i++) {
        int matchID = trainees[i].id % mCount;
        while (usedMentors[matchID]) {
            matchID = (matchID + 1) % mCount;
        }
        mentors[matchID].matchedTraineeID = trainees[i].id;
        usedMentors[matchID] = 1;
    }
}

void printMatches(Trainee trainees[], int tCount, Mentor mentors[], int mCount) {
    printf("\n[Match Results]\n");
    for (int i = 0; i < mCount; i++) {
        for (int j = 0; j < tCount; j++) {
            if (trainees[j].id == mentors[i].matchedTraineeID) {
                printf("Trainee: %s(ID: %d) <--> Mentor: %s(ID: %d)\n",
                       trainees[j].nickname, trainees[j].id,
                       mentors[i].name, mentors[i].id);
                break;
            }
        }
    }
}

int main() {
    srand((unsigned int)time(NULL));
    
    Trainee trainees[MAX_TRAINEES];
    Mentor mentors[MAX_MENTORS];
    int tCount, mCount = MAX_MENTORS;

    printf("Enter number of trainees (max 100): ");
    scanf("%d", &tCount);

    initializeTrainees(trainees, tCount);
    initializeMentors(mentors, mCount);
    matchMentoring(trainees, tCount, mentors, mCount);
    printMatches(trainees, tCount, mentors, mCount);

    return 0;
}
