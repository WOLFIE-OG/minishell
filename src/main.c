/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otodd <otodd@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:25:24 by ssottori          #+#    #+#             */
/*   Updated: 2024/07/16 18:25:42 by otodd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_var_signal;

static void	ft_create_builtin_array(t_root *root)
{
	root->builtin_array = ft_strarrayappend2(NULL,
			ft_strdup("cd"));
	root->builtin_array = ft_strarrayappend2(root->builtin_array,
			ft_strdup("pwd"));
	root->builtin_array = ft_strarrayappend2(root->builtin_array,
			ft_strdup("export"));
	root->builtin_array = ft_strarrayappend2(root->builtin_array,
			ft_strdup("unset"));
	root->builtin_array = ft_strarrayappend2(root->builtin_array,
			ft_strdup("env"));
	root->builtin_array = ft_strarrayappend2(root->builtin_array,
			ft_strdup("exit"));
	root->builtin_array = ft_strarrayappend2(root->builtin_array,
			ft_strdup("echo"));
}

void	ft_init_shell(t_root *root, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	//ft_config_siginit();
	root->env = ft_init_env(env);
	ft_create_builtin_array(root);
}

static char	*ft_set_prompt(t_root *root)
{
	root->prompt = ft_strarrayappend2(NULL, ft_strdup(BGRN));
	root->prompt = ft_strarrayappend2(root->prompt,
			ft_strdup(ft_get_var(root, "USER")->value));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("@"));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("minishell:"));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup(RESET));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup(BBLU));
	root->prompt = ft_strarrayappend2(root->prompt,
			ft_strdup(ft_get_var(root, "PWD")->value));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup(RESET));
	root->prompt = ft_strarrayappend2(root->prompt, ft_strdup("$ "));
	return (ft_strarraytostr(root->prompt));
}

/*
ft_echo(ft_strarrayappend2(ft_strarrayappend2(NULL,
	"/usr/bin"), get_var(root, "PWD")->value));
	printf("%d\n", is_builtin(root, "cd"));
	ft_pwd(root);
	ft_unset(root, "TESTVAR");
	ft_env(root);
*/
static void	ft_builtin_test(t_root *root)
{
	char	**tmp;
	char	*tmp2;
	t_token	*head;

	if (!ft_token_size(root->tokens))
		return ;
	if (!ft_strcmp(root->tokens->str, "cd"))
		ft_cd(root);
	else if (!ft_strcmp(root->tokens->str, "export"))
		ft_export(root);
	else if (!ft_strcmp(root->tokens->str, "env"))
		ft_env(root);
	else if (!ft_strcmp(root->tokens->str, "unset"))
		ft_unset(root);
	else if (!ft_strcmp(root->tokens->str, "exit"))
		ft_exit(root, EXIT_SUCCESS);
	else if (!ft_strcmp(root->tokens->str, "echo"))
		ft_echo(root);
	else if (!ft_strcmp(root->tokens->str, "pwd"))
		ft_pwd(root);
	else
	{
		head = root->tokens;
		tmp2 = ft_strjoin("/bin/", head->str);
		tmp = ft_strarrayappend2(NULL, ft_strdup(tmp2));
		free(tmp2);
		head = head->next;
		while (head)
		{
			tmp = ft_strarrayappend2(tmp, ft_strdup(head->str));
			head = head->next;
		}
		ft_runner_process(root, tmp);
		ft_free_array(tmp, ft_strarraylen(tmp));
		free(tmp);
	}
}

static void	print_tokens(t_token *head)
{
	t_token *current = head;
	while (current)
	{
		printf("token value = '%s' -> token type = %d | index = %d\n", current->str, current->type, current->index);
		current = current->next;
	}
}

static void	free_tokens(t_token *head)
{
	t_token *current = head;
	t_token *next;

	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}

static int	tokenizer_tester(int ac, char **av)
{
	int i = 1;
	t_token *tokens = NULL;

	if (ac > 1)
	{
		while (i < ac)
		{
			printf("input = %s\n", av[i]);
			tokens = ft_tokenizer(av[i]);
			print_tokens(tokens);
			free_tokens(tokens);
			printf("\n");
			i++;
		}
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	*tmp;
	t_root	root;

	g_var_signal = 0;
	ft_init_shell(&root, ac, av, envp);
	tokenizer_tester(ac, av);
	ft_config_siginit();
	// ft_config_sigquit();
	while (true)
	{
		tmp = ft_set_prompt(&root);
		input = readline(tmp);
		ft_free_array(root.prompt, ft_strarraylen(root.prompt));
		free(root.prompt);
		free(tmp);
		// ft_test_token();
		if (!input)
		{
			printf("exit\n"); //handling EOF
			break ;
		}
		root.tokens = ft_tokenizer(input);
		print_tokens(root.tokens);
		ft_builtin_test(&root);
		free_tokens(root.tokens);
		add_history(input);
		free(input);
	}
	ft_kill_shell(&root, EXIT_SUCCESS);
}
