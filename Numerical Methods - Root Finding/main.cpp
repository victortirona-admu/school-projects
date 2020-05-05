#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <complex>
using namespace std;

double * readText(){
    cout <<  endl << "INFO: Reading text: " << endl;
    double arr[1000];
    int i = 0;
    double digit;
    int ctr = 0;
    string inFileName, getcontent;

    while(inFileName.find(".txt") == string::npos){
        cout << "Enter filename (with extension): ";
        cin >> inFileName;
    }
    string fileName = inFileName;
    fstream inFileStr(inFileName.c_str(), ios::in);

    if(inFileStr.fail()){
        cout << "Unable to open " << inFileName << endl;
        exit(1);
    }

    if(inFileStr.is_open()){
        while(inFileStr >> digit){
            arr[i] = digit;
            ctr++;
            i++;
        }
    }
    static double info[1000];

    for(int a = 0; a < ctr; a++){
        info[a] = arr[a];
        if (fileName == "p6.txt"){
            info[a+1] = 1;
        }
    }
    return info;
}

double evaluateExponent(double base, int exponent)
{
    double pow=1;
    for (int j = 0; j<exponent; j++)
    {
        pow=pow*base;
    }
    return pow;
}

complex<double> evaluateComplexExponent(complex<double> base, int exponent)
{
    complex<double> pow=1;
    for (int j = 0; j<exponent; j++)
    {
        pow=pow*base;
    }
    return pow;
}

double absoluteValue(double number){
    if (number < 0)
    {
        number = number*(-1);
    }
    return number;
}

double * bairstow(double info[], double r, double s)
{
    int lenInfo = info[0];
    double b_n[lenInfo+2];
    double c_n[lenInfo+2];
    static double rs[2]; //just to make sure r and s aren't equal to rs
    double err_r = 100;
    double err_s = 100;
    int ctr = 1;
    b_n[lenInfo+2] = 0;
    b_n[lenInfo+1] = 0;
    c_n[lenInfo+2] = 0;
    c_n[lenInfo+1] = 0;

    while (((err_r > 0.000000001) || (err_s > 0.000000001)))
    {
        //lists b_n from lowest power to highest power with two 0s at the end
        for (int i=lenInfo; i>=0; i--)
        {
            //computing for the b and c values in bairstow's method
            b_n[i] = info[i+1] + r*b_n[i+1] + s*b_n[i+2];
            c_n[i] = b_n[i] + r*c_n[i+1] + s*c_n[i+2];
        }

        //computing for the new r and s values
        rs[0] = r+(((b_n[0]*c_n[3])-(b_n[1]*c_n[2]))/((c_n[2]*c_n[2])-(c_n[1]*c_n[3])));
        rs[1] = s+(((b_n[1]*c_n[1])-(b_n[0]*c_n[2]))/((c_n[2]*c_n[2])-(c_n[1]*c_n[3])));

        err_r = absoluteValue(((rs[0]-r)/rs[0]))*100;
        err_s = absoluteValue(((rs[1]-s)/rs[1]))*100;

        r = rs[0];
        s = rs[1];
        ctr++;
    }
    return rs;
}

double * twoSyntheticDivision(double polynomial[], double r, double s){
    int N = polynomial[0];

    double a = polynomial[N+1];
    for(int i = 1; i<=N+1; i++){
        polynomial[i]=polynomial[i]/a;
    }

    double newPolynomial1[N+1];
    newPolynomial1[0] = N-1;
    static double newPolynomial2[1000];
    newPolynomial2[0] = N-2;
    double b = -r, c = -s;
    double rootRealPart1, rootRealPart2, rootImPart1, rootImPart2, currentRemainder = 1, remainderR1, remainderR2, remainderI1, remainderI2;
    double remainderReal1[N+1];
    double remainderIm1[N+1];
    double remainderReal2[N];
    double remainderIm2[N];

    //if roots are imaginary
    if(b*b-4*c<0){
        rootRealPart1 = -b/2;
        rootRealPart2 = -b/2;
        rootImPart1 = sqrt(-(b*b-4*c))/2;
        rootImPart2 = -rootImPart1;

        //first division
        remainderReal1[N] = 1;
        remainderIm1[N] = 0;
        for(int i = N-1; i>0; i--){
            remainderReal1[i] = remainderReal1[i+1]*rootRealPart1 - rootImPart1*remainderIm1[i+1] + polynomial[i+1];
            remainderIm1[i] = rootRealPart1*remainderIm1[i+1] + rootImPart1*remainderReal1[i+1];
        }
        remainderR1 = remainderReal1[1]*rootRealPart1 - rootImPart1*remainderIm1[1] + polynomial[1];
        remainderI1 = rootRealPart1*remainderIm1[1] + rootImPart1*remainderReal1[1];

        //second division
        newPolynomial2[N-1] = 1;
        for(int i = N-2; i>0; i--){
            newPolynomial2[i] = remainderReal1[i+1]+newPolynomial2[i+1]*rootRealPart1;
        }
        //getting remainder
        remainderReal2[N-1] = 1;
        remainderIm2[N-1] = 0;
        for(int i = N-2; i>0; i--){
            remainderReal2[i] = remainderReal2[i+1]*rootRealPart2 - rootImPart2*remainderIm2[i+1] + remainderReal1[i+1];
            remainderIm2[i] = rootRealPart2*remainderIm2[i+1] + rootImPart2*remainderReal2[i+1] + remainderIm1[i+1];
        }
        remainderR2 = remainderReal2[1]*rootRealPart2 - rootImPart2*remainderIm2[1] + remainderReal1[1];
        remainderI2 = rootRealPart2*remainderIm2[1] + rootImPart2*remainderReal2[1] + remainderIm1[1];

    }

    //if roots are real
    else{
        //quadratic formula
        rootRealPart1 = (-b + sqrt(b*b-4*c))/2;
        rootRealPart2 = (-b - sqrt(b*b-4*c))/2;
        rootImPart1 = 0;
        rootImPart2 = 0;
        remainderI1 = 0;
        remainderI2 = 0;

        //first division
        newPolynomial1[N] = 1;
        for(int i = N-1; i>0; i--){
            newPolynomial1[i] = currentRemainder*rootRealPart1 + polynomial[i+1];
            currentRemainder = newPolynomial1[i];
        }
        remainderR1 = currentRemainder*rootRealPart1 + polynomial[1];

        //second division
        newPolynomial2[N-1] = 1;
        currentRemainder = 1;
        for(int i = N-2; i>0; i--){
            newPolynomial2[i] = currentRemainder*rootRealPart2 + newPolynomial1[i+1];
            currentRemainder = newPolynomial2[i];
        }
        remainderR2 = currentRemainder*rootRealPart1 + polynomial[1];
    }
    //newPolynomial2 is the old polynomial divided by the quadratic root
    //roots are (rootRealPart1, rootImPart1) and (rootRealPart2, rootImPart2)
    return newPolynomial2;
}

