#include <stdio.h>
#include <stdlib.h>


// TODO: Implement a helper named check_permissions that matches the prototype below.
int check_permissions(char *a1, char *a2){
    
    char c = '-';

    for (int i = 0; i < 9; i++) {
        if (a1[i] == c) {
            continue;
        }   
        else if (a1[i] != a2[i]) {
            return 1;
        }
    }
    return 0;
};


int main(int argc, char** argv) {
    if (!(argc == 2 || argc == 3)) {
        fprintf(stderr, "USAGE: count_large size [permissions]\n");
        return 1;
    }
    int size = strtol(argv[1], NULL, 10);
    char *permissions = "";
    if (argc == 3){
        permissions = argv[2];
    }
    char perms_to_compare[10];
    int size_to_compare;
    int count = 0;
    char header[6];
    int filesize;
    scanf("%s %d", header, &filesize);
    char *dir = "d";
    while ((scanf("%10s %*d %*s %*s %d %*s %*d %*s %*s", perms_to_compare, &size_to_compare) != EOF)) {
        if (argc == 3 && (perms_to_compare[0] != *dir)){
            if (size_to_compare > size && check_permissions(permissions, &perms_to_compare[1]) == 0){
                count += 1;
                //printf("%d\n", size_to_compare);
                //printf("%s\n", perms_to_compare);
            }
        }
        else if (argc == 2){
            if (size_to_compare > size){
                count += 1;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}
