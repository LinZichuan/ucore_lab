#include <stdio.h>
#include <ulib.h>

int magic = -0x10384;

int
main(void) {
    int pid, code;
    cprintf("======================enter user code\n");
    cprintf("I am the parent. Forking the child...\n");
    if ((pid = fork()) == 0) {
        cprintf("pid %d exec!\n", pid);
        cprintf("I am the child.\n");
        cprintf("pid %d exit!\n", pid);
        yield();
        yield();
        yield();
        yield();
        yield();
        yield();
        yield();
        exit(magic);
    }
    else {
        cprintf("I am parent, fork a child pid %d\n",pid);
    }
    assert(pid > 0);
    cprintf("I am the parent, waiting now..\n");

    assert(waitpid(pid, &code) == 0 && code == magic);
    assert(waitpid(pid, &code) != 0 && wait() != 0);
    cprintf("waitpid %d ok.\n", pid);

    cprintf("pid %d exit pass.\n", pid);
    cprintf("======================exit user code\n");
    return 0;
}

