#include <iostream>
#include <map>

typedef long unsigned int lu_int;

int main(int argc, char ** argv){
	lu_int N,M;
	std::cin>>N;
	lu_int tmp;
	std::map<lu_int,lu_int> beasts;
	for(lu_int i=0;i<N;++i){
		std::cin>>tmp;
		beasts.insert(tmp);
	}
	std::cin>>M;
	lu_int count=0;
	for(lu_int i=0;i<M-1;++i){
		std::cin>>tmp;
		count=beasts.count(tmp);
		std::cout<<count<<' ';
		//if(i!=M-1) std::cout<<' ';
	}
	std::cin>>tmp;
	count=beasts.count(tmp);
	std::cout<<count<<' ';
	return 0;
}
