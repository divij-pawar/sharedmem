# Shared memory explainer code
Sharing memory between two processes one running in C++ and one running in Python
We write to memory from C++ and read from Python.

# References
## C++
* [sys/ipc.h](https://pubs.opengroup.org/onlinepubs/7908799/xsh/sysipc.h.html)
* [ftok](https://pubs.opengroup.org/onlinepubs/7908799/xsh/ftok.html) 
* [shmget](https://pubs.opengroup.org/onlinepubs/7908799/xsh/shmget.html)
* [shmat](https://pubs.opengroup.org/onlinepubs/7908799/xsh/shmat.html)
* [shmdt](https://pubs.opengroup.org/onlinepubs/7908799/xsh/shmdt.html)
* [shmctl](https://pubs.opengroup.org/onlinepubs/7908799/xsh/shmctl.html)

## Python
* [sysv_ipc](https://semanchuk.com/philip/sysv_ipc/)
* [SharedMemory](https://semanchuk.com/philip/sysv_ipc/#shared_memory)
* [Ftok issue](https://semanchuk.com/philip/sysv_ipc/#ftok_weakness)
