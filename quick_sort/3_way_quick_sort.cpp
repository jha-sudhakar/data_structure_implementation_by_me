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
		void swap(int i, int j);
		void quick_sort(const int low, const int high);
		void print_array();
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
	N = 1 + rand()%40;
	ap = new int[N];
	av = new int[N];

	for(int i=0; i<N; i++)
	{
		int val = 10+ rand()%90;
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

void Qsort::swap(int i, int j)
{
	int tmp = ap[i];
	ap[i] = ap[j];
	ap[j] = tmp;
}

void Qsort::print_array()
{
	for(int i=0;i<N; i++)
		cout << ap[i] <<" ";
	cout << endl;	
}

void Qsort::quick_sort(const int low, const int high)
{
	if(low >= high)
		return;

	int key = ap[low];
	int mid_s = low+1;
	int i=low+1,j=high;
	/*
		j:- value on its right are greater than key.
		mid_s:- value on its left are smaller than key;
	*/
	for(; i<=j; ) 
	{
		if(ap[i] <= key)
		{
			swap(i, mid_s);
			if(ap[mid_s] != key)
				mid_s++;
			i++;	
		} else
		{
			swap(i, j);
			j--;
		}	
	}
	swap(low, mid_s-1);
	mid_s--;

	//print_array();
#ifdef DEBUG
for(int k=low; k<mid_s; k++)
		cout << ap[k] << " ";
cout<<"*** ";
for(int k=mid_s; k<=j; k++)
		cout << ap[k] << " ";
cout<<"*** ";
for(int k=j+1; k<=high; k++)
		cout << ap[k] << " ";
	cout << endl;
#endif

	quick_sort(low, mid_s-1);
	quick_sort(j+1, high);
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
