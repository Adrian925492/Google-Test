CXX = C:\ProgramowanieToolchain\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\g++.exe
CC = C:\ProgramowanieToolchain\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe

CXXFLAGS = -std=gnu++11 -Wall
INCLUDES = \
-IFramework/googletest-master/googletest/ \
-IFramework/googletest-master/googletest/include \
-IFramework/googletest-master/googlemock/ \
-IFramework/googletest-master/googlemock/include \

LDFLAGS = 

GTEST_DIR = Framework/googletest-master/googletest/src
GMOCK_DIR = Framework/googletest-master/googlemock/src

TESTSOURCES = \
$(GTEST_DIR)/gtest-all.cc \
$(GMOCK_DIR)/gmock-all.cc \
$(GTEST_DIR)/gtest_main.cc \

SOURCES = \
Source/List/SimpleListTest.cc \
Source/List/ForwardListTest.cc \
Source/List/ListTest.cc \
Source/Stack/StackTest.cc \
Source/Queue/SingleSideQueueTest.cc \
Source/Queue/DoubleSideQueueTest.cc \
Source/BoubleSorting/BoubleSortingTest.cc \
Source/CountingSort/CountingSortTest.cc \
Source/FastSort/FastSortTest.cc \
Source/PositioningSort/PositioningSortTest.cc \
Source/SortByChoose/SortByChooseTest.cc \
Source/SortByInsert/SortByInsertTest.cc \
Source/SortByMerge/SortByMergeTest.cc \
Source/LineSearch/LineSearchTest.cc \
Source/BinarySearch/BinarySearchTest.cc \
Source/TetrarySearch/TetrarySearchTest.cc \
Source/InterpolativeSearch/InterpolativeSearchTest.cc \
Source/JumpingSearch/JumpingSearchTest.cc \
Source/ExpotentialSearch/ExpotentialSearchTest.cc \
Source/SublistSearch/SublistSearchTest.cc \
Source/AnagramCheck/AnagramCheckTest.cc \
Source/PalindromeCheck/PalindromeCheckTest.cc \
Source/DecimalBinaryConversion/DecimalBinaryConversionTest.cc \
Source/SearchingPattern/SearchingPatternTest.cc \
Source/BST/BSTTest.cc \
Source/AVL/AVLTest.cc \
Source/BinaryHeap/BinaryHeapTest.cc \
Source/HashTable/HashTableTest.cc \

NAME = DataStructuresAndAlgorithms_UT

OUTPUT_DIR = Output\UT
OBJ_DIR = $(OUTPUT_DIR)\Obj

SRC = $(SOURCES) $(TESTSOURCES)

OBJECTS = \
$(addprefix $(OBJ_DIR)/, $(notdir $(filter %.o, $(SRC:.cpp=.o)))) \
$(addprefix $(OBJ_DIR)/, $(notdir $(filter %.o, $(SRC:.cc=.o))))

vpath %.cc Source/List Source/Stack Source/Queue  Source/BoubleSorting \
Source/CountingSort Source/FastSort Source/PositioningSort Source/SortByChoose \
Source/SortByInsert Source/SortByMerge Source/LineSearch Source/BinarySearch \
Source/TetrarySearch Source/InterpolativeSearch Source/JumpingSearch \
Source/ExpotentialSearch Source/SublistSearch Source/AnagramCheck Source/PalindromeCheck \
Source/DecimalBinaryConversion Source/SearchingPattern Source/BST Source/AVL Source/BinaryHeap Source/HashTable\
Source $(GTEST_DIR) $(GMOCK_DIR)

all: $(OUTPUT_DIR) $(NAME)
	@echo $(OBJECTS)

$(NAME): $(OBJECTS)
	$(CXX) -o $(OUTPUT_DIR)/$(NAME).exe $(OBJECTS)

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