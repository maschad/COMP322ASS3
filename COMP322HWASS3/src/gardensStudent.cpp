#include "gardens.h"
#include <stack>
#include <iostream>
#include <math.h>

 /* 0-credit */
Fraction ContinuedFraction::getApproximation(unsigned int k) const {
	cf_int temp;
    Fraction toRet;
	unsigned int i = k;


	while( i > 1)
    {
    	if(i == k)
    	{
    		toRet.numerator = 1;
    		toRet.denominator = next();
    		i--;
    	}
    	else
    	{
    		temp = next();
    		toRet.numerator = toRet.denominator;
    		toRet.denominator = toRet.denominator*next() + temp;
    		i--;
    	}
    	if(i == 1)
    	{
    		toRet.denominator = toRet.denominator*next() + temp;
    	}
    }

    return toRet;
}


RationalCF::RationalCF(Fraction f): PeriodicCF({})
{
	cf_int t,t1;
	cf_int b = f.denominator;
	cf_int a = f.numerator;
	while( b != 0)
	{
		t = a/b;
		a-= t*b;
		t1 = a;
		a = b;
		b = t1;
		fixedPart.push_back(t);
	}
}

RationalCF::~RationalCF() {
}

/* QUESTION 3*/

cf_int PeriodicCF::next() const {
	cf_int i = *iteratorPosition;

	(*iteratorPosition)++;

	if(i < fixedPart.size())
	{
		return fixedPart.at(i);
	}
	else
	{
		return periodicPart.at((i- fixedPart.size()) % periodicPart.size());
	}

}

bool PeriodicCF::hasNoMore() const {
	return (*iteratorPosition >= fixedPart.size() && periodicPart.size() == 0);
}

void PeriodicCF::resetIterator() const {
    *iteratorPosition = 0;
}

PeriodicCF::~PeriodicCF() {
    delete iteratorPosition;
}



/* QUESTION 4*/

MagicBoxCF::MagicBoxCF(ContinuedFraction const* f, unsigned long aParam, unsigned long bParam): a(aParam) , b(bParam)
{
	mbnums = new cf_int[4];
	this->boxedFraction = f;
	resetIterator();
}

cf_int MagicBoxCF::next() const {

	while( ((mbnums[2] == 0 || mbnums[3] == 0) && !(mbnums[2] == 0 && mbnums[3] == 0)) ||
            (mbnums[2] != 0 && mbnums[3] != 0 && mbnums[0] / mbnums[2] != mbnums[1] / mbnums[3]) ) {
		// while the indeces are not yet ready to spit q
		if(boxedFraction->hasNoMore)
		{
            // no more integers to spit from cf
			mbnums[0] = mbnums[1];
			mbnums[2] = mbnums[3];
            continue;
		}
		//read p
			cf_int p = next();
		//change box accordingly
		int i = mbnums[1],
            j = mbnums[0] + mbnums[1] * p,
			k = mbnums[3],
			l = mbnums[2] + mbnums[3] * p;
		mbnums[0] = i;
		mbnums[1] = j;
		mbnums[2] = k;
		mbnums[3] = l;
    }
    // if we reached the end of the cf - return -1
	if(mbnums[2] == 0 && mbnums[3] == 0) return -1;

    // return q and change box accordingly
	int q = mbnums[0] / mbnums[2];
	int i = mbnums[2],
		j = mbnums[3],
		k = mbnums[0] - mbnums[2] * q,
		l = mbnums[1] - mbnums[3] * q;
	mbnums[0] = i;
	mbnums[1] = j;
	mbnums[2] = k;
	mbnums[3] = l;
	return q;

}

bool MagicBoxCF::hasNoMore() const {
	return (mbnums[2] == 0 && mbnums[3] == 0);
}

void MagicBoxCF::resetIterator() const {
	mbnums[0] = a;
	mbnums[1] = b;
	mbnums[2] = 1;
	mbnums[3] = 0;
	boxedFraction->resetIterator();
}

MagicBoxCF::~MagicBoxCF() {
    delete[] mbnums;
}



/* QUESTION 5*/

ostream &operator<<(ostream& outs, const ContinuedFraction &cf) {
	int length = 10;


	bool first = true; //true to separate the first item with a ;
	// do the fixed part first
	cout << "[";
	cf.resetIterator();

	while(!cf.hasNoMore())
	{
		cout << cf.next();
		if(--length == 0)
		{
			break;
		}
		else
		{
			cout << ((first) ? "; " : ", ");
		}
		first = false;
	}
	cout << "]";
	return outs;
}


/* QUESTION 6 */

float Flower::getAngle(unsigned int k) const {
    //TODO
}

Flower::Flower(const ContinuedFraction *f, unsigned int apxLengthParam) : apx_length(apxLengthParam)
{

}

Seed Flower::getSeed(unsigned int k) const {
    //TODO
}

vector<Seed> Flower::getSeeds(unsigned int k) const {
    //TODO
}


Flower::~Flower() {
    //TODO
}

/* QUESTION 7*/

void Flower::writeMVGPicture(ostream &out, unsigned int k, unsigned int scale_x, unsigned int scale_y) const {
    //TODO
}





