#include <stdio.h>

int main() {
    char phone[11];
    int num;
    int error = 0;

    scanf("%s", phone);
    while (scanf("%d", &num) != EOF) {
        if (num == -1){
            printf("%s\n", phone);
        } 
    
	    else if (num < -1 || num > 9) {
           error += 1;
	       printf("ERROR\n");
        }

        else {
	       printf("%c\n", phone[num]);
        }
    }
    if (error == 0) {
        return 0;
    } else {
        return 1;
    }
}
