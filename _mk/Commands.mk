.PHONY += run re rerun drun dre drerun tidy clear clean fclear fclean tidy leaks clogs

# Define a recursive wildcard function
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# Define all object files from source files
SRCS = $(call rwildcard, $(SRC_DIR)/, *.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Define all the subdirectories that object files will be placed in
OBJ_SUB_DIRS = $(sort $(dir $(OBJS)))


# Project target defined by PROJECT_NAME
$(PROJECT_NAME): $(OBJS)
	@printf "\n$(BLUE)Linking with flags: $(LDFLAGS)\n$(DEFCOL)"
	@printf "${MAGENTA}Linking $(PROJECT_NAME)...\n${DEFCOL}"
	$(CC) -o $(PROJECT_NAME)$(EXT) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)
	@printf "${GREEN}$(PROJECT_NAME) linked\n${DEFCOL}"

# Compile source files
# NOTE: This pattern will compile every module defined on $(OBJS)
# %.o: %.c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(LOG_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_SUB_DIRS)
	@printf "${YELLOW}Compiling $<...\n${DEFCOL}"
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM) -MMD -MP

# Include dependency files, so that they are recompiled if headers change
-include $(OBJS:.o=.d)

# Redo and/or Run the project
re: clean release
rerun: re run
run: release
	@printf "Launching $(PROJECT_NAME)...\n"
	@./$(PROJECT_NAME)$(EXT)
	@printf "Project executed\n"

# Redo and/or Debug the project
dre: clean debug
drerun: dre drun
drun: debug
	@printf "Launching $(PROJECT_NAME) in debug mode...\n"
	@./$(PROJECT_NAME)$(EXT)
	@printf "Project executed\n"

# Clean all .o files
clear: clean
clean:
	@printf "$(MAGENTA)Cleaning object files...\n$(DEFCOL)"
	@rm -rf $(OBJ_DIR)
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
ifeq ($(PLATFORM_OS),WINDOWS)
	@del *.o *.exe /s
else ifeq ($(PLATFORM_OS),LINUX)
	@find -type f -executable | xargs file -i | grep -E 'x-object|x-archive|x-sharedlib|x-executable' | rev | cut -d ':' -f 2- | rev | xargs rm -fv
else ifeq ($(PLATFORM_OS),OSX)
	@find . -type f -perm +ugo+x -delete
	@rm -f *.o
endif
else ifeq ($(PLATFORM),PLATFORM_RPI)
	@find . -type f -executable -delete
	@rm -fv *.o
else ifeq ($(PLATFORM),PLATFORM_WEB)
	@del *.o *.html *.js
endif
	@printf "$(GREEN)Object files cleaned\n$(DEFCOL)"

# Clean all .o files and executable
fclear: fclean
fclean: clean
	@printf "Cleaning executable...\n"
	@rm -f $(PROJECT_NAME)$(EXT)
	@printf "Executable cleaned\n"

# Run the clang-tidy static analysis tool
tidy:
	@printf "Running clang-tidy...\n"
	@clang-tidy $(SRCS) -- $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)
	@printf "clang-tidy finished\n"


# Check for memory leaks
leaks: debug
	@printf "Checking for memory leaks...\n"
	@valgrind --log-file=valgrind-out.txt $(VFLAGS) ./$(PROJECT_NAME)$(EXT)
	@printf "Memory leaks checked\n"
	@printf "Check valgrind-out.txt for details\n"

clogs:
	@rm -f $(LOG_DIR)/*.log
	@printf "Logs deleted\n"