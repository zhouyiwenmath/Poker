#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#define NUM_SUIT 4
#define NUM_CARD_IN_SUIT 13 
#define NUM_CARD_IN_DECK 52 


/* Implementing suits */


typedef enum suit {HEART, SPADE, DIAMOND, CLUB} suit;


/* Implementing a single card */


typedef struct card {
	suit s;
	int p;    /* between 1 and 13, with 1 reprecenting Ace */
} card;


int is_valid(const card* pc)
{
	if ((pc -> p < 1) || (pc -> p > NUM_CARD_IN_SUIT))
	{
		return 0;
	}
	return 1;
}


void print_card(const card* pc)
{
	assert(is_valid(pc));
	switch(pc -> s)
	{
		case HEART: 
			if (pc -> p == 1)
			{
				printf(" [ ♥ A ] "); break;
			}
			else if (pc -> p == 11)
			{
				printf(" [ ♥ J ] "); break;
			} 
			else if (pc -> p == 12)
			{
				printf(" [ ♥ Q ] "); break;
			} 
			else if (pc -> p == 13)
			{
				printf(" [ ♥ K ] "); break;
			} 
			else
			{
				printf(" [ ♥ %d ] ", pc -> p); break;
			}
		case SPADE:
			if (pc -> p == 1)
			{
				printf(" [ ♠ A ] "); break;
			}
			else if (pc -> p == 11)
			{
				printf(" [ ♠ J ] "); break;
			} 
			else if (pc -> p == 12)
			{
				printf(" [ ♠ Q ] "); break;
			} 
			else if (pc -> p == 13)
			{
				printf(" [ ♠ K ] "); break;
			} 
			else
			{
				printf(" [ ♠ %d ] ", pc -> p); break;
			}
		case DIAMOND:
			if (pc -> p == 1)
			{
				printf(" [ ♦ A ] "); break;
			}
			else if (pc -> p == 11)
			{
				printf(" [ ♦ J ] "); break;
			} 
			else if (pc -> p == 12)
			{
				printf(" [ ♦ Q ] "); break;
			} 
			else if (pc -> p == 13)
			{
				printf(" [ ♦ K ] "); break;
			} 
			else
			{
				printf(" [ ♦ %d ] ", pc -> p); break;
			}
		case CLUB:
			if (pc -> p == 1)
			{
				printf(" [ ♣ A ] "); break;
			}
			else if (pc -> p == 11)
			{
				printf(" [ ♣ J ] "); break;
			} 
			else if (pc -> p == 12)
			{
				printf(" [ ♣ Q ] "); break;
			} 
			else if (pc -> p == 13)
			{
				printf(" [ ♣ K ] "); break;
			} 
			else
			{
				printf(" [ ♣ %d ] ", pc -> p); break;
			}
		default: printf("error on date... "); break;
	}
}


/* Implementing a deck of cards, drawing cards and shuffling. */


typedef struct deck {
	card c[NUM_CARD_IN_DECK];
} deck;


void initialize_deck(deck* pd)
{
	for (int i = 0; i < NUM_SUIT; i++)
	{
		for (int j = 0; j < NUM_CARD_IN_SUIT; j++)
		{
			(pd -> c)[i * NUM_CARD_IN_SUIT + j].s = i;
			(pd -> c)[i * NUM_CARD_IN_SUIT + j].p = j + 1;
		}
	}
}


void shuffle_deck(deck* pd)
{
	card temp_c;
	for (int i = 0; i < NUM_CARD_IN_DECK - 1; i++) 
	{
		int j = i + rand() / (RAND_MAX / (NUM_CARD_IN_DECK - i) + 1);
		temp_c = (pd -> c)[j];
		(pd -> c)[j] = (pd -> c)[i];
		(pd -> c)[i] = temp_c;
	}
}


void print_deck(const deck* pd)
{
	printf("\nStart priniting deck: \n\n");
	for (int i = 0; i < NUM_SUIT; i++)
	{
		for (int j = 0; j < NUM_CARD_IN_SUIT; j++)
		{
			print_card(&((pd -> c)[i * NUM_CARD_IN_SUIT + j]));
		}
		printf("\n");
	}
	printf("\n\nFinished printing deck.\n");
}


