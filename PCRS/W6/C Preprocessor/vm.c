#include <stdio.h>

#define PAGE_PRESENT  0
#define PAGE_PROT     1
#define PAGE_RW       2
#define PAGE_USER     3
#define PAGE_DIRTY    4
#define PAGE_ACCESSED 5

#define SET(var, flag)   ((var) |= 1 << (flag))
#define ISSET(var, flag) ((var) & (1 << (flag)))

#define WARN(cond) \
    do { \
        if (cond) fprintf(stderr, "Warning (%s:%d): %s\n", __FILE__, __LINE__, #cond); \
    } while (0)

/*
Step 5: You can do everything that you did with the macro 
        by using a regular C language features instead. 

enum page_flags {
 PAGE_PRESENT,
 PAGE_PROT,
 PAGE_RW,
 PAGE_USER,
 PAGE_DIRTY,
 PAGE_ACCESSED
};

static inline void SET(int *var, int flag) {
    (*var) |= 1 << flag;
}
*/


int main() {
    int page_flag = 0;
    SET(page_flag, PAGE_USER);
    printf("PAGE_USER: %d\n", page_flag);

    page_flag = 0;
    SET(page_flag, PAGE_DIRTY);
    printf("PAGE_DIRTY: %d\n", page_flag);

    // Step 2: add nested macros
    //WARN(ISSET(page_flag, PAGE_USER));

    // Step 3: nest the SET macro inside a printf statement 
    printf("%d\n", SET(page_flag, PAGE_DIRTY));

    // Step 4: nest the SET macro inside another application of the SET macro
    //         what goes wrong now? 
    SET(SET(page_flag, PAGE_USER), PAGE_DIRTY);

    return 0;
}

