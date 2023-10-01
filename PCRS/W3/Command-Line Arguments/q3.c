/* Returns the sum of two integers in the string input_line.

   input_line is a string containing two integers separated by one
   or more spaces.
   
   Assume that the string will not be more than 20 characters 
   long and that it contains two integers separated only by whitespace. 
   There may also be spaces before the first integer 
   and/or after the last, but there won't be any other characters 
   in the string.
   
   For example, get_sum("   123  5  ") should return the integer 128, 
   and get_sum("-14 30") should return the integer 16.
   
   Hint: use strtol().
*/
int get_sum(const char *input_line) {
    int s1, s2;
    char *p;
    s1 = strtol(input_line, &p, 10);
    s2 = strtol(p, NULL, 10);
