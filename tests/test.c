


typedef int myInt;

void func1()
{
	char array[100500];
	char * ptr = array;
	
	
	ptr[111] = 1234;

	array[10000000] = 10;
}


void func2()
{
	char array[100500];

	array[10000000] = 10;
}