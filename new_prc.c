//tnew_process.c
#include "shell.h"

/**
 * tnew_process - create a new process
 * @args: array of strings that contains the command and its flags
 *
 * Return: 1 if success, 0 otherwise.
 */
int tnew_process(char **args)
{
 pid_t pid;
 int status;

pid = fork();
 if (pid ==  0)
 {
  /* child process */
  if (execvp(args[0], args) == -1)
  {
   perror("error in tnew_process: child process");
  }
  exit(EXIT_FAILURE);
 }
 else if (pid < 0)
 {
  /* error forking */
  perror("error in tnew_process: forking");
 }
 else
 {
  /* parent process */
  do {
   waitpid(pid, &status, WUNTRACED);
  } while (!WIFEXITED(status) && !WIFSIGNALED(status));
 }
 return (-1);
}
