#include "../../include/minishell.h"
/*
    execute command as child procces in order to keep minishell running
    TODO: support characters like "|", ">", "<", etc.
*/

void execute(char *path, char **command_table)
{
    pid_t   pid;
    int     status;
    struct  rusage ru;

    pid=fork();
    if (pid < 0) 
    {
        err_msg("fork failed");
    }
    else if (pid == 0) 
    {
        execve(path, command_table,NULL);
        perror("command failed");
        // ^ This can only be reached if execve fails
        exit(1);
    }
    wait4(pid, &status, 0, &ru);
}
