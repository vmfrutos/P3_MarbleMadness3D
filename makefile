EXEC := marbledMadness

DIRSRC := src/
DIROBJ := obj/
DIRHEA := include/

CXX := g++

# Flags de compilación -----------------------------------------------
CXXFLAGS := -I $(DIRHEA) -Wall 
CXXFLAGS += `pkg-config --cflags OGRE`
CXXFLAGS += `pkg-config	--cflags OgreBullet` 
CXXFLAGS += `pkg-config --cflags bullet`

# Flags del linker ---------------------------------------------------
LDFLAGS += `pkg-config --libs-only-L OgreBullet`
LDFLAGS += `pkg-config --libs-only-L bullet`

LDLIBS := `pkg-config --libs-only-l OGRE`
LDLIBS += `pkg-config --libs-only-l OgreBullet`
LDLIBS += `pkg-config --libs-only-l bullet`
LDLIBS += -lOIS
LDLIBS += -lGL
LDLIBS += -lstdc++
LDLIBS += -lConvexDecomposition

# Modo de compilación (-mode=release -mode=debug) --------------------
ifeq ($(mode), release) 
	CXXFLAGS += -O2 -D_RELEASE
else 
	CXXFLAGS += -g -D_DEBUG
	mode := debug
endif

# Obtención automática de la lista de objetos a compilar -------------
OBJS := $(subst $(DIRSRC), $(DIROBJ), \
	$(patsubst %.cpp, %.o, $(wildcard $(DIRSRC)*.cpp)))

.PHONY: all clean

all: info $(EXEC)

info:
	@echo '------------------------------------------------------'
	@echo '>>> Using mode $(mode)'
	@echo '    (Please, call "make" with [mode=debug|release])  '
	@echo '------------------------------------------------------'

# Enlazado -----------------------------------------------------------
$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Compilación --------------------------------------------------------
$(DIROBJ)%.o: $(DIRSRC)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDLIBS)

# Limpieza de temporales ---------------------------------------------
clean:
	rm -f *.log $(EXEC) *~ $(DIROBJ)* $(DIRSRC)*~ $(DIRHEA)*~ 
