CXX = C:\ProgramowanieToolchain\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\g++.exe
CC = C:\ProgramowanieToolchain\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe

USE_STATIC_LIBRARY := 0

CXXFLAGS = -std=gnu++11 -Wall
INCLUDES = \
-IFramework/googletest-master/googletest/ \
-IFramework/googletest-master/googletest/include \
-IFramework/googletest-master/googlemock/ \
-IFramework/googletest-master/googlemock/include \

LDFLAGS = 

LIBDIR = \
-LLib

LIB = \
-lgtest

GTEST_DIR = Framework/googletest-master/googletest/src
GMOCK_DIR = Framework/googletest-master/googlemock/src

TESTSOURCES = \
$(GTEST_DIR)/gtest-all.cc \
$(GMOCK_DIR)/gmock-all.cc \
$(GTEST_DIR)/gtest_main.cc \

SOURCES = \
Source/InitialTest.cc \


NAME = GoogleTest

OUTPUT_DIR = Output\UT
OBJ_DIR = $(OUTPUT_DIR)\Obj

SRC = $(SOURCES) #$(TESTSOURCES)

OBJECTS = \
$(addprefix $(OBJ_DIR)/, $(notdir $(filter %.o, $(SRC:.cpp=.o)))) \
$(addprefix $(OBJ_DIR)/, $(notdir $(filter %.o, $(SRC:.cc=.o))))

vpath %.cc Source $(GTEST_DIR) $(GMOCK_DIR)

all: $(OUTPUT_DIR) $(NAME)
	@echo $(OBJECTS)

$(NAME): $(OBJECTS)
	$(CXX) -o $(OUTPUT_DIR)/$(NAME).exe $(OBJECTS) $(LIBDIR) $(LIB) 

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

$(OBJ_DIR)/%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

$(OUTPUT_DIR):
	mkdir $(subst /, \\, $@)
	mkdir $(subst /, \\, $(OBJ_DIR))

clean:
ifneq ($(wildcard $(OUTPUT_DIR)/.*),)
	rmdir $(subst /, \\, $(OUTPUT_DIR)) /s /q
endif