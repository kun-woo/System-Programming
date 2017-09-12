#include "hw1.h"

#include <stdlib.h>
#include <stdio.h>

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif

int keyAlpChecker(char *givenKey, char *alphabet);
int const_keyAlpChecker(char *givenKey, const char *alphabet);
int keyDupChecker(char *givenKey);
unsigned short string_length(char *givenString);
unsigned short const_string_length(const char* givenKey);
unsigned short c_changer(int argc, char **argv, unsigned short mode, unsigned short rDigit, unsigned short cDigit);
unsigned short r_changer(int argc, char **argv, unsigned short mode, unsigned short rDigit, unsigned short cDigit);
unsigned short k_changer(unsigned short mode, char *givenKey);
unsigned short d_changer(unsigned short mode);
unsigned short e_changer(unsigned short mode);
unsigned short p_changer(unsigned short mode);
unsigned short f_changer(unsigned short mode);
unsigned short rc_checker(unsigned short mode);
int al_selector(unsigned short mode);
void poly_table_constructer(unsigned short diff, char *alphabet);
void poly_table_designer(unsigned short col, char *alphabet);
int poly_table_encrypter(unsigned short col, char *alphabet);
int poly_table_decrypter(unsigned short col, char *alphabet);
int encryptChecker(char *polybius_table_ptr, char c, unsigned short col, char *alphabet);
int poly_cipher(unsigned short mode, char *alphabet);
void poly_cipher_helper(int index);
int fm_mtable_indexer(const char *morse_string, char c);
void fm_ktable_indexer(const char *alphabet);
int fm_encrypter(const char *alphabet);
int fm_decrypter(const char *morse_string, const char *alphabet);
int fm_cipher(unsigned short mode, const char *alphabet);
void fm_cipher_helper(int index);
int ft_traverser(char *morse_string, const char *morse_string_buff, char **table);
int morse_buff_allocator(const char *morse_string, char *my_buff, int size, int index);
int cleaner(const char *morse_string, char *my_buff, int index);
int compare_string(char *first, const char *second);

/**
 * @brief Validates command line arguments passed to the program.
 * @details This function will validate all the arguments passed to the program
 * and will return a unsigned short (2 bytes) that will contain the
 * information necessary for the proper execution of the program.
 *
 * IF -p is given but no (-r) ROWS or (-c) COLUMNS are specified this function
 * MUST set the lower bits to the default value of 10. If one or the other
 * (rows/columns) is specified then you MUST keep that value rather than assigning the default.
 *
 * @param argc The number of arguments passed to the program from the CLI.
 * @param argv The argument strings passed to the program from the CLI.
 * @return Refer to homework document for the return value of this function.
 */
