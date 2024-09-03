#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

#define INT64_MAX_DIGT 19

int CheckUnderflow(const char* str); 
int CheckOverflow(const char *str);
static inline void skips(const char** strnumber);
size_t strnumberlen(const char* str) ;
int strnumcmp(const char* strnumber, const char* strnumber2);


size_t strnumberlen(const char* str) {
    skips(&str);
    const char* iterator = str;
    while(*iterator <= '9' && *iterator >= '0') {
        (iterator++);
    }
    return (iterator - str);
}

void skips(const char** strnumber) {

    while(**strnumber == ' ') {
        (*strnumber)++;
    }
    while(**strnumber == '0') {
        (*strnumber)++;
    }
    if(**strnumber == '\0' || **strnumber == ' ') (*strnumber)--;
}

int strnumcmp(const char* strnumber, const char* strnumber2) {
    
    skips(&strnumber);
    skips(&strnumber2);

    bool signstr = *strnumber == '-';
    bool signstr2 = *strnumber2 == '-';

    //ja retorna o valor de comparação com base no sinal
    if(signstr == 0 && signstr2 == 1 && isdigit(*(strnumber + 1)) && isdigit(*(strnumber2 + 1)))
        return 1;
    else if (signstr2 == 0 && signstr == 1 && isdigit(*(strnumber + 1)) && isdigit(*(strnumber2 + 1)))
        return -1;

    if(*strnumber == '-' || *strnumber == '+')   strnumber++;
    if(*strnumber2 == '-' || *strnumber2 == '+')   strnumber2++;

    if(!isdigit(*strnumber) || !isdigit(*strnumber2)) {
        printf("NAN\n");
        return -2;
    }

    const char* iterator = strnumber;

    size_t len = strnumberlen(strnumber);
    size_t len2 = strnumberlen(strnumber2);

    if(len == len2) {
        //dá skip nos digitos iguais
        while(*iterator == *strnumber2 && isdigit(*iterator) && isdigit(*strnumber2)) {
            iterator++; strnumber2++;
        }
        if(*iterator == '\0' && *strnumber2 == '\0') return 0;

        // verificação no caso de uma das string chegar ao 0
        iterator = (!isdigit(*iterator)) ? iterator - 1 : iterator;
        strnumber2 = (!isdigit(*strnumber2)) ? strnumber2 - 1 : strnumber2;

        return (*iterator > *strnumber2 ? 1 - 2 * signstr : -1 + 2 * signstr2);
    }
    return len > len2 ? 1 - 2 * signstr : -1 + 2 * signstr;
}

int64_t strtoi64(const char* str) {
    
    if(CheckOverflow(str) == 1) return INT64_MAX;
    if(CheckUnderflow(str) == 1) return INT64_MIN;

    bool sign = *str == '-';
    if(sign) str++;
    
    long long result = 0;
    size_t len = strnumberlen(str);
    skips(&str);
    
    for(size_t i = 0; i < len; i++){
        result = 10 * result + str[i] - '0';
    }
    return result * (1 - 2 * sign);
}

int CheckOverflow(const char *str) {
    const char MaxInt[] = "9223372036854775807";
    return (strnumcmp(MaxInt, str) < 0);
}

int CheckUnderflow(const char* str) {
    const char Minint[] = "-9223372036854775808";
    return (strnumcmp(Minint, str) > 0);
}


char* strget(char* str, size_t size) {
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';
    return str;

}
int main()
{
    printf("%lld", strtoi64("12345678910"));
    return 0;
}
