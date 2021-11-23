/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:28:16 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/23 15:35:53 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sh_count_word(char const *s)
{
	int	i;
	int	count;
	int quote;

	if (ft_strlen(s) < 3)
		return (1);
	i = 0;
	count = 1;
	quote = 0;
	while (s[i])
	{
		if (is_quote(s[i], quote) > 0)
		{
			quote = is_quote(s[i], quote);
			if (quote != S_OPEN || quote != D_OPEN)
				quote = 0;
		}
		if (quote == 0 && check_priority(s, i) > 0)
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

int	sh_make_word(t_bundle *bundle, char const *s, int j, int word_len)
{
	int		i;

	i = 0;
	while (word_len)
		bundle->cmd_line[i++] = s[j - word_len--];
	bundle->cmd_line[i] = '\0';
	return (0);
}

int	cut_cmd(t_bundle *bundles, char const *s)
{
	int		i;
	int		j;
	int		word_len;

	i = 0;
	j = 0;
	word_len = 0;
	while (s[j]) // 세미콜론 유무 및 우선순위 체크하여 각 bundle의 cmd_line 생성
	{
		if (!is_quote(s[j], bundles[i].quote) && check_priority(s, j))
		{
			bundles[i].priority = check_priority(s, j);
			j += 2;
		}
		while (s[j] && !(!bundles[i].quote && check_priority(s, j)))
		{
			bundles[i].quote = is_quote(s[j++], bundles[i].quote);
			if (bundles[i].quote != S_OPEN || bundles[i].quote != D_OPEN)
				bundles[i].quote = 0;
			word_len++;
		}
		if (set_bundle_line(&bundles[i], word_len))
			return (i);
		word_len = sh_make_word(&bundles[i], s, j, word_len);
		i++;
	}
	return (-1);
}

t_bundle	*split_bundle(char **env, char const *str)
{
	int			bundles_num;
	t_bundle	*bundles;
	int			i;

	bundles_num = sh_count_word(str); // 우선순위 구문 count
	bundles = (t_bundle *)malloc(sizeof(t_bundle) * (bundles_num + 1));
	if (bundles == NULL)
		return (NULL);
	bundles[bundles_num].cmd_line = NULL;
	set_bundle(bundles, env, bundles_num, str);
	i = cut_cmd(bundles, str);
	// if (i > -1)
	// 	free_bundle(bundles);
	return (bundles);
}