unsigned short validargs(int argc, char **argv) {
    unsigned short mode = 0x00AA; //mode is initailized to 0
    unsigned short rDigit = 10; //# of row
    unsigned short cDigit = 10; //# of column
    if ((argc >1)){

      if (keyAlpChecker("-h", *(argv+1)) == 1)
      {
        return 0x8000;
      }
      if (keyAlpChecker("-p", *(argv+1)) == 1)
      {
        mode = p_changer(mode);
        if ((argc >2) && (keyAlpChecker("-e", *(argv+2)) == 1))
        {
          mode = e_changer(mode);
          for (int i = 3; i < argc; ++i)
          {
            if(**(argv+i) == '-' &&(keyAlpChecker("-k", *(argv+i)) == 1)){
              unsigned short temp_mode = k_changer(mode, *(argv+i+1));
              if ((temp_mode != mode) && (temp_mode == 0))
              {
                return 0;
              }
              mode = temp_mode;
              if ((i+2) == argc)
              {
                  //printf("Mode is %04x\n", mode);
                mode = rc_checker(mode);
                return mode;
              }
            }
            if (**(argv+i) == '-' && (keyAlpChecker("-c", *(argv+i)) == 1)){
              mode = c_changer(i, argv, mode, rDigit, cDigit);
              if ((i+2) == argc)
              {
                  //printf("Mode is %04x\n", mode);
                mode = rc_checker(mode);
                return mode;
              }
            }
            if (**(argv+i) == '-' && (keyAlpChecker("-r", *(argv+i)) == 1)){
                //printf("CHANGER BEFORE Mode is %04x\n", mode);
              mode = r_changer(i, argv, mode, rDigit, cDigit);
                //printf("CHANGER AFTER Mode is %04x\n", mode);
              if ((i+2) == argc)
              {
                  //printf("Mode is %04x\n", mode);
                mode = rc_checker(mode);
                return mode;
              }
            }
          }
          if ((argc == 4))
          {
              //printf("Wrong Command\n");
            return 0;
          }
            //printf("Mode is %04x\n", mode);
          mode = rc_checker(mode);
          return mode;
        }
        if ((argc >2) && (keyAlpChecker("-d", *(argv+2)) == 1))
        {
          mode = d_changer(mode);
          for (int i = 3; i < argc; ++i)
          {
            if(**(argv+i) == '-' &&(keyAlpChecker("-k", *(argv+i)) == 1)){
              unsigned short temp_mode = k_changer(mode, *(argv+i+1));
              if ((temp_mode != mode) && (temp_mode == 0))
              {
                return 0;
              }
              mode = temp_mode;
              if ((i+2) == argc)
              {
                  //printf("Mode is %04x\n", mode);
                mode = rc_checker(mode);
                return mode;
              }
            }
            if (**(argv+i) == '-' && (keyAlpChecker("-c", *(argv+i)) == 1)){
              mode = c_changer(i, argv, mode, rDigit, cDigit);
              if ((i+2) == argc)
              {
                  //printf("Mode is %04x\n", mode);
                mode = rc_checker(mode);
                return mode;
              }
            }
            if (**(argv+i) == '-' && (keyAlpChecker("-r", *(argv+i)) == 1)){
                //printf("CHANGER BEFORE Mode is %04x\n", mode);
              mode = r_changer(i, argv, mode, rDigit, cDigit);
                //printf("CHANGER AFTER Mode is %04x\n", mode);
              if ((i+2) == argc)
              {
                  //printf("Mode is %04x\n", mode);
                mode = rc_checker(mode);
                return mode;
              }
            }
          }
          if ((argc == 4))
          {
              //printf("Wrong Command\n");
            return 0;
          }
            //printf("Mode is %d\n", mode);
          mode = rc_checker(mode);
          return mode;
        }
        return 0;
      }
      if (keyAlpChecker("-f", *(argv+1)) == 1)
      {
        mode = f_changer(mode);
        if ((argc >2) && (keyAlpChecker("-e", *(argv+2)) == 1))
        {
          mode = e_changer(mode);
          for (int i = 3; i < argc; ++i){
            if(**(argv+i) == '-' &&(keyAlpChecker("-k", *(argv+i)) == 1)){
              unsigned short temp_mode = k_changer(mode, *(argv+i+1));
              if ((temp_mode != mode) && (temp_mode == 0))
              {
                return 0;
              }
              mode = temp_mode;
              if ((i+2) == argc)
              {
                  //printf("Mode is %04x\n", mode);
                return mode;
              }
            }
          }
          if ((argc == 4))
          {
              //printf("Wrong Command\n");
            return 0;
          }
            //printf("Mode is %04x\n", mode);
          return mode;
        }
        if ((argc >2) && (keyAlpChecker("-d", *(argv+2)) == 1))
        {
          mode = d_changer(mode);
          for (int i = 3; i < argc; ++i){
            if(**(argv+i) == '-' &&(keyAlpChecker("-k", *(argv+i)) == 1)){
              unsigned short temp_mode = k_changer(mode, *(argv+i+1));
              if ((temp_mode != mode) && (temp_mode == 0))
              {
                return 0;
              }
              mode = temp_mode;
              if ((i+2) == argc)
              {
                  //printf("Mode is %04x\n", mode);
                return mode;
              }
            }
          }
          if ((argc == 4))
          {
              //printf("Wrong Command\n");
            return 0;
          }
            //printf("Mode is %d\n", mode);
          return mode;
        }
        return 0;
      }
      return 0;
    }
    return 0; //Error: Wrong command
  }

