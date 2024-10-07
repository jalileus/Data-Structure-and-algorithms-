/*
implement a class complex number with operations
*/
#include<iostream>
#include<cmath>
using namespace std;

class complex{
private:
    double real,imag;
public:
    complex(double r = 0, double i = 0)
    {
        real = r;
        imag = i;
    }

    friend ostream & operator << (ostream &out, const complex& other);
    friend istream & operator >> (istream &in, complex& other);

    complex(const complex& other):real(other.real),imag(other.imag){}

    complex operator + (const complex& other)
    {
        cout<<"the Sum of the two numbers: ";

        complex res;
        res.real = real + other.real;
        res.imag = imag + other.imag;
        return res;
    }

    complex operator - (const complex& other)
    {
        cout<<"the Subtraction of the two numbers: ";

        complex res;
        res.real = real - other.real;
        res.imag = imag - other.imag;
        return res;
    }

    complex operator * (const complex& other)
    {
        cout<<"the Multiplication of the two numbers: ";

        complex res;
        res.real = (real)*(other.real) - (imag)*(other.imag);
        res.imag = (imag)*(other.real) + (real)*(other.imag);
        return res;
    }

    complex operator / (const complex& other)
    {
        cout<<"the Division of the two numbers: "; 
        complex res;
        res.real = (real*other.real + imag*other.imag) / (pow(other.real,2) + pow(other.imag,2));
        res.imag = (imag*other.real - real*other.imag) / (pow(other.real,2) + pow(other.imag,2));
        return res;
    }
};

ostream & operator << (ostream &out,const complex &other)
{
    if(other.imag<0 && other.imag != 0 && other.real != 0)
    {   
        if(other.imag == -1)
        {
        out<<other.real<<" - i";
        }
        else
        {
        out<<other.real<<other.imag<<"i";
        }
    }

    else if(other.imag == 0)
    {
        out<<other.real;
    }  

    else if(other.real == 0)
    {
        if(other.imag == 1)
        {
            out<<"i";
        }
        else if(other.imag == -1)
        {
            out<<"-i";
        }
        else
        {
            out<<other.imag<<"i";
        }
    }

    else
    {
        if(other.imag == 1)
        {
            out<<other.real<<" + "<<"i";   
        }
        else
        {
            out<<other.real<<" + "<<other.imag<<"i";
        }
    }
    return out;
}

istream & operator >> (istream &in,complex &other)
{
    cout<<"enter the real part:"<<endl;
    in>>other.real;
    cout<<"enetr the imaginary part:"<<endl;
    in>>other.imag;
    return in;
}

int main(){
    complex c1,c2;
    cout<<"input the first number:"<<endl;
    cin>>c1;
    cout<<"the first number is:"<<endl;
    cout<<c1<<endl;

    cout<<"input the second number:"<<endl;
    cin>>c2;
    cout<<"the second number is:"<<endl;
    cout<<c2<<endl;

    const complex c3 = c1 + c2;
    cout<<c3<<endl;
    const complex c4 = c1 - c2;
    cout<<c4<<endl;
    const complex c5 = c1 * c2;
    cout<<c5<<endl;
    const complex c6 = c1 / c2;
    cout<<c6<<endl;

    return 0;
}
