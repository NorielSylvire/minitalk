# Tools
NAME = server
CNAME = client
TNAME = minitalk-test
CC = clang
CFLAGS = -Wall -Wextra -Werror -I $(INC_PATH) $(DBGFLAGS)
COBJFLAGS = $(CFLAGS) -c
DBGFLAGS =
RMFLAGS = -fr

# Paths
TGT_PATH = .
BIN_PATH = $(TGT_PATH)/
OBJ_PATH = $(TGT_PATH)/obj
DBG_PATH = debug
SRC_PATH = src
INC_PATH = $(SRC_PATH)/include
LFT_PATH = $(SRC_PATH)/libft
MSRC_PATH = $(SRC_PATH)/main/server
CLNT_PATH = $(SRC_PATH)/main/client
CMMN_PATH = $(SRC_PATH)/main/common
BSRC_PATH = $(SRC_PATH)/bonus
TSRC_PATH = $(SRC_PATH)/test

# Source and object files
HDRS =
MSRC =
MAIN = $(MSRC_PATH)/main.c
OBJ = $(MSRC:%.c=$(OBJ_PATH)/%.o)
CSRC = $(CLNT_PATH)/client.c
CMAIN = $(CLNT_PATH)/main.c
COBJ = $(CSRC:%.c=$(OBJ_PATH)/%.o)
USRC = $(CMMN_PATH)/ascii_converter.c
UOBJ = $(USRC:%.c=$(OBJ_PATH)/%.o)
BSRC =
BMAIN = $(BSRC_PATH)/main.c
BOBJ = $(BSRC:%.c=$(OBJ_PATH)/%.o)
TSRC = $(TSRC_PATH)/common_tests.c
TMAIN = $(TSRC_PATH)/tmain.c
TOBJ = $(TSRC:%.c=$(OBJ_PATH)/%.o) \
	$(TMAIN:%.c=$(OBJ_PATH)/%.o)

# Config
# Unwanted files to be deleted
UNW = .DS_Store ./*/.DS_Store
# No. of seconds the screen output will be visible for
SECONDS_VISIBLE = 4
# BONUS = 0 if you're going to do bonus: BONUS := 1

# Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: $(CNAME) $(NAME)

$(CNAME): mkdir $(COBJ) $(CMAIN)
	@echo "\n$(GREEN)$(CNAME) objects compiled successfully.$(DEF_COLOR)\n"
	@make -C $(LFT_PATH)
	@cp $(LFT_PATH)/libft.a $(BIN_PATH)/libft
	@echo "\n$(YELLOW)Linking $(CNAME) objects.$(DEF_COLOR)\n"
	@$(CC) $(CFLAGS) $(COBJ) $(CMAIN:%.c=$(OBJ_PATH)/%.o) -L$(BIN_PATH) -lft -o $@
	@echo "$(GREEN)$(CNAME) compiled successfully.$(DEF_COLOR)\n"

$(NAME): mkdir $(OBJ) $(MAIN)
	@echo "\n$(GREEN)$(NAME) objects compiled successfully.$(DEF_COLOR)\n"
	@make -C $(LFT_PATH)
	@cp $(LFT_PATH)/libft.a $(BIN_PATH)/libft
	@echo "\n$(YELLOW)Linking $(NAME) objects.$(DEF_COLOR)\n"
	@$(CC) $(CFLAGS) $(OBJ) $(MAIN:%.c=$(OBJ_PATH)/%.o) -L$(BIN_PATH) -lft -o $@
	@echo "$(GREEN)$(NAME) compiled successfully.$(DEF_COLOR)\n"

debug: DBGFLAGS := -g
debug: all

# bonus: BONUS := 1
# and add -D$(BONUS) to your COBJFLAGS.
# Do this if you'll use the same files for bonus and mandatory.
bonus: all
# Or compile here if you'll use separate bonus and mandatory files.

test: $(TOBJ) $(UOBJ) #all!!!!!!!
	@echo "\n$(GREEN)$(TNAME) objects compiled successfully.$(DEF_COLOR)\n"
	@echo "$(YELLOW)Linking objects.$(DEF_COLOR)\n"
	@$(CC) $(CFLAGS) $(TOBJ) $(UOBJ) -L$(BIN_PATH) -lft -ltest42 -o $(TNAME)
	@echo "$(GREEN)$(TNAME) compiled successfully.$(DEF_COLOR)\n"
	@echo "$(MAGENTA)Running tests.$(DEF_COLOR)\n"
	@./$(BIN_PATH)/$(TNAME)
	@make fclean

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(COBJFLAGS) $^ -o $@

mkdir:
	@mkdir -p $(BIN_PATH)
	@mkdir -p $(OBJ_PATH)
#	@mkdir -p $(OBJ_PATH)/other/path

preclean:
	@echo "\n$(YELLOW)Cleaning project up...$(DEF_COLOR)"

postclean:
	@echo "\n$(GREEN)Done!$(DEF_COLOR)"

clean: preclean clean-body postclean

clean-body:
	@$(RM) $(RMFLAGS) $(OBJ_PATH)

fclean: preclean fclean-body postclean

fclean-body: clean-body
	@$(RM) $(RMFLAGS) $(NAME)

xclean: preclean xclean-body postclean

xclean-body: fclean-body
	@$(RM) $(RMFLAGS) $(UNW)

re: fclean all

bre: fclean bonus

try: re xclean
	norminette

btry: bre xclean
	norminette

ctry: try
	sleep $(SECONDS_VISIBLE); clear

cbtry: btry
	sleep $(SECONDS_VISIBLE); clear

.PHONY: all clean fclean xclean re bonus bre
