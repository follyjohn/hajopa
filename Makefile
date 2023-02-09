########################################################################
#######################  HAJOPA Makefile  ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++17 -lstdc++fs
LDFLAGS = -lpthread -pthread

# Makefile settings - Can be customized.
APPNAME = hajopa
EXT = .cpp
SRCDIR = src
OBJDIR = dist

############## Do not change anything from here downwards! #############
SRC = src/main.cpp src/Message.cpp src/HMessage.cpp src/Channel.cpp src/Issuer.cpp src/Subscriber.cpp src/MessageBus.cpp src/Worker.cpp src/Broker.cpp
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)
# Header files to be included in the executable
INCLUDES = -I include/ -I /usr/local/include

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)


# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<




################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)

# Clean all files with the extension .txt
.PHONY: cleantxt
cleantxt:
	find . -name "*.txt" -type f -delete

#---------------------------------
# IMPLICITE TARGETS RULLES
#---------------------------------

.cc.o:; ${CCC} ${CCFLAGS} $*.cc
