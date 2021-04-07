// uloha8-2.c -- Samuel Bubán, 7.4.2021 01:07

#include <stdio.h>
#include <stdlib.h>


int kid_food[100][100], kid_drink[100][100], kid_food_amount[100], kid_drink_amount[100], taken_food[100], taken_drink[100];


int assign(int kid, int n) {

    if (kid == n) {
        return 0;
    }

    int best = 0;
    int new_out;

    // Loop through favorite foods
    for (int i = 0; i < kid_food_amount[kid]; i++) {
        
        // Loop through favorite drinks
        for (int ii = 0; ii < kid_drink_amount[kid]; ii++) {

            if (!taken_food[kid_food[kid][i]] && !taken_drink[kid_drink[kid][ii]]) {

                taken_drink[kid_drink[kid][ii]] = 1;
                taken_food[kid_food[kid][i]] = 1;

                new_out = 1 + assign(kid + 1, n);

                if (new_out > best) {
                    best = new_out;
                }

                taken_drink[kid_drink[kid][ii]] = 0;
                taken_food[kid_food[kid][i]] = 0;
            }
        }
    }

    new_out = assign(kid + 1, n);

    if (new_out > best) {
        best = new_out;
    }

    return best;
}


int main() {

    int n, f, d;

    while (scanf("%d %d %d", &n, &f, &d) > 0) {

        // Load all
        for (int i = 0; i < n; i++) {

            taken_drink[i] = 0;
            taken_food[i] = 0;
        }

        for (int i = 0; i < n; i++) {

            scanf("%d %d", kid_food_amount + i, kid_drink_amount + i);

            for (int ii = 0; ii < kid_food_amount[i]; ii++) {

                scanf("%d", &(kid_food[i][ii]));
            }
            for (int ii = 0; ii < kid_drink_amount[i]; ii++) {

                scanf("%d", &(kid_drink[i][ii]));
            }
        }

        // Compute
        printf("%d\n", assign(0, n));
    }

    return 0;
}