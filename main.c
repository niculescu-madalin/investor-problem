#include <stdio.h>
#include <stdlib.h>

#include "investor.h"

int main () {
    int *chosen_offers_count, no_offers, capital;

    printf("\n Enter the total capital: ");
    scanf("%d", &capital);
    printf(" Enter how many offers you wish to be generated: ");
    scanf("%d", &no_offers);

    struct offer *offers;
    offers = malloc(no_offers * sizeof(struct offer));
    generate_offers(offers, no_offers);

    printf("\n ======== Random offers ===========\n");
    print_offers(offers, no_offers);

    chosen_offers_count = investor(capital, no_offers, offers);
    print_chosen_offers (chosen_offers_count, no_offers, offers);


    return 0;
}

