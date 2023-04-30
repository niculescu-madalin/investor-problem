#ifndef INVESTOR_H_INCLUDED
#define INVESTOR_H_INCLUDED

struct offer{
    int id;
    int price;
    int profit;
    int count;
};

void generate_offers(struct offer *offers, int no_offers);
int *investor(int capital, int no_offers, struct offer *offers);
void print_offers(struct offer *offers, int no_offers);
void print_chosen_offers (int *chosen_offers_count, int no_offers, struct offer *offers);

#endif // INVESTOR_H_INCLUDED
