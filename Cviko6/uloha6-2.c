// uloha6-2.c -- Samuel Bubán, 23.3.2021 15:07

#include <stdio.h>
#include <stdlib.h>


int isInArray(int n, int* arr, int num) {

    for (int i = 0; i < n; i++) {

        if (arr[i] == num) {

            return 1;
        }
    }

    return 0;
}


void generation(int n, int** arr, int depth, int* min, int* cur_arr, int* out_arr) {

    if (depth == n) {

        int current_cost = 0;

        // Calculate current cost
        for (int i = 0; i < n - 1; i++) {

            current_cost += arr[cur_arr[i]][cur_arr[i + 1]];
        }

        // Current cost is better
        if (current_cost < *min) {

            *min = current_cost;
            
            for (int i = 0; i < n; i++) {

                out_arr[i] = cur_arr[i];
            }
        }
        // Current cost is equal
        else if (current_cost == *min) {

            int overwrite = 0;

            // Find smaller path
            for (int i = 0; i < n; i++) {
                
                if (cur_arr[i] < out_arr[i]) {

                    overwrite = 1;
                    break;
                }
                else if (cur_arr[i] > out_arr[i]) {

                    break;
                }
            }

            if (!overwrite) {

                return;
            }

            // Cost is the same, but path is smaller
            for (int i = 0; i < n; i++) {

                out_arr[i] = cur_arr[i];
            }
        }

        return;
    }

    if (depth == 0) {

        cur_arr[0] = 0;
        generation(n, arr, depth + 1, min, cur_arr, out_arr);
        return;
    }

    for (int i = 0; i < n; i++) {

        if (isInArray(depth, cur_arr, i)) {

            continue;
        }

        cur_arr[depth] = i;
        generation(n, arr, depth + 1, min, cur_arr, out_arr);
    }

    return;
}


int main() {

    int n, min = 0;
    scanf("%d", &n);

    int **arr = (int**) malloc(sizeof(int*) * n);
    int *out_arr = (int*) malloc(sizeof(int) * n);
    int *cur_arr = (int*) malloc(sizeof(int) * n);
    
    for (int i = 0; i < n; i++) {

        arr[i] = (int*) malloc(sizeof(int) * n);
        out_arr[i] = -1;
        cur_arr[i] = -1;
    }

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            scanf("%d", &(arr[i][j]));
            min += arr[i][j];
        }
    }

    generation(n, arr, 0, &min, cur_arr, out_arr);
    printf("%d\n", min);

    for (int i = 0; i < n; i++) {

        printf("%d ", out_arr[i] + 1);
    }

    printf("\n");

    return 0;
}
