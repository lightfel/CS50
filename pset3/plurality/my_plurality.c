#include <stdio.h>
#include <string.h>
#include <cs50.h>

#define CANDIDATE_MAX 9

typedef struct  s_candidate
{
    char    *name;
    int     votes;
}               t_candidate;

void    vote(t_candidate*, int);
void    print_winner(t_candidate*, int);

int main(int argc, char **argv)
{
    t_candidate candidates[CANDIDATE_MAX];
    int candidate_count;
    int voter_count;

    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return (1);
    }
    candidate_count = argc - 1;
    if (candidate_count > CANDIDATE_MAX)
    {
        printf("Maximum number of candidates is %i\n", CANDIDATE_MAX);
        return (2);
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }
    voter_count = get_int("Number of voters: ");
    for (int i = 0; i < voter_count; i++)
        vote(candidates, candidate_count);
    print_winner(candidates, candidate_count);
    return (0);
}

void    vote(t_candidate *p_candidates, int candidate_count)
{
    while (1)
    {
        char *name = get_string("Vote: ");
        for (int i = 0; i < candidate_count; i++)
        {
            if (!strcmp(p_candidates[i].name, name))
            {
                p_candidates[i].votes++;
                return ;
            }
        }
        printf("Invalid vote.\n");
    }
}

void    print_winner(t_candidate *p_candidates, int candidate_count)
{
    int max_votes = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (p_candidates[i].votes > max_votes)
            max_votes = p_candidates[i].votes;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (p_candidates[i].votes == max_votes)
            printf("%s\n", p_candidates[i].name);
    }
    return ;
}
