 #include <pthread.h>
 #include <stdio.h>
 int a, b, sum;
 pthread_mutex_t lock;
 void *read_a(void *arg) {
 pthread_mutex_lock(&lock);
 printf("Thread 1: Enter value of a: ");
 scanf("%d", &a);
 pthread_mutex_unlock(&lock);
 return NULL;
 }
 void *read_b(void *arg) {
 pthread_mutex_lock(&lock);
 printf("Thread 2: Enter value of b: ");
 scanf("%d", &b);
 pthread_mutex_unlock(&lock);
 return NULL;
 }
 void *compute_sum(void *arg) {
 pthread_mutex_lock(&lock);
 sum = a + b;
 printf("Thread 3: Sum of a and b = %d\n", sum);
 pthread_mutex_unlock(&lock);
 return NULL;
 }
 int main() {
 pthread_t t1, t2, t3;
 pthread_mutex_init(&lock, NULL);
 pthread_create(&t1, NULL, read_a, NULL);
 pthread_create(&t2, NULL, read_b, NULL);
 pthread_join(t1, NULL);
 pthread_join(t2, NULL);
 pthread_create(&t3, NULL, compute_sum, NULL);
 pthread_join(t3, NULL);
 pthread_mutex_destroy(&lock);
 return 0;
 }