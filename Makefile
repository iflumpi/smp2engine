PROJECT_NAME := SMP2-Engine

# compiler
ifdef WINDOWS
CC := x86_64-w64-mingw32-g++
else
CC := g++
endif

# build folder
BUILD_DIR := build

# source code of core
SRC_CORE := src/Core/Simulator.cpp src/Core/EventManager.cpp src/Core/Logger.cpp \
		    src/Core/Common.cpp src/Core/Publication.cpp src/Core/Scheduler.cpp src/Core/TimeKeeper.cpp \
		    src/Core/GenericComponent.cpp src/Core/PublishOperation.cpp src/Core/Request.cpp src/Core/TypeRegistry.cpp

# source code and binaries of smp2 interpreter
SRC_INTERPRETER := src/Interpreter/Interpreter.cpp src/Interpreter/main.cpp src/Interpreter/Parser.cpp
OBJ_INTERPRETER := $(BUILD_DIR)/main.out

# source code and binaries of smp2 models
SRC_EXAMPLE_MODEL := src/Models/Example/Example.cpp src/Models/Example/Assembly.cpp
OBJ_EXAMPLE_MODEL := $(BUILD_DIR)/libExample.so
SRC_ADCS_MODEL := src/Models/Adcs/Gyroscope.cpp src/Models/Adcs/ReactionWheel.cpp src/Models/Adcs/StarTracker.cpp \
				  src/Models/Adcs/AdcsController.cpp src/Models/Adcs/Model.cpp src/Models/Adcs/Assembly.cpp \
				  src/Models/Adcs/Pid/GenericPid.cpp src/Models/Adcs/Pid/QuaternionFeedbackPd.cpp
OBJ_ADCS_MODEL := $(BUILD_DIR)/libAdcs.so

# source code of smp2 controller
SRC_CONTROLLER := src/Controller/Controller.cpp

# source code, header and binaries of smp2 wrapper
SRC_WRAPPER := src/Interpreter/extern.cpp src/Interpreter/Parser.cpp
HEADER_WRAPPER := src/Interpreter/extern.h
OBJ_WRAPPER := $(BUILD_DIR)/extern.so

# flags
COMMON_FLAGS := -std=c++11 -g
ifdef WINDOWS
COMMON_FLAGS += -DWINDOWS
endif
SHARED_FLAGS = -shared -fPIC
INTERPRETER_FLAGS := $(COMMON_FLAGS) -ldl -lpthread
MODELS_FLAGS := $(COMMON_FLAGS) $(SHARED_FLAGS)
WRAPPER_FLAGS := $(INTERPRETER_FLAGS) $(SHARED_FLAGS)
INCLUDE_FLAGS = -I src

all: $(OBJ_INTERPRETER) $(OBJ_EXAMPLE_MODEL) $(OBJ_ADCS_MODEL) $(OBJ_WRAPPER)

interpreter: $(OBJ_INTERPRETER)
	
$(OBJ_INTERPRETER): $(SRC_INTERPRETER) $(SRC_CONTROLLER) $(SRC_CORE)
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_CORE) $(SRC_CONTROLLER) $(SRC_INTERPRETER) -o $(OBJ_INTERPRETER) $(INCLUDE_FLAGS) $(INTERPRETER_FLAGS)
	
models: $(SRC_EXAMPLE_MODEL) $(OBJ_ADCS_MODEL)

$(OBJ_EXAMPLE_MODEL): $(SRC_EXAMPLE_MODEL)
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_EXAMPLE_MODEL) -o $(OBJ_EXAMPLE_MODEL) $(INCLUDE_FLAGS) $(MODELS_FLAGS)
	
$(OBJ_ADCS_MODEL): $(SRC_ADCS_MODEL)
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_ADCS_MODEL) -o $(OBJ_ADCS_MODEL) $(INCLUDE_FLAGS) $(MODELS_FLAGS)
	
wrapper: $(OBJ_WRAPPER)

$(OBJ_WRAPPER): $(SRC_CORE) $(SRC_CONTROLLER) $(SRC_WRAPPER) $(HEADER_WRAPPER)
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC_CORE) $(SRC_CONTROLLER) $(SRC_WRAPPER) -o $(OBJ_WRAPPER) $(INCLUDE_FLAGS) $(WRAPPER_FLAGS)
	
clean: $(BUILD_DIR)
	rm -Rf $(BUILD_DIR)