/* For checking if the key is in alphabet or argument*/
  int keyAlpChecker(char *givenKey, char *alphabet){
  char *initAlphabet = alphabet; //For go back to the starting point of alphabet
  while(*givenKey != '\0'){
    if (*givenKey == *alphabet)
    {
      givenKey++;
      if (*givenKey == '\0')
      {
        return 1;
      }
    }
    while( *givenKey != *alphabet){
      alphabet++;
      if (*givenKey == *alphabet)
      {
        givenKey++;
              alphabet = initAlphabet; //init
              if (*givenKey == '\0')
              {
                return 1;
              }
              break;
            }
            if (*alphabet == '\0')
            {
              givenKey++;
              alphabet = initAlphabet;
              if (*givenKey == '\0')
              {
                return 0;
              }
            }
          }
        }
        return 0;
      }
      int const_keyAlpChecker(char *givenKey, const char *alphabet){
const char *initAlphabet = alphabet; //For go back to the starting point of alphabet
while(*givenKey != '\0'){
  if (*givenKey == *alphabet)
  {
    givenKey++;
    if (*givenKey == '\0')
    {
      return 1;
    }
  }
  while( *givenKey != *alphabet){
    alphabet++;
    if (*givenKey == *alphabet)
    {
      givenKey++;
            alphabet = initAlphabet; //init
            if (*givenKey == '\0')
            {
              return 1;
            }
            break;
          }
          if (*alphabet == '\0')
          {
            givenKey++;
            alphabet = initAlphabet;
            if (*givenKey == '\0')
            {
              return 0;
            }
          }
        }
      }
      return 0;
    }
/* For checking if the key has duplicates*/
    int keyDupChecker(char *givenKey){
      char *first = givenKey;
      char *second = givenKey+1;
      if (*second == '\0')
      {
        return 1;
      }
      while(*(first) != *(second) ){
        second++;
        if (*(second) == '\0')
        {
          if (*(first+1) == '\0' )
          {
            return 1;
          }
          first++;
          if (*(first+1) == '\0')
          {
            return 1;
          }
          second = first+1;
        }
      }
      return 0;
    }
/*For counting size of string */
    unsigned short string_length(char *givenString){
      char *ptr = givenString;
      int counter = 0;
      while(*ptr != '\0'){

        counter++;
        ptr++;
        if (*ptr == '\0')
        {
          return counter;
        }
      }
      return 0;
    }
    unsigned short const_string_length(const char *givenString){
      const char *ptr = givenString;
      int counter = 0;
      while(*ptr != '\0'){

        counter++;
        ptr++;
        if (*ptr == '\0')
        {
          return counter;
        }
      }
      return 0;
    }
    unsigned short c_changer(int argc, char **argv, unsigned short mode, unsigned short rDigit, unsigned short cDigit){
  //printf("c_changer\n");
      cDigit = atoi(*(argv+argc+1));
  mode = mode & 0xFFF0; //set column as 0
  mode = mode | cDigit;
  //printf("Row of Mode is %d\n", mode & 0x00F0);
  return mode;
}
unsigned short r_changer(int argc, char **argv, unsigned short mode, unsigned short rDigit, unsigned short cDigit){
  //printf("r_changer\n");
  rDigit = atoi(*(argv+argc+1));
  rDigit = rDigit << 4;
  mode = mode & 0xFF0F; //set row as 0
  mode = mode | rDigit;
  //printf("column of Mode is %d\n", mode & 0x000F);
  return mode;
}
unsigned short k_changer(unsigned short mode, char *givenKey){
    //printf("k_changer\n");
  if (al_selector(mode) == 0)
  {
    if(keyAlpChecker(givenKey, polybius_alphabet)==1){
      if (keyDupChecker(givenKey)==1)
      {
        key = givenKey;
      //printf("The Key is %s\n", key);
        return mode;
      }
    //printf("Duplicates!\n");
      return 0;
    }
  //printf("Invalid character\n");
    return 0;
  }
  else if (al_selector(mode) == 1){
    if(const_keyAlpChecker(givenKey, fm_alphabet)==1){
      if (keyDupChecker(givenKey)==1)
      {
        key = givenKey;
      //printf("The Key is %s\n", key);
        return mode;
      }
    //printf("Duplicates!\n");
      return 0;
    }
  //printf("Invalid character\n");
    return 0;
  }
  else {
    return 0;
  }
}
unsigned short d_changer(unsigned short mode){
  char *initalizer = ""; //Initializing key for safety!
  key = initalizer;
  unsigned short d = 1;
  mode = mode | (d << 13);
  return mode;
}
unsigned short e_changer(unsigned short mode){
  char *initalizer = "";
  key = initalizer;
  unsigned short e = 0;
  mode = mode | (e << 13);
  return mode;
}
unsigned short p_changer(unsigned short mode){
  unsigned short p = 0;
  mode = mode | (p << 14);
  return mode;
}
unsigned short f_changer(unsigned short mode){
  unsigned short f = 1;
  mode = mode | (f << 14);
  return mode;
}
unsigned short rc_checker(unsigned short mode){
  unsigned short one = 15;
  unsigned short rDigit = (mode >> 4) & one;
  unsigned short cDigit = (mode) & one;
  //printf("MODE: %04x\n", mode);
  //printf("ROW: %d\n", rDigit);
  //printf("COL: %d\n", cDigit);
  if (al_selector(mode) == 0)
  {
    if (string_length(polybius_alphabet) > rDigit * cDigit)
    {
    //printf("Smaller Than Alphabet");
      return 0;
    }
    else{
      return mode;
    }
  }
  else if (al_selector(mode) == 1)
  {
    if (const_string_length(fm_alphabet) > rDigit * cDigit)
    {
    //printf("Smaller Than Alphabet");
      return 0;
    }
    else{
      return mode;}
    }
    else{
      return 0;
    }
  }
  int al_selector(unsigned short mode){
    unsigned short checker = 1;
    checker = (mode >> 14) & checker;
    switch(checker){
      case 0:
      return 0; //polybius
      case 1:
      return 1; //fractionated
    }
  //printf("For safety, return -1");
    return -1;
  }
