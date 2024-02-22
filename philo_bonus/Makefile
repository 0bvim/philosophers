# program name #
NAME = philo_bonus

# shell #
SHELL := /bin/bash

# misc #
COUNT := -1
SLEEP := sleep 0.2

# colors #
DEFAULT=\033[39m
BLACK=\033[30m
ORANGE=\033[93m
BLUE=\033[94m
WHITE=\033[97m
RESET=\033[0m
RESET_TERM=\r\033[K

# messages #
MANDATORY = $(NAME) compiled
LBONUS = $(NAME)_bonus Program compiled
CLEAN = Objects delete
FCLEAN = Program delete
COMP = Compiling

# debug and normal flags #
DFLAGS = -Wall -Wextra -Werror -g3 # TO DEBBUG
CFLAGS = -Wall -Werror -Wextra -g3 -pedantic -flto -MD -MP # FOR DEPENDENCIES
LFLAGS = -march=native # TO OPTIMIZE FOR SPECIFIC ARCHITECTURE
FFLAGS =  -lpthread -pthread # FLAGS THAT ONLY WORK AT THE END OF LINE (AFTER OBJECTS)

# paths #
SRC = src
INC = includes
OBJ = obj

# includes #
HEADERS = $(addprefix $(INC)/, philo.h)

# files path #


# files mandatory #
CFILES = $(addprefix $(SRC)/, file1.c file2.c file3.c)

VAL = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt
VAL_TXT = valgrind-out.txt

# obj dir #
OBJECT = $(CFILES:%.c=$(OBJ)/%.o)

# define debbug #
ifdef WITH_DEBBUG
	CFLAGS = $(DFLAGS)
endif

# functions #
define create_objects_dir
	mkdir -p $(dir $@)
endef

define compile
	$(CC) -o $(NAME) $(CFLAGS) $(LFLAGS) $(INCLUDES) $(LINCLUDES) $(OBJECT) $(BIN_OBJ) $(FFLAGS)
	$(SLEEP)
	printf "\n$(MAGENTA)$(MANDATORY)\n$(RESET)"
endef

define compile_bonus
	$(CC) -o $(NAME) $(CFLAGS) $(LFLAGS) $(INCLUDES) $(LINCLUDES) $(OBJECT) $(BIN_OBJ) $(FFLAGS)
	$(SLEEP)
	printf "\n$(MAGENTA)$(MANDATORY)\n$(RESET)"
endef

define compile_source
	$(eval COUNT=$(shell expr $(COUNT) + 1))
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<
	printf "$(RESET_TERM)$(RESET)%d%%  $(BLUE)$(COMP) $(notdir $<) -> $(notdir $@) to $(ORANGE)$(NAME) \r$(RESET)" $$(echo $$(($(COUNT) * 100 / $(words $(OBJECT)))))
endef

define clean
	$(RM) -rf $(OBJ)/ && $(RM) -rf $(VAL_TXT)
	$(SLEEP)
	printf "$(RED)$(CLEAN)$(RESET)\n"
endef

define fclean
	$(call eraseBins)
	@$(SLEEP)
	@printf "$(RED)$(FCLEAN)$(RESET)\n"
endef

define debug
	$(call clean)
	$(call fclean)
	$(MAKE) WITH_DEBBUG=TRUE -s
endef

define eraseBins
	$(if $(NAME),@$(RM) $(NAME))
	$(if $(BLIBNAME),@$(RM) $(BLIBNAME))
endef

define help
	echo -e "${BG_DARK_GREEN}${ORANGE}Available targets:${RESET}"
	echo -e "${BG_DARK_GREEN}${ORANGE}all:${RESET}${LIGHT_GRAY}Build philo mandatory${RESET}"
	echo -e "${BG_DARK_GREEN}${ORANGE}re:${RESET}${LIGHT_GRAY}Rebuild the program${RESET}"
	echo -e "${BG_RED}${ORANGE}clean:${RESET}${LIGHT_GRAY}Remove the object files${RESET}"
	echo -e "${BG_RED}${ORANGE}fclean:${RESET}${LIGHT_GRAY}Remove the program and the object files${RESET}"
	echo -e "${BG_BLUE}${ORANGE}debug:${RESET}${LIGHT_GRAY}Build the program with debugging information${RESET}"
endef

# rules #
all: $(NAME)

$(NAME): $(OBJECT) $(BIN_OBJ)
	$(call create_objects_dir)
	$(call compile)

$(OBJ)/%.o: %.c
	$(call create_objects_dir)
	$(call compile_source)

-include $(OBJECT:.o=.d)

clean:
	$(call clean)

fclean: clean
	$(call fclean)

re: fclean all

bonus:
	$(call bonus)

debug:
	$(call debug)

help:
	$(call help)

.PHONY: all bonus clean fclean re debug help Makefile
.DEFAULT_GOAL := all
.SILENT:
