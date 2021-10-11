NAME	= philo_bonus

SORCES	= ft_monitors.c ft_output.c ft_inits.c ft_utils.c philo.c

DIRS	= ./src

INCL	= ./includes

SRC		= $(addprefix $(DIRS)/,$(SORCES))

OBJ		= $(SRC:.c=.o)

BOBJ	= $(BSORC:.c=.o)

HEAD	= $(INCL)/philo.h

CC		= gcc

CFLAG	= -Wall -Wextra -Werror

RM		= rm -f

%.o:	%.c $(HEAD)
	$(CC) $(CFLAG) -c $< -o $@

$(NAME):	$(OBJ) $(HEAD)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)
	@echo $(NAME) is compiled!

all: $(NAME)

clean:
	$(RM) $(OBJ) $(BOBJ)
	@echo Objects files cleaned!

fclean: clean
	$(RM) $(NAME) $(BNAME)
	@echo All cleaned!

re: fclean all

bonus: $(NAME)
