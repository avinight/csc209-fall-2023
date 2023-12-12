int num_filters = max(argc - 3, 1);
    int pipes[num_filters][2];

    for (int i = 0; i < num_filters; i++)
    {
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            return 1;
        }
    }

    // loop through filter commands and create child processes.
    for (int i = 0; i < num_filters; i++)
    {
        int child_pid = fork();
        if (child_pid == -1)
        {
            perror("fork");
            return 1;
        }
        else if (child_pid == 0) // child process
        {
            // redirect input from the pipe
            if (i == 0)
            {
                // if first filter
                FILE *input_file = fopen(argv[1], "rb");
                if (input_file == NULL)
                {
                    perror("fopen");
                    exit(1);
                }

                if (dup2(fileno(input_file), fileno(stdin)) == -1)
                {
                    perror("dup2");
                    fclose(input_file);
                    exit(1);
                }

                fclose(input_file);
            }
            else
            {
                // else read from previous filters stdout
                if (dup2(pipes[i - 1][0], fileno(stdin)) == -1)
                {
                    perror("dup2");
                    exit(1);
                }
                close(pipes[i - 1][0]);
            }

            if (i == num_filters - 1)
            {
                close(pipes[i][0]); // close read end
            }

            // redirect output to file
            if (i == num_filters - 1)
            {
                // if last file, redirect to output file
                FILE *output_file = fopen(argv[2], "wb");
                if (output_file == NULL)
                {
                    perror("fopen");
                    exit(1);
                }

                if (dup2(fileno(output_file), fileno(stdout)) == -1)
                {
                    perror("dup2");
                    fclose(output_file);
                    exit(1);
                }

                fclose(output_file);
            }
            else
            {
                // else redirect output to the pipe
                if (dup2(pipes[i][1], fileno(stdout)) == -1)
                {
                    perror("dup2");
                    exit(1);
                }
            }

            close(pipes[i][1]); // close write end

            // execute the filter command
            run_command(argv[i + 3] != 0 ? argv[i + 3] : "copy");
        }
        else // parent process
        {
            close(pipes[i][0]); // close read end
            close(pipes[i][1]); // close write end

            // if (i != num_filters - 1) // if not last filter, wait for child to finish
            // {
            //     wait(NULL);
            // }
        }
    }