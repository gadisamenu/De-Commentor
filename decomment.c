#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/****************************************************************************/
/*  Author: Gadisa Amenu                                                    */
/*  ID: UGR/8440/ 12                                                        */
/*  Section: 2                                                              */
/****************************************************************************/



//definition of enum states 
typedef enum StateTypes {INCOMMENT,STRING,NORMAL,ONSLASH,ONSTAR,CHARACTER}StateTypes;

// a function that handles normal state 
void handle_normal(int* c, StateTypes* state);

// a function that handles string state
void handle_string(int*c, StateTypes *state);

// a function that handles incomment state
void handle_incomment(int*c ,StateTypes * state);

// a function that handles onslash state
void handle_onslash(int* c, StateTypes * state, int * comment_str_ln,int* lines);

// a function that handles character state
void handle_character(int *c ,StateTypes* state);

// a function that handles onstar state
void handle_onstar(int *c ,StateTypes* state);

int main(int argc,const char* argv[])
{
        StateTypes state = NORMAL;
        int c ;
        int lines = 1;
        int comment_start_line;

        while(( c = getchar( ) )!= EOF){

            //counting new lines
            if(c == (int)('\n')){
                        lines ++;
            }

            //checking the states
            switch (state) {
                case NORMAL:
                    handle_normal(&c,&state);
                    break;

                case INCOMMENT:
                    handle_incomment(&c,&state);
                    break;

                case STRING:
                    handle_string(&c,&state);
                    break;

                case CHARACTER:
                    handle_character(&c, &state);
                    break;

                case ONSLASH:
                    handle_onslash(&c, &state, &comment_start_line, &lines);
                    break;

                case ONSTAR:
                    handle_onstar(&c, &state);
                    break;
            }
        }

        // checking recjection 
        if (state == INCOMMENT || state == ONSTAR){
            putchar((int)('\n'));
            fprintf(stderr, "Error: line %d: unterminated comment\n",comment_start_line);
            exit(-1);
        }
        exit(0);
}




/**
*implementation of functions
*/
// NORMAL state handler
void handle_normal(int* c, StateTypes* state){
    if ((*c) == (int)('"')) 
        *state = STRING;
        
    else if(*c == (int)('\''))
        *state = CHARACTER;
   
    else if (*c == (int)('/')){
        *state = ONSLASH;
        return;
    }
    putchar(*c);
}


// STRING state handler
void handle_string(int*c, StateTypes *state){
    if (*c == (int)('"'))
        *state = NORMAL;
    putchar(*c);
}

// INCOMMENT state handler
void handle_incomment(int*c ,StateTypes * state){
    if (*c == (int)('\n'))
        putchar(*c);
    
    else if (*c == (int)('*'))
        *state = ONSTAR;
}

//ONSLASH state handler
void handle_onslash(int* c, StateTypes * state, int * comment_str_ln,int* lines){
    if (*c == (int)('*')){
        *state = INCOMMENT;
        *comment_str_ln = *lines;
        putchar((int)(' '));
        return;
    }
    else if (*c == (int)('"'))
        *state = STRING;
    else if ( *c == (int)('\''))
        *state = CHARACTER;
    else
        *state = NORMAL;
    putchar((int)('/'));
    putchar(*c);
}

// CHARACTER state handler
void handle_character(int *c ,StateTypes* state){

    if(*c == (int)('\'')){
        *state = NORMAL;
    }
    putchar(*c);
}

// ONSTAR state handler
void handle_onstar(int *c ,StateTypes* state){
    
    if (*c == (int)('/'))
        *state = NORMAL;
    
    else{
        if (*c == (int)('\n'))
            putchar(*c);
        *state = INCOMMENT;
    }
        
}
