#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int diff;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i], name))
        {
            ranks[rank] = i;
            return (true);
        }
    }
    return (false);
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
            preferences[ranks[i]][ranks[j]]++;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pairs[pair_count].diff = preferences[i][j] - preferences[j][i];
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pairs[pair_count].diff = preferences[j][i] - preferences[i][j];
                pair_count++;
            }
        }
    }
    return;
}

static void swap_pairs(pair* a, pair* b)
{
    pair tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
    return ;
}

static int calc_diff(int index)
{
    return (preferences[pairs[index].winner][pairs[index].loser] - preferences[pairs[index].loser][pairs[index].winner]);
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < MAX * (MAX - 1) / 2; i++)
    {
        if (pairs[i].diff)
        {
            printf("pairs[%d].winner = %d\n", i, pairs[i].winner);
            printf("pairs[%d].loser = %d\n", i, pairs[i].loser);
            printf("pairs[%d].diff = %d\n", i, pairs[i].diff);
        }
    }
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            if (calc_diff(j) < calc_diff(j + 1))
                swap_pairs(pairs + j, pairs + j + 1);
        }
    }
    for (int i = 0; i < MAX * (MAX - 1) / 2; i++)
    {
        if (pairs[i].diff)
        {
            printf("pairs[%d].winner = %d\n", i, pairs[i].winner);
            printf("pairs[%d].loser = %d\n", i, pairs[i].loser);
            printf("pairs[%d].diff = %d\n", i, pairs[i].diff);
        }
    }
    return ;
}

static bool check_cycle(int start, int end)
{
    if (start == end)
        return (true);
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i] && check_cycle(start, i))
            return (true);
    }
    return (false);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        //locked[pairs[i].winner][pairs[i].loser] = true;
        if (!check_cycle(pairs[i].winner, pairs[i].loser))
            locked[pairs[i].winner][pairs[i].loser] = true;
    }
    /*
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (locked[i][j] == true)
                printf("%s -> %s ... true\n", candidates[i], candidates[j]);
        }
    }
    */
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int end[MAX] = {};

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
                end[j]++;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (end[i] == 0)
            printf("%s\n", candidates[i]);
    }
    return ;
}
