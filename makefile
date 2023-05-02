# name of C++ compiler
CXX       = g++
# options to C++ compiler
CXX_FLAGS = -std=c++17 -pedantic-errors -Wall -Wextra -Werror
# flag to linker to make it link with math library
LDLIBS    = -lm
# list of object files
OBJS      = test-driver.o
# name of executable program
EXEC      = test.out

# by convention the default target (the target that is built when writing
# only make on the command line) should be called all and it should
# be the first target in a makefile
all : $(EXEC)

# however, the problem that arises with the previous rule is that make
# will think all is the name of the target file that should be created
# so, we tell make that all is not a file name
.PHONY : all

# this rule says that target $(EXEC) will be built if prerequisite
# files $(OBJS) have changed more recently than $(EXEC)
# text $(EXEC) will be replaced with value test.out
# text $(OBJS) will be substituted with list of prerequisites in line 10
# line 31 says to build $(EXEC) using command $(CXX) with
# options $(CXX_FLAGS) specified on line 6
$(EXEC) : $(OBJS)
	$(CXX) $(CXX_FLAGS) $(OBJS) -o $(EXEC) $(LDLIBS)

# target test-driver.o depends on both test-driver.cpp and test.hpp
# and is created with command $(CXX) given the options $(CXX_FLAGS)
test-driver.o : test-driver.cpp test.hpp
	$(CXX) $(CXX_FLAGS) -c test-driver.cpp -o test-driver.o

# says that clean is not the name of a target file but simply the name for
# a recipe to be executed when an explicit request is made
.PHONY : clean
# clean is a target with no prerequisites;
# typing the command in the shell: make clean
# will only execute the command which is to delete the object files
clean :
	rm -f $(OBJS) $(EXEC)

# says that rebuild is not the name of a target file but simply the name
# for a recipe to be executed when an explicit request is made
.PHONY : rebuild
# rebuild is for starting over by removing cleaning up previous builds
# and starting a new one
rebuild :
	$(MAKE) clean
	$(MAKE)

.PHONY : test
test : $(EXEC)
	./$(EXEC) < 0.txt > 0-output.txt 
	./$(EXEC) < 1.txt > 1-output.txt 
	./$(EXEC) < 2.txt > 2-output.txt 
	./$(EXEC) < 3.txt > 3-output.txt 
	./$(EXEC) < 4.txt > 4-output.txt 
	./$(EXEC) < 5.txt > 5-output.txt 
	./$(EXEC) < 6.txt > 6-output.txt 
	./$(EXEC) < 7.txt > 7-output.txt 
	./$(EXEC) < 8.txt > 8-output.txt 
	./$(EXEC) < 9.txt > 9-output.txt 
	diff -y --strip-trailing-cr --suppress-common-lines 0-o.txt 0-output.txt
	diff -y --strip-trailing-cr --suppress-common-lines 1-o.txt 1-output.txt
	diff -y --strip-trailing-cr --suppress-common-lines 2-o.txt 2-output.txt
	diff -y --strip-trailing-cr --suppress-common-lines 3-o.txt 3-output.txt
	diff -y --strip-trailing-cr --suppress-common-lines 4-o.txt 4-output.txt
	diff -y --strip-trailing-cr --suppress-common-lines 5-o.txt 5-output.txt
	diff -y --strip-trailing-cr --suppress-common-lines 6-o.txt 6-output.txt
	diff -y --strip-trailing-cr --suppress-common-lines 7-o.txt 7-output.txt
	diff -y --strip-trailing-cr --suppress-common-lines 8-o.txt 8-output.txt
	diff -y --strip-trailing-cr --suppress-common-lines 9-o.txt 9-output.txt