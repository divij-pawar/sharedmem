# Tested on Python3.6.8
import sysv_ipc as ipc

def main():
    path = "/tmp"
    key = ipc.ftok(path, 2333)
    shm = ipc.SharedMemory(key, 0, 0)

    #I found if we do not attach ourselves
    #it will attach as ReadOnly.
    shm.attach(0,0)
    buf = shm.read(19)
    print(buf)
    shm.detach()
    pass

if __name__ == '__main__':
    main()