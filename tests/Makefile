# couleurs
bold=$(shell (tput bold))
normal=$(shell (tput sgr0))

# différents dossier du dépot
BINDIR = bin
CPPDIR = cpp
OBJDIR = obj
SRCDIR = src

# nom du binaire de test compilé
NAME   = test
TARGET = $(BINDIR)/$(NAME)

# configuration de compilation
CC	= g++
INC	= -I ../includes
CFLAGS	= -std=c++11 -Wall -Wextra -Werror
LDFLAGS = -pthread

# les fichiers .o à générer pour les tests
CXXMAIN = $(CPPDIR)/main.cpp
OBJECTS = $(shell find $(SRCDIR) -name '*.h' | sed 's/\.h/\.o/g' | sed 's/$(SRCDIR)\//$(OBJDIR)\//g') $(OBJDIR)/main.o
CPPS = $(shell echo $(OBJECTS) | sed 's/\.o/\.cpp/g' | sed 's/$(OBJDIR)\//$(CPPDIR)\//g') 

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $(TARGET))
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC_OBJECTS) $(OBJECTS) -o $(TARGET)
	@echo "Les tests ont été compilé."
	@echo "Veuillez lancer $(bold)tests/$(TARGET)$(normal)"

$(OBJECTS): $(CPPS)

$(CXXMAIN):
	cxxtestgen --root --error-printer -o $(CXXMAIN) 

$(CPPDIR)/%.cpp: $(SRCDIR)/%.h
	@mkdir -p $(dir $@)
	cxxtestgen --part --error-printer -o $@ $< 

$(OBJDIR)/%.o: $(CPPDIR)/%.cpp
	@-mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(CPPDIR)
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(BINDIR)

.PHONY: $(TARGET)
