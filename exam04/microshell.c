/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:58:53 by thi-phng          #+#    #+#             */
/*   Updated: 2022/03/18 17:58:56 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef enum    s_type
{
    SEP,
    PIPE,
    END
}               t_type;

typedef struct      s_cmd
{
    char        **av;
    char        **env;
    t_type      type;
    t_type      prev_cmd_type;
    int         pipe_fd[2];
    int         prev_cmd_pipe;    
}                   t_cmd;

// *** UTILS *** //
int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void    putstr_err(char *str, int len)
{
    write(2, str, len);
}

int     err_int(char *s1, char *s2)
{
    write(2, "error: ", 7);
    if (s1)
        putstr_err(s1, ft_strlen(s1));
    if (s2)
        putstr_err(s2, ft_strlen(s2));
    write(2, "\n", 1);
    return (1);
}

// *** CD *** //
int ft_cd(t_cmd *cmd)
{
    int i = 0;

    while (cmd->av[i])
        i++;
    if (i != 2)
        return (err_int("cd: bad arguments", NULL));
    if (chdir (cmd->av[0]) < 0)
        return (err_int("cd: cannot change directory path to ", cmd->av[0]));
    return (0);
}

// *** EXEC *** //
int ft_exec(t_cmd *cmd)
{
    pid_t   pid;

    if (cmd->type == PIPE)
    {
        if (pipe(cmd->pipe_fd) == -1)
            return (err_int("fatal", NULL));
    }
    pid = fork();
    if (pid == 0)//child
    {
        if (cmd->prev_cmd_type == PIPE)
            if (dup2(cmd->prev_cmd_pipe, 0) < 0)
                return (err_int("fatal", NULL));
        if (cmd->type == PIPE)
            if (dup2(cmd->pipe_fd[1], 1) < 0)
                return (err_int("fatal", NULL));
        if (execve(cmd->av[0], cmd->av, cmd->env) == -1)
        {
            err_int("cannot execute ", cmd->av[0]);
            exit (1);
        }
    }
    else //pere
    {
        waitpid(pid, 0, 0);
        if (cmd->prev_cmd_type == PIPE)
            close (cmd->prev_cmd_pipe);
        if (cmd->type == PIPE)
            close (cmd->pipe_fd[1]);
        if(cmd->prev_cmd_type == PIPE && cmd->type != PIPE)
            close (cmd->pipe_fd[0]);
    }
    return (0);
}

// *** PARSING *** //
int cmd_end(t_cmd *cmd, char **av)
{
    int i = 0;
    while (cmd->av[i])
    {
        if (!strcmp(cmd->av[i], "|"))
        {
            cmd->type = PIPE;
            av[i] = NULL;
            return (i);
        }
        if (!strcmp(cmd->av[i], ";"))
        {
            cmd->type = SEP;
            av[i] = NULL;
            return (i);
        }
        i++;
    }
    cmd->type = END;
    return (i);
}

int parse_cmd(t_cmd *cmd, char **av)
{
    int len;

    cmd->av = av;
    cmd->prev_cmd_type = cmd->type;
    cmd->prev_cmd_pipe = cmd->pipe_fd[0];
    len = cmd_end(cmd, av);
    return (len);
}

// *** MAIN *** //
int main(int ac, char **av, char **env)
{
    int     res = 0;
    int     i;
    int     avance;
    t_cmd   cmd;

    cmd.env = env;
    cmd.pipe_fd[0] = 0;
    cmd.pipe_fd[1] = 1;
    
    i = 1;
    while (i < ac && av[i])
    {
        avance = parse_cmd(&cmd, &av[i]);
        if (avance)
        {
            if (!strcmp(av[i], "cd"))
                res = ft_cd(&cmd);
            else
                res = ft_exec(&cmd);
        }
        i += avance + 1;
    }
    return (res);
}
