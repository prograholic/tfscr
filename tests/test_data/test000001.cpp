class Example
{
public:
	
	typedef int & reference;
	
	reference operator [] (unsigned int pos)
	{
		return mArray[pos];
	}
	
	
private:
	int mArray[100500];
};




void func1()
{
	Example e;
	
	e[2] = 10;
}