

int main() {
    // set up the second argument to office_hours
    // (this is done for you and you do not need to set any other fields)
    struct timeval window;
    window.interval = 5 * 60;
    // set up first argument to office_hours
    pd_set read_pds;
    PD_ZERO(&read_pds);
    PD_SET(MICHELLE, &read_pds);
    PD_SET(JEN, &read_pds);

    // call office_hours (use window as the second parameter)
    if (office_hours(&read_pds, window) == -1) {
        perror("office_hours");
        exit(1);
    }

    // print the appropriate message(s)
    if (PD_ISSET(MICHELLE, &read_pds)) {
        printf("Michelle has office hours.\n");
    }
    if (PD_ISSET(JEN, &read_pds)) {
        printf("Jen has office hours.\n");
    }
}