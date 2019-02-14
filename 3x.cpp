#include "G7R.h"
#include <iostream>
#include <random>
#include <cstring>

using namespace std;

const double ga=0.07667533/0.1873479;
const double gc=0.09463397/0.1873479;
const double gt=0.0160386/0.1873479;
const double ca=0.07334453/0.22282149;
const double cg=0.08144008/0.22282149;
const double ct=0.06803688/0.22282149;
const double ag=0.1352778/0.19424901;
const double ac=0.03321736/0.19424901;
const double at=0.02575385/0.19424901;
const double ta=0.14717589/0.39558158;
const double tc=0.10889809/0.39558158;
const double tg=0.13950761/0.39558158;

const double rate=0.0001;

random_device rd;
mt19937 e2(rd());
uniform_real_distribution<> dist(0, 1);

inline
char mutate(char i) {
	double r=dist(e2);
	switch(i) {
		case 'G':if(r<ga) return 'A'; else if(r<ga+gc) return 'C'; else return 'T';
		case 'C':if(r<ca) return 'A'; else if(r<ca+cg) return 'G'; else return 'T';
		case 'A':if(r<ag) return 'G'; else if(r<ag+ac) return 'C'; else return 'T';
		case 'T':if(r<ta) return 'A'; else if(r<ta+tc) return 'C'; else return 'G';
	};

	cerr<<"Error! "<< i << endl; exit(999);
}

inline
int trial() {
	unsigned int pos=43;
	unsigned int count=0;
	char *triple;
	while(pos<11337) {
		if(pos>=7537 && pos<7545) { pos=7545; }
                if(pos==5695) pos+=3;

		triple=mutant+pos*sizeof(char);
		if(dist(e2)<rate) triple[0]=mutate(triple[0]);
		if(dist(e2)<rate) triple[1]=mutate(triple[1]);
		if(dist(e2)<rate) triple[2]=mutate(triple[2]);

		if     (triple[0]=='T'&&triple[1]=='A'&&triple[2]=='G') { count++; }
		else if(triple[0]=='T'&&triple[1]=='A'&&triple[2]=='A') { count++; }
		else if(triple[0]=='T'&&triple[1]=='G'&&triple[2]=='A') { count++; }
		pos+=3;
	}

	memcpy(mutant,genome,sizeof(mutant));
	return (count>0);
}

int main(int argc, char** argv) {
	unsigned int sum=0;
	for( int c=0; c<1000000; c++) {
		sum+=trial();
	}
	cout << sum << endl;
}


