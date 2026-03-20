#include "minishell.h"

t_token	*ft_find_matching_paren(t_token *open_paren)
{
	t_token	*runner;
	int		count;

	if (!open_paren || open_paren->type != TOK_L_PAREN)
		return (NULL);
	runner = open_paren->next;
	count = 1;
	while (runner && count > 0)
	{
		if (runner->type == TOK_L_PAREN)
			count++;
		else if (runner->type == TOK_R_PAREN)
			count--;
		if (count > 0)
			runner = runner->next;
	}
	return (runner);
}

t_ast	*ft_create_subshell_node(t_token *current, t_minishell *data)
{
	t_ast	*node;
	t_token	*inside_content;
	t_token	*after_subshell;
	t_token	*r_paren;

	r_paren = ft_find_matching_paren(current);
	if (!r_paren || r_paren == current->next)
	{
		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
		return (NULL);
	}
	inside_content = current->next;
	after_subshell = r_paren->next;
	r_paren->prev->next = NULL;
	if (after_subshell)
		after_subshell->prev = NULL;
	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_SUBSHELL;
	node->left = ft_create_tree(inside_content, data);
	node->right = ft_create_tree(after_subshell, data);
	if (!node->left || !node->right)
		return (ft_free_ast(node), NULL);
	return (node);
}
