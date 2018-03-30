#include <set>
#include <iostream>
typedef long unsigned int lu_int;

lu_int modl(lu_int a, lu_int b, lu_int c){
	lu_int min =  (a<b) ? a : b;
	lu_int max =  (a>b) ? a : b;
	lu_int modul=max%c;
	lu_int res=0;
	for(unsigned int i=0;i<8*sizeof(lu_int);i++){
		if((min>>i)==0) break;
		if (((min & (1<<i)) >>i)!=0) res+=modul;
		(res>=c) ? res-=c : 0;
		//if(res>=c) res-=c;
		modul*=2;
		(modul>=c) ? modul-=c : 0;
	}
	return res;
}


int main(int argc, char ** argv){
	lu_int A, N, serial;
	lu_int B=1.e+9+7;
	std::cin>>A>>N;
	const unsigned int year=2015;
	const unsigned int month=9;
	const unsigned int day=24;
	const unsigned int max_hour=24;
	const unsigned int max_min=60;
	const unsigned int max_sec=60;
	const lu_int max_num=max_hour*max_min*max_sec;
	std::set<lu_int> ser_set; 
	lu_int a[6];
	a[0]=A%B;
	for(int i=1;i<6;++i) a[i]=modl(a[i-1],a[0],B);
	lu_int date= modl(year,a[0],B)+modl(month,a[1],B)+modl(day,a[2],B);
	if(date>=B) date%=B; 
	for(unsigned int i=0;i<max_num;i++){
		lu_int date_tmp =date;
		int hour=i/(max_min*max_sec);
		int min=(i%(max_min*max_sec))/(max_sec);
		int sec=i%max_sec;
		date_tmp+=(modl(hour,a[3],B)+modl(min,a[4],B)+modl(sec,a[5],B));
		ser_set.insert(date_tmp%B);
	}
	lu_int num=0;
	for(unsigned int i=0;i<N;i++){
		std::cin>>serial;
		if(ser_set.find(serial)!=ser_set.end()) ++num;
	}
	std::cout<<num;
	return 0;
	
}
