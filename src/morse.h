#include<string.h>
#include <ctype.h>

void str_to_morse(char *str, char *morse) {

    int j=0;
    for(int i=0;i<=strlen(str);i++)
    {
            switch(toupper(str[i]))
            {
                case 'A':
                morse[j++]='.';
                morse[j++]='-';
                morse[j]='/';
                break;

                case 'B':
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j]='/';
                break;

                case 'C':
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j]='/';
                break;

                case 'D':
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j]='/';
                break;

                case 'E':
                morse[j++]='.';
                morse[j]='/';
                break;

                case 'F':
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j]='/';
                break;

                case 'G':
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='.';
                morse[j]='/';
                break;

                case 'H':
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j]='/';
                break;

                case 'I':
                morse[j++]='.';
                morse[j++]='.';
                morse[j]='/';
                break;

                case 'J':
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='-';
                morse[j]='/';
                break;

                case 'K':
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='-';
                morse[j]='/';
                break;

                case 'L':
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j]='/';
                break;

                case 'M':
                morse[j++]='-';
                morse[j++]='-';
                morse[j]='/';
                break;

                case 'N':
                morse[j++]='-';
                morse[j++]='.';
                morse[j]='/';
                break;

                case 'O':
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='-';
                morse[j]='/';
                break;

                case 'P':
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='.';
                morse[j]='/';
                break;

                case 'Q':
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='-';
                morse[j]='/';
                break;

                case 'R':
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j]='/';
                break;

                case 'S':
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j]='/';
                break;

                case 'T':
                morse[j++]='-';
                morse[j]='/';
                break;

                case 'U':
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j]='/';
                break;

                case 'V':
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j]='/';
                break;

                case 'W':
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='-';
                morse[j]='/';
                break;

                case 'X':
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j]='/';
                break;

                case 'y':
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='-';
                morse[j]='/';
                break;

                case 'Z':
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j]='/';
                break;

                case '0':
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='-';
                morse[j]='/';
                break;

                case '1':
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='-';
                morse[j]='/';
                break;

                case '2':
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='-';
                morse[j]='/';
                break;

                case '3':
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='-';
                morse[j]='/';
                break;

                case '4':
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j]='/';
                break;

                case '5':
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j]='/';
                break;

                case '6':
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j]='/';
                break;

                case '7':
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j]='/';
                break;

                case '8':
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j]='/';
                break;

                case '9':
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='.';
                morse[j]='/';
                break;

                case '.':
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='-';
                morse[j]='/';
                break;

                case ',':
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='-';
                morse[j]='/';
                break;

                case ':':
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j]='/';
                break;

                case '?':
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j]='/';
                break;


                case '-':
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j]='/';
                break;

                case ';':
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j]='/';
                break;

                case '"':
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j]='/';
                break;

                case '+':
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j]='/';
                break;

                case '/':
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j]='/';
                break;

                case '&':
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j]='/';
                break;

                case '$':
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j]='/';
                break;


                case '@':
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='-';
                morse[j++]='.';
                morse[j]='/';
                break;

                case '=':
                morse[j++]='-';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='.';
                morse[j++]='-';
                morse[j]='/';
                break;

                case ' ':
                morse[j]=' ';
                break;
            }
        j++;
    }
    morse[j-3]='\0';
}