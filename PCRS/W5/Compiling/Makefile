OBJFILES = compare_sorts.o sorts.o

%.o: %.c sorts.h
	gcc -c $< -o $@

compare_sorts: $(OBJFILES)
	echo making this target
	gcc $(OBJFILES) -o compare_sorts

.PHONY: clean
clean:
	rm compare_sorts $(OBJFILES)
