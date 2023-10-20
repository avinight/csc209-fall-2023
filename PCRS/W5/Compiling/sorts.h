typedef void (*SortFunc_t)(int *, int);

void bubble_sort(int *, int);
void selection_sort(int *, int);
void insertion_sort(int *, int);

typedef struct {
    char *name;
    SortFunc_t sort_func;
} sort_info;

const int NUM_SORTS = 3;
sort_info SORTS[] = {
    {.name = "bubble", .sort_func = bubble_sort},
    {.name = "selection", .sort_func = selection_sort},
    {.name = "insertion", .sort_func = insertion_sort}
};


