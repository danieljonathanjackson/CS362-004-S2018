#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	/* assign random char from '[','(','{',' ', 'a', 'x', '}',')',']' 
	*/
	
	char randomChar;
	int randInt=0; 
	
	// select a random integer between 0-8
	randInt = rand() % 9;
    //assign random char
	if(randInt == 0) randomChar = 91; //'[';
	if(randInt == 1) randomChar = 40; //'(';
    if(randInt == 2) randomChar = 123; //'{';
    if(randInt == 3) randomChar = 32; //' ';
    if(randInt == 4) randomChar = 97; //'a';
    if(randInt == 5) randomChar = 120; //'x';
    if(randInt == 6) randomChar = 125; // '}';
    if(randInt == 7) randomChar = 41; //')' ;
    if(randInt == 8) randomChar = 93; //']';
	
	return randomChar;
}


char *inputString()
{
    // TODO: rewrite this function
	/* return random 5 letter word, only  use letters r,e,s,t,
		the chars in 'reset'
	
	*/
	
	int i, randInt;
	char randomChar;
	//allocate string
	char* mystring;
	
	char* literal = "01234"; //initial string
	
	mystring = malloc(6 * sizeof(char));
	memset(mystring, '\0', 6);	
	sprintf(mystring, "%s", literal);
	// randomly assign char to each char in string
	for (i=0;i<5;i++){
		// select a random integer between 0-3
		randInt = rand() % 4;
		
		if(randInt == 0) randomChar = 'r';
		if(randInt == 1) randomChar = 'e';
		if(randInt == 2) randomChar = 's';
		if(randInt == 3) randomChar = 't';
			
		// assign random char to string position
		mystring[i] = randomChar;
		//printf("i = %d: randomChar = %c, mystring = %s, state = %d\n", i, randomChar, mystring);
	}
	
    return mystring;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;

  while (1)	  
  {
	tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
