#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

pthread_mutex_t lock;
pthread_cond_t cond;
int num_chars = 0;
int num_ten = 0;
int num_fifty = 0;

void *watcher(void *arg) {
    pthread_mutex_lock(&lock);
    while (num_fifty == 0) {
        if (num_chars > 10 && num_ten == 0) {
            printf(">10\n");
            num_ten = 1;
        }
        if (num_chars > 50) {
            printf(">50\n");
            num_fifty = 1;
            break;
        }
        pthread_cond_wait(&cond, &lock);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, watcher, NULL);

    while (true) {
        char c;
        if (scanf("%c", &c) == EOF) {
            break;
        }

        pthread_mutex_lock(&lock);
        num_chars++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }

    pthread_join(thread, NULL);

    printf("Number of characters entered:%d\n", num_chars);

  
}
