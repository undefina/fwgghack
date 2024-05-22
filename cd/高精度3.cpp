class BigFloat
{
private :
    BigInt Numerator, Denominator;
public :
    BigFloat() { }
    template<typename T>
    BigFloat(T number)
    {
        (*this) = number;
    }
    inline operator bool() const
    {
        return *this != 0;
    }
    inline operator int() const
    {
        return Numerator / Denominator;
    }
    inline operator unsigned() const
    {
        return Numerator / Denominator;
    }
    inline operator double()
    {
        return stod((*this).str(15));
    }
    inline operator float()
    {
        return stof((*this).str(7));
    }
    inline operator char() const
    {
        return int(*this);
    }
    inline operator BigInt() const
    {
        return Numerator / Denominator;
    }
    inline BigInt numerator()
    {
        return Numerator;
    }
    inline BigInt denominator()
    {
        return Denominator;
    }
    inline void numerator(BigInt number)
    {
        Numerator = number;
        (*this).shrink_to_fit();
    }
    inline void denominator(BigInt number)
    {
        Denominator = number;
        (*this).shrink_to_fit();
    }
    template<typename T>
    inline void numerator(T number)
    {
        Numerator = number;
        (*this).shrink_to_fit();
    }
    template<typename T>
    inline void denominator(T number)
    {
        Denominator = number;
        (*this).shrink_to_fit();
    }
    inline void shrink_to_fit()
    {
        Numerator.is_negative ^= Denominator.is_negative;
        Denominator.is_negative = false;
        if (Denominator.Digits.size() >= 1000)
        {
            BigInt GCD = __gcd(Numerator, Denominator);
            Numerator /= GCD;
            Denominator /= GCD;
        }
    }
    std::string str(int Digits = 0)
    {
        if (Denominator == 0)
        {
            return "inf";
        }
        std::string answer;
        bool negative_temp = false;
        BigInt numerator = Numerator, denominator = Denominator;
        if (numerator.is_negative ^ denominator.is_negative)
        {
            negative_temp = true;
        }
        numerator.is_negative = false;
        denominator.is_negative = false;
        for (int i = 0; i < Digits; i++)
        {
            numerator.Digits.push_front(0);
        }
        numerator /= denominator;
        for (int i = Digits; i < numerator.Digits.size(); i++)
        {
            answer.push_back(numerator.Digits[i] + '0');
        }
        if (Digits >= numerator.Digits.size())
        {
            answer.push_back('0');
        }
        if (negative_temp)
        {
            answer.push_back('-');
        }
        reverse(answer.begin(), answer.end());
        if (Digits)
        {
            answer.push_back('.');
            std::string temp;
            for (int i = 0; i < Digits; i++)
            {
                temp.push_back(numerator.Digits[i] + '0');
            }
            reverse(temp.begin(), temp.end());
            for (int i = temp.size(); i < Digits; i++)
            {
                answer.push_back('0');
            }
            answer += temp;
        }
        return answer;
    }
    inline friend std::istream& operator >> (std::istream& input_stream, BigFloat& object)
    {
        std::string number;
        input_stream >> number;
        object = number;
        return input_stream;
    }
    friend std::ostream& operator << (std::ostream& output_stream, BigFloat object)
    {
        if (object.Denominator == 0)
        {
            if (object.Numerator == 0)
            {
                output_stream << "Undefined";
                return output_stream;
            }
            else
            {
                output_stream << "inf";
                return output_stream;
            }
        }
        BigInt GCD = __gcd(object.Numerator, object.Denominator);
        object.Numerator /= GCD;
        object.Denominator /= GCD;
        output_stream << std::fixed << object.Numerator << '/' << object.Denominator;
        return output_stream;
    }
    BigFloat& operator = (std::string number)
    {
        if (number[0] == '-')
        {
            Numerator.is_negative = true;
        }
        int dot_place = 0;
        Numerator.Digits.resize(number.size());
        Numerator.Digits[number.size() - 1] = 0;
        for (int i = number.size() - 1; i >= Numerator.is_negative; i--)
        {
            if (number[i] != '.')
            {
                Numerator.Digits[number.size() - i - (bool)dot_place - 1] = number[i] - '0';
            }
            else
            {
                dot_place = number.size() - i - 1;
            }
        }
        if (dot_place)
        {
            Numerator.Digits.pop_back();
        }
        Denominator.Digits = std::deque<int>(dot_place + 1);
        Denominator.Digits[dot_place] = 1;
        (*this).shrink_to_fit();
        return *this;
    }
    template<typename T>
    inline BigFloat& operator = (T number)
    {
        std::stringstream string_stream;
        string_stream << std::fixed << number;
        *this = string_stream.str();
        return *this;
    }
    inline friend bool operator > (BigFloat first_object, BigFloat second_object)
    {
        return first_object.Numerator * second_object.Denominator > second_object.Numerator * first_object.Denominator;
    }
    inline friend bool operator < (BigFloat first_object, BigFloat second_object)
    {
        return first_object.Numerator * second_object.Denominator < second_object.Numerator * first_object.Denominator;
    }
    inline friend bool operator == (BigFloat first_object, BigFloat second_object)
    {
        return first_object.Numerator * second_object.Denominator == second_object.Numerator * first_object.Denominator;
    }
    inline friend bool operator >= (BigFloat first_object, BigFloat second_object)
    {
        return first_object.Numerator * second_object.Denominator >= second_object.Numerator * first_object.Denominator;
    }
    inline friend bool operator <= (BigFloat first_object, BigFloat second_object)
    {
        return first_object.Numerator * second_object.Denominator <= second_object.Numerator * first_object.Denominator;
    }
    inline friend bool operator != (BigFloat first_object, BigFloat second_object)
    {
        return first_object.Numerator * second_object.Denominator != second_object.Numerator * first_object.Denominator;
    }
    template<typename T>
    inline friend bool operator > (BigFloat first_object, T number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object > second_object;
    }
    template<typename T>
    inline friend bool operator < (BigFloat first_object, T number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object < second_object;
    }
    template<typename T>
    inline friend bool operator == (BigFloat first_object, T number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object == second_object;
    }
    template<typename T>
    inline friend bool operator >= (BigFloat first_object, T number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object >= second_object;
    }
    template<typename T>
    inline friend bool operator <= (BigFloat first_object, T number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object <= second_object;
    }
    template<typename T>
    inline friend bool operator != (BigFloat first_object, T number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object != second_object;
    }
    template<typename T>
    inline friend bool operator > (T number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object > second_object;
    }
    template<typename T>
    inline friend bool operator < (T number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object < second_object;
    }
    template<typename T>
    inline friend bool operator == (T number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object == second_object;
    }
    template<typename T>
    inline friend bool operator >= (T number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object >= second_object;
    }
    template<typename T>
    inline friend bool operator <= (T number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object <= second_object;
    }
    template<typename T>
    inline friend bool operator != (T number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object != second_object;
    }
    inline friend bool operator > (BigFloat first_object, BigInt number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object > second_object;
    }
    inline friend bool operator < (BigFloat first_object, BigInt number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object < second_object;
    }
    inline friend bool operator == (BigFloat first_object, BigInt number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object == second_object;
    }
    inline friend bool operator >= (BigFloat first_object, BigInt number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object >= second_object;
    }
    inline friend bool operator <= (BigFloat first_object, BigInt number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object <= second_object;
    }
    inline friend bool operator != (BigFloat first_object, BigInt number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object != second_object;
    }
    inline friend bool operator > (BigInt number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object > second_object;
    }
    inline friend bool operator < (BigInt number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object < second_object;
    }
    inline friend bool operator == (BigInt number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object == second_object;
    }
    inline friend bool operator >= (BigInt number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object >= second_object;
    }
    inline friend bool operator <= (BigInt number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object <= second_object;
    }
    inline friend bool operator != (BigInt number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object != second_object;
    }
    inline friend BigFloat operator - (BigFloat object)
    {
        return 0 - object;
    }
    inline friend BigFloat operator + (BigFloat first_object, BigFloat second_object)
    {
        first_object.Numerator = first_object.Numerator * second_object.Denominator + second_object.Numerator * first_object.Denominator;
        first_object.Denominator *= second_object.Denominator;
        first_object.shrink_to_fit();
        return first_object;
    }
    inline friend BigFloat operator - (BigFloat first_object, BigFloat second_object)
    {
        first_object.Numerator = first_object.Numerator * second_object.Denominator - second_object.Numerator * first_object.Denominator;
        first_object.Denominator *= second_object.Denominator;
        first_object.shrink_to_fit();
        return first_object;
    }
    inline friend BigFloat operator * (BigFloat first_object, BigFloat second_object)
    {
        first_object.Numerator *= second_object.Numerator;
        first_object.Denominator *= second_object.Denominator;
        first_object.shrink_to_fit();
        return first_object;
    }
    inline friend BigFloat operator / (BigFloat first_object, BigFloat second_object)
    {
        first_object.Numerator *= second_object.Denominator;
        first_object.Denominator *= second_object.Numerator;
        first_object.shrink_to_fit();
        return first_object;
    }
    inline friend BigFloat operator % (BigFloat object, BigInt MOD)
    {
        object.Numerator *= pow(object.Denominator, phi(MOD) - 1);
        object.Numerator %= MOD;
        object.Denominator = 1;
        return object;
    }
    template<typename T>
    inline friend BigFloat operator + (BigFloat first_object, T number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object + second_object;
    }
    template<typename T>
    inline friend BigFloat operator - (BigFloat first_object, T number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object - second_object;
    }
    template<typename T>
    inline friend BigFloat operator * (BigFloat first_object, T number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object * second_object;
    }
    template<typename T>
    inline friend BigFloat operator / (BigFloat first_object, T number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object / second_object;
    }
    inline friend BigFloat operator % (BigFloat object, int MOD)
    {
        object.Numerator *= pow(object.Denominator, phi(MOD) - 1);
        object.Numerator %= MOD;
        object.Denominator = 1;
        return object;
    }
    template<typename T>
    inline friend BigFloat operator + (T number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object + second_object;
    }
    template<typename T>
    inline friend BigFloat operator - (T number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object - second_object;
    }
    template<typename T>
    inline friend BigFloat operator * (T number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object * second_object;
    }
    template<typename T>
    inline friend BigFloat operator / (T number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object / second_object;
    }
    inline friend BigFloat operator + (BigFloat first_object, BigInt number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object + second_object;
    }
    inline friend BigFloat operator - (BigFloat first_object, BigInt number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object - second_object;
    }
    inline friend BigFloat operator * (BigFloat first_object, BigInt number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object * second_object;
    }
    inline friend BigFloat operator / (BigFloat first_object, BigInt number)
    {
        BigFloat second_object;
        second_object = number;
        return first_object / second_object;
    }
    inline friend BigFloat operator + (BigInt number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object + second_object;
    }
    inline friend BigFloat operator - (BigInt number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object - second_object;
    }
    inline friend BigFloat operator * (BigInt number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object * second_object;
    }
    inline friend BigFloat operator / (BigInt number, BigFloat second_object)
    {
        BigFloat first_object;
        first_object = number;
        return first_object / second_object;
    }
    template<typename T>
    inline BigFloat& operator += (T number)
    {
        *this = *this + number;
        return *this;
    }
    template<typename T>
    inline BigFloat& operator -= (T number)
    {
        *this = *this - number;
        return *this;
    }
    template<typename T>
    inline BigFloat& operator *= (T number)
    {
        *this = *this * number;
        return *this;
    }
    template<typename T>
    inline BigFloat& operator /= (T number)
    {
        *this = *this / number;
        return *this;
    }
    template<typename T>
    inline BigFloat& operator %= (T number)
    {
        *this = *this % number;
        return *this;
    }
    inline BigFloat& operator += (BigInt number)
    {
        *this = *this + number;
        return *this;
    }
    inline BigFloat& operator -= (BigInt number)
    {
        *this = *this - number;
        return *this;
    }
    inline BigFloat& operator *= (BigInt number)
    {
        *this = *this * number;
        return *this;
    }
    inline BigFloat& operator /= (BigInt number)
    {
        *this = *this / number;
        return *this;
    }
    inline BigFloat& operator %= (BigInt number)
    {
        *this = *this % number;
        return *this;
    }
    inline BigFloat& operator ++ ()
    {
        Numerator += Denominator;
        return (*this);
    }
    inline BigFloat operator ++ (int32_t)
    {
        Numerator += Denominator;
        return (*this) - 1;
    }
    inline BigFloat& operator -- ()
    {
        Numerator -= Denominator;
        return (*this);
    }
    inline BigFloat operator -- (int32_t)
    {
        Numerator -= Denominator;
        return (*this) + 1;
    }
};
inline BigFloat abs(BigFloat number)
{
    BigInt Numerator = number.numerator();
    Numerator.is_negative = false;
    number.numerator(Numerator);
    BigInt Denominator = number.denominator();
    Denominator.is_negative = false;
    number.denominator(Denominator);
    return number;
}
BigFloat floor(BigFloat number, int Digits = 0)
{
    if (number.denominator() == 0)
    {
        return number;
    }
    number = number.str(Digits);
    return number;
}
BigFloat ceil(BigFloat number, int Digits = 0)
{
    if (number.denominator() == 0)
    {
        return number;
    }
    BigFloat number2;
    number2.numerator(1);
    std::string temp = "1";
    while (Digits--)
    {
        temp.push_back('0');
    }
    number2.denominator(temp);
    number += number2;
    number2.denominator(number.denominator());
    number -= number2;
    return number;
}
BigFloat round(BigFloat number, int Digits = 0)
{
    if (number.denominator() == 0)
    {
        return number;
    }
    std::string temp = number.str(Digits + 1);
    if (temp[temp.size() - 1] >= '5')
    {
        temp = '0' + temp;
        for (int i = temp.size() - 2; i >= 0; i--)
        {
            if (temp[i] == '.')
            {
                continue;
            }
            if (temp[i] != '9')
            {
                temp[i]++;
                break;
            }
            else
            {
                temp[i] = '0';
            }
        }
    }
    temp.pop_back();
    number = temp;
    return number;
}
BigFloat sqrt(BigInt number, int depth = 7)
{
    BigFloat temp = 0;
    BigFloat ans = 1;
    while (ans != temp)
    {
        temp = ans;
        ans = (5 * temp) / 4 + number / (4 * temp) - (temp * temp * temp) / (temp * temp + number);
        ans = floor(ans, depth);
    }
    return ans;
}
BigFloat sqrt(BigFloat number, int depth = 7)
{
    BigFloat temp = 0;
    BigFloat ans = 1;
    while (ans != temp)
    {
        temp = ans;
        ans = (5 * temp) / 4 + number / (4 * temp) - (temp * temp * temp) / (temp * temp + number);
        ans = floor(ans, depth);
    }
    return ans;
}
BigFloat cbrt(BigInt number, int depth = 7)
{
    BigFloat temp = 0;
    BigFloat ans = 1;
    while (ans != temp)
    {
        temp = ans;
        ans = temp - (temp * temp * temp - number) / (3 * temp * temp);
        ans = floor(ans, depth);
    }
    return ans;
}
BigFloat cbrt(BigFloat number, int depth = 7)
{
    BigFloat temp = 0;
    BigFloat ans = 1;
    while (ans != temp)
    {
        temp = ans;
        ans = temp - (temp * temp * temp - number) / (3 * temp * temp);
        ans = floor(ans, depth);
    }
    return ans;
}