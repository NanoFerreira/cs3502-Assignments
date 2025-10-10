
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define NUM_ACCOUNTS  2
#define TRANSACTIONS 100000
#define NUM_THREADS 100
#define INITIAL_BALANCE 100

typedef struct{
	int account_id;
	double balance;
	int transaction_count;
	pthread_mutex_t lock;
} Account;

Account accounts[NUM_ACCOUNTS];


void* teller_thread(void* arg){
	int teller_id = *(int*)arg;
	srand(time(NULL));
	for (int i = 0; i<TRANSACTIONS; i++){
	int rand_num = rand()%(sizeof(accounts)/sizeof(accounts[0]));
	int randBal = 10;
		pthread_mutex_lock(&accounts[rand_num].lock);
//		printf("previous balance: %lf\n\n", account.balance);
		accounts[rand_num].balance += randBal;
		pthread_mutex_unlock(&accounts[rand_num].lock);
//		printf("Teller %d: Transaction %d\n", teller_id, i);
//		printf("balance increase: %lf\n\n", account.balance);

}
	return NULL;
}
int main(){
	//	Account acc = accounts[0];
	//accounts[0].balance = 1000.0;
	pthread_t threads[NUM_THREADS];
	int thread_ids [NUM_THREADS];
//	printf("Initial balance: %lf\n", account.balance);
	for(int i = 0; i < NUM_ACCOUNTS; i++) {
		pthread_mutex_init(&accounts[i].lock, NULL) ;
		accounts[i].balance = INITIAL_BALANCE ;
		accounts[i].transaction_count = 0;
	}



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
