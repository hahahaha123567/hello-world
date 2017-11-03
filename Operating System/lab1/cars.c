# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <string.h> // strlen()
# include <unistd.h> // sleep()

// init car info
# define MAX_NUMBER 50
enum direction {
    north = 0,
    west = 1,
    south = 2,
    east = 3
};
char * name[] = {"north", "west", "south", "east"};
struct car_info {
    int num;            // sequence number
    enum direction dir; // direction
} car[MAX_NUMBER];
int car_num_total;      // car number

// init thread info
pthread_t thread[MAX_NUMBER];       // thread id
pthread_mutex_t mutex[4];           // protect condition variable
pthread_cond_t resource[4];  // if this resource is used, car behind cannot go
pthread_mutex_t right_block[4];     // 
sem_t deadlock;                     // semaphore -> deadlock

// init mutex, condition and semephore
void init ()
{
    for (int i = 0; i < 4; ++i) {
        pthread_mutex_init(&mutex[i], NULL);
        pthread_cond_init(&resource[i], NULL);
        pthread_mutex_init(&right_block[i], NULL);
    }
    sem_init(&deadlock, 0, 3); // semephore init to 3
}

void * go (void * tempArgument)
{
    struct car_info * arg = tempArgument;
    // if there has been a car, wait
    pthread_mutex_lock(&mutex[arg->dir]);
    pthread_cond_wait(&resource[arg->dir], &mutex[arg->dir]);
    pthread_mutex_unlock(&mutex[arg->dir]);
    // at the cross
    printf("car %d from %s arrives at crossing\n", arg->num, name[arg->dir]);
    usleep(1);
    // check deadlock
    sem_wait(&deadlock);
    // apply resource
    pthread_mutex_lock(&right_block[arg->dir]);
    // wait for car right
    pthread_mutex_lock(&right_block[(arg->dir + 1 ) % 4]);
    pthread_mutex_unlock(&right_block[(arg->dir + 1 ) % 4]);
    // go
    printf("car %d from %s leaving at crossing\n", arg->num, name[arg->dir]);
    // alert the car left
    pthread_mutex_unlock(&right_block[arg->dir]);
    sem_post(&deadlock);
    sleep(1); // prevent starvation
    // alert the car behind
    pthread_mutex_lock(&mutex[arg->dir]);
    pthread_cond_signal(&resource[arg->dir]);
    pthread_mutex_unlock(&mutex[arg->dir]);
}

void delete ()
{
    for (int i = 0; i < 4; ++i) {
        pthread_mutex_destroy(&mutex[i]);
        pthread_cond_destroy(&resource[i]);
        pthread_mutex_destroy(&right_block[i]);
    }
    sem_destroy(&deadlock);
}

int main (int argc, char * argv[])
{
    // init the semaphores
    init();
    // input
    if (argc == 1) {
        printf("Please input in cli argument\n");
        return 0;
    }
    int car_num_total = strlen(argv[1]);
    for (int i = 0; i < car_num_total; ++i) {
        car[i].num = i + 1;
        switch (argv[1][i]) {
            case 'n': car[i].dir = north; pthread_create(&thread[i], NULL, * go, &car[i]); break;
            case 'e': car[i].dir = east;  pthread_create(&thread[i], NULL, * go, &car[i]); break;
            case 's': car[i].dir = south; pthread_create(&thread[i], NULL, * go, &car[i]); break;
            case 'w': car[i].dir = west;  pthread_create(&thread[i], NULL, * go, &car[i]); break;
            default : printf("illegal input\n"); return 1;
        }
    }
    // initial release the block
    usleep(1);
    for (int i = 0; i < 4; ++i) {
        pthread_cond_signal(&resource[i]);
    }
    // wait for the 4 threads
    for (int i = 0; i < 4; ++i) {
        pthread_join(thread[i], NULL);
    }
    // delete the semaphores
    delete();

    return 0;
}