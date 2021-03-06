#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <limits.h>
#include <assert.h>
#include <ctype.h>

const int MEM_STEP = 100;
const int BUF_SIZE = 1000;

const char UNCMP_CHARS[] = {' ', '?', '?', '?', '(', ')', '.', '?', ',', ':', ';', '!', '?'};
const int UNCMP_CHARS_COUNT = sizeof(UNCMP_CHARS) / sizeof(char);

const char INPUT_FILE[] = "D:/C projects/Onegin/text/Onegin.txt";
const char OUTPUT_FILE_1[] = "D:/C projects/Onegin/text/Onegin_Alphabet_sort.txt";
const char OUTPUT_FILE_2[] ="D:/C projects/Onegin/text/Onegin_Rhyming_dictionary.txt";

enum Error
{
    NO_ERRORS = 0,
    CANT_OPEN_FILE_ERROR,
    NO_DATA_ERROR,
    ALLOCATE_ERROR,
    ERROR_
};


struct String
{
    size_t length;
    char * str;
};

struct StringList
{
    size_t length;
    String ** item;
};


StringList * getStringList (const char * fname, enum Error * err = NULL);
Error saveStringList (const char * fname, const StringList * strList);

int AlphabetCmp (const String ** str1, const String ** str2);//compare begins of strings
int RhymingCmp (const String ** str1, const String ** str2);//compare ends of words

void printStringList (const StringList * strList);


int main()
{
    SetConsoleCP (1251);
    SetConsoleOutputCP (1251);


    StringList * stringList = getStringList (INPUT_FILE);

    qsort (stringList -> item, stringList -> length, sizeof (String*),
          (int(*) (const void *, const void *)) AlphabetCmp);

    saveStringList (OUTPUT_FILE_1, stringList);

    qsort (stringList -> item, stringList -> length, sizeof (String*),
          (int(*) (const void *, const void *)) RhymingCmp);

    saveStringList (OUTPUT_FILE_2, stringList);

    //printStringList (stringList);

    return 0;
}


StringList * getStringList (const char * fname, enum Error* err)
{
    assert (fname);

    if (err) *err = NO_ERRORS;

    FILE * file;

    if ((file = fopen (fname, "r")) == NULL)
    {
        if (err) *err = CANT_OPEN_FILE_ERROR;
        return NULL;
    }

    int c = getc (file);
    if (c == EOF)
    {
        if (err) *err = NO_DATA_ERROR;
        return NULL;
    }
    else
        ungetc (c, file);


    StringList * strList = NULL;
    if((strList = (StringList*) calloc(1, sizeof (StringList))) == NULL ||
       (strList -> item = (String **) calloc(MEM_STEP, sizeof (String *))) == NULL)
    {
        if (err) *err = ALLOCATE_ERROR;
        return NULL;
    }

    strList -> length = MEM_STEP;

    int strNumb = 0;
    while (c != EOF)
    {

        if (strNumb >= strList -> length)
        {
            String ** newItems = NULL;
            if ((newItems = (String **) realloc (strList -> item, (strList -> length + MEM_STEP) * sizeof (String *))) == NULL)
            {
                if (err) *err = ALLOCATE_ERROR;
                return strList;
            }

            strList -> item = newItems;
            strList -> length += MEM_STEP;
        }

        char buf[BUF_SIZE] = {};
        int n = 0;
        while((c = getc(file)) != '\n' && c != EOF)
            buf[n++] = c;

        if(n > 0)
        {
            if((strList -> item [strNumb] = (String*) calloc(1, sizeof(String))) == NULL ||
               (strList -> item [strNumb] -> str = (char*) calloc(n, sizeof(char))) == NULL)
            {
                if(err) *err = ALLOCATE_ERROR;
                return strList;
            }

            memcpy(strList -> item [strNumb] -> str, buf, n * sizeof(char));
            strList -> item [strNumb] -> length = n;

            strNumb ++;
        }

    }

    fclose (file);

    String ** newItems = NULL;
    if((newItems = (String **) realloc(strList -> item, strNumb * sizeof (String *))) == NULL)
    {
        if (err) *err = ALLOCATE_ERROR;
        return strList;
    }

    strList -> item = newItems;
    strList -> length = strNumb;

    return strList;
}

