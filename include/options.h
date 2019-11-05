#define ENTER 10
#define UP 'A'
#define DOWN 'B'
#define ESC 33
#define LBRACK 91
#define QUIT 'q'

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define IS_QUIT(c) (c == QUIT)
#define IS_DIRECTION(c) (c == UP || c == DOWN)
#define IS_ENTER(c) (c == ENTER)

#define ARG_OFFSET 1 

typedef char input;
typedef char direction;

typedef struct Option{
    char *name;
}Option;

typedef struct Options {
    int size;
    Option* cur_option;
    Option* options;
}Options;

Options init_options_from_args(int, char**);
input get_input();
int getch();
void display();
void conclude_option(Option *);
void move_option_selection(Options*, direction);
void quit();



