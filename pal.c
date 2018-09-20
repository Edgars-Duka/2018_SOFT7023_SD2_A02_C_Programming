
//--------------------------------------------------
// INCLUDE SECTION
//--------------------------------------------------
#include "pal.h"



//--------------------------------------------------
// gen_num
//--------------------------------------------------
int gen_num(int lb, int ub) {
	//1. We create the output variable with an initial value.
	int res = 0;

	//2. We assign num to a random value in the desired range
	res = (rand() % (ub - lb)) + lb;

	//3. We return the output variable
	return res;
}

//--------------------------------------------------
// my_getchar
//--------------------------------------------------
char my_get_char() {
	//1. We create the output variable with the value the user has input by keyboard
	char res = getchar();

	//2. We discard any extra character the user has input by keyboard
	boolean finish = False;
	char dummy_char = ' ';

	while (finish == False) {
		dummy_char = getchar();
		if (dummy_char == '\n')
			finish = True;
	}

	//3. We return the output variable
	return res;
}

//--------------------------------------------------
// initialise_array
//--------------------------------------------------
void initialise_array(int a[6], int num) {
	//creating an array int 5 because there are 6 numbers 0-5 (int doesnt count 0 as a number)
	int i = 5;
	while (i >= 0)
	{
	//  checks the remainder of a division from array and decreces the int by 1. 
	//(does it for each number of the array list till it hits 0)
		a[i] = num % 10;
		num = num / 10;
		i = i - 1;
	}
}

//--------------------------------------------------
// is_pal
//--------------------------------------------------
boolean is_pal(int a[6]) {
	//1. create output variable +initial value to True
	boolean b = True;

	//2.checking if the number is palindrome or not.
	//if not, do the loop all over again till it is palindrme

	int i = 0;
	int size = 6;

	while ((b == True) && (i < (size/2)))//if inside of brackets is TRUE then continue
	{
		if (a[i] != a[(size-1) - i])
			b = False;
		else
			i = i + 1;
	}
	return b;
}

//--------------------------------------------------
// ask_for_command
//--------------------------------------------------
char ask_for_command() {
	char res = ' ';

	// valid command while if loop, easy bit first... if false, print error + asking user for a new valid command
	boolean valid = False;
	while (valid == False) 
	{
		printf("NEW MOVEMENT: Please enter a valid command by keyword:\n");
		printf("Valid commands are: a\td\tw\tx\n");
	
	// have to use this due to cant change other classes where its used 
		res = my_get_char();

		//If the new command is a valid (a,d,w or s), update valid to ture and return res
		if ((res == 'a', 'A') || (res == 'd', 'D') || (res == 'w', 'W') || (res == 'x', 'X'))
			valid = True;
	}
	return res;
}

//--------------------------------------------------
// process_movement
//--------------------------------------------------
//
// int a[6] = actual array
// int** p_p = pointer to a pointer ( used to change the value inside without changing the original value) 
// int * p_nm = pointer to update the actual count of how many moves the user took
// char c = asking user for command with specific buttons ( a, d, w, x)



void process_movement(int a[6], int** p_p, int* p_nm, char c){

	//1. using switch statement for different valid commands (easiest option)
	switch (c) {

	case 'A':
	case 'a':
		// If we are not in the 1st position (left) 
		if ((*p_p) > &a[0]) {
			//moveing pointer once to the left 
			(*p_p) = (*p_p) - 1;
			
			//update the number of movements
			(*p_nm) = (*p_nm) + 1;

			//clearing the screen with 50 emptylines each time a valid comand has happened 
			for (int i = 0; i < 50; i++)
				printf("\n");
		}
		break;

	case 'D':
	case 'd':
		//If we are not in the last position (right)		
		if ((*p_p) < (&a[0] + 5)) {
			//moveing pointer once to the right 
			(*p_p) = (*p_p) + 1;
			
			//update the number of movements
			(*p_nm) = (*p_nm) + 1;

			//clearing the screen with 50 emptylines each time a valid comand has happened 
			for (int i = 0; i < 50; i++)
				printf("\n");
		}
		break;

	case 'W':
	case 'w':
		//If we are not in the top diget (9)		
		if ((**p_p) < 9) {
			// incrementing previouse number by 1
			(**p_p) = (**p_p) + 1;
			
			//update the number of movements
			(*p_nm) = (*p_nm) + 1;

			//clearing the screen with 50 emptylines each time a valid comand has happened 
			for (int i = 0; i < 50; i++)
				printf("\n");
		}
		break;

	case 'X':
	case 'x':
		//If we are not in the bottom diget (0)		
		if ((**p_p) > 0) {
			// decrementing previouse number by 1
			(**p_p) = (**p_p) - 1;


			//update the number of movements
			(*p_nm) = (*p_nm) + 1;

			//clearing the screen with 50 emptylines each time a valid comand has happened 
			for (int i = 0; i < 50; i++)
				printf("\n");

		}
		break;
	}

}

//--------------------------------------------------
// print_status
//--------------------------------------------------
void print_status(int a[6], int* p, int nm) {

	//clearing the screen with an emptyline each time a invalid comand has happened 
		printf("\n");

	//banner
	printf("\n------ Game Status -------\n");

	// printing array actual numbers
	printf(" Number = { ");

	for (int i = 0; i < 6; i++) {
		printf("%d ", a[i]);
	}
	printf("}\n");

	//Print pointer ( spaces for realigning the pointer into place) 
	printf("            ");


	// int spaces = ìnt pointer -  int pointer array position 0 
	int spaces = (int)(p - &a[0]);

	// Pointer hopping movement  giving it 2 spaces and responding with 2 spaces each time 
	for (int i = 0; i < (2 * spaces); i++)
		printf(" ");
	printf("^");
	printf("\n");

	//total number of movements
	printf(" Num mov = %d\n", nm);

	printf("--------------------------\n");
}

//--------------------------------------------------
// user_game_palindrome
//--------------------------------------------------
void user_game_palindrome(int pal_num) {
	
	//1. calling all variables/ classes for the game
	int a[6];
	initialise_array(a, pal_num);
	int* p = a + gen_num(0, 6);
	int num_mov = 0;

	// When array is playing (not palindrome)
	char game = ' ';
	print_status(a, p, num_mov);

	while (!is_pal(a)) {
		
		game = ask_for_command();
		// Process the command from above
		process_movement(a, &p, &num_mov, game);
		// Print current status
		print_status(a, p, num_mov);
	}

	// Game won banner
	printf("\n-------------------------\n");
	printf("------- SOLVED! ---------\n");
	printf("-------------------------\n");

}