void draw_cards(int number_of_cards, deck* pd, card* pot)   /* pot: where to put the drawn cards */
{
	assert(number_of_cards < NUM_CARD_IN_DECK);
	card temp_c;
	for (int i = 0; i < number_of_cards; i++) 
	{
		int j = i + rand() / (RAND_MAX / (NUM_CARD_IN_DECK - i) + 1);
		temp_c = (pd -> c)[j];
		(pd -> c)[j] = (pd -> c)[i];
		(pd -> c)[i] = temp_c;
	}
	for (int i = 0; i < number_of_cards; i++)
	{
		pot[i] = (pd -> c)[i];   /* pass by value */
	}
}


/* Determining hands of 5 cards */


typedef enum poker_hands {
	ROYAL_FLUSH, 
	STRAIGHT_FLUSH,
	FOUR_OF_A_KIND,
	FULL_HOUSE,
	FLUSH,
	STRAIGHT,
	THREE_OF_A_KIND,
	TWO_PAIR,
	PAIR,
	ACE_HIGH_OR_LESS,
	NUMBER_OF_HAND_TYPES
} poker_hands;


void print_card_type(poker_hands result)
{
	switch (result)
	{
		case ROYAL_FLUSH: printf("\n ♪ Royal Flush ♪ \n"); break;
		case STRAIGHT_FLUSH: printf("\n ♪ Straight Flush ♪ \n"); break;
		case FOUR_OF_A_KIND: printf("\n ♪ Four of a Kind ♪ \n"); break;
		case FULL_HOUSE: printf("\n ♪ Full House ♪ \n"); break;
		case FLUSH: printf("\n ♪ Flush ♪ \n"); break;
		case STRAIGHT: printf("\n ♪ Straight ♪ \n"); break;
		case THREE_OF_A_KIND: printf("\n ♪ Three of a Kind ♪ \n"); break;
		case TWO_PAIR: printf("\n ♪ Two Pair ♪ \n"); break;
		case PAIR: printf("\n ♪ Pair ♪ \n"); break;
		case ACE_HIGH_OR_LESS: printf("\n ♪ Ace high or less ♪ \n"); break;
		default: printf("\n ♪ No idea... ♪ \n"); break;
	}
}


int cmpfunc (const void* a, const void* b) {
   return ((((card*)a) -> p) - (((card*)b) -> p));
}


