
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
	accounts[0].balance = 500;
	accounts[1].balance = 500;
	transfer(0, 1, 100);
	transfer(1,0,100);

return NULL;
}

void transfer(int from_id, int to_id, double amount){
printf("Thread %ld: Attempting transfer from %d to %d\n",pthread_self(), from_id, to_id);
pthread_mutex_lock(&accounts[from_id].lock);
printf("Thread %ld: Locked account %d\n", pthread_self(), from_id);
// Simulate processing delay - gives other thread time to create

usleep(300); // Sleep for 100 microseconds
printf("Thread %ld: Waiting for account %d\n", pthread_self(), to_id);
pthread_mutex_lock(&accounts[to_id].lock);
// If we get here , no deadlock occurred this time
accounts[from_id].balance -= amount;
accounts[to_id].balance += amount;
pthread_mutex_unlock(&accounts[to_id].lock);
pthread_mutex_unlock(&accounts[from_id].lock);
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
