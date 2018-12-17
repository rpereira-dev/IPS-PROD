# nom du binaire compilé
NAME   = main
TARGET = $(BINDIR)/$(NAME)
ALGO               = 0
ALGO_NUM_THREADS   = 4

# le style à utiliser pour formatter le code source
ASTYLE_STYLE = google

# les différents dossiers du dépot
SRCDIR	= src
INCDIR	= includes
BINDIR	= bin
OBJDIR	= obj
TESTDIR	= tests
DOCDIR	= docs

# configuration de compilation
CC	= g++
INC	= -I $(INCDIR)
CFLAGS	= -std=c++11 -Wall -Wextra -Werror -DALGO=$(ALGO)
LDFLAGS = -larmadillo

# si algo 7, alors il faut ajouter pthread
ifeq ($(ALGO),7)
CFLAGS  += -DALGO_NUM_THREADS=$(ALGO_NUM_THREADS)
LDFLAGS += -pthread
endif

# recuperes les includes
INCLUDES = $(shell find $(INCDIR) -name '*.h' -o name '*.hpp' | tr '\n' ' ')

# recuperes les fichiers sources et les fichiers objets à générer
SRC_FILES := $(shell find $(SRCDIR) -name '*.cpp' -o -name '*.c' | sed s/$(SRCDIR)/$(OBJDIR)/g)
OBJECTS := $(SRC_FILES:.c=.o)
OBJECTS := $(OBJECTS:.cpp=.o)

all: $(TARGET)

$(DOCDIR):
	make -C $(DOCDIR)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@-mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@-mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(TESTDIR): $(OBJECTS)
	@SRC_OBJECTS='$(addprefix ../, $(filter-out $(OBJDIR)/main.o, $(OBJECTS)))' make -C $(TESTDIR)

astyle:
	astyle --style=$(ASTYLE_STYLE) $(shell find $(SRCDIR) $(INCDIR) $(TESTDIR) -name '*.cpp' -o -name '*.hpp' -o -name '*.c' -o -name '*.h') -n

clean:
	rm -rf $(OBJECTS)
	make -C $(DOCDIR) clean
	make -C $(TESTDIR) clean

fclean: clean
	rm -rf $(TARGET)
	rm -rf $(OBJDIR)
	make -C $(DOCDIR) fclean
	make -C $(TESTDIR) fclean

re: fclean all

# couleurs
bold=$(shell (tput bold))
normal=$(shell (tput sgr0))

help:
	@echo '$(bold)Règles du Makefile$(normal)'
	@echo "\t$(bold)$(TARGET)$(normal) \tCompile le programme dans $(TARGET)"
	@echo "\t$(bold)clean$(normal) \t\tSupprime les fichiers objets (.cpp compilés en .o)"
	@echo "\t$(bold)fclean$(normal) \t\t'clean' puis supprime le programme"
	@echo "\t$(bold)$(DOCDIR)$(normal) \t\tGénère la documentation dans le dossier $(DOCDIR)"
	@echo "\t$(bold)help$(normal) \t\tAffiche ce message d'aide"
	@echo "\t$(bold)$(TESTDIR)$(normal) \t\tLance les tests unitaires"
	@echo "\t$(bold)astyle$(normal) \t\tFormatte, indente et beautifie le code source"


.PHONY: all clean docs tests astyle
