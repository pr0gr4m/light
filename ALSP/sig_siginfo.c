#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sa_sigaction_usr(int signum, siginfo_t *si, void *sv);

int main()
{
	struct sigaction sa_usr1;
	struct sigaction sa_usr2;
	memset(&sa_usr1, 0, sizeof(struct sigaction));
	sa_usr1.sa_sigaction = sa_sigaction_usr;
	sigfillset(&sa_usr1.sa_mask);
	sa_usr1.sa_flags = SA_SIGINFO;
	memset(&sa_usr2, 0, sizeof(struct sigaction));
	sa_usr2.sa_sigaction = sa_sigaction_usr;
	sigemptyset(&sa_usr2.sa_mask);
	sa_usr2.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa_usr1, NULL);
	sigaction(SIGUSR2, &sa_usr2, NULL);

	printf("[MAIN] SIGNAL-Handler installed, pid(%d) \n", getpid());
	for (;;) {
		pause();
		printf("[MAIN] Recv SIGNAL...\n");
	}
	return EXIT_SUCCESS;
}

void sa_sigaction_usr(int signum, siginfo_t *si, void *sv)
{
	int i;
	printf("\t (signo:%d) (UID:%d) (PID:%d)\n", si->si_signo, si->si_uid, si->si_pid);
	for (i = 0; i < 10; i++) {
		printf("\tSignal(%s):%d sec. \n", signum == SIGUSR1 ? "USR1" : "USR2", i);
		sleep(1);
	}
}
