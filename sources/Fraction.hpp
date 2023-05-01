#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
namespace ariel{

class Fraction {
public:
    Fraction();
    
    Fraction(int num, int den );
    
    Fraction(float num);
    

   int getNumerator()const{
        return this->m_num;
    }
    int getDenominator()const{
        return this->m_den;
    }

    friend std::ostream &operator<<(std::ostream& out_put, const Fraction& franc){
        int tgcd=gcd(franc.m_num , franc.m_den);
        if(franc>=0){
        out_put << franc.m_num/tgcd<< "/" << franc.m_den/tgcd;
        }else{out_put <<'-'<< abs(franc.m_num/tgcd)<< "/" << abs(franc.m_den/tgcd);}
        if(franc.m_den==0){throw std::runtime_error("Denominator cannot be zero");}
        
        return out_put;}
   
    Fraction operator+(const Fraction& other) const;
    friend Fraction operator+( const Fraction& fracconst ,float num);
    friend Fraction operator+( float num,const Fraction& fracconst );
    ////////////////////////////
    //bool isValidStream(int numerator, int denominator);
    bool checkInteger(std::string input);
    friend std::istream &operator>>(std::istream& in_put,  Fraction& franc);
    ///////////////////
    Fraction operator-(const Fraction& other) const;
    friend Fraction operator-( const Fraction& fracconst ,float num);
    friend Fraction operator-( float num,const Fraction& fracconst );

    Fraction operator*(const Fraction& other) const;
    friend Fraction operator*(float num, const Fraction& frac);
    friend Fraction operator*( const Fraction& frac,float num );

    Fraction operator/(const Fraction& other) const;
    friend Fraction operator/(const Fraction& frac, float num);
    friend Fraction operator/(float num,const Fraction& frac);

    Fraction operator++();
    Fraction operator++(int);

    Fraction operator--();
    Fraction operator--(int);

    bool operator>(float value)const ;
    bool operator>(const Fraction& other)const ;
    friend bool operator>(float num,const Fraction& frac);
    friend bool operator>=(float num,const Fraction& frac);
    bool operator>=(float value) const;
    bool operator>=(const Fraction& other)const ;
    
    bool operator<(float value)const ;
    bool operator<(const Fraction& other) const;
    friend bool operator<(float num,const Fraction& frac);
    friend bool operator<=(float num,const Fraction& frac);
    bool operator<=(float value)const;
    bool operator<=(const Fraction& other)const ;

    bool operator!=(const Fraction& other)const ;
    friend bool operator!=(float num,const Fraction& frac);
    bool operator!=(float value)const;
    bool operator==(const Fraction& other) const;
    bool operator==(float num ) const;
    Fraction reduce();


    ////////overflows check
    int addOverflow(int val1,int val2)const;
    int subOverflow(int val1, int val2)const;
    int mulOverflow(int val1, int val2)const;
private:
    int m_num;
    int m_den;
    
    static int gcd(int num, int den);
};

}
#endif // FRACTION_HPP