int is_royal_flush(card* hand_copy)    /* this function is going to modify hand_copy. Length must be 5. */
{
	if ((hand_copy[0].s == hand_copy[1].s) && (hand_copy[1].s == hand_copy[2].s) && (hand_copy[2].s == hand_copy[3].s) && (hand_copy[3].s == hand_copy[4].s))
	{
		qsort(hand_copy, 5, sizeof(card), cmpfunc);
		if ((hand_copy[0].p == 1) && (hand_copy[1].p == 10) && (hand_copy[2].p == 11) && (hand_copy[3].p == 12) && (hand_copy[4].p == 13))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}


int is_straight_flush(card* hand_copy)    /* this function is going to modify hand_copy. Length must be 5. NOT INCLUDING ROYAL FLUSH. */
{
	if ((hand_copy[0].s == hand_copy[1].s) && (hand_copy[1].s == hand_copy[2].s) && (hand_copy[2].s == hand_copy[3].s) && (hand_copy[3].s == hand_copy[4].s))
	{
		qsort(hand_copy, 5, sizeof(card), cmpfunc);
		if ((hand_copy[1].p == hand_copy[0].p + 1) && (hand_copy[2].p == hand_copy[1].p + 1) && (hand_copy[3].p == hand_copy[2].p + 1) && (hand_copy[4].p == hand_copy[3].p + 1))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}


int is_four_of_a_kind(card* hand_copy)    /* this function is going to modify hand_copy. Length must be 5. */
{
	qsort(hand_copy, 5, sizeof(card), cmpfunc);
	if ((hand_copy[1].p == hand_copy[0].p) && (hand_copy[2].p == hand_copy[1].p) && (hand_copy[3].p == hand_copy[2].p) )
	{
		return 1;
	}
	else if ((hand_copy[1].p == hand_copy[2].p) && (hand_copy[2].p == hand_copy[3].p) && (hand_copy[3].p == hand_copy[4].p) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int is_full_house(card* hand_copy)    /* this function is going to modify hand_copy. Length must be 5. */
{
	qsort(hand_copy, 5, sizeof(card), cmpfunc);
	if ((hand_copy[1].p == hand_copy[0].p) && (hand_copy[2].p == hand_copy[1].p) && (hand_copy[3].p == hand_copy[4].p) )
	{
		return 1;
	}
	else if ((hand_copy[1].p == hand_copy[0].p) && (hand_copy[3].p == hand_copy[2].p) && (hand_copy[4].p == hand_copy[3].p) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int is_flush(card* hand_copy)    /* Length must be 5. Including Royal Flush. */
{
	if ((hand_copy[0].s == hand_copy[1].s) && (hand_copy[1].s == hand_copy[2].s) && (hand_copy[2].s == hand_copy[3].s) && (hand_copy[3].s == hand_copy[4].s))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int is_straight(card* hand_copy)    /* this function is going to modify hand_copy. Length must be 5. Including Royal Flush and straight flush. */
{
	qsort(hand_copy, 5, sizeof(card), cmpfunc);
	if ((hand_copy[1].p == hand_copy[0].p + 1) && (hand_copy[2].p == hand_copy[1].p + 1) && (hand_copy[3].p == hand_copy[2].p + 1) && (hand_copy[4].p == hand_copy[3].p + 1))
	{
		return 1;
	}
	else if ((hand_copy[0].p == 1) && (hand_copy[1].p == 10) && (hand_copy[2].p == 11) && (hand_copy[3].p == 12) && (hand_copy[4].p == 13))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int is_three_of_a_kind(card* hand_copy)    /* this function is going to modify hand_copy. Length must be 5. Including Full house. */
{
	qsort(hand_copy, 5, sizeof(card), cmpfunc);
	if ((hand_copy[1].p == hand_copy[0].p) && (hand_copy[2].p == hand_copy[1].p) )
	{
		return 1;
	}
	else if ((hand_copy[2].p == hand_copy[1].p) && (hand_copy[3].p == hand_copy[2].p) )
	{
		return 1;
	}
	else if ((hand_copy[3].p == hand_copy[2].p) && (hand_copy[4].p == hand_copy[3].p) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int is_two_pair(card* hand_copy)    /* this function is going to modify hand_copy. Length must be 5. Including Full house and four of a kind, etc. */
{
	qsort(hand_copy, 5, sizeof(card), cmpfunc);
	if ((hand_copy[0].p == hand_copy[1].p) && (hand_copy[2].p == hand_copy[3].p) )
	{
		return 1;
	}
	else if ((hand_copy[0].p == hand_copy[1].p) && (hand_copy[3].p == hand_copy[4].p) )
	{
		return 1;
	}
	else if ((hand_copy[1].p == hand_copy[2].p) && (hand_copy[3].p == hand_copy[4].p) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int is_pair(card* hand_copy)    /* this function is going to modify hand_copy. Length must be 5. Including many other kinds. */
{
	qsort(hand_copy, 5, sizeof(card), cmpfunc);
	if ((hand_copy[0].p == hand_copy[1].p) || (hand_copy[1].p == hand_copy[2].p) || (hand_copy[2].p == hand_copy[3].p) || (hand_copy[3].p == hand_copy[4].p) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


poker_hands determine_5_card_type(card* hand_copy)
{
	if (is_royal_flush(hand_copy))
	{
		return ROYAL_FLUSH;
	}
	else if (is_straight_flush(hand_copy))
	{
		return STRAIGHT_FLUSH;
	}
	else if (is_four_of_a_kind(hand_copy))
	{
		return FOUR_OF_A_KIND;
	}
	else if (is_full_house(hand_copy))
	{
		return FULL_HOUSE;
	}
	else if (is_flush(hand_copy))
	{
		return FLUSH;
	}
	else if (is_straight(hand_copy))
	{
		return STRAIGHT;
	}
	else if (is_three_of_a_kind(hand_copy))
	{
		return THREE_OF_A_KIND;
	}
	else if (is_two_pair(hand_copy))
	{
		return TWO_PAIR;
	}
	else if (is_pair(hand_copy))
	{
		return PAIR;
	}
	else
	{
		return ACE_HIGH_OR_LESS;
	}
}


void print_5_card_type(card* hand_copy)    /* this function is going to modify hand_copy. Length must be 5s. */
{
	poker_hands result = determine_5_card_type(hand_copy);
	print_card_type(result);
}


/* Determine best 5 cards of hand */


poker_hands determine_best_5_card_type(const card* hand, int hand_length)    /* Length must be at least 5. */
{
	assert(hand_length >= 5);
	card temp_hand[5];
	poker_hands result = ACE_HIGH_OR_LESS;
	poker_hands cache = ACE_HIGH_OR_LESS;
	for (int i1 = 0; i1 < hand_length - 4; i1++)
	{
		for (int i2 = i1 + 1; i2 < hand_length - 3; i2++)
		{
			for (int i3 = i2 + 1; i3 < hand_length - 2; i3++)
			{
				for (int i4 = i3 + 1; i4 < hand_length - 1; i4++)
				{
					for (int i5 = i4 + 1; i5 < hand_length; i5++)
					{
						temp_hand[0] = hand[i1];
						temp_hand[1] = hand[i2];
						temp_hand[2] = hand[i3];
						temp_hand[3] = hand[i4];
						temp_hand[4] = hand[i5];
						cache = determine_5_card_type(temp_hand);
						if (cache < result)
						{
							result = cache;
						}
					}
				}
			}
		}
	}
	return result;
}


/* Some testing code */


void list_all_poker_hands()
{
	deck d;
	initialize_deck(&d);
	
	printf("\n ---------- List of poker hands ------------ \n");
	
	card hand[5] = {d.c[26 + 0], d.c[26 + 9], d.c[26 + 10], d.c[26 + 11], d.c[26 + 12]};
	print_5_card_type(hand);
	for (int i = 0; i < 5; i++)
	{
		print_card(hand + i);
	}
	printf("\n");
	
	hand[0] = d.c[39 + 7];
	hand[1] = d.c[39 + 6];
	hand[2] = d.c[39 + 5];
	hand[3] = d.c[39 + 4];
	hand[4] = d.c[39 + 3];
	print_5_card_type(hand);
	for (int i = 0; i < 5; i++)
	{
		print_card(hand + i);
	}
	printf("\n");
	
	hand[0] = d.c[10];
	hand[1] = d.c[13 + 10];
	hand[2] = d.c[26 + 10];
	hand[3] = d.c[39 + 10];
	hand[4] = d.c[26 + 6];
	print_5_card_type(hand);
	for (int i = 0; i < 5; i++)
	{
		print_card(hand + i);
	}
	printf("\n");
	
	hand[0] = d.c[9];
	hand[1] = d.c[13 + 9];
	hand[2] = d.c[26 + 9];
	hand[3] = d.c[39 + 8];
	hand[4] = d.c[26 + 8];
	print_5_card_type(hand);
	for (int i = 0; i < 5; i++)
	{
		print_card(hand + i);
	}
	printf("\n");
	
	hand[0] = d.c[13 + 3];
	hand[1] = d.c[13 + 10];
	hand[2] = d.c[13 + 7];
	hand[3] = d.c[13 + 1];
	hand[4] = d.c[13 + 8];
	print_5_card_type(hand);
	for (int i = 0; i < 5; i++)
	{
		print_card(hand + i);
	}
	printf("\n");
	
	hand[0] = d.c[39 + 8];
	hand[1] = d.c[26 + 7];
	hand[2] = d.c[13 + 6];
	hand[3] = d.c[26 + 5];
	hand[4] = d.c[0 + 4];
	print_5_card_type(hand);
	for (int i = 0; i < 5; i++)
	{
		print_card(hand + i);
	}
	printf("\n");
	
	hand[0] = d.c[39 + 6];
	hand[1] = d.c[26 + 6];
	hand[2] = d.c[13 + 6];
	hand[3] = d.c[39 + 12];
	hand[4] = d.c[26 + 2];
	print_5_card_type(hand);
	for (int i = 0; i < 5; i++)
	{
		print_card(hand + i);
	}
	printf("\n");
	
	hand[0] = d.c[39 + 3];
	hand[1] = d.c[13 + 3];
	hand[2] = d.c[26 + 2];
	hand[3] = d.c[39 + 2];
	hand[4] = d.c[39 + 11];
	print_5_card_type(hand);
	for (int i = 0; i < 5; i++)
	{
		print_card(hand + i);
	}
	printf("\n");
	
	hand[0] = d.c[0];
	hand[1] = d.c[26 + 0];
	hand[2] = d.c[39 + 7];
	hand[3] = d.c[13 + 3];
	hand[4] = d.c[0 + 6];
	print_5_card_type(hand);
	for (int i = 0; i < 5; i++)
	{
		print_card(hand + i);
	}
	printf("\n");
	
	hand[0] = d.c[26 + 2];
	hand[1] = d.c[39 + 10];
	hand[2] = d.c[13 + 7];
	hand[3] = d.c[0 + 3];
	hand[4] = d.c[13 + 1];
	print_5_card_type(hand);
	for (int i = 0; i < 5; i++)
	{
		print_card(hand + i);
	}
	printf("\n");
	
}


void test_1()
{
	srand(time(0));
	
	deck d;
	int number_of_drawn_cards = 7;
	
	card test_1[number_of_drawn_cards];
	card test_2[number_of_drawn_cards];
	
	initialize_deck(&d);
	
	printf("\n ---------- Testing code ------------ ");
	
	printf("\n\nTest 1 - draw 7 cards in random:\n");
	draw_cards(number_of_drawn_cards, &d, test_1);
	for (int i = 0; i < number_of_drawn_cards; i++)
	{
		print_card(test_1 + i);
	}
	
	printf("\n\nTest 2 - draw 7 cards in random and sort pips:\n");
	draw_cards(number_of_drawn_cards, &d, test_2);
	qsort(test_2, number_of_drawn_cards, sizeof(card), cmpfunc);
	for (int i = 0; i < number_of_drawn_cards; i++)
	{
		print_card(test_2 + i);
	}
	
	printf("\n\n");
	
}


void test_2(int number_of_drawn_cards)
{
	srand(time(0));
	
	deck d;
	
	card test[number_of_drawn_cards];
	
	initialize_deck(&d);
	
	printf("\n ---------- Testing code ------------ ");
	
	printf("\n\nTest - draw %d cards in random, and determine hand:\n", number_of_drawn_cards);
	draw_cards(number_of_drawn_cards, &d, test);
	for (int i = 0; i < number_of_drawn_cards; i++)
	{
		print_card(test + i);
	}
	poker_hands result = determine_best_5_card_type(test, number_of_drawn_cards);
	print_card_type(result);
	
	
	printf("\n\n");
	
}


/* Simulate probability of different hands */


void simulate_probability(int number_of_drawn_cards, int* count_array, double* probability_array, int repeat)   /* length of probaility_array must be equal to NUMBER_OF_HAND_TYPES */
{
	assert(repeat > 1);
	printf("\nStart simulation... number of trials: %d\n\n", repeat);
	srand(time(0));
	
	for (int i = 0; i < NUMBER_OF_HAND_TYPES; i++)
	{
		count_array[i] = 0;
		probability_array[i] = 0.0;
	}
	
	deck d;
	card test[number_of_drawn_cards];
	poker_hands test_result;
	
	initialize_deck(&d);
	
	for (int i = 0; i < repeat; i++)
	{
		draw_cards(number_of_drawn_cards, &d, test);
		test_result = determine_best_5_card_type(test, number_of_drawn_cards);
		count_array[test_result] += 1;
	}
	
	for (int i = 0; i < NUMBER_OF_HAND_TYPES; i++)
	{
		probability_array[i] = (float)count_array[i] / (float)repeat;
	}
}


void print_probability(int number_of_drawn_cards, const double* probability_array)
{
	printf("\n\n ----- Printing probability of poker hands, when each time draws %d cards: -----\n\n", number_of_drawn_cards);
	printf(" ♪ Royal Flush:  %lf %% \n", probability_array[ROYAL_FLUSH] * 100);
	printf(" ♪ Straight Flush:  %lf %% \n", probability_array[STRAIGHT_FLUSH] * 100);
	printf(" ♪ Four of a kind:  %lf %% \n", probability_array[FOUR_OF_A_KIND] * 100);
	printf(" ♪ Full house:  %lf %% \n", probability_array[FULL_HOUSE] * 100);
	printf(" ♪ Flush:  %lf %% \n", probability_array[FLUSH] * 100);
	printf(" ♪ Straight:  %lf %% \n", probability_array[STRAIGHT] * 100);
	printf(" ♪ Three of a kind:  %lf %% \n", probability_array[THREE_OF_A_KIND] * 100);
	printf(" ♪ Two pairs:  %lf %% \n", probability_array[TWO_PAIR] * 100);
	printf(" ♪ One pair:  %lf %% \n", probability_array[PAIR] * 100);
	printf(" ♪ Ace high or less:  %lf %% \n", probability_array[ACE_HIGH_OR_LESS] * 100);
	
	printf("\n");
}


/* main() */


int main(void)
{
	
	srand(time(0));
	
	deck d;
	int number_of_drawn_cards = 7;
	
	initialize_deck(&d);
	shuffle_deck(&d);
	
	list_all_poker_hands();
	test_2(number_of_drawn_cards);
	
	int count_array[NUMBER_OF_HAND_TYPES];
	double probability_array[NUMBER_OF_HAND_TYPES];
	
	int repeat = 1000000;
	
	clock_t begin = clock();
	
	simulate_probability(number_of_drawn_cards, count_array, probability_array, repeat);
	print_probability(number_of_drawn_cards, probability_array);
	
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	
	
	printf("... time spent for simulation: %lf s.", time_spent);
	
	return 0;
	
}
