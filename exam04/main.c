#include <libc.h>
#include <stdbool.h>

void print(char *s)
{
	while (*s)
		write(2, s++, 1);
}

void cd(char **cmd_list)
{
	if (!cmd_list[1] || cmd_list[2])
	{
		printf("error: cd: bad arguments\n");
		return ; // error
	}
	if (chdir(cmd_list[1]) < 0)
	{
		print("error: cd: cannot change directory to ");
		print(cmd_list[1]);
		print("\n");
		return ; // error
	}
}

int	main(int ac, char **av, char **envp)
{
	char *cmd_list[1000000] = {NULL};

	if (ac == 1)
		return 0;
	int i = 1;
	int nbr_of_cmds = 0;
	int fd[2];
	execute:
	for (; i < ac && strcmp(av[i], ";"); i++) {
		int j = 0;
		while (i < ac && strcmp(av[i], "|") && strcmp(av[i], ";"))
			cmd_list[j++] = av[i++];
		cmd_list[j] = NULL;
		if (cmd_list[0] && !strcmp(cmd_list[0], "cd"))
		{
			cd(cmd_list);
			continue ;
		}
		nbr_of_cmds++;
		if (av[i] && !strcmp(av[i], "|"))
		{
			if (pipe(fd) < 0)
			{
				print("error: fatal\n");
				return 1;
			}
		}
		int id = fork();
		if (id < 0)
		{
			print("error: fatal\n");
			return 1;
		}
		if (id == 0)
		{
			if (av[i] && !strcmp(av[i], "|"))
			{
				dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
			}
			execve(cmd_list[0], cmd_list, envp);
			return 1;
		}
		else
		{
			close(0);
			if (av[i] && !strcmp(av[i], "|"))
			{
				dup2(fd[0], 0);
				close(fd[0]);
				close(fd[1]);
			}
		}
	}
	for (int x = 0; x < nbr_of_cmds; x++)
		waitpid(-1, NULL, 0);
	if (av[i] && !strcmp(av[i], ";"))
	{
		i++;
		goto execute;
	}
}