#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;
#define max_l 5100
struct Bignum
{
	int num[max_l];
	int length;
	Bignum(string s){rd(s);}
	Bignum(){memset(num,0,sizeof(num));length=1;}
	void operator =(Bignum b)
	{
		for(int i=0;i<max_l;++i)
			this->num[i]=b.num[i];
		length=b.length;
	}
	bool operator <=(Bignum a){
		if(length<a.length) return 1;
		if(length>a.length) return 0;
		for(int i=length;i>=1;--i){
			if(num[i]<a.num[i]) return 1;
			if(num[i]>a.num[i]) return 0;
		}
		return 1;
	}
	bool operator >=(Bignum a){
		return a<=*this;
	}
	void rd(string s)
	{
		memset(num,0,sizeof(num));
		length=s.size();
		for(int i=1;i<=length;++i)
			num[i]=s[length-i]-'0';
	}
	void output()
	{
		for(int i=length;i>=1;--i)
			cout<<num[i];
	}
	void add(Bignum b){
		int maxlen=max(length,b.length);
		int ptr=1;
		for(;ptr<=maxlen;ptr++){
			num[ptr]+=b.num[ptr];
			if(num[ptr]>=10){
				num[ptr]-=10;
				num[ptr+1]++;
			}
		}
		length=maxlen;
		if(num[length+1]){length++;}
	}
	void sub(Bignum b)
	{
		int maxlen=max(length,b.length);
		int ptr=1;
		for(;ptr<=maxlen;ptr++){
			num[ptr]-=b.num[ptr];
			while(num[ptr]<0){
				num[ptr]+=10;
				num[ptr+1]--;
			}
		}
		while(num[maxlen]==0 && maxlen>1) maxlen--;
		length=maxlen;
	}
	void sub_output(Bignum b)
	{
		if(b<=*this){
			sub(b);
			output();
		}
		else{
			b.sub(*this);
			cout<<"-";
			b.output();
		}
	}
	void mul(Bignum b){
		Bignum d;
		memset(d.num,0,sizeof(d.num));
		for(int i=1;i<=length;++i){
			int x=0;
			for(int j=1;j<=b.length;++j){
				d.num[i+j-1]+=num[i]*b.num[j]+x;
				x=d.num[i+j-1]/10;
				d.num[i+j-1]%=10;
			}
			d.num[i+b.length]=x;
		}
		int maxlen=length+b.length;
		while(d.num[maxlen]==0 && maxlen>1) maxlen--;
		d.length=maxlen;
		*this=d;
	}
	void div(Bignum b){
		Bignum d,temp;
		int maxlen=length;
		memset(d.num,0,sizeof(d.num));
		int len=length-b.length+1;
		for(int i=len;i>0;--i){
			memset(temp.num,0,sizeof(temp.num));
			for(int j=1;j<=b.length;++j){
				temp.num[j+i-1]=b.num[j];
			}
			temp.length=b.length+i-1;
			while(*this>=temp){
				d.num[i]++;
				this->sub(temp);
			}
		}
		while(d.num[maxlen]==0 && maxlen>1) maxlen--;
		d.length=maxlen;
		*this=d;
	}
	void div_low(int d)
	{
		int ans[max_l];
		int x=0;
		memset(ans,0,sizeof(ans));
		int len=length;
		reverse(num+1,num+1+len);
		for(int i=1;i<=len;++i){
			ans[i]=(num[i]+10*x)/d;
			x=(num[i]+10*x)%d;
		}
		int anslen=1;
		while(ans[anslen]==0 && anslen<len)
			anslen++;
		Bignum c;
		for(int i=anslen;i<=len;++i)
			c.num[i-anslen+1]=ans[i];
		c.length=len-anslen+1;
		reverse(c.num+1,c.num+1+c.length);
		*this=c;
	}
	void mod(Bignum b){
		Bignum temp(*this);
		temp.div(b);
		temp.mul(b);
		this->sub(temp);
	}
};
int main()
{
	ios_base::sync_with_stdio(false);cin.tie(0);
	string s1,s2;
	cin>>s1>>s2;
	Bignum a(s1),b(s2);
	a.div(b);
	a.output();
}