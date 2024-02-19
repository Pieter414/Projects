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
} pair;

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
bool cycle(int winner, int loser);
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
    // TODO
    // 1. Check if the name given in the candidates list
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // 2. assign an rank-th of the ranks array, the index of the candidates + return true
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // 3. Update the preferences between i and j, make the loop that pair between the ranking
    for (int i = 0; i < candidate_count; i++)
    {
        int prefer_choice = ranks[i];
        // 4. Loop in the way that compare one item to the
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[prefer_choice][ranks[j]]++;
            // printf("the-%i item has been prefered than the-%i", prefer_choice, ranks[j]); -> check preference
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // 5. Loop the preferences and comparing them
    int index = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // 6. hold the data of the data 1 and 2, and comparing them
            int prefer_i = preferences[i][j];
            int prefer_j = preferences[j][i];
            // printf("%s: %i\n%s: %i\n", candidates[i], prefer_i, candidates[j], prefer_j); // -> to check comparing who to who

            // 7. assign the winner and loser when comparing pairs, if tie continue
            if (prefer_i > prefer_j)
            {
                pairs[index].winner = i;
                pairs[index].loser = j;
                index++;
                // printf("winner: %s\nloser: %s\n", candidates[pairs[index].winner], candidates[pairs[index].loser]);
                pair_count++;
            }
            else if (prefer_j > prefer_i)
            {
                pairs[index].winner = j;
                pairs[index].loser = i;
                index++;
                // printf("winner: %s\nloser: %s\n", candidates[pairs[index].winner], candidates[pairs[index].loser]);
                pair_count++;
            }
            // printf("%i\n", pair_count); //-> check the pair count
        }
    }

    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("rank %ith\nwinner: %s\nloser: %s\n\n", i, candidates[pairs[i].winner], candidates[pairs[i].loser]);
    // }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // 8. Loop through all the pairs
    int arr[pair_count], prefer_winner, prefer_loser;

    for (int i = 0; i < pair_count; i++)
    {
        // 9. Get hold the preferences between winner and loser, hold the arr[i]
        arr[i] = preferences[pairs[i].winner][pairs[i].loser];
        // prefer_loser = preferences[pairs[i].loser][pairs[i].winner]; -> unused code
        // differ[i] = prefer_winner - prefer_loser; -> unused code
    }

    // 10. sort the pairs by decreasing order of strength, the bigger differ is the highest
    pair hold;

    for (int j = 0; j < pair_count - 1; j++)
    {
        int id = j;
        // 10a. check if the pairs winner higher than the first, i + 2 to compare with the next pairs winner
        for (int k = j + 1; k < pair_count; k++)
        {
            // 10b. if the pairs winner count is lower than the next, swap them
            if (arr[k] >= arr[j])
            {
                id = k;
            }
        }
        if (id != j)
        {
            hold = pairs[j];
            pairs[j] = pairs[id];
            pairs[id] = hold;
        }
    }

    // just for checking
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("rank %ith\nwinner: %s(%i)\nloser: %s(%i)\n\n", i, candidates[pairs[i].winner],
    //     preferences[pairs[i].winner][pairs[i].loser], candidates[pairs[i].loser], preferences[pairs[i].loser][pairs[i].winner]);
    // }
    // return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    bool chained;
    int hold;
    // 11. Loop all the pairs and check to make lock pair
    for (int i = 0; i < pair_count; i++)
    {
        // 12. Go to function to detect if the pairs going to cycled, false if not, true if going cycled
        chained = cycle(pairs[i].winner, pairs[i].loser);

        // 13. If the pairs not cycled, lock the pair
        if (!chained)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        // printf("locked[%s][%s] = %d\n", candidates[pairs[i].winner], candidates[pairs[i].loser],
        // locked[pairs[i].winner][pairs[i].loser]);// -> for checking
    }
    return;
}

bool cycle(int winner, int loser)
{
    // 12a. If winner and loser is the same, just quit (base case)
    if (winner == loser)
    {
        return false;
    }

    else
    {
        for (int i = 0; i < candidate_count; i++)
        {
            bool result = false;
            // 12b. Check if there a locked that loser is a winner in previous locked pairs
            if (locked[loser][i])
            {
                // 12c. Check if the loser is the winner that kept from the first recursion, if false they going to recursion
                if (!locked[loser][winner])
                {
                    result = cycle(winner, i);
                }

                // 12d. If true the pairs become cycle so return true so they doesn't lock
                else
                {
                    return true;
                }
            }

            // 12e. To return result, when result is true or all branced already checked
            if (result || i == candidate_count - 1)
            // Only return result if all branches checked or the last checked branch showed circularity
            {
                return result;
            }
        }
    }

    // 12f. If they loop and found nothing wrong, return false
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    string winner = "";
    bool check;

    // 14. Loop all the locked pair
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // 15. If the j winner over i, make the i cannot be the winner by making check is true
            if (locked[j][i])
            {
                check = true;
            }
            // printf("locked[%s][%s] = %d -> check = %d\n", candidates[j], candidates[i], locked[j][i], check);// -> for checking
        }

        // 16. If i isnt losing to any the pairs, make i the winner
        if (!check)
        {
            winner = candidates[i];
        }
        check = false;
    }
    printf("%s\n", winner);
    return;
}
