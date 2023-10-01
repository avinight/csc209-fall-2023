SHELL = /bin/bash
FLAGS = -Wall -Werror -std=c99
.PHONY: test_part1 test_part2 clean

count_large: count_large.o 
	gcc ${FLAGS} -o $@ $^

%.o: %.c 
	gcc ${FLAGS} -c $<

test_part1: count_large
	# Given testcase
	@test_cl_output1=`./count_large 1000 rwx------ < handout.test`; \
	if [ ! -z $$test_cl_output1 ] && [ $$test_cl_output1 -eq 2 ]; then \
		echo passed tc1; \
	else \
		echo failed tc1; \
	fi
	# target specific + greater
	@test_cl_output2=`./count_large 1000 rwx--xr-x < handout.test`; \
	if [ ! -z $$test_cl_output2 ] && [ $$test_cl_output2 -eq 1 ]; then \
		echo passed tc2; \
	else \
		echo failed tc2; \
	fi 
	# if element is equal, we do not count it
	@test_cl_output3=`./count_large 88 < handout.test`; \
	if [ ! -z $$test_cl_output3 ] && [ $$test_cl_output3 -eq 3 ]; then \
		echo passed tc3; \
	else \
		echo failed tc3; \
	fi 
	# target multiple specific + discard folder
	@test_cl_output4=`./count_large 80 ------r-- < handout.test`; \
	if [ ! -z $$test_cl_output4 ] && [ $$test_cl_output4 -eq 2 ]; then \
		echo passed tc4; \
	else \
		echo failed tc4; \
	fi 
	# target specific and lower
	@test_cl_output5=`./count_large 1 rwxrwxrwx < handout.test`; \
	if [ ! -z $$test_cl_output5 ] && [ $$test_cl_output5 -eq 0 ]; then \
		echo passed tc5; \
	else \
		echo failed tc5; \
	fi 

validate_sin: validate_sin.o sin_helpers.o
	gcc ${FLAGS} -o $@ $^

test_part2: validate_sin
	# given test case
	@test_vs_output1=`./validate_sin 810620716`; \
	if [ "$$test_vs_output1" == "Valid SIN" ]; then \
		echo passed tc1; \
	else \
		echo failed tc1; \
	fi
	# test invalid + doesn't start with 0
	@test_vs_output2=`./validate_sin 123456789`; \
	if [ "$$test_vs_output2" == "Invalid SIN" ]; then \
		echo passed tc2; \
	else \
		echo failed tc2; \
	fi
	# test invalid starting with 0
	@test_vs_output3=`./validate_sin 010620716`; \
	if [ "$$test_vs_output3" == "Invalid SIN" ]; then \
		echo passed tc3; \
	else \
		echo failed tc3; \
	fi
	# test another valid test case
	@test_vs_output4=`./validate_sin 667545396`; \
	if [ "$$test_vs_output4" == "Valid SIN" ]; then \
		echo passed tc4; \
	else \
		echo failed tc4; \
	fi
	# test sin number that starts with 0, but %10 is 0.
	@test_vs_output5=`./validate_sin 000000000`; \
	if [ "$$test_vs_output5" == "Invalid SIN" ]; then \
		echo passed tc5; \
	else \
		echo failed tc5; \
	fi

clean:
	rm -f *.o validate_sin count_large
