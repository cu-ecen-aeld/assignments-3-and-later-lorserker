#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;

    struct thread_data * thdata = (struct thread_data *)thread_param;

    int err = 0;

    err = usleep(thdata->wait_to_obtain_ms * 1000);
    if (err) {
        thdata->thread_complete_success = false;
    }

    if (!err) {
        err = pthread_mutex_lock(thdata->mutex);
        if (err) {
            thdata->thread_complete_success = false;
        }
    }

    if (!err) {
        err = usleep(thdata->wait_to_release_ms * 1000);
        if (err) {
            thdata->thread_complete_success = false;
        }
    }

    if (!err) {
        err = pthread_mutex_unlock(thdata->mutex);
        if (err) {
            thdata->thread_complete_success = false;
        }
    }

    if (!err) {
        thdata->thread_complete_success = true;
    }

    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */

    if (!thread || !mutex) {
        return false;
    }

    struct thread_data * thdata = malloc(sizeof(struct thread_data));
    if (!thdata) {
        return false;
    }

    thdata->thread = thread;
    thdata->mutex = mutex;
    thdata->thread_complete_success = false;
    thdata->wait_to_obtain_ms = wait_to_obtain_ms;
    thdata->wait_to_release_ms = wait_to_release_ms;

    int err = pthread_create(thdata->thread, NULL, threadfunc, thdata);
    if (err) {
        free(thdata);
    }

    return err == 0;
}

