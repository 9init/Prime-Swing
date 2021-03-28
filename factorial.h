#include <math.h>

const int smallOddSwing[] = {
    1,1,1,3,3,15,5,35,35, 315, 63, 693, 231, 3003, 429, 6435, 6435,
    109395,12155,230945,46189,969969,88179,2028117,676039,16900975,
    1300075,35102025,5014575,145422675,9694845,300540195,300540195 };

const int smallOddFactorial[] = {
    1,1,1,3,3,15,45,315, 315, 2835, 14175, 155925, 467775, 6081075,
    42567525, 638512875, 638512875 };

struct factorials{
    long int oddFact;
    long int sqrOddFact=1;
};

long int product(long int m, long int len){
    if (len == 1) return m;
    if (len == 2) return m * (m - 2);
    long int hlen = len >> 1;
    return product(m-(hlen*2), len-hlen) * product(m, hlen);
}

factorials oddFactorial(long int n){
    factorials fact;

    if (n < 17){
        fact.oddFact = smallOddFactorial[n];
        fact.sqrOddFact = smallOddFactorial[(long int) n/2];
    }else{
        factorials f = oddFactorial((long int) n/2);
        fact.oddFact = f.sqrOddFact;
        long int oddSwing;
        if (n < 33) 
            oddSwing = smallOddSwing[n]; 
        else{
            long int len = (n - 1); // 4
            if ((n % 4) != 2) len += 1;
            long int high = n - ((n + 1) & 1);
            oddSwing = product(high, len); // oldOddFact
        }
        fact.oddFact = (long int)(pow(fact.sqrOddFact,2 )) * oddSwing;
    }
    return fact;
}

long int factorial(long int n){
    if (n == 0) return 1;
    if (n <  0) return 0;
    
    long int N = n, bits = n;
    while (N != 0){
        bits -= (N & 1);
        N >>= 1;
    }
    factorials F = oddFactorial(n);
    return F.oddFact * pow(2, bits);
}
