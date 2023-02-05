#include <stdlib.h>
#include <stdio.h>

int strsize(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

int charttolower(char str) 
{
    if (str >= 'A' && str <= 'Z')
    {
        str = str + 32;
    } else
    {
        return str;
    }
    return 0;
}

int strtoupper(char *str) 
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - 32;
        }
        i++;
    }
    return 0;
}

int strtolower(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {   
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] + 32;
        }
        i++;
    }
    return 0;
}

int strcompare(char* str1, char* str2)
{
    int i;
    int size1 = strsize(str1);
    int size2 = strsize(str2);
    int pluspetit;
    if(size1 < size2) pluspetit = size1;
    else pluspetit = size2;

    for(i = 0 ; i < pluspetit ; i++)
    {
            if(str1[i] < str2[i]) return 0;
            if(str1[i] > str2[i]) return 0;
    }
    if(size1 < size2) return 0;
    if(size1 > size2) return 0;
    return 1;
}

int chartype(char ch){
    if (ch >= 'A' && ch <= 'Z') return 1;
    if (ch >= 'a' && ch <= 'z') return 2;
    if (ch >= '0' && ch <= '9') return 3;
    return 4;
}

int strsort(char *str)
{
    int i = 0, j = 0, flag = 0;
    char tmpstr;

    while (flag == 0)
    {
        flag = 1;
        for (i = 0; i < strsize(str) - 1; i++)
        {   
            char c1 = str[i];
            char c2 = str[i+1];
            int c1type = chartype(c1);
            int c2type = chartype(c2);
            if (c1type == 1) c1 += 32;
            if (c2type == 1) c2 += 32;
            if (c1type == 3) c1 += 200;
            if (c2type == 3) c2 += 200;
            if (c1type == 4) c1 -= 200;
            if (c2type == 4) c2 -= 200;

            if (c1 > c2)
            {
                tmpstr = str[i];
                str[i] = str[i+1];
                str[i+1] = tmpstr;
                flag = 0;
            }
        }
    }
    
    return 0;
}

int strcopy(char *str1, char *str2)
{
    for(int i = 0; i < strsize(str2) + 1; i++) str1[i] = str2[i];
    return 0;
}

char *strcopy2(char *str1)
{
    int i = 0;
    int size1 = strsize(str1);
    char *str2 = malloc(sizeof(char) * size1 + 1);

    while (str1[i] != '\0')
    {
        str2[i] = str1[i];
        i++;
    }
    return str2;
}



int strrevert(char *str)
{
    int i = 0;
    int j = strsize(str) - 1;
    char tmpstr;

    while (i < j)
    {
        tmpstr = str[i];
        str[i] = str[j];
        str[j] = tmpstr;
        i++;
        j--;
    }
    return 0;
}

char* strconcat(char *str1, char *str2) 
{
    int addition = strsize(str1) + strsize(str2);
    char *toret = malloc(addition + 1);
    strcopy(toret, str1);

    for (int i = 0; i < strsize(str2); i++)
    {
        toret[i + strsize(str1)] = str2[i]; 
    }
    toret[strsize(str1) + strsize(str2)] = 0;
    return toret;
}

int strsortargs(int argc, char **args)
{
    int size = argc;
    char firstletter;
    char *tmpstr;

    for(int i = 1; i < size - 1; i++)
    {
        if(args[i][0] > args[i+1][0])
        {
            tmpstr = args[i];
            args[i] = args[i+1];
            args[i+1] = tmpstr;
        }
    }
    return 0;
}


