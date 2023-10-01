int main() {

    int i = 81;
    int *pt = &i;
    int **pt_ptr = &pt;

    int *r= *pt_ptr;
    int k = *r;
   
    // We don't actually need the intermediate value r. 
    // We can dereference pt_ptr twice like this.
    int k1 = **pt_ptr;
  
    // We can even have triple pointers.
    int ***pt_ptr_ptr = &pt_ptr;
    int k2 = ***pt_ptr_ptr;
    return 0;
}
