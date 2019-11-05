#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "../include/options.h"
#include <string.h>
#include <stdlib.h>
#include <signal.h>

void go_up(int size){
    for (int i=0; i<size; i++) {
        fprintf(stderr,"\033[F");
    }
};

void clear_output(int size) {
    go_up(size);
    for (int i=0; i< size; i++) {
		char empty[100];
		memset(empty, ' ', 99);
        fprintf(stderr,"                                                 \n");
    }
    go_up(size);
}

void handle_interrupt(int dummy){
    quit();
}

int main(int argc, char **argv) {
    signal(SIGINT, handle_interrupt); 
    Options options = init_options_from_args(argc, argv);
    display(&options);
    while (1) {
        input c = get_input();
        if (IS_ENTER(c)) {
            conclude_option(options.cur_option);
        } else if (IS_DIRECTION(c)) {
            move_option_selection(&options, c);
        } else if (IS_QUIT(c)) {
            quit();
        }
        go_up(options.size);
        display(&options);
    }
}

void display(const Options *options) {
    for (int i=0; i<options->size; i++){
        if (options->cur_option == options->options + i) {
            fprintf(stderr, RED "%s <" RESET, options->options[i].name);
        } else {
            fprintf(stderr,"%s            ", options->options[i].name);
        }
        fprintf(stderr,"\n");
    };
}

Options init_options_from_args(int argc, char **argv) {
    Options options;
    options.size = argc - ARG_OFFSET;
	int start_pos = 0;
	char *starting_option_name = argv[1];
    if (options.size < 1) {
        quit();
    }
    options.options = malloc(sizeof(char *) * options.size);
   
    for (int i=0; i < argc - ARG_OFFSET; i++) {
        options.options[i].name = malloc(sizeof(char) * (strlen(argv[i+ARG_OFFSET]) + 1));
        strcpy(options.options[i].name, argv[i+ARG_OFFSET]); 
		if (strcmp(starting_option_name, argv[i+ARG_OFFSET]) == 0){
			start_pos = i;
		}
    }
    options.cur_option = options.options + start_pos;
    return options;
}

void move_option_selection(Options *options, direction d) {
    if (d == UP && options->cur_option > options->options) {
        options->cur_option--;
    } else if (d == DOWN && options->cur_option < options->options + options->size - 1) {
        options->cur_option++;
    }
}

void conclude_option(Option* option) {
	printf("%s", option->name);
    quit();
}

int getch() {
    int ch;
    struct termios oldt;
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

input get_input() {
    char c0 = getch();
    if (c0 == 27 && getch() == 91) {
        char c = getchar();
        if (c == 'A' || c == 'B') {
            return c;
        } else {
            return 0;
        }
    } else if (c0 == 10 || c0 == 'q') {
        return c0;
    } else {
        return 0;
    }
}

void quit(){
    exit(0);
}
