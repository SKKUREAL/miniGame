



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int drawCard (int * arr);
int YP (int * dealercard, int * playercard, int * Pnum, int * arr, int * YN);
int print(int * dealercard, int * playercard);

int main () {

    srand(time(NULL));

    int cards[15] = {1,2,3,4,5,6,7,8,9,10,10,10,10,11,11}; // '1','2','3','4','5','6','7','8','9','X','J','Q','K','A','A'
    int dealercard[10] ={0};
    int playercard[10] ={0};

    int YN =0;

    int PNum= 2;

    printf("카드를 뽑습니다.\n");
    dealercard[0] = drawCard(cards);
    dealercard[1] = drawCard(cards);
    playercard[0] = drawCard(cards);
    playercard[1] = drawCard(cards);

    print(dealercard, playercard);

    printf("1or0?: ");

    scanf("%d", &YN);
    fflush(stdin);

    if(YN == 1) {
        YP(dealercard, playercard, &PNum, cards, &YN);
    }
    else NP(dealercard, playercard, &PNum, cards, &YN);

    return 0;
}


int drawCard (int * arr) {

    int number=0;
    int save =0;

    while (1) {
        number = rand()%15;
        if (arr[number] != -1) {
            save = arr[number];
            arr[number] = -1;
            break;
        }

    }
    

    return save;
}

int YP (int * dealercard, int * playercard, int * Pnum, int * arr, int * YN) {

    playercard[*Pnum] = drawCard(arr);

    *Pnum = *Pnum +1;

    int playersum =0;

    for(int i = 0; i <10; i++) {
        playersum = playersum + playercard[i];
    }
    print(dealercard, playercard);

    if(playersum > 21) {
        printf("패배");
        return 0;
    }
    else {
        printf("1or0?: ");
        scanf("%d", YN);
        fflush(stdin);
        if(*YN == 1) YP(dealercard, playercard, Pnum, arr, YN);
        else NP(dealercard, playercard, Pnum, arr, YN);
    }

    return 0;
}

int print(int * dealercard, int * playercard) {

    printf("\n");
    for(int i = 0; i <10; i++) {
        if(dealercard[i] != 0) printf("%d ",dealercard[i]);
    }

    printf("\n");
    for(int j = 0; j <10; j++) {
        if(playercard[j] != 0) printf("%d ",playercard[j]);
    }
    printf("\n");

    return 0;
}

int NP (int * dealercard, int * playercard, int * Pnum, int * arr, int * YN) {

    int dealersum = 0;
    int playersum = 0;
    int number =0;
    int save =0;
    int dealerNum =2;

    for(int i = 0; i <10; i++) {
        dealersum = dealersum + dealercard[i];
    }
    for(int i = 0; i <10; i++) {
        playersum = playersum + playercard[i];
    }

    while (dealersum < 17) {
        number = rand()%15;
        if (arr[number] != -1) {
            save = arr[number];
            arr[number] = -1;
            dealersum = dealersum + save;
            dealercard[dealerNum] = save;
            dealerNum++;
        }

    }

    printf("\n");
    printf("최종결과");
    printf("\n");
    print(dealercard, playercard);
    printf("\n");

    if(dealersum > 21) {
        printf("승리->(딜러: %d 당신: %d)", dealersum, playersum);
    }
    else if (playersum > dealersum) {
        printf("승리->(딜러: %d 당신: %d)", dealersum, playersum);
    }
    else {
        printf("패배->(딜러: %d 당신: %d)", dealersum, playersum);
    }

}