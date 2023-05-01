#include "Fraction.hpp"

#include <iostream>
#include <stdexcept>
#include <limits>
using namespace ariel;
using namespace std;
#define MAX_INT  std::numeric_limits<int>::max()
#define MIN_INT  std::numeric_limits<int>::min()

Fraction::Fraction() : m_num(0), m_den(1) {
    
}
Fraction::Fraction(float num){
    
    this->m_num = (num * 1000); // convert the float to an integer
    this->m_den = 1000;

    
    
}
//Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}
// Fraction(double value) {
//             int sign = (value < 0) ? -1 : 1;
//             value = fabs(value);
//             //int whole = static_cast<int>(value);
//             numerator = whole * sign;
//             value -= whole;
//             while (fabs(round(value) - value) > 0.0001) {
//                 value *= 10;
//                 numerator *= 10;
//             }
//             denominator = static_cast<int>(round(value));
//             simplify();
//         }
// operator double() const { return static_cast<double>(numerator) / denominator; }
Fraction::Fraction(int num, int den):m_num(num),m_den(den) {
    if (den == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    if (den < 0 ) {
        num = -num;
        den = -den;
        this->m_num = num;
        this->m_den = den;
    }
   
    
    
}

Fraction Fraction::reduce() {
    
    int gcd = Fraction::gcd(m_num, m_den);
    if(gcd!=0 && m_num!=0){
        m_num /= gcd;}
    m_den /= gcd;

    return *this;
}

int Fraction::gcd(int num, int den) {
    if(num!=0){
    return den == 0 ? num : gcd(den, num % den);}
    return 1;
}
// std::istream& ariel::operator>>(std::istream& in_put,  Fraction& franc){
// char temp='/';
//        int num=0;
//        int den=0;
//        in_put >> num >> den;
//        if(franc.getDenominator()==0){throw std::runtime_error("Denominator cannot be zero");}
//         franc=Fraction(franc.getNumerator(),franc.getDenominator());
//         return in_put;
// }
// ostream &operator<<(ostream &os, const Fraction &f) {
//     os << to_string(f.num());
//     if (f.den() != 1) {
//         os << '/' << to_string(f.den());
//     }
//     return os << m_num << '/' << m_den;
// }
//////////////////////////////////////////////////
bool Fraction::checkInteger(std::string input){
    bool isNeg=false;
    size_t itr=0;
    if(input[0] == '-')
    {
        isNeg=true;
        itr=1;
    }
 
    for(size_t i = itr ; i < input.length() ; i++)
    {
        if(!std::isdigit(input[i])){
            return false;
        }
    }
    return true;
}
std::istream& ariel::operator>>(std::istream& stream, ariel::Fraction& other){
    int numerator = 0, denominator = 0;
    stream >> numerator >> denominator ;
    bool check = false;//isValidStream(numerator, denominator);
    bool isNumerator = other.checkInteger(std::to_string(numerator));
    bool isDenominator = other.checkInteger(std::to_string(denominator));
    check= (isNumerator && isDenominator && (denominator != 0));
    if (check == true) {
        other = Fraction(numerator, denominator).reduce();
    }else {
        throw std::runtime_error("Invalid input format");
    }
    return stream;
}
// ############### UTILS ###############

// bool ariel::Fraction::isValidStream(int numerator, int denominator){
//     bool isNumerator = checkInteger(std::to_string(numerator));
//     bool isDenominator = checkInteger(std::to_string(denominator));
//     return isNumerator && isDenominator && (denominator != 0);
// }




/////////////////////////////////////////////////////
Fraction Fraction::operator+(const Fraction& other) const {
    
    int num =addOverflow(mulOverflow(m_num, other.m_den) , mulOverflow(m_den, other.m_num));
    int den = mulOverflow(m_den, other.m_den);
    
    return Fraction(num, den).reduce();
}
Fraction ariel::operator+( const Fraction& fracconst ,float num){
   Fraction temp(num);

    return (fracconst+temp).reduce();
}
Fraction ariel::operator+(float num,const Fraction& fracconst ){
   Fraction temp(num);

    return (fracconst+temp).reduce();
}
Fraction Fraction::operator-(const Fraction& other) const {
    int num =subOverflow(mulOverflow(m_num, other.m_den) , mulOverflow(m_den , other.m_num));
    int den =mulOverflow(m_den , other.m_den);
    return Fraction(num, den).reduce();
}

Fraction ariel::operator-(const Fraction& other, float num) {
    Fraction temp(num);
    return (other-temp).reduce();
}
Fraction ariel::operator-(float num,const Fraction& other)  {
    Fraction temp(num);
    return (temp-other).reduce();
}


Fraction Fraction::operator*(const Fraction& other) const {
    int first_gcd=gcd(m_num,m_den);
    int second_gcd=gcd(other.getDenominator(),other.getNumerator());
    int num =mulOverflow(m_num/first_gcd ,other.m_num/second_gcd);
    int den = mulOverflow( m_den/first_gcd ,other.m_den/second_gcd);
    return Fraction(num, den).reduce();
}
Fraction ariel::operator*(float num,const Fraction& franc){
    Fraction temp(num);
    
    return (franc*temp).reduce();
}

Fraction ariel::operator*(const Fraction& franc,float num){
    Fraction temp(num);
    
    return (franc*temp).reduce();
}
Fraction Fraction::operator/(const Fraction& other) const {
    int first_gcd=gcd(m_num,m_den);
    int second_gcd=gcd(other.getDenominator(),other.getNumerator());
    int num = mulOverflow( m_num/first_gcd , other.m_den/second_gcd);
    int den =mulOverflow(m_den/first_gcd , other.m_num/second_gcd);
    if(den==0){throw std::runtime_error("Denominator cannot be zero");}
    return Fraction(num, den).reduce();
}
Fraction ariel::operator/(const Fraction& frac, float num) {
    // Convert the number to a fraction
    Fraction num_fraction(num);

    
   

    return (frac/num_fraction).reduce();
}
Fraction ariel::operator/( float num,const Fraction& frac) {
    // Convert the number to a fraction
    //if(num==0){throw std::runtime_error("cant dividing zero");}
    Fraction num_fraction(num);

    

    return (num_fraction/frac).reduce();
}

Fraction Fraction::operator++() {
    m_num += m_den;
    return (*this).reduce();
}

Fraction Fraction::operator++(int) {
    Fraction temp(*this);
    ++(*this);
    return temp.reduce();
}

Fraction Fraction::operator--() {
    m_num -= m_den;
    return (*this).reduce();
}

Fraction Fraction::operator--(int) {
    Fraction temp(*this);
    --(*this);
    return temp.reduce();
}


bool Fraction::operator>( float value)const{
    Fraction other(value);
    return ((m_num * other.m_den) > (other.m_num * m_den));
}
bool Fraction::operator>(const Fraction& other) const{


    return (m_num*other.m_den > other.m_num* m_den);
}

bool Fraction::operator>=(const Fraction& other) const{


    return (m_num*other.m_den >= other.m_num* m_den);
}
bool Fraction::operator>=(float value)  const{
    Fraction other(value);
    return ((m_num * other.m_den) >= (other.m_num * m_den));
    
}
bool ariel::operator>(float num,const Fraction& frac){
    Fraction temp(num);
    return (temp>frac);
}
bool ariel::operator>=(float num,const Fraction& frac){
    Fraction temp(num);
    return ((temp.m_num * frac.m_den) >= (frac.m_num * temp.m_den));
}

bool Fraction::operator<(float value)const  {
    Fraction other(value);
    return (m_num * other.m_den < other.m_num * m_den);
}

bool Fraction::operator<(const Fraction& other)const {


    return (m_num * other.m_den < other.m_num * m_den);
}
bool Fraction::operator<=(const Fraction& other)const {

    
    return ((m_num * other.m_den) <= (other.m_num * m_den));
}
bool Fraction::operator<=(float value) const {
    Fraction other(value);
    return ((m_num * other.m_den) <= (other.m_num * m_den));
}

bool ariel::operator<(float num,const Fraction& frac){
    
    return (frac>num);
}
bool ariel::operator<=(float num,const Fraction& frac){
    
    return (frac>=num);
}
//NE
bool Fraction::operator!=(const Fraction& other)const {
    return (m_num*other.m_den != other.m_num* m_den);
}
bool ariel::operator!=(float num,const Fraction& frac){
    //Fraction temp=Fraction(num);
    return ((frac-num)!=0);
    };

bool Fraction::operator!=(float value)const{
    return ((m_num/m_den) != value);
};



bool Fraction::operator==(const Fraction& other) const{
    return ((std::abs((static_cast<double>(m_num)/m_den)-(static_cast<double>(other.m_num)/other.m_den)) < 0.0009));
}
bool Fraction::operator==(float num ) const{
    if(num<1){
        return (((static_cast<double>(m_num)/m_den)-num) < 0.0001);
    }
    return (((m_num/m_den)-num) < 0.0001);
}
int Fraction::addOverflow(int x,int y)const{
    if ( (y > 0 && x > MAX_INT - y) || (y < 0 && x < MIN_INT - y)){
        throw std::overflow_error("overflow on add");
        }
    else {
        return x+y;
    }
}

int Fraction::subOverflow(int x, int y)const{
    if ( (y < 0  &&  x > MAX_INT + y)||  (y > 0 && x < MIN_INT + y) ){
        throw std::overflow_error("overflow on sub");
    }
    else {
        return x-y;
    }
}
int Fraction::mulOverflow(int x, int y)const{
    long long tmp = static_cast<long long>(x) * y;
    if ( (tmp > MAX_INT) || (tmp < MIN_INT) ) {
        throw std::overflow_error("overflow on mul");
    }else {
        return x * y;
    }
}
