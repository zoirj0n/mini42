
#include "minishell.h"

static char *get_dir_contents(void)
{
	char *contents;
	DIR *dp;
	struct dirent *dirp;
	char *cwd;

	cwd = getcwd(NULL, 0);
	contents = ft_strdup("");
	if (cwd == NULL)
		return (ft_strdup(""));
	dp = opendir(cwd);
	deallocate_memory(&cwd);
	if (dp == NULL)
		return (ft_strdup(""));
	dirp = readdir(dp);
	while (dirp != NULL)
	{
		if (dirp->d_name[0] != '.' && contents[0] != '\0')
			contents = join_and_free_strings(contents, "\n", 1);
		if (dirp->d_name[0] != '.')
			contents = join_and_free_strings(contents, dirp->d_name, 1);
		dirp = readdir(dp);
	}
	closedir(dp);
	return (contents);
}

static char *single_wildcard(char *token)
{
	char *res;

	res = get_dir_contents();
	if (*res == '\0')
		res = ft_strdup(token);
	while (ft_strchr(res, '\n') != NULL)
		ft_strchr(res, '\n')[0] = ' ';
	deallocate_memory(&token);
	return (res);
}

static char *expand_wildcard_cleanup(char *res, char *token,
									 t_wildcard **split_wc, char **contents)
{
	size_t i;

	if (ft_strlen(res) == 0)
	{
		deallocate_memory(&res);
		res = ft_strdup(token);
	}
	deallocate_memory(&token);
	i = 0;
	while (split_wc[i] != NULL)
	{
		deallocate_memory(&split_wc[i]->str);
		deallocate_memory(&split_wc[i]);
		i++;
	}
	deallocate_memory(&split_wc);
	(void)split_wc;
	release_string_array(contents);
	return (remove_quote_characters(res));
}

static bool check_for_wildcards(t_wildcard **wildcards)
{
	size_t i;
	bool all_charseqs;

	i = 0;
	all_charseqs = true;
	while (wildcards[i] != NULL)
	{
		if (wildcards[i]->is_wildcard == true)
			all_charseqs = false;
		i++;
	}
	return (all_charseqs);
}

char *apply_wildcard_expansion(char *token)
{
	char **contents;
	char *contents_str;
	t_wildcard **wildcards;
	int i;
	char *res;

	if (ft_strncmp(token, "*", ft_strlen(token)) == 0)
		return (single_wildcard(token));
	res = ft_strdup("");
	contents_str = get_dir_contents();
	contents = ft_split(contents_str, '\n');
	deallocate_memory(&contents_str);
	wildcards = parse_wildcard_pattern(token);
	if (check_for_wildcards(wildcards) == true)
		return (expand_wildcard_cleanup(res, token, wildcards, contents));
	i = -1;
	while (contents[++i] != NULL)
	{
		if (compare_string_with_wildcard(contents[i], wildcards) == true && res[0] != '\0')
			res = join_and_free_strings(res, " ", 1);
		if (compare_string_with_wildcard(contents[i], wildcards) == true)
			res = join_and_free_strings(res, contents[i], 1);
	}
	return (expand_wildcard_cleanup(res, token, wildcards, contents));
}
