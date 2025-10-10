
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define NUM_ACCOUNTS  3
#define TRANSACTIONS 1000
#define NUM_THREADS 10


typedef struct{
	int account_id;
	double balance;
	int transaction_count;
} Account;

Account accounts[NUM_ACCOUNTS];


void* teller_thread(void* arg){
	int teller_id = *(int*)arg;
	srand(time(NULL));
	for (int i = 0; i<TRANSACTIONS; i++){
	int rand_num = rand()%(sizeof(accounts)/sizeof(accounts[0]));
	int randBal = 1;

//		printf("previous balance: %lf\n\n", account.balance);
		for (int j = 0; j<10; j++){
		accounts[rand_num].balance += randBal;
		}
//		printf("Teller %d: Transaction %d\n", teller_id, i);
//		printf("balance increase: %lf\n\n", account.balance);

}
	return NULL;
}
int main(){
	//	Account acc = accounts[0];
	//accounts[0].balance = 1000.0;
	pthread_t threads[NUM_THREADS];
	int thread_ids [ NUM_THREADS ];
//	printf("Initial balance: %lf\n", account.balance);
	for ( int i = 0; i < NUM_THREADS ; i++) {
	thread_ids[i] = i;
	pthread_create(&threads[i], NULL, teller_thread, &thread_ids[i]);
}
	for ( int i = 0; i < NUM_THREADS ; i++) {
	pthread_join(threads[i], NULL);
}	

	double final_balance = 0;
	for(int i = 0; i< NUM_ACCOUNTS; i++){
	final_balance += accounts[i].balance;
	}
	printf("Final balance: %lf\n", final_balance);
}
