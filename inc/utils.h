/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbleskin <vbleskin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 22:19:07 by vlad              #+#    #+#             */
/*   Updated: 2026/05/07 10:00:00 by gemini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list	t_list;

struct s_list
{
	void			*content;
	struct s_list	*next;
};

/* ------ FONCTIONS DE MANIPULATION & VERIFICATION DE CARACTERES ------ */

/**
	* Verifie si un caractere est une lettre majuscule ou minuscule,
	* - return : une valeur si VRAI et 0 si FAUX.
	*/
int			ft_isalpha(int c);

/**
	* Verifie si un caractere est un chiffre,
	* - return : une valeur si VRAI et 0 si FAUX.
	*/
int			ft_isdigit(int c);

/**
	* Verifie si un caractere est alpha-numerique,
	* - return : une valeur si VRAI et 0 si FAUX.
	*/
int			ft_isalnum(int c);

/**
	* Verifie si un caractere est dans la table ASCII,
	* - return : une valeur si VRAI et 0 si FAUX.
	*/
int			ft_isascii(int c);

/**
	* Verifie si un caractere est printable,
	* - return : une valeur si VRAI et 0 si FAUX.
	*/
int			ft_isprint(int c);

/**
	* Verifie si un caractere est une lettre majuscule,
	* - return : une valeur si VRAI et 0 si FAUX.
	*/
int			ft_isupper(int c);

/**
	* Verifie si un caractere est une lettre minuscule,
	* - return : une valeur si VRAI et 0 si FAUX.
	*/
int			ft_islower(int c);

/**
	* Convertit une lettre minuscule en majuscule,
	* - return : le caractere converti ou c inchange.
	*/
int			ft_toupper(int c);

/**
	* Convertit une lettre majuscule en minuscule,
	* - return : le caractere converti ou c inchange.
	*/
int			ft_tolower(int c);

/* ------ FONCTIONS DE MANIPULATION & RECHERCHE DE CHAINES ------ */

/**
	* Calcule la longueur d'une chaine de caracteres,
	* - return : la longueur de la chaine.
	*/
int			ft_strlen(const char *str);

/**
	* Copie jusqu'a s caractere(s) de src dans dest et termine par '\0',
	* - return : la taille totale de la chaine qu'on essaye de creer.
	*/
size_t		ft_strlcpy(char *dest, const char *src, size_t s);

/**
	* Concatene src a la fin de dest en garantissant la terminaison '\0',
	* - return : la longueur totale de la chaine qu'on a essaye de creer.
	*/
size_t		ft_strlcat(char *dest, const char *src, size_t s);

/**
	* Cherche la premiere occurrence d'un caractere dans une chaine,
	* - return : un pointeur vers le caractere trouve ou NULL.
	*/
char		*ft_strchr(const char *s, int c);

/**
	* Cherche la derniere occurrence d'un caractere dans une chaine,
	* - return : un pointeur vers le caractere trouve ou NULL.
	*/
char		*ft_strrchr(const char *s, int c);

/**
	* Compare deux chaines sur au plus n caracteres,
	* - return : la difference entre les deux premiers caracteres differents.
	*/
int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			ft_strcmp(const char *s1, const char *s2);

/**
	* Cherche une sous-chaine dans une chaine (taille limitee),
	* - return : un pointeur vers le debut de la sous-chaine ou NULL.
	*/
char		*ft_strnstr(const char *big, const char *little, size_t len);

/**
	* Duplique une chaine de caracteres,
	* - return : un pointeur vers la nouvelle chaine ou NULL.
	*/
char		*ft_strdup(const char *s);

/**
	* Duplique jusqu'a 'n' caracteres de la chaine 'src'
	* - return : un pointeur vers la nouvelle chaine ou NULL.
	*/
char		*ft_strndup(char *src, size_t n);

/**
	* Alloue et retourne une sous-chaine a partir de s,
	* - return : la sous-chaine allouee ou NULL.
	*/
char		*ft_substr(char const *s, unsigned int start, size_t len);

/**
	* strjoin avec un separateur.
	*/