//construct polybius table
  void poly_table_constructer(unsigned short diff, char *alphabet){
    char *polybius_table_ptr = polybius_table;
    for (int i = 0; i < string_length(alphabet); ++i)
    {
      *(polybius_table_ptr+i) = *(polybius_alphabet+i);
    }
    for (int i = 0; i < diff; ++i)
    {
      *(polybius_table_ptr+i+string_length(alphabet)) = '\0';
    }
  }
//Find indexes that is storing the key's letter and Rearrange Them
  void poly_table_designer(unsigned short col, char *alphabet){
    char *polybius_table_ptr = polybius_table;
    if(*(key) != '\0'){
      for (int i = 0; i < const_string_length(key); ++i)
      {
        for (int j = 0; j < string_length(alphabet); ++j)
        {
      if(*(polybius_table_ptr+j) == *(key+const_string_length(key)-1-i)){ //starting from the very last of key
        poly_cipher_helper(j);
      }
    }
  }
}
  // return 0; There is no key to set in Table
}
//Search for input letters in Table and Print their x-axis and y-axis out
int poly_table_encrypter(unsigned short col, char *alphabet){
  char *polybius_table_ptr = polybius_table;
  int c = 1;
  while (c != EOF) {
    c = getchar();
    //Check if c is in Alphabet
    if (encryptChecker(polybius_table_ptr, c, col, alphabet) == 0 && (c != EOF))
    {
      //printf("Input is not in Alphabet");
      return 0;
    }
  }
  return 1;
}
//Decrypter
int poly_table_decrypter(unsigned short col, char *alphabet){
  char *polybius_table_ptr = polybius_table;
  int pairChecker =1;
  int x =0;
  int y = 0;
  int index = 0;
  int c = 1;
  while (c != EOF) {
    c = getchar();
    while (c != EOF) {
      if (pairChecker == 1)
      {
        if (c == ' ')
        {
          fprintf(stdout, "%c", ' ');
          break;
        }
        if (c == '\n')
        {
          fprintf(stdout, "%c", '\n');
          break;
        }
        if (c >= '0' && c <= '9')
        {
          x= c - '0';
          pairChecker++;
          break;
        }
        if (c >= 'A' && c <= 'F')
        {
          x= (c - 'A') + 10;
          pairChecker++;
          break;
        }
      }
      else if (pairChecker == 2)
      {
        if (c == ' ')
        {
          fprintf(stdout, "%c", ' ');
          break;
        }
        if (c == '\n')
        {
          fprintf(stdout, "%c", '\n');
          break;
        }
        if (c >= '0' && c <= '9')
        {
          y = c - '0';
          pairChecker = 1;
          index = x * col + y;
          fprintf(stdout, "%c", *(polybius_table_ptr+index));
          break;
        }
        if (c >= 'A' && c <= 'F')
        {
          y = (c - 'A') + 10;
          pairChecker = 1;
          index = x * col + y;
          fprintf(stdout, "%c", *(polybius_table_ptr+index));
          break;
        }
      }
      else{
        //printf("Error: pairChecker is%d\n", pairChecker);
        return 0;
      }
    }
  }
  return 1;
}

