# --------------------------------------------------------------------
#	$@ - Nombre del objetivo
#	$^ - Todas las dependencias
#	$< - Primera dependencia
# --------------------------------------------------------------------

EXEC := pacman

DIRSRC := src/
DIROBJ := obj/
DIRHEA := include/

CXX := g++

# Flags de compilación -----------------------------------------------
CXXFLAGS := -I $(DIRHEA) -Wall -I/usr/local/include/cegui-0/CEGUI -I/usr/local/include/cegui-0
CXXFLAGS += `pkg-config --cflags OGRE OGRE-Overlay`
CXXFLAGS += `pkg-config --cflags OIS`
CXXFLAGS += `pkg-config --cflags SDL2_mixer`

# Flags del linker ---------------------------------------------------
LDFLAGS := `pkg-config --libs OGRE OGRE-Overlay`
LDFLAGS += `pkg-config --libs-only-L SDL2_mixer`
LDFLAGS += `pkg-config --libs-only-l SDL2_mixer glu`
LDFLAGS += `pkg-config --libs gl xerces-c`
LDFLAGS += -lIce -lIceUtil
LDFLAGS += -lOIS -lGL -lstdc++ -lboost_system  -lCEGUIBase-0 -lCEGUIOgreRenderer-0

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

all: dirs info $(EXEC)

info:
	@echo '------------------------------------------------------'
	@echo '>>> Using mode $(mode)'
	@echo '    (Please, call "make" with [mode=debug|release])  '
	@echo '------------------------------------------------------'

dirs:
	mkdir -p $(DIROBJ)
# Enlazado -----------------------------------------------------------
$(EXEC): $(OBJS)
	$(CXX) -o $@  $^ $(LDFLAGS) 
	@echo
	@echo 'Compilacion terminada!'

# Compilación --------------------------------------------------------
$(DIROBJ)main.o: $(DIRSRC)main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)
$(DIROBJ)%.o: $(DIRSRC)%.cpp $(DIRHEA)%.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

# Limpieza de temporales ---------------------------------------------
clean:
	rm -f *.log $(EXEC) *~ $(DIROBJ)* $(DIRSRC)*~ $(DIRHEA)*~ 



