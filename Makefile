CC := g++
TO := -o

C_OPTS := -O0 -std=c++11 -pedantic-errors -Wall -Wextra \
          -Wunused -Wunused-function -Wunused-label -Wunused-local-typedefs \
          -Wunused-macros -Wunused-parameter  -Wno-unused-result \
          -Wunused-value  -Wunused-variable -Wunused-const-variable \
          -Wunused-but-set-parameter -Wunused-but-set-variable -Wuseless-cast

L_OPTS := -lstdc++ -lm

# Debug
C_OPTS += -ggdb -DROB_DEBUG

COMPILE := $(CC) -c $(OPTS) $(C_OPTS)

LINK := $(CC) $(OPTS) $(L_OPTS)

##############################################################################
# Rules
##############################################################################
%.o : %.cpp
	@echo "***** Compiling -> $@"
	@$(COMPILE) $(TO) $@ $<

run.o: main.o \
     list_from_edges.o read_edges.o read_tasks.o \
     parent_task_count.o \
     ltf_schedule.o tbls_schedule.o contingency_schedule.o uniform_scale.o
	$(REPORT)
	@echo "***** Linking -> $@"
	@$(LINK) $(TO) $@ $(filter %.o,$^)
	@echo

plot_data.o: plot.o \
           list_from_edges.o read_edges.o read_tasks.o \
           parent_task_count.o \
           ltf_schedule.o tbls_schedule.o contingency_schedule.o uniform_scale.o
	$(REPORT)
	@echo "***** Linking -> $@"
	@$(LINK) $(TO) $@ $(filter %.o,$^)
	@echo

plot.o: plot.cpp task.hpp adj_list.hpp schedule.hpp

main.o: main.cpp task.hpp adj_list.hpp schedule.hpp

contingency_schedule.o: contingency_schedule.cpp schedule.hpp

list_from_edges.o: list_from_edges.cpp adj_list.hpp

ltf_schedule.o: ltf_schedule.cpp task.hpp schedule.hpp

parent_task_count.o: parent_task_count.cpp schedule.hpp

read_edges.o: read_edges.cpp task.hpp

read_tasks.o: read_tasks.cpp task.hpp

tbls_schedule.o: tbls_schedule.cpp schedule.hpp task.hpp

uniform_scale.o: uniform_scale.cpp schedule.hpp

clean:
	rm -rf ./run ./*.o