void printStringList (const StringList * strList)
{
    assert (strList);

    for (int i = 0; i < strList -> length; i++)
    {
        for (int j = 0; j < strList -> item [i] -> length; j++)
            putchar ((strList -> item) [i] -> str [j]);

        putchar ('\n');
    }
}

Error saveStringList (const char * fname, const StringList * strList)
{
    assert (fname);
    assert (strList);

    FILE * file;

    if ((file = fopen (fname, "w")) == NULL)
        return CANT_OPEN_FILE_ERROR;

    for (int i = 0; i < strList -> length; i++)
    {
        for (int j = 0; j < strList -> item [i] -> length; j++)
            putc ((strList -> item) [i] -> str [j], file);

        putc ('\n', file);
    }

    fclose (file);

    return NO_ERRORS;
}


int AlphabetCmp (const String ** str1, const String ** str2)
{
    assert (str1);
    assert (str2);

    int isInformativeStr (const String * str);

    //if string consists only of uncomparable symbols
    if (!isInformativeStr (*str1))
        return 2 * CHAR_MAX;
    if (!isInformativeStr (*str2))
        return -2 * CHAR_MAX;

    char tolower_ (const char c);

    int isUncmpChar (const char c);


    int i1 = 0;
    int i2 = 0;
    while (i1 < (* str1) -> length && i2 < (* str2) -> length)
    {
        if      (isUncmpChar ((* str1) -> str [i1]))
            i1 ++;
        else if (isUncmpChar ((* str2) -> str [i2]))
            i2 ++;
        else if (tolower_ ((* str1) -> str [i1]) == tolower_ ((* str2) -> str [i2]))
            i1 ++, i2 ++;
        else
            return tolower_ ((* str1) -> str [i1]) - tolower_ ((* str2) -> str [i2]);
    }


    return (i1 < (* str1) -> length)?
                tolower_ ((* str1) -> str [--i1]) : - tolower_ ((* str2) -> str [--i2]);
}

int RhymingCmp (const String ** str1, const String ** str2)
{
    assert (str1);
    assert (str2);

    int isInformativeStr (const String * str);

    //if string consists only of uncomparable symbols
    if (!isInformativeStr (*str1))
        return 2 * CHAR_MAX;
    if (!isInformativeStr (*str2))
        return -2 * CHAR_MAX;

    char tolower_(const char c);

    int isUncmpChar(const char c);


    int i1 = (* str1) -> length - 1;
    int i2 = (* str2) -> length - 1;
    while(i1 >= 0 && i2 >= 0)
    {
        if      (isUncmpChar ((* str1) -> str [i1]))
            i1 --;
        else if (isUncmpChar ((* str2) -> str [i2]))
            i2 --;
        else if (tolower_ ((* str1) -> str [i1]) == tolower_ ((* str2) -> str [i2]))
            i1 --, i2 --;
        else
            return tolower_ ((* str1) -> str [i1]) - tolower_ ((* str2) -> str [i2]);
    }


    return (i1 >= 0)?
           tolower_ ((* str1) -> str [++i1]) : - tolower_ ((* str2) -> str [++i2]);
}


int isUncmpChar (const char c)
{
    for (int i = 0; i < UNCMP_CHARS_COUNT; i++)
        if (c == UNCMP_CHARS[i])
            return 1;

    return 0;
}

char tolower_ (const char c)
{
    if(c >= '?' && c <= '?')
        return c - 'A' + 'a';
    else
        return tolower (c);
}

int isInformativeStr (const String * str)
{
    assert (str);

    for (int i = 0; i < str -> length; i ++)
        if (!isUncmpChar (str -> str[i]))
            return 1;
    return 0;
}
