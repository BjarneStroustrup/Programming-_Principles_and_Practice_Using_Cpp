#
# This is a common Makefile for code examples from the book
# "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
#

#
# Usage:
#     make        - Build all examples
#     make clean  - Clean all examples
#     make test   - Run the test suite
#

INCLUDES = -I"../GUI" -I"$(FLTK)"
LIBS     = -lstdc++ -lbookgui -lfltk -lfltk_images
CXXFLAGS = $(INCLUDES) -Wall -time -O3 -DNDEBUG
LIBFLAGS = -L"../GUI"
AR       = ar

ifneq ($(strip $(shell gcc -v 2>&1 |grep "cygwin")),)
  CYGWIN = true
endif

ifneq ($(strip $(shell gcc -v 2>&1 |grep "darwin")),)
  MACOSX = true
endif

ifeq ($(CYGWIN),true)
  LIBS := $(LIBS) -lfltk_jpeg -luser32 -lgdi32 -lshell32 -lole32 -luuid -lWs2_32 -lComCtl32
else ifeq ($(MACOSX),true)
  LIBS := $(LIBS) -lfltk_jpeg -framework Carbon -framework ApplicationServices
else
  LIBS := $(LIBS) -lX11 -ljpeg
endif

.SUFFIXES: .cpp .o

# Create a list of source files.
SOURCES  = $(shell ls *.cpp)
# Create a list of object files from the source file lists.
OBJECTS = ${SOURCES:.cpp=.o}     
# Create a list of targets.
TARGETS = ${SOURCES:.cpp=.exe}     

# Build all targets by default
all: 	$(TARGETS)

# Files with extension .no-link.cpp are not intended for linking
%.no-link.exe: %.no-link.o
	@echo Linking skipped for $@
	@echo ================================================================================
	@echo Done building $@
	@echo ================================================================================
	@echo
	@echo

# A rule to build .exe file out of a .o file
%.exe: %.o ../GUI/libbookgui.a
	$(CXX) -o $@ $(LIBFLAGS) $< $(LIBS)
	@echo ================================================================================
	@echo Done building $@
	@echo ================================================================================
	@echo
	@echo

# A rule to build .o file out of a .cpp file
%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# A rule to build the common GUI library
../GUI/libbookgui.a: ../GUI/*.h ../GUI/*.cpp
	@(cd ../GUI; $(MAKE))

# A rule to clean all the intermediates and targets
clean:	
	rm -rf $(TARGETS) $(OBJECTS) *.out *.stackdump

# A rule to run set of tests
test:
	@for file in *.exe; do \
	    name=`basename $$file .exe` ; \
	    name=`basename $$name .crash` ; \
	    if (ls $$name.crash.exe >/dev/null 2>&1) ; then \
	        continue ; \
	    fi ; \
	    echo ======================================== [ $$file ] ; \
	    if (ls $$name.*in >/dev/null 2>&1) ; then \
	        for f in $$name.*in; do \
	            echo ; \
	            echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ { "$$f" } ; \
	            cat "$$f" ; \
	            echo ; \
	            echo ---------------------------------------- ; \
	            ./$$file < "$$f" ; \
	        done ; \
	    else \
	      ./$$file ; \
	    fi \
	done ; \
	echo -n 
