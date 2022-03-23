#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "ft_split.c"

bool match(char *wildcard, char *s) {
    // match begin
    for (int i = 0; wildcard[i] && s[i] && wildcard[i] != '*'; i++) {
        if (s[i] != wildcard[i])
            return false;
    }
    // match end
    for (int i = ft_strlen(wildcard), j = ft_strlen(s); i > 0 && j > 0 && wildcard[i] != '*'; j--, i--) {
        if (s[j] != wildcard[i])
            return false;
    }

    // match midle
    char **words = ft_split(wildcard, '*');
    for (int i = 0, j = 0; words[i]; i++) {
        if (!strstr(s + j, words[i]))
            return false;
        j += ft_strlen(words[i]);
    }
    return true;
}

int main(int ac, char **av) {
    if (ac != 3) {
        dup2(2, 1);
        printf("Invalid number of args\n");
        return 1;
    }

    printf("%s\n", match(av[1], av[2]) ? "Match" : "Don't match");
}