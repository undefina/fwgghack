#include<deque>
#include<string>
#include<vector>
#include<complex>
#include<assert.h>
#include<algorithm>
#define PI 3.14159265358979323846
void fft(std::vector<std::complex<double>>&a, bool invert)
{
    for (int i = 1, j = 0; i < a.size(); i++)
    {
        int bit = int(a.size()) >> 1;
        for (; j & bit; bit >>= 1)
        {
            j ^= bit;
        }
        j ^= bit;
        if (i < j)
        {
            swap(a[i], a[j]);
        }
    }
    for (int len = 2; len <= a.size(); len <<= 1)
    {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        std::complex<double>wlen(cos(ang), sin(ang));
        for (int i = 0; i < a.size(); i += len)
        {
            std::complex<double>w(1);
            for (int j = 0; j < (len >> 1); j++)
            {
                std::complex<double>u = a[i + j], v = a[i + j + (len >> 1)] * w;
                a[i + j] = u + v;
                a[i + j + (len >> 1)] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
    {
        for (int i = 0; i < a.size(); i++)
        {
            a[i] /= a.size();
        }
    }
}
struct BigInt
{
    bool is_negative = false;
    std::deque<int>Digits = { 0 };
    BigInt() { }
    template<typename T>
    BigInt(T number)
    {
        (*this) = number;
    }
    inline operator std::string() const
    {
        std::stringstream string_stream;
        string_stream << *this;
        return string_stream.str();
    }
    inline operator bool() const
    {
        return *this != 0;
    }
    inline operator int32_t() const
    {
        return std::stoi(*this);
    }
    inline operator int64_t() const
    {
        return std::stoll(*this);
    }
    inline operator unsigned() const
    {
        return std::stoul(*this);
    }
    inline operator double() const
    {
        return std::stod(*this);
    }
    inline operator float() const
    {
        return std::stof(*this);
    }
    inline operator char() const
    {
        return int(*this);
    }
    inline void shrink_to_fit()
    {
        int new_size = Digits.size();
        while (new_size > 1 && Digits[new_size - 1] == 0)
        {
            new_size--;
        }
        Digits.resize(new_size);
    }
    inline friend std::istream& operator >> (std::istream& input_stream, BigInt& object)
    {
        std::string number;
        input_stream >> number;
        object = number;
        return input_stream;
    }
    friend std::ostream& operator << (std::ostream& output_stream, BigInt object)
    {
        object.shrink_to_fit();
        if (object.is_negative && (object.Digits.size() != 1 || object.Digits[0] != 0))
        {
            output_stream << '-';
        }
        bool leading_zeros = true;
        for (int i = object.Digits.size() - 1; i >= 0; i--)
        {
            leading_zeros &= !object.Digits[i];
            if (object.Digits[i] || !leading_zeros)
            {
                output_stream << object.Digits[i];
            }
        }
        if (leading_zeros)
        {
            output_stream << '0';
        }
        return output_stream;
    }
    BigInt& operator = (std::string number)
    {
        if (number[0] == '-')
        {
            is_negative = true;
        }
        else
        {
            is_negative = false;
        }
        Digits.resize(number.size());
        int number_size = number.size();
        while (number.size() > is_negative)
        {
            if (number.back() != '.')
            {
                Digits[number_size - number.size()] = number.back() - '0';
            }
            else
            {
                number.pop_back();
                *this = number;
                return *this;
            }
            number.pop_back();
        }
        if (number.size())
        {
            Digits.pop_back();
        }
        return *this;
    }
    template<typename T>
    inline BigInt& operator = (T number)
    {
        std::stringstream string_stream;
        string_stream << std::fixed << number;
        *this = string_stream.str();
        return *this;
    }
    friend bool operator > (BigInt first_object, BigInt second_object)
    {
        if (first_object.is_negative)
        {
            if (second_object.is_negative)
            {
                first_object.is_negative = false;
                second_object.is_negative = false;
                return first_object < second_object;
            }
            else
            {
                return false;
            }
        }
        else if (second_object.is_negative)
        {
            return true;
        }
        if (first_object.Digits.size() < second_object.Digits.size())
        {
            first_object.Digits.resize(second_object.Digits.size());
        }
        else if (first_object.Digits.size() > second_object.Digits.size())
        {
            second_object.Digits.resize(first_object.Digits.size());
        }
        for (int i = first_object.Digits.size() - 1; i >= 0; i--)
        {
            if (first_object.Digits[i] < second_object.Digits[i])
            {
                return false;
            }
            else if (first_object.Digits[i] > second_object.Digits[i])
            {
                return true;
            }
        }
        return false;
    }
    friend bool operator < (BigInt first_object, BigInt second_object)
    {
        if (first_object.is_negative)
        {
            if (second_object.is_negative)
            {
                first_object.is_negative = false;
                second_object.is_negative = false;
                return first_object > second_object;
            }
            else
            {
                return true;
            }
        }
        else if (second_object.is_negative)
        {
            return false;
        }
        if (first_object.Digits.size() < second_object.Digits.size())
        {
            first_object.Digits.resize(second_object.Digits.size());
        }
        else if (first_object.Digits.size() > second_object.Digits.size())
        {
            second_object.Digits.resize(first_object.Digits.size());
        }
        for (int i = first_object.Digits.size() - 1; i >= 0; i--)
        {
            if (first_object.Digits[i] < second_object.Digits[i])
            {
                return true;
            }
            else if (first_object.Digits[i] > second_object.Digits[i])
            {
                return false;
            }
        }
        return false;
    }
    friend bool operator == (BigInt first_object, BigInt second_object)
    {
        if (first_object.Digits.size() < second_object.Digits.size())
        {
            first_object.Digits.resize(second_object.Digits.size());
        }
        else if (first_object.Digits.size() > second_object.Digits.size())
        {
            second_object.Digits.resize(first_object.Digits.size());
        }
        if (first_object.Digits == second_object.Digits)
        {
            first_object.shrink_to_fit();
            second_object.shrink_to_fit();
            return (!(first_object.is_negative ^ second_object.is_negative) || (first_object.Digits.size() == 1 && first_object.Digits[0] == 0));
        }
        else
        {
            return false;
        }
    }
    inline friend bool operator >= (BigInt first_object, BigInt second_object)
    {
        return first_object > second_object || first_object == second_object;
    }
    inline friend bool operator <= (BigInt first_object, BigInt second_object)
    {
        return first_object < second_object || first_object == second_object;
    }
    inline friend bool operator != (BigInt first_object, BigInt second_object)
    {
        return !(first_object == second_object);
    }
    template<typename T>
    inline friend bool operator > (BigInt first_object, T number)
    {
        BigInt second_object;
        second_object = number;
        return first_object > second_object;
    }
    template<typename T>
    inline friend bool operator < (BigInt first_object, T number)
    {
        BigInt second_object;
        second_object = number;
        return first_object < second_object;
    }
    template<typename T>
    inline friend bool operator == (BigInt first_object, T number)
    {
        BigInt second_object;
        second_object = number;
        return first_object == second_object;
    }
    template<typename T>
    inline friend bool operator >= (BigInt first_object, T number)
    {
        BigInt second_object;
        second_object = number;
        return first_object >= second_object;
    }
    template<typename T>
    inline friend bool operator <= (BigInt first_object, T number)
    {
        BigInt second_object;
        second_object = number;
        return first_object <= second_object;
    }
    template<typename T>
    inline friend bool operator != (BigInt first_object, T number)
    {
        BigInt second_object;
        second_object = number;
        return first_object != second_object;
    }
    template<typename T>
    inline friend bool operator > (T number, BigInt second_object)
    {
        BigInt first_object;
        first_object = number;
        return first_object > second_object;
    }
    template<typename T>
    inline friend bool operator < (T number, BigInt second_object)
    {
        BigInt first_object;
        first_object = number;
        return first_object < second_object;
    }
    template<typename T>
    inline friend bool operator == (T number, BigInt second_object)
    {
        BigInt first_object;
        first_object = number;
        return first_object == second_object;
    }
    template<typename T>
    inline friend bool operator >= (T number, BigInt second_object)
    {
        BigInt first_object;
        first_object = number;
        return first_object >= second_object;
    }
    template<typename T>
    inline friend bool operator <= (T number, BigInt second_object)
    {
        BigInt first_object;
        first_object = number;
        return first_object <= second_object;
    }
    template<typename T>
    inline friend bool operator != (T number, BigInt second_object)
    {
        BigInt first_object;
        first_object = number;
        return first_object != second_object;
    }
    friend BigInt operator + (BigInt first_object, BigInt second_object)
    {
        if (second_object.is_negative)
        {
            second_object.is_negative = false;
            return first_object - second_object;
        }
        if (first_object.is_negative)
        {
            first_object.is_negative = false;
            return second_object - first_object;
        }
        int carry = 0;
        if (first_object.Digits.size() < second_object.Digits.size())
        {
            first_object.Digits.resize(second_object.Digits.size());
        }
        if (first_object.Digits.size() > second_object.Digits.size())
        {
            second_object.Digits.resize(first_object.Digits.size());
        }
        for (int i = 0; i < first_object.Digits.size() - 1; i++)
        {
            first_object.Digits[i] += carry + second_object.Digits[i];
            carry = first_object.Digits[i] / 10;
            first_object.Digits[i] %= 10;
        }
        first_object.Digits[first_object.Digits.size() - 1] += carry;
        first_object.shrink_to_fit();
        return first_object;
    }
    friend BigInt operator - (BigInt first_object, BigInt second_object)
    {
        if (second_object.is_negative)
        {
            second_object.is_negative = false;
            return first_object + second_object;
        }
        if (first_object < second_object)
        {
            first_object = second_object - first_object;
            first_object.is_negative = !first_object.is_negative;
            return first_object;
        }
        bool borrow = false;
        second_object.Digits.resize(first_object.Digits.size());
        for (int i = 0; i < first_object.Digits.size(); i++)
        {
            first_object.Digits[i] -= second_object.Digits[i] + borrow;
            if (first_object.Digits[i] < 0)
            {
                first_object.Digits[i] += 10;
                borrow = true;
            }
            else
            {
                borrow = false;
            }
        }
        first_object.shrink_to_fit();
        return first_object;
    }
    friend BigInt operator * (BigInt first_object, BigInt second_object)
    {
        if (first_object.Digits.size() * second_object.Digits.size() <= (first_object.Digits.size() + second_object.Digits.size()) * log2(first_object.Digits.size() + second_object.Digits.size()))
        {
            BigInt result;
            result.Digits.resize(first_object.Digits.size() + second_object.Digits.size());
            for (int i = 0; i < second_object.Digits.size(); i++)
            {
                int carry = 0;
                for (int j = 0; j < first_object.Digits.size(); j++)
                {
                    result.Digits[i + j] += first_object.Digits[j] * second_object.Digits[i] + carry;
                    carry = result.Digits[i + j] / 10;
                    result.Digits[i + j] %= 10;
                }
                result.Digits[i + first_object.Digits.size()] = carry;
            }
            result.shrink_to_fit();
            result.is_negative = first_object.is_negative ^ second_object.is_negative;
            return result;
        }
        first_object.is_negative ^= second_object.is_negative;
        int new_size = 1;
        while (new_size < first_object.Digits.size() + second_object.Digits.size())
        {
            new_size <<= 1;
        }
        first_object.Digits.resize(new_size);
        second_object.Digits.resize(new_size);
        std::vector<std::complex<double>>fa(first_object.Digits.begin(), first_object.Digits.end()), fb(second_object.Digits.begin(), second_object.Digits.end());
        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < new_size; i++)
        {
            fa[i] *= fb[i];
        }
        fft(fa, true);
        for (int i = 0; i < new_size; i++)
        {
            first_object.Digits[i] = round(fa[i].real());
        }
        int carry = 0;
        for (int i = 0; i < new_size; i++)
        {
            first_object.Digits[i] += carry;
            carry = first_object.Digits[i] / 10;
            first_object.Digits[i] %= 10;
        }
        first_object.shrink_to_fit();
        return first_object;
    }
    friend BigInt operator / (BigInt first_object, BigInt second_object)
    {
        assert(second_object != 0);
        BigInt result, carry;
        result.is_negative = first_object.is_negative ^ second_object.is_negative;
        first_object.is_negative = false;
        second_object.is_negative = false;
        carry.Digits.resize(first_object.Digits.size());
        result.Digits.resize(first_object.Digits.size());
        for (int i = first_object.Digits.size() - 1; i >= 0; i--)
        {
            carry.Digits.push_front(first_object.Digits[i]);
            int answer = 9;
            BigInt temp = second_object * 9;
            while (answer >= 0)
            {
                if (temp <= carry)
                {
                    break;
                }
                temp -= second_object;
                answer--;
            }
            result.Digits[i] = answer;
            carry -= second_object * answer;
        }
        result.shrink_to_fit();
        return result;
    }
    friend BigInt operator % (BigInt first_object, BigInt second_object)
    {
        assert(second_object != 0);
        BigInt result, carry;
        bool negative_temp = first_object.is_negative;
        first_object.is_negative = false;
        second_object.is_negative = false;
        carry.Digits.resize(first_object.Digits.size());
        result.Digits.resize(first_object.Digits.size());
        for (int i = first_object.Digits.size() - 1; i >= 0; i--)
        {
            carry.Digits.push_front(first_object.Digits[i]);
            int answer = 9;
            BigInt temp = second_object * 9;
            while (answer >= 0)
            {
                if (temp <= carry)
                {
                    break;
                }
                temp -= second_object;
                answer--;
            }
            result.Digits[i] = answer;
            carry -= second_object * answer;
        }
        carry.is_negative = negative_temp;
        carry.shrink_to_fit();
        return carry;
    }
    friend BigInt operator | (BigInt first_object, BigInt second_object)
    {
        if (first_object.is_negative)
        {
            return ~(~first_object & ~second_object);
        }
        bool flip = false;
        if (second_object.is_negative)
        {
            flip = true;
            second_object = ~second_object;
        }
        std::string first_number, second_number;
        while (first_object)
        {
            int64_t block = first_object % (1 << 30);
            first_object /= (1 << 30);
            for (int i = 0; i < 30; i++)
            {
                if (!block && !first_object)
                {
                    break;
                }
                first_number.push_back((block % 2) + '0');
                block /= 2;
            }
        }
        while (second_object)
        {
            int64_t block = second_object % (1 << 30);
            second_object /= (1 << 30);
            for (int i = 0; i < 30; i++)
            {
                if (!block && !second_object)
                {
                    break;
                }
                second_number.push_back((block % 2) + '0');
                block /= 2;
            }
        }
        first_number.push_back('0');
        second_number.push_back('0');
        while (first_number.size() < second_number.size())
        {
            first_number.push_back('0');
        }
        while (first_number.size() > second_number.size())
        {
            second_number.push_back('0');
        }
        if (flip)
        {
            for (int i = 0; i < second_number.size(); i++)
            {
                if (second_number[i] == '0')
                {
                    second_number[i] = '1';
                }
                else
                {
                    second_number[i] = '0';
                }
            }
        }
        for (int i = 0; i < first_number.size(); i++)
        {
            first_number[i] = ((first_number[i] - '0') || (second_number[i] - '0')) + '0';
        }
        if (first_number.back() - '0')
        {
            flip = true;
            for (int i = 0; i < first_number.size(); i++)
            {
                if (first_number[i] == '0')
                {
                    first_number[i] = '1';
                }
                else
                {
                    first_number[i] = '0';
                }
            }
        }
        else
        {
            flip = false;
        }
        BigInt answer, temp = 1;
        reverse(first_number.begin(), first_number.end());
        while (first_number.size())
        {
            if (first_number.back() - '0')
            {
                answer += temp;
            }
            temp += temp;
            first_number.pop_back();
        }
        if (flip)
        {
            return ~answer;
        }
        return answer;
    }
    friend BigInt operator & (BigInt first_object, BigInt second_object)
    {
        if (first_object.is_negative)
        {
            return ~(~first_object | ~second_object);
        }
        bool flip = false;
        if (second_object.is_negative)
        {
            flip = true;
            second_object = ~second_object;
        }
        std::string first_number, second_number;
        while (first_object)
        {
            int64_t block = first_object % (1 << 30);
            first_object /= (1 << 30);
            for (int i = 0; i < 30; i++)
            {
                if (!block && !first_object)
                {
                    break;
                }
                first_number.push_back((block % 2) + '0');
                block /= 2;
            }
        }
        while (second_object)
        {
            int64_t block = second_object % (1 << 30);
            second_object /= (1 << 30);
            for (int i = 0; i < 30; i++)
            {
                if (!block && !second_object)
                {
                    break;
                }
                second_number.push_back((block % 2) + '0');
                block /= 2;
            }
        }
        first_number.push_back('0');
        second_number.push_back('0');
        while (first_number.size() < second_number.size())
        {
            first_number.push_back('0');
        }
        while (first_number.size() > second_number.size())
        {
            second_number.push_back('0');
        }
        if (flip)
        {
            for (int i = 0; i < second_number.size(); i++)
            {
                if (second_number[i] == '0')
                {
                    second_number[i] = '1';
                }
                else
                {
                    second_number[i] = '0';
                }
            }
        }
        for (int i = 0; i < first_number.size(); i++)
        {
            first_number[i] = ((first_number[i] - '0') && (second_number[i] - '0')) + '0';
        }
        if (first_number.back() - '0')
        {
            flip = true;
            for (int i = 0; i < first_number.size(); i++)
            {
                if (first_number[i] == '0')
                {
                    first_number[i] = '1';
                }
                else
                {
                    first_number[i] = '0';
                }
            }
        }
        else
        {
            flip = false;
        }
        BigInt answer, temp = 1;
        reverse(first_number.begin(), first_number.end());
        while (first_number.size())
        {
            if (first_number.back() - '0')
            {
                answer += temp;
            }
            temp += temp;
            first_number.pop_back();
        }
        if (flip)
        {
            return ~answer;
        }
        return answer;
    }
    friend BigInt operator ^ (BigInt first_object, BigInt second_object)
    {
        if (first_object == 0)
        {
            return second_object;
        }
        if (second_object == 0)
        {
            return first_object;
        }
        if (first_object < 0 && second_object < 0)
        {
            return ~first_object ^ ~second_object;
        }
        if (first_object < 0)
        {
            return ~(~first_object ^ second_object);
        }
        if (second_object < 0)
        {
            return ~(first_object ^ ~second_object);
        }
        std::string first_number, second_number;
        while (first_object)
        {
            int64_t block = first_object % (1 << 30);
            first_object /= (1 << 30);
            for (int i = 0; i < 30; i++)
            {
                if (!block && !first_object)
                {
                    break;
                }
                first_number.push_back((block % 2) + '0');
                block /= 2;
            }
        }
        while (second_object)
        {
            int64_t block = second_object % (1 << 30);
            second_object /= (1 << 30);
            for (int i = 0; i < 30; i++)
            {
                if (!block && !second_object)
                {
                    break;
                }
                second_number.push_back((block % 2) + '0');
                block /= 2;
            }
        }
        while (first_number.size() < second_number.size())
        {
            first_number.push_back('0');
        }
        while (first_number.size() > second_number.size())
        {
            second_number.push_back('0');
        }
        for (int i = 0; i < first_number.size(); i++)
        {
            first_number[i] = ((first_number[i] - '0') ^ (second_number[i] - '0')) + '0';
        }
        reverse(first_number.begin(), first_number.end());
        BigInt answer, temp = 1;
        while (first_number.size())
        {
            if (first_number.back() - '0')
            {
                answer += temp;
            }
            temp += temp;
            first_number.pop_back();
        }
        return answer;
    }
    friend BigInt operator >> (BigInt object, int number)
    {
        if (number < 0)
        {
            return object << -number;
        }
        if (object.is_negative)
        {
            return ~(~object >> number);
        }
        std::string bits;
        while (object)
        {
            int64_t block = object % (1 << 30);
            object /= (1 << 30);
            for (int i = 0; i < 30; i++)
            {
                if (!block && !object)
                {
                    break;
                }
                bits.push_back((block % 2) + '0');
                block /= 2;
            }
        }
        reverse(bits.begin(), bits.end());
        bits.resize((number > bits.size() ? 0 : bits.size() - number));
        BigInt answer, temp = 1;
        while (bits.size())
        {
            if (bits.back() - '0')
            {
                answer += temp;
            }
            temp += temp;
            bits.pop_back();
        }
        return answer;
    }
    friend BigInt operator << (BigInt object, int number)
    {
        if (number == 0)
        {
            return object;
        }
        else if (number < 0)
        {
            return object >> -number;
        }
        std::string bits;
        bool negative_temp = object.is_negative;
        object.is_negative = false;
        while (object)
        {
            int64_t block = object % (1 << 30);
            object /= (1 << 30);
            for (int i = 0; i < 30; i++)
            {
                if (!block && !object)
                {
                    break;
                }
                bits.push_back((block % 2) + '0');
                block /= 2;
            }
        }
        reverse(bits.begin(), bits.end());
        while (number--)
        {
            bits.push_back('0');
        }
        BigInt answer, temp = 1;
        while (bits.size())
        {
            if (bits.back() - '0')
            {
                answer += temp;
            }
            temp += temp;
            bits.pop_back();
        }
        answer.is_negative = negative_temp;
        return answer;
    }
    template<typename T>
    inline friend BigInt operator + (BigInt first_object, T number)
    {
        BigInt second_object;
        second_object = number;
        return first_object + second_object;
    }
    template<typename T>
    inline friend BigInt operator - (BigInt first_object, T number)
    {
        BigInt second_object;
        second_object = number;
        return first_object - second_object;
    }
    template<typename T>
    inline friend BigInt operator * (BigInt first_object, T number)
    {
        BigInt second_object;
        second_object = number;
        return first_object * second_object;
    }
    template<typename T>
    inline friend BigInt operator / (BigInt first_object, T number)
    {
        BigInt second_object;
        second_object = number;
        return first_object / second_object;
    }
    template<typename T>
    inline friend BigInt operator % (BigInt first_object, T number)
    {
        BigInt second_object;
        second_object = number;
        return first_object % second_object;
    }
    template<typename T>
    inline friend BigInt operator | (BigInt first_object, T number)
    {
        BigInt second_object;
        second_object = number;
        return first_object | second_object;
    }
    template<typename T>
    inline friend BigInt operator & (BigInt first_object, T number)
    {
        BigInt second_object;
        second_object = number;
        return first_object & second_object;
    }
    template<typename T>
    inline friend BigInt operator ^ (BigInt first_object, T number)
    {
        BigInt second_object;
        second_object = number;
        return first_object ^ second_object;
    }
    template<typename T>
    inline friend BigInt operator + (T number, BigInt second_object)
    {
        BigInt first_object;
        first_object = number;
        return first_object + second_object;
    }
    template<typename T>
    inline friend BigInt operator - (T number, BigInt second_object)
    {
        BigInt first_object;
        first_object = number;
        return first_object - second_object;
    }
    template<typename T>
    inline friend BigInt operator * (T number, BigInt second_object)
    {
        BigInt first_object;
        first_object = number;
        return first_object * second_object;
    }
    template<typename T>
    inline friend BigInt operator / (T number, BigInt second_object)
    {
        BigInt first_object;
        first_object = number;
        return first_object / second_object;
    }
    template<typename T>
    inline friend BigInt operator % (T number, BigInt second_object)
    {
        BigInt first_object;
        first_object = number;
        return first_object % second_object;
    }
    template<typename T>
    inline friend BigInt operator | (T number, BigInt second_object)
    {
        BigInt first_object;
        first_object = number;
        return first_object | second_object;
    }
    template<typename T>
    inline friend BigInt operator & (T number, BigInt second_object)
    {
        BigInt first_object;
        first_object = number;
        return first_object & second_object;
    }
    template<typename T>
    inline friend BigInt operator ^ (T number, BigInt second_object)
    {
        BigInt first_object;
        first_object = number;
        return first_object ^ second_object;
    }
    template<typename T>
    inline BigInt& operator += (T number)
    {
        *this = *this + number;
        return *this;
    }
    template<typename T>
    inline BigInt& operator -= (T number)
    {
        *this = *this - number;
        return *this;
    }
    template<typename T>
    inline BigInt& operator *= (T number)
    {
        *this = *this * number;
        return *this;
    }
    template<typename T>
    inline BigInt& operator /= (T number)
    {
        *this = *this / number;
        return *this;
    }
    template<typename T>
    inline BigInt& operator %= (T number)
    {
        *this = *this % number;
        return *this;
    }
    template<typename T>
    inline BigInt& operator |= (T number)
    {
        *this = *this | number;
        return *this;
    }
    template<typename T>
    inline BigInt& operator &= (T number)
    {
        *this = *this & number;
        return *this;
    }
    template<typename T>
    inline BigInt& operator ^= (T number)
    {
        *this = *this ^ number;
        return *this;
    }
    inline BigInt& operator >>= (int number)
    {
        *this = *this >> number;
        return *this;
    }
    inline BigInt& operator <<= (int number)
    {
        *this = *this << number;
        return *this;
    }
    inline BigInt& operator ++ ()
    {
        (*this) = (*this) + 1;
        return (*this);
    }
    inline BigInt operator ++ (int32_t)
    {
        (*this) = (*this) + 1;
        return (*this) - 1;
    }
    inline BigInt& operator -- ()
    {
        (*this) = (*this) - 1;
        return (*this);
    }
    inline BigInt operator -- (int32_t)
    {
        (*this) = (*this) - 1;
        return (*this) + 1;
    }
    inline friend BigInt operator - (BigInt object)
    {
        return 0 - object;
    }
    inline BigInt operator ~ ()
    {
        return  0 - (*this) - 1;
    }
};
BigInt __gcd(BigInt first_number, BigInt second_number)
{
    return second_number == 0 ? first_number : __gcd(second_number, first_number % second_number);
}
inline BigInt __lcm(BigInt first_number, BigInt second_number)
{
    return first_number * second_number / __gcd(first_number, second_number);
}
BigInt phi(BigInt number)
{
    BigInt answer = number;
    for (BigInt i = 2; i * i <= number; i++)
    {
        if (number % i == 0)
        {
            while (number % i == 0)
            {
                number /= i;
            }
            answer -= answer / i;
        }
    }
    if (number > 1)
    {
        answer -= answer / number;
    }
    return answer;
}
int phi(int number)
{
    int answer = number;
    for (int i = 2; i * i <= number; i += 1)
    {
        if (number % i == 0)
        {
            while (number % i == 0)
            {
                number /= i;
            }
            answer -= answer / i;
        }
    }
    if (number > 1)
    {
        answer -= answer / number;
    }
    return answer;
}
inline BigInt abs(BigInt number)
{
    number.is_negative = false;
    return number;
}
#include <iostream> 
int main()
{
	BigInt a("-088");a+=a;
	std::cout<<a;
    return 0;
}
