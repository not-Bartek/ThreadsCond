#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

#define BUFFERSIZE 256
#define READCHUNKS 4
#define THREAD_NUM 3
volatile sig_atomic_t work = 1;

typedef struct
{
    int id;
    int *idlethreads;
    int *condition;
    pthread_cond_t *cond;
    pthread_mutex_t *mutex;
} thread_arg;

void sigint_handler(int sig) { work = 0; }

void set_handler(void (*f)(int), int sigNo)
{
    struct sigaction act;
    memset(&act, 0x00, sizeof(struct sigaction));
    act.sa_handler = f;
    
    if (-1 == sigaction(sigNo, &act, NULL))
        ERR("sigaction");
}

ssize_t bulk_read(int fd, char *buf, size_t count)
{
    int c;
    size_t len = 0;
    do
    {
        c = TEMP_FAILURE_RETRY(read(fd, buf, count));
        if (c < 0)
            return c;
        if (c == 0)
            return len;
        buf += c;
        len += c;
        count -= c;
    } while (count > 0);
    return len;
}

ssize_t bulk_write(int fd, char *buf, size_t count)
{
    int c;
    size_t len = 0;
    do
    {
        c = TEMP_FAILURE_RETRY(write(fd, buf, count));
        if (c < 0)
            return c;
        buf += c;
        len += c;
        count -= c;
    } while (count > 0);
    return len;
}

void cleanup(void *arg) { pthread_mutex_unlock((pthread_mutex_t *)arg); }

int main() {
    return 0;
}