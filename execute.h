# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>

int start_process(char **args);

int execute_command(char **args);
