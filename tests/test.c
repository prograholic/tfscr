



char hhhh[200] = {0, 1, 2}


void func1(const int * bugoga)
{
	char array[100500] = {1, 2, 3};
	char * ptr = array;
	
	
	ptr[111] = 1234;

	array[10000000] = 10;
}


void func2()
{
	char array[100500];

	array[10000000] = 10;
}