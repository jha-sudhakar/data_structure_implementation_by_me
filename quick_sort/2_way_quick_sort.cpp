#include<assert.h>
#include<stdio.h>
#include<stdlib.h>

#include<algorithm>
#include<iostream>
using namespace std;

class Qsort
{
	private:
		int *ap, *av;
		unsigned int N;

		void init();
		void generate_random_input();
		void quick_sort(const int low, const int high);
	public:
		Qsort();
		void automated_test(unsigned int loop);
};

Qsort::Qsort()
{
	ap = av = NULL;
	N = 0;
	srand(time(NULL));
}

void Qsort::init()
{
	delete [] ap;
	delete [] av;
	ap = av = NULL;
	N = 0;
}

void Qsort::generate_random_input()
{
	N = 1 + rand()%5000;
	ap = new int[N];
	av = new int[N];

	for(int i=0; i<N; i++)
	{
		int val = rand()%100;
		ap[i] = av[i] = val;
	}
}

void Qsort::automated_test(unsigned int loop)
{
	while(loop)
	{
		cout <<"Executing loop " << loop << endl;
		init();
		generate_random_input();

#ifdef DEBUG
		cout<<"Input    => ";
		for(int i=0; i<N; i++)
			cout << ap[i] <<" ";
		cout << endl;	
#endif

		std::sort(av, av+N);
#ifdef DEBUG
		cout<<"STL sort => ";
		for(int i=0; i<N; i++)
			cout << av[i] <<" ";
		cout << endl;	
#endif

		quick_sort(0,N-1);
		for(int i=0; i<N; i++)
		{
			if(ap[i] != av[i])
			{
				cout <<"Index= " << i <<", Mismatch- expected= " << av[i] <<", actual= " << ap[i] << endl;
				assert(false);
			}
		}

#ifdef DEBUG
		cout<<"Output   => ";
		for(int i=0; i<N; i++)
			cout << ap[i] <<" ";
		cout << endl;	
#endif
		loop--;
	}
}

void Qsort::quick_sort(const int low, const int high)
{
	if(low >= high)
		return;

	int key = ap[low];
	int i =low+1, j = high;
	while(i <= j)
	{
		if(ap[i] <= key)
			i++;
		else if(ap[j] >= key)
			j--;
		else
		{
			int tmp = ap[i];
			ap[i] = ap[j];
			ap[j] = tmp;
			i++; j--;
		}
	}

	ap[low] = ap[i-1];
	ap[i-1] = key;
	quick_sort(low, i-2);
	quick_sort(i, high);
}


int main(int argc, char* argv[])
{
	if(argc != 2)	
	{
		cout << "Usage:-  exe iteration" << endl;
		return 0;
	}
	Qsort obj;
	int loop = atoi(argv[1]);
	obj.automated_test(loop);
	return 0;
}
