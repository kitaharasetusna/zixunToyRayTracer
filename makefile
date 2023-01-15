#define linktartget
linkTarget = toolRayTracer

#define linked library
LIBS = -lSDL2

#define -options(flags)
CFLAGS = -std=c++17 -Ofast


#define the object files 
# objects =  main.o \
# 			 app.o \
# 				...   too redundent
# need changings every time we make changes on cpp files(add)
objects = main.o \
		  app.o \
		  $(patsubst %.cpp, %.o, $(wildcard ./myRayTracer/*.cpp)) \
		  $(patsubst %.cpp, %.o, $(wildcard ./myRayTracer/myPrimatives/*.cpp)) \
		  $(patsubst %.cpp, %.o, $(wildcard ./myRayTracer/myLights/*.cpp)) \
		  $(patsubst %.cpp, %.o, $(wildcard ./myRayTracer/mymyMaterials/*.cpp)) 

# define rebuildables: easier for clean and rebuild
rebuildables = $(objects) $(linkTarget)

#rule No.1.
$(linkTarget):$(objects)
	g++ -g -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)

#rule NO.2.
%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)

#rebuild-clean
.PHONEY:
clean:
	rm $(rebuildables)