double * returnTwoRoots(double r, double s){
    static double twoRoots [4];
    double b = -r, c = -s;
    //if roots are imaginary
    if(b*b-4*c<0){
        twoRoots[0] = -b/2;
        twoRoots[1] = sqrt(-(b*b-4*c))/2;
        twoRoots[2] = -b/2;
        twoRoots[3] = -twoRoots[1];
    }

    else{
        //quadratic formula
        twoRoots[0] = (-b + sqrt(b*b-4*c))/2;
        twoRoots[1] = 0;
        twoRoots[2] = (-b - sqrt(b*b-4*c))/2;
        twoRoots[3] = 0;
    }
    return twoRoots;
}

void evaluateFunction(int lenOrigPoly, double roots[], double origInfo[]){
    complex<double> cmplx;
    complex<double> sum;

    for (int i = 0; i < lenOrigPoly*2; i=i+2){
        double a = roots[i];
        double b = roots[i+1];
        cmplx.real(a);
        cmplx.imag(b);
        int exp = lenOrigPoly;
        sum=0;
        for(int j=1; j<lenOrigPoly+2; j++){
        sum = sum + origInfo[lenOrigPoly+2-j]*evaluateComplexExponent(cmplx,exp);
        exp--;
        }
        cout << "f(" << roots[i] << ", " << roots[i+1] << ") = " << abs(sum) << endl;
    }
}

int main()
{
    int x;
    //passing the array in the function into an array in main
    double *addressOfInfo = readText(); //accesses the address of the static array
    double info[1000];
    double origInfo[1000];
    for (int i = 0; i < *(addressOfInfo)+3; i++)
    {
        origInfo[i] = *(addressOfInfo + i);
        info[i] = *(addressOfInfo + i);
    }

    int rootNumber = 0; //counter for how many roots have been computed for multiplied by 2 (for the imag. and real parts)
    int lenOrigPoly = info[0];
    int lenInfo = info[0];
    double roots[lenOrigPoly*2];

    while(info[0] >= 2)
    {
    double r= (info[lenInfo]/info[lenInfo+1]); //initial values of r and s from the website
    double s= (info[lenInfo-1]/info[lenInfo+1]); //initial values of r and s from the website
    if (origInfo[lenOrigPoly+2] == 1){
        r=1;
        s=1;
    }
    double *rs = bairstow(info,r,s); //accesses the address of the static array
    r = *(rs);
    s = *(rs+1);

    double *addressOfRoots = returnTwoRoots(r, s);
    for (int i = 0; i < 4 ; i++){
        roots[i+rootNumber] = *(addressOfRoots+i);
    }
    rootNumber = rootNumber+4;

    double *addressOfDivision = twoSyntheticDivision(info,r,s);
    for (int i = 0; i < *(addressOfDivision)+2; i++)
    {
        info [i] = *(addressOfDivision + i);
    }

    lenInfo = info[0];
    }

    if (lenInfo == 1){
        roots[rootNumber] = -info[1];
        roots[rootNumber+1] = 0;
    }



    //print
    cout << "Polynomial:" << endl;
    for(int i = lenOrigPoly+1; i >0; i--){
        cout << origInfo[i] << " x^" << i-1 << endl;
    }

    cout << endl << "Roots:" << endl;
    for (int i = 0; i < lenOrigPoly*2; i=i+2){
        cout << "(" << roots[i] << ", " << roots[i+1] << ")" << endl;
    }

    cout << endl << "Evaluating polynomials at identified roots:" << endl;
    evaluateFunction(lenOrigPoly, roots, origInfo);
    
    cin>>x; //added to prevent console application from closing immediately; input anything into x and the console application will exit
    
    return 0;
}


