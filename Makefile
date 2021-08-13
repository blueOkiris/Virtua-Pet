## Build Settings

# Main project
OBJNAME :=		vpet.exe
CPPC :=			g++
CPPFLAGS :=		-O2 -Wall -std=c++17
INC :=			-Iinclude/ -ISFML-2.5.1/include
LD :=			g++
LDFLAGS :=		-LSFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lm
SRC :=			$(wildcard src/*.cpp)
HFILES :=		$(wildcard include/*.hpp)
OBJS :=			$(subst src/,obj/,$(subst .cpp,.o,$(SRC)))

.PHONY : all
all : $(OBJNAME)

# SFML library
SFML_URL :=	https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip

## Targets

# Helper targets
obj/%.o : src/%.cpp $(HFILES) SFML-2.5.1
	-mkdir obj
	$(CPPC) -o $@ $(CPPFLAGS) $(INC) -c $<

sfml.zip :
	curl $(SFML_URL) -o sfml.zip

SFML-2.5.1 : sfml.zip
	tar -xf sfml.zip
	-copy-dlls.bat

.PHONY : clean
clean :
	-rm -rf obj/
	-rm -rf SFML-2.5.1
	-rm -rf sfml.zip
	-rm -rf $(OBJNAME)
	-rmdir /q /s obj
	-rmdir /q /s SFML-2.5.1
	-del /q sfml.zip
	-del /q *.dll
	-del /q $(OBJNAME)

# Main Target
$(OBJNAME) : $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)
