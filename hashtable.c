# include "hashtable.h" 

# define PR_ONE 54059
# define PR_TWO 76963 
# define PR_THREE 86969 
# define FIRST 37
# define NUM_ELE 10 
# define MEM_SIZE 1000

int index_list[100];
int count = 0;

unsigned long
hash_function (char *word) {
    unsigned num = FIRST;
    while (*word) {
        num = (num * PR_ONE) ^ (word[0] * PR_TWO);
        word++;
    }
    num = (num % PR_THREE) % NUM_ELE;
    return num;
}

elem *create_ele (elem **table, char *alias, char *command) {
    elem *temp = (elem *) malloc(sizeof(elem));
    if (!temp) {
        fprintf(stderr, "create_ele: temp malloc error\n");
        exit(EXIT_FAILURE);
    }
    temp->alias = (char *) malloc(MEM_SIZE);
    if (!alias) {
        fprintf(stderr, "create_ele: alias malloc error\n");
        exit(EXIT_FAILURE);
    }
    temp->command = (char *) malloc(MEM_SIZE);
    if (!command) {
        fprintf(stderr, "create_ele: command malloc error\n");
        exit(EXIT_FAILURE);
    }
    strcpy(temp->alias, alias);
    strcpy(temp->command, command);
    unsigned long index = hash_function(alias);
    while (table[index] != NULL) {
        index++;
    }
    temp->index = index;
    index_list[count++] = index;
    return temp;
}

void insert_ele (elem **table, char *alias, char *command) {
    elem *temp = create_ele(table, alias, command);
    table[temp->index] = temp;
}

elem *get_ele (elem **table, char *alias) {    
    unsigned long address = hash_function(alias);
    address %= NUM_ELE;
    while (1) {
        if (strcmp(table[address]->alias, alias) == 0) {
            return table[address];
        }
        address++;
    }
}

void free_table (elem **table) {
    extern int alias_indexes[10]; 
    extern int num_aliases;
    for (int i = 0; i < num_aliases; ++i) {
        elem *temp = get_ele(table, table[alias_indexes[i]]->alias);
        // printf("FREEEING %s\n", temp->alias);
        free(temp->alias);
        free(temp->command);
        free(temp);
    }
}

