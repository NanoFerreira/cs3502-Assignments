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
	time_t time;
} Account;

Account accounts[NUM_ACCOUNTS];


void* teller_thread(void* arg){
	int teller_id = *(int*)arg;
	accounts[0].balance = 500;
	accounts[1].balance = 500;
//	transfer_time(0, 1, 100);
//	transfer_time(1,0,100);
	transfer_logic(0, 1, 100);
	transfer_logic(1,0,100);

return NULL;
}

void transfer_time(int from_id, int to_id, double amount){
time_t abs_timeout = time(NULL) + 0.01;
printf("Thread %ld: Attempting transfer from %d to %d\n",pthread_self(), from_id, to_id);
pthread_mutex_timedlock(&accounts[from_id].lock, &abs_timeout);
printf("Thread %ld: Locked account %d\n", pthread_self(), from_id);


usleep(300); 
printf("Thread %ld: Waiting for account %d\n", pthread_self(), to_id);
pthread_mutex_timedlock(&accounts[to_id].lock, &abs_timeout);

accounts[from_id].balance -= amount;
accounts[to_id].balance += amount;

pthread_mutex_unlock(&accounts[to_id].lock);
pthread_mutex_unlock(&accounts[from_id].lock);
}

void transfer_logic(int from_id, int to_id, double amount){

id1 = from_id;
id2 = to_id;

if(from_id>to_id){
	id2 = from_id;
	id1 = to_id;
}


printf("Thread %ld: Attempting transfer from %d to %d\n",pthread_self(), from_id, to_id);
pthread_mutex_lock(&accounts[id1].lock);
printf("Thread %ld: Locked account %d\n", pthread_self(), from_id);


usleep(300);
printf("Thread %ld: Waiting for account %d\n", pthread_self(), to_id);
pthread_mutex_timedlock(&accounts[id2].lock4);

accounts[from_id].balance -= amount;
accounts[to_id].balance += amount;
pthread_mutex_unlock(&accounts[id2].lock);
pthread_mutex_unlock(&accounts[id1].lock);
}


int main(){
	//	Account acc = accounts[0];
	//	accounts[0].balance = 1000.0;
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
