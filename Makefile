G++ = g++ -g -std=c++17 -Wvla -Wall --pedantic
VALGRIND = valgrind --tool=memcheck --leak-check=full --track-origins=yes
Objects = Objects/Trigger.cpp Objects/GameObject.cpp Objects/Item.cpp Objects/Creature.cpp Objects/Container.cpp Objects/Room.cpp 
GamePlay = GamePlay/Attack.cpp GamePlay/Map.cpp 
Utility = Utility/UtilityFunctions.cpp
SRCS = main.cpp $(Objects) $(GamePlay) $(Utility)  
OBJS = $(SRCS:%.cpp=%.o)

EXEC = proj1

all: compile runSample
memory: compile runValgrind

.c.o:
	$(G++) -c $(SRCS)

compile: $(OBJS)
	$(G++) -o $(EXEC) $(OBJS)

compile_full: $(SRCS)
	$(G++) -o $(EXEC) $(SRCS)

runSample: $(EXEC) sample.txt.xml
	./$(EXEC) sample.txt.xml

runValgrind: $(EXEC) sample.txt.xml
	$(VALGRIND) ./$(EXEC) sample.txt.xml

clean:
	rm -rf $(EXEC)
	rm -rf $(OBJS)

