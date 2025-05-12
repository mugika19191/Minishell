/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:06:02 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/10 14:07:26 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	return_promp(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	int_hadler(int sig, siginfo_t *info, void *context)
{
	t_pipe		*pipe;
	siginfo_t	*infor;

	infor = info;
	pipe = g_env_pointer;
	if (sig == SIGINT)
	{
		if (pipe->pid == 0)
			kill(pipe->pid, SIGINT);
		printf("\n");
		return_promp();
		set_flag(pipe, 130);
	}
	if (sig == SIGTSTP)
	{
		printf("\nExit\n");
		kill(pipe->pid_shell, SIGINT);
		set_flag(pipe, 148);
	}
}

int	init_sigaction(struct sigaction *sig, t_pipe *pipe)
{
	sig->sa_sigaction = int_hadler;
	sig->sa_flags = SA_SIGINFO;
	sigemptyset(&sig->sa_mask);
	if (sigaction(SIGINT, sig, NULL) == -1)
		return (1);
	if (sigaction(SIGTSTP, sig, NULL) == -1)
		return (1);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