char		*ft_super_join(char const *s1, char const *s2, char sep);

/**
	* Alloue et retourne la concatenation de s1 et s2,
	* - return : la nouvelle chaine ou NULL.
	*/
char		*ft_strjoin(char const *s1, char const *s2);

/**
	* Alloue et retourne une copie de s1 sans les caracteres set au debut/fin,
	* - return : la chaine nettoyee ou NULL.
	*/
char		*ft_strtrim(char const *s1, char const *set);

/**
	* Alloue et retourne un tableau de chaines obtenu en separant s par c,
	* - return : le tableau de chaines (termine par NULL) ou NULL.
	*/
char		**ft_split(char const *s, char c);

/**
	* Applique f a chaque caractere de s pour creer une nouvelle chaine.
	*/
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
	* Applique f a chaque caractere de s (modification sur place).
	*/
void		ft_striteri(char *s, void (*f)(unsigned int, char*));

/* ------ FONCTIONS DE CONVERSION ------ */

/**
	* Convertit le debut d'une chaine en entier (atoi),
	* - return : l'entier converti.
	*/
int			ft_atoi(const char *str);

/**
	* Alloue et retourne une chaine representant l'entier n.
	*/
char		*ft_itoa(int n);

/* ------ FONCTIONS D'ALLOCATIONS & MANIPULATION DE MEMOIRE ------ */

/**
	* Cherche un caractere dans une zone memoire.
	*/
void		*ft_memchr(const void *s, int c, size_t n);

/**
	* Compare deux zones memoire.
	*/
int			ft_memcmp(const void *s1, const void *s2, size_t n);

/**
	* Remplit une zone memoire avec un octet constant.
	*/
void		*ft_memset(void *s, int c, size_t n);

/**
	* Met a zero des octets dans une zone memoire.
	*/
void		ft_bzero(void *s, size_t n);

/**
	* Copie une zone memoire.
	*/
void		*ft_memcpy(void *dest, const void *src, size_t n);

/**
	* Copie une zone memoire (gere le chevauchement).
	*/
void		*ft_memmove(void *dest, const void *src, size_t n);

/**
	* Alloue la memoire pour un tableau et met tout a zero.
	*/
void		*ft_calloc(size_t nmemb, size_t size);

/* ------ FONCTIONS D'ECRITURE (file descriptor) ------ */

/**
	* Ecrit le caractere c sur le descripteur de fichier fd.
	*/
void		ft_putchar_fd(char c, int fd);

/**
	* Ecrit la chaine s sur le descripteur de fichier fd.
	*/
void		ft_putstr_fd(char *s, int fd);

/**
	* Ecrit la chaine s suivie d'un retour a la ligne sur fd.
	*/
void		ft_putendl_fd(char *s, int fd);

/**
	* Ecrit l'entier n sur le descripteur de fichier fd.
	*/
void		ft_putnbr_fd(int n, int fd);

/* ------ FONCTIONS DE MANIPULATION DE LISTES CHAINEES ------ */

/**
	* Alloue et retourne un nouvel element de liste.
	*/
t_list		*ft_lstnew(void *content);

/**
	* Ajoute l'element new au debut de la liste lst.
	*/
void		ft_lstadd_front(t_list **lst, t_list *elem);

/**
	* Compte le nombre d'elements de la liste.
	*/
int			ft_lstsize(t_list *lst);

/**
	* Renvoie le dernier element de la liste.
	*/
t_list		*ft_lstlast(t_list *lst);

/**
	* Ajoute l'element new a la fin de la liste.
	*/
void		ft_lstadd_back(t_list **lst, t_list *elem);

/**
	* Supprime et libere la memoire d'un element.
	*/
void		ft_lstdelone(t_list *lst, void (*del)(void*));

/**
	* Supprime et libere la liste et ses suites.
	*/
void		ft_lstclear(t_list **lst, void (*del)(void*));

/**
	* Itere sur la liste et applique f au contenu de chaque element.
	*/
void		ft_lstiter(t_list *lst, void (*f)(void *));

/**
	* Itere sur la liste et applique f pour creer une nouvelle liste.
	*/
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
