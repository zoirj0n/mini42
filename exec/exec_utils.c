
#include "minishell.h"

/**
 * @brief Checks if the dir/path to the directory exists.
 *
 * @param path
 * @return int
 */
int	check_directory_status(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

/**
 * @brief A wrapper functions which calls the clos function.
 * It closes the fds if its != -1 (Invalid Fds).
 *
 * @param fd
 */
void	close_descriptor(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

/**
 * @brief Joins the path to the command.
 *
 * @param bin
 * @param paths
 * @param path
 */
static void	join_path(char *bin, char **paths, char **path)
{
	int	i;

	i = 0;
	while (bin != NULL && paths != NULL && paths[i] != NULL)
	{
		*path = ft_strjoin(paths[i], bin);
		if (*path == NULL || access(*path, F_OK) != -1)
			break ;
		deallocate_memory(path);
		i++;
	}
}

/**
 * @brief Get the full path of a command.
 *
 * @param bin
 * @param env
 * @return char*
 */
char	*resolve_command_path(char *bin, char **env)
{
	int		i;
	char	*path;
	char	**paths;
	char	*bin_cpy;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	paths = ft_split(ft_strchr(env[i], '=') + 1, ':');
	i = 0;
	bin_cpy = ft_strdup(bin);
	bin = join_and_free_strings("/", bin, 2);
	join_path(bin, paths, &path);
	if (bin == NULL || paths == NULL || paths[i] == NULL)
		path = NULL;
	deallocate_memory(&bin);
	release_string_array(paths);
	if (path == NULL)
		return (bin_cpy);
	deallocate_memory(&bin_cpy);
	return (path);
}