//For encryption, check if input is in alphabet and print
int encryptChecker(char *polybius_table_ptr, char c, unsigned short col, char *alphabet){
  for (int j = 0; j < string_length(alphabet); ++j)
  {
    if(*(polybius_table_ptr+j) == c){
      int x = j / col;
      int y = j % col;
        // //printf("//\t'%c' is at (%d, %d), index number is %d\n",c, x, y, j);
      fprintf(stdout, "%X%X", x, y);
      return 1;
    }
    else if (c == ' ' || c == '\t')
    {
      fprintf(stdout, "%c", ' ');
      return 1;
    }
    else if (c == '\n')
    {
      fprintf(stdout, "%c", '\n');
      return 1;
    }
  }
  return 0;
}
//For encrypt and decrypt polybius
int poly_cipher(unsigned short mode, char *alphabet){
  unsigned short row = (mode >> 4) & 0x000F;
  unsigned short col = (mode) & 0x000F;
  unsigned short diff = row*col - string_length(alphabet);
  poly_table_constructer(diff, alphabet);
  poly_table_designer(col, alphabet);
  if((((mode >> 13) & 1) == 0)){
    return poly_table_encrypter(col, alphabet);
  }
  if((((mode >> 13) & 1) == 1)){
    return poly_table_decrypter(col, alphabet);
  }
  return 1;
}
//For rearranging table
void poly_cipher_helper(int index){
  char *polybius_table_ptr = polybius_table;
  char index_key = *(polybius_table_ptr+index);
  while(index >= 1)
  {
    *(polybius_table_ptr+index) = *(polybius_table_ptr+index-1);
    index--;
    if (index == 0)
    {
      *(polybius_table_ptr) = index_key;
      break;
    }
  }
}
//Indexing morse_table with ASCII code
int fm_mtable_indexer(const char *morse_string, char c){
  char *ascii_alphabet="!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
  for (int i = 0; i < string_length(ascii_alphabet); ++i)
  {
    if (c == *(ascii_alphabet+i))
    {
      return i;
    }
  }
  if (c == '\n')
  {
    fprintf(stdout, "%c", c);
    return -2;
  }
  if (c == ' ') //treat multiple white space as one
  {
    morse_string = "xx";
    return -3;
  }
  morse_string = "";
  return -1;
}
void fm_ktable_indexer(const char *alphabet){
  const char *fm_alphabet_ptr = alphabet;
  char *fm_key_ptr = fm_key;
  for (int i = 0; i < const_string_length(fm_alphabet_ptr); ++i)
  {
    *(fm_key_ptr+i) = *(fm_alphabet_ptr+i); //Assign fm_key with fm_alphabet
  }
  if(*(key) != '\0'){
    for (int i = 0; i < const_string_length(key); ++i)
    {
      for (int j = 0; j < const_string_length(alphabet); ++j)
      {
      if(*(fm_key_ptr+j) == *(key+const_string_length(key)-1-i)){ //starting from the very last of key
        fm_cipher_helper(j);
      }
    }
  }
}
}
int fm_encrypter(const char *alphabet){
  int white_space = 0; //for counting continuous ws
  long space1;
  char *my_buff = (char *) &space1; //for containing the last char
  const char *indicator =""; //indicate whether word has finished or the letter has finished
  const char **fm_table_ptr = fractionated_table;
  const char **morse_table_ptr = morse_table;
  int c = 1;
  //Initializing Buffer with empty char
  *(my_buff) = '\0';
  *(my_buff+1) = '\0';
  *(my_buff+2) = '\0';
  *(my_buff+3) = '\0';
  while (c != EOF){
    c = getchar();
    printf("THe very Input: %c\n", c);
    const char *morse_string = "";
    int index_mt = fm_mtable_indexer(morse_string, c);
    switch(index_mt){
      case -1:
      white_space = 0;
      return 0;
      case -2:
      white_space = 0;
      continue;
      case -3:
      white_space ++;
      if (white_space > 1)
      {
        continue;
      }
      if (*(my_buff+string_length(my_buff)-1) == 'x')
      {
        *(my_buff+string_length(my_buff)-1) = '\0';
        indicator = "xx";
      }
      if (*my_buff == '\0')
      {
        indicator = "x";
      }
          int index_WS = morse_buff_allocator(indicator, my_buff, 3, 0);
          if (string_length(my_buff) == 3)
          {
            for (int i = 0; i < 26; ++i)
            {
              if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
              {
                char *fm_key_ptr_a = fm_key;
                fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
              *(my_buff) = '\0';
              *(my_buff+1) = '\0';
              *(my_buff+2) = '\0';
                break;
              }
            }
          }
            continue; //That there is nothing to print, read another char
          if (cleaner(indicator, my_buff, index_WS)==1)
          {
            continue;
          }
          printf("SOMETHING GOOOO WRONGGG");
          continue;
          default:
          white_space = 0;
          morse_string = *(morse_table_ptr+index_mt); //Get morse code
          printf("For Beginning: MS: %s, MB: %s\n", morse_string, my_buff);
        }
        if (*morse_string ==  '\0')
        {
          return 0; //Morse is Empty. Failed
        }
      fm_ktable_indexer(alphabet); //assign value in fm_key with key
      if (*my_buff == '\0')
      {
       if (const_string_length(morse_string) < 3)
       {
        *my_buff = *(morse_string);
        *(my_buff+1) = 'x';
        if (const_string_length(morse_string) == 2)
        {
          *(my_buff) = *(morse_string);
          *(my_buff+1) = *(morse_string);
          *(my_buff+2) = 'x';
            //Buff is now 3 => print and clear buff
          printf("Buff is %s and MS: %s\n", my_buff, morse_string);
          for (int i = 0; i < 26; ++i)
          {
            if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
            {
              char *fm_key_ptr_a = fm_key;
              fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
              *(my_buff) = '\0';
              *(my_buff+1) = '\0';
              *(my_buff+2) = '\0';
              break;
            }
          }
          continue;
        }
        continue;
      }
      else{
        int index = 0;
        while(const_string_length(morse_string) - index > 2){
            //=>Assign 3 letter to my_buff and record the index at that point (or take out those three from first and pull the rest to front)
          index = morse_buff_allocator(morse_string, my_buff, 3, index);
          printf("First Rounder: MB: %s, INDEX=%d\n", my_buff, index);
          for (int i = 0; i < 26; ++i)
          {
            if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
            {
              char *fm_key_ptr_a = fm_key;
              fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
              *(my_buff) = '\0';
              *(my_buff+1) = '\0';
              *(my_buff+2) = '\0';
              break;
            }
          }
          if (index == 0)
          {
            break; //That there is nothing to print, read another char
          }
        }
        if (index == 0)
        {
          *(my_buff) = 'x';
          if (string_length(my_buff) == 3)
          {
            for (int i = 0; i < 26; ++i)
            {
              if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
              {
                char *fm_key_ptr_a = fm_key;
                fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
                *(my_buff) = '\0';
                *(my_buff+1) = '\0';
                *(my_buff+2) = '\0';
                break;
              }
            }
          }
            continue; //That there is nothing to print, read another char
          }
          if (cleaner(morse_string, my_buff, index)==1)
          {
            continue;
          }
        printf("Check out INDEX!: MB: %s, INDEX=%d\n", my_buff, index);
        continue;
        }
      }
      else{ //when buffer is in place
        if (string_length(my_buff)==1)
        {
          int index = 0;
          index = morse_buff_allocator(morse_string, my_buff, 3, index);
          printf("Second Rounder: MB: %s, INDEX=%d\n", my_buff, index);
          if (index == 0)
          {
            //Buffer 2 => +X and Print and clear Buffer and Read Next
            //Buffer 3 => Print and clear Buffer and +X and Read Next
            if (string_length(my_buff) == 2)
            {
              *(my_buff+2) = 'x';
              for (int i = 0; i < 26; ++i)
              {
                if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
                {
                  char *fm_key_ptr_a = fm_key;
                  fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
                  *(my_buff) = '\0';
                  *(my_buff+1) = '\0';
                  *(my_buff+2) = '\0';
                  break;
                }
              }
              continue;
            }
            else {
              printf("12 Rounder: MB: %s, INDEX=%d\n", my_buff, index);
              for (int i = 0; i < 26; ++i)
              {
                if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
                {
                  char *fm_key_ptr_a = fm_key;
                  fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
                  *(my_buff) = '\0';
                  *(my_buff+1) = '\0';
                  *(my_buff+2) = '\0';
                  break;
                }
              }
              *(my_buff) = 'x';
              continue;
            }
          }
          //This means Morse_string is > 2 that Print => flush B =>Read until morse_String is gone => Read Next
          printf("Fourth Rounder: MB: %s, INDEX=%d\n", my_buff, index);
          for (int i = 0; i < 26; ++i)
          {
            if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
            {
              char *fm_key_ptr_a = fm_key;
              fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
              *(my_buff) = '\0';
              *(my_buff+1) = '\0';
              *(my_buff+2) = '\0';
              break;
            }
          }
          while (const_string_length(morse_string) - index > 2){
            //=>Assign 3 letter to my_buff and record the index at that point (or take out those three from first and pull the rest to front)
            index = morse_buff_allocator(morse_string, my_buff, 3, index);
            printf("Third Rounder: MB: %s, INDEX=%d\n", my_buff, index);
            for (int i = 0; i < 26; ++i)
            {
              if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
              {
                char *fm_key_ptr_a = fm_key;
                fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
                *(my_buff) = '\0';
                *(my_buff+1) = '\0';
                *(my_buff+2) = '\0';
                break;
              }
            }
            if (index == 0)
            {
            break; //That there is nothing to print, read another char
          }
        }
        if (index == 0){
            //Buffer 2 => +X and Print and clear Buffer and Read Next
            //Buffer 3 => Print and clear Buffer and +X and Read Next
          if (string_length(my_buff) == 2)
          {
            *(my_buff+2) = 'x';
            printf("Fifth Rounder: MB: %s, INDEX=%d\n", my_buff, index);
            for (int i = 0; i < 26; ++i)
            {
              if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
              {
                char *fm_key_ptr_a = fm_key;
                fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
                *(my_buff) = '\0';
                *(my_buff+1) = '\0';
                *(my_buff+2) = '\0';
                break;
              }
            }
            continue;
          }
          else {
            printf("Sixth Rounder: MB: %s, INDEX=%d\n", my_buff, index);
            for (int i = 0; i < 26; ++i)
            {
              if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
              {
                char *fm_key_ptr_a = fm_key;
                fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
                *(my_buff) = '\0';
                *(my_buff+1) = '\0';
                *(my_buff+2) = '\0';
                break;
              }
            }
            *(my_buff) = 'x';
            continue;
          }
        }
        //cleaner
        if (cleaner(morse_string, my_buff, index)==1)
          {
            continue;
          }
      }
      else if (string_length(my_buff) == 2){
        int index = 0;
        index = morse_buff_allocator(morse_string, my_buff, 3, index);
        printf("Seventh Rounder: MB: %s, INDEX=%d\n", my_buff, index);
        if (index == 0)
        {
            //Buffer 3 => Print and clear Buffer and +X and Read Next
          printf("11 Rounder: MB: %s, INDEX=%d\n", my_buff, index);
          for (int i = 0; i < 26; ++i)
          {
            if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
            {
              char *fm_key_ptr_a = fm_key;
              fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
              *(my_buff) = '\0';
              *(my_buff+1) = '\0';
              *(my_buff+2) = '\0';
              break;
            }
          }
          *(my_buff) = 'x';
          continue;
        }
          //This means Morse_string is > 1 that Print => flush B =>Take Morse_String
        printf("8 Rounder: MB: %s, INDEX=%d\n", my_buff, index);
        for (int i = 0; i < 26; ++i)
        {
          if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
          {
            char *fm_key_ptr_a = fm_key;
            fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
            *(my_buff) = '\0';
            *(my_buff+1) = '\0';
            *(my_buff+2) = '\0';
            break;
          }
        }
        while (const_string_length(morse_string) - index > 2){
            //=>Assign 3 letter to my_buff and record the index at that point (or take out those three from first and pull the rest to front)
          index = morse_buff_allocator(morse_string, my_buff, 3, index);
          printf("9 Rounder: MB: %s, INDEX=%d\n", my_buff, index);
          for (int i = 0; i < 26; ++i)
          {
            if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
            {
              char *fm_key_ptr_a = fm_key;
              fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
              *(my_buff) = '\0';
              *(my_buff+1) = '\0';
              *(my_buff+2) = '\0';
              break;
            }
          }
          if (index == 0)
          {
            break; //That there is nothing to print, read another char
          }
        }
        if (index == 0)
        {
            //Buffer 3 => Print and clear Buffer and +X and Read Next
          printf("10 Rounder: MB: %s, INDEX=%d\n", my_buff, index);
          for (int i = 0; i < 26; ++i)
          {
            if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
            {
              char *fm_key_ptr_a = fm_key;
              fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
              *(my_buff) = '\0';
              *(my_buff+1) = '\0';
              *(my_buff+2) = '\0';
              break;
            }
          }
          *(my_buff) = 'x';
          continue;
        }
        if (cleaner(morse_string, my_buff, index)==1)
          {
            continue;
          }
      }
      else{
        printf("Can't Be Here\n");
        printf("The Buff is: %s, The length is %d\n" ,my_buff, string_length(my_buff));
      }
    }
  }
  return 1;
}
int fm_decrypter(const char *morse_string, const char *alphabet){
  return 0;
}
int fm_cipher(unsigned short mode, const char *alphabet){
  if((((mode >> 13) & 1) == 0)){
    return fm_encrypter(alphabet);
  }
  if((((mode >> 13) & 1) == 1)){
    // return fm_decrypter(col, alphabet);
  }
  return 1;
}
void fm_cipher_helper(int index){
  char *fm_key_ptr_h = fm_key;
  char index_key = *(fm_key_ptr_h+index);
  while(index >= 1)
  {
    *(fm_key_ptr_h+index) = *(fm_key_ptr_h+index-1);
    index--;
    if (index == 0)
    {
      *(fm_key_ptr_h) = index_key;
      break;
    }
  }
}
//Return index
int morse_buff_allocator(const char *morse_string, char *my_buff, int size, int index){
  int i = 0;
  int j = 0;
  if (*(morse_string+index) == '\0')
  {
    return 0;
  }
  while (*(my_buff+i) == '\0')
  {
    *(my_buff+i) = *(morse_string+index+j);
    i++;
    j++;
    if(*(morse_string+index+j) == '\0'){
      return 0;
    }
    if ( i == size)
    {
      return index+j;
    }
  }
  while(*(my_buff+i) != '\0'){
    i++;
    while (*(my_buff+i) == '\0'){
      *(my_buff+i) = *(morse_string+index+j);
      i++;
      j++;
      if (*(morse_string+index+j) == '\0')
      {
        return 0;
      }
      if (i == size)
      {
        return index+j;
      }
    }
  }
  return 0;
}
int cleaner(const char *morse_string, char *my_buff, int index){
  const char **fm_table_ptr = fractionated_table;
  int second_F = morse_buff_allocator(morse_string, my_buff, 3, index);
  if (second_F != 0)
  {
    printf("SOMETHING GOT WAY WRONGGGGG\n");
    return 0;
  }
  if (compare_string("xx", morse_string) != 0)
  {
    int forX = morse_buff_allocator("x", my_buff, 3, 0);
    if (forX != 0)
    {
      printf("HOLY, SOMETHING GOT WAY WRONGGGGG\n");
      return 0;
    }
  }
  if (string_length(my_buff) == 3)
  {
    for (int i = 0; i < 26; ++i)
    {
      if (compare_string(my_buff, *(fm_table_ptr+i)) == 0)
      {
        char *fm_key_ptr_a = fm_key;
        fprintf(stdout, "%c\n", *(fm_key_ptr_a+i));
                //clear buffer
        *(my_buff) = '\0';
        *(my_buff+1) = '\0';
        *(my_buff+2) = '\0';
        break;
      }
    }
    return 1;
  }
  return 1;
}

int compare_string(char *first, const char *second)
{
 while(*first==*second)
 {
  if ( *first == '\0' || *second == '\0' )
   break;

 first++;
 second++;
}
if( *first == '\0' && *second == '\0' )
  return 0;
else
  return -1;
}
