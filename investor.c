#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include "investor.h"

void generate_offers(struct offer *offers, int no_offers){ // geneareaza componentele ofertelor aleatoriu
    int iterator;
    time_t t;

    srand((unsigned) time(&t));
    for(iterator = 0; iterator < no_offers; iterator++){
        offers[iterator].id = iterator + 1;
        offers[iterator].price = rand() % 100 + 1;
        offers[iterator].profit = rand() % 100 + 1;
        offers[iterator].count = rand() % 10 + 1;
    }
}

int *investor(int capital, int no_offers, struct offer *offers) { // este algorimul principal, alege ofertele si numara acitiunile achizitionate pentru a optine un profit maxim
    int offers_iterator, capital_iterator, actions_iterator, current_profit, *matrix, **offers_profits, *chosen_offers_count;
    matrix = calloc((no_offers + 1) * (capital + 1), sizeof (int));
    offers_profits = malloc((no_offers + 1) * sizeof (int *)); // este matricea care contine profiturile pentru numarul de oferte i (offers_iterator) si capital c (capital_iterator)
    offers_profits[0] = matrix;
    for (offers_iterator = 1; offers_iterator <= no_offers; offers_iterator++) {
        offers_profits[offers_iterator] = &matrix[offers_iterator * (capital + 1)];
        for (capital_iterator = 0; capital_iterator <= capital; capital_iterator ++) {
            offers_profits[offers_iterator][capital_iterator] = offers_profits[offers_iterator - 1][capital_iterator];
            for (actions_iterator = 1; actions_iterator <= offers[offers_iterator - 1].count; actions_iterator++) {
                if (actions_iterator * offers[offers_iterator - 1].price > capital_iterator) {
                    break;
                }
                current_profit = offers_profits[offers_iterator - 1][capital_iterator - actions_iterator * offers[offers_iterator - 1].price] + actions_iterator * offers[offers_iterator - 1].profit;
                if (current_profit > offers_profits[offers_iterator][capital_iterator]) {
                    offers_profits[offers_iterator][capital_iterator] = current_profit;
                }
            }
        }
    }
    chosen_offers_count = calloc(no_offers, sizeof (int)); // este matricea X care numa numarul de actiuni luate dintr-o oferta
    for (offers_iterator = no_offers, capital_iterator = capital; offers_iterator > 0; offers_iterator--) {
        int current_offer = offers_profits[offers_iterator][capital_iterator];
        for (actions_iterator = 0; current_offer != offers_profits[offers_iterator - 1][capital_iterator] + actions_iterator * offers[offers_iterator - 1].profit; actions_iterator++) {
            chosen_offers_count[offers_iterator - 1]++;
            capital_iterator -= offers[offers_iterator - 1].price;
        }
    }
    free(matrix);
    free(offers_profits);
    return chosen_offers_count;
}

void print_offers(struct offer *offers, int no_offers){
    int iterator;

    printf("\n Offers:");
    for (iterator = 0; iterator < no_offers ; iterator++) {
        printf("\n id: %d price: %d profit: %d number of actions: %d",offers[iterator].id, offers[iterator].price, offers[iterator].profit, offers[iterator].count);
    }
    printf (" \n");
}

void print_chosen_offers (int *chosen_offers_count, int no_offers, struct offer *offers) {
    int i, total_actions_count = 0, total_cost = 0, total_profit = 0;

    printf("\n Offers chosen: \n");
    for (i = 0; i < no_offers; i++) {
        if (chosen_offers_count[i]) {
            printf(" id: %-10d count: %2d price: %3d profit: %3d\n", offers[i].id, chosen_offers_count[i], chosen_offers_count[i] * offers[i].price, chosen_offers_count[i] * offers[i].profit);
            total_actions_count += chosen_offers_count[i];
            total_cost += chosen_offers_count[i] * offers[i].price;
            total_profit += chosen_offers_count[i] * offers[i].profit;
        }
    }
    printf(" total actions count: %3d price: %3d profit: %3d\n", total_actions_count, total_cost, total_profit);
}
