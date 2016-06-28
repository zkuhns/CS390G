#include <omp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 32

char SYMBOLS[] = {
'0','1','2','3','4','5','6','7','8','9',
'a','b','c','d','e','f','g','h','i','j',
'k','l','m','n','o','p','q','r','s','t',
'u','v','w','x','y','z','A','B','C','D',
'E','F','G','H','I','J','K','L','M','N',
'O','P','Q','R','S','T','U','V','W','X',
'Y','Z',
};

int SYMBOLS_SIZE;

char password[MAXSIZE];
char check[MAXSIZE];

int compare(char password[], char check[]);
int generate_combinations(char check[], int index);

int found;

long start_time;
long end_time;

int main(int argc, char* argv[]) {
    SYMBOLS_SIZE = sizeof(SYMBOLS);

    strcpy(password, argv[1]);

    start_time = omp_get_wtime();

    #pragma omp parallel private(check)
    {
        for (int i = 0; i < MAXSIZE; i++) {
            check[i] = '\0';
        }

        for (int i = 0; i < MAXSIZE; i++) {
            if (found) {
                continue;
            }

            #pragma omp for
            for (int j = 0; j < SYMBOLS_SIZE; j++) {
                if (!found) {
                    check[0] = SYMBOLS[j];
                    for (int k = 1; k <= i; k++) {
                        check[k] = '0';
                    }

                    if (compare(check, password)) {
                        found = 1;
                    }

                    if (generate_combinations(check, i)) {
                        found = 1;
                    }
                }
            }
        }
    }

    end_time = omp_get_wtime();

    printf("Time elapsed: %d\n", end_time - start_time);

    found = 0;
    start_time = omp_get_wtime();

    //#pragma omp parallel private(check)
    {
        for (int i = 0; i < MAXSIZE; i++) {
            check[i] = '\0';
        }

        for (int i = 0; i < MAXSIZE; i++) {
            if (found) {
                continue;
            }

            //#pragma omp for
            for (int j = 0; j < SYMBOLS_SIZE; j++) {
                if (!found) {
                    check[0] = SYMBOLS[j];
                    for (int k = 1; k <= i; k++) {
                        check[k] = '0';
                    }

                    if (compare(check, password)) {
                        found = 1;
                    }

                    if (generate_combinations(check, i)) {
                        found = 1;
                    }
                }
            }
        }
    }

    end_time = omp_get_wtime();

    printf("Time elapsed: %d\n", end_time - start_time);
}

int generate_combinations(char check[], int index) {
    if (index == 0) {
        return 0;
    } else {
        for (int i = 0; i < SYMBOLS_SIZE; i++) {
            if (generate_combinations(check, index-1)) {
                return 1;
            }

            check[index] = SYMBOLS[i];

            if (compare(check, password)) {
                return 1;
            }
        }
    }

    return 0;
}

int compare(char password[], char check[]) {
    if (!strcmp(check,password)) {
        printf("%s %s\n", password, check);
        return 1;
    }

    return 0;
}
