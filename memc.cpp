/*
Code is tested on Centos
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define GETEKYDIR ("/tmp") // shared memory directory
#define PROJECTID  (2333) // unique project id
#define SHMSIZE (1024) // shared memeory size

// error function where buf is error string
void err_exit(const char* buf) 
{
    fprintf(stderr, "%s\n", buf);
    exit(1);
}

int main(int argc, char **argv)
{
    // returns key = -1 if ftok is unsuccessful
    key_t key = ftok(GETEKYDIR, PROJECTID); 
    if ( key < 0 )
        err_exit("ftok error");
 
    /*
    IPC_CRET - Flag for creating a new segment
    IPC_EXCL - Used with IPC_CRET to ensure it creates a segment
    Bitwise or with 0664 will set access permission of the memory segment

    shmid will be -1 if shmget is unsuccessful in returning shared memory identifier and errno will be set
    */
    int shmid = shmget(key, SHMSIZE, IPC_CREAT | IPC_EXCL | 0664);
    if ( shmid == -1 ) 
    {
        if ( errno == EEXIST ) 
        {
            printf("shared memeory already exist\n");
            shmid = shmget(key ,0, 0);
            printf("reference shmid = %d\n", shmid);
        } 
        else 
        {
            perror("errno");
            err_exit("shmget error");
        }
    }

    char *addr;

    /* shmat (shared memory identifier to be attached, attach to first avaliable address,
    calling process has both read and write permissions) and returns segment's start address*/
    if ( (addr = (char*) shmat(shmid, 0, 0) ) == (void*)-1) 
    {
        //if addr is void, remove the shared mem identifier and destroy the shared memory segment
        if (shmctl (shmid, IPC_RMID, NULL) == -1)
            err_exit("shmctl error");
        else 
        {
            printf("Attach shared memory failed\n");
            printf("remove shared memory identifier successful\n");
        }

        err_exit("shmat error");
    }

    strcpy( addr, "String to be shared\n" );

    printf("Enter to exit"); 
    getchar();
    // Detach memory segment at addr and return error if unsuccessful
    if ( shmdt(addr) < 0) 
        err_exit("shmdt error");
    // Remove the shared mem identifier and destroy the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
        err_exit("shmctl error");
    else {
        printf("Finally\n");
        printf("remove shared memory identifier successful\n");
    }

    return 0;
}