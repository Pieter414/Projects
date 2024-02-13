// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 45;

// Hash table
node *table[N];

// Count
int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // return true if word found in dict, false if dont. Case insensitive
    int index = hash(word);
    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int strlen = 0;
    for (int i = 0; i < LENGTH + 1; i++)
    {
        if (word[i] == '\0')
        {
            return strlen - 1;
        }
        strlen++;
    }
    return strlen - 1;
}

// Loads dictionary into memory, returning true if successful, else false
// ./speller dictionaries/small texts/lalaland.txt
bool load(const char *dictionary)
{
    // TODO
    // 1. Open the dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // 2. Read string from file
    char holder[LENGTH + 1];

    while (fscanf(dict, "%s", holder) != EOF)
    {
        // 3. Create new node and copy the holder to the temp node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(dict);
            return false;
        }

        strcpy(n->word, holder);

        // 4. Hash the word by using hash function
        int index = hash(n->word);

        // 5. Insert node into hash table, so you jut need assign the n

        // 5a. Need to make a functional pointer
        // if the first array is null
        if (table[index] == NULL)
        {
            n->next = NULL;
        }
        // if the array already have something in it
        else
        {
            n->next = table[index];
            // table[index] = n;
        }

        // 5b. The actual insert
        table[index] = n;

        count++;
    }
    // true if successfully load all the data,
    // false if there memory error or some sort after trying to allocate or file couldnt open
    // hash function based on the length of the string as index

    // i really forget to fclose the dict
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *temp;
    node *cursor;

    // 1. check each one of the indexed table
    for (int i = 0; i < N; i++)
    {
        // 2. point the cursor and temp
        cursor = table[i];
        temp = cursor;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}
