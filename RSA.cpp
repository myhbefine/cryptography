#include <iostream>
#include <stdio.h>
#define maxn 1005
using namespace std;
string pp,qq,ee;
string str_m;
const int Mod = 10;

struct HP {//自定义一个高精度类型
    int p[maxn],len;//p为储存大数的数组，len为大数的长度
    int b;//因为运算过程会出现负数，所以b=1时该数为正，b=-1时该数为负
    HP() {//构造函数，初值为0
        memset(p,0,sizeof p);
        len = 0;
        b=1;
    }
    void print() {//打印大数
        printf("%d",p[len]);
        for (int i=len-1;i>0;--i) {
            printf("%d",p[i]);
        }
        printf("\n");
    }
}p,q,n,phin,e,d,C,M,m;//p和q为两个大素数，phin为n的欧拉函数值，M是明文，C为M加密后的密文，m为C解密后的明文

bool operator > (const HP &a,const HP &b) {//重载比较运算符，大数与大数的比较，由于该程序中使用比较符时均为正数，所以不用考虑正负
    if(a.len>b.len) return true;
    if(a.len<b.len) return false;
    for(int i=a.len;i>0;--i){
        if(a.p[i]>b.p[i]) return true;
        if(a.p[i]<b.p[i]) return false;
    }
    return true;
}

HP operator + (const HP &a,const HP &b) {//重载加号，大数加大数
    HP operator - (const HP &a,const HP &b);
    int f=1;
    if(a.b==-1&&b.b==-1){
        f=-1;
    }//若两个数均为负数，则两个数相加得到的数也为负数
    else if(a.b==-1){
        HP c=a;
        c.b=1;
        return (b-c);
    }//若a为负数，c=-a,则a+b=b-c
    else if(b.b==-1){
        HP c=b;
        c.b=1;
        return (a-c);
    }//若b为负数，c=-b,则a+b=a-c
    HP c;
    c.len=max(a.len, b.len);
    c.b=f;
    int x=0;
    for(int i=1;i<=c.len;++i){
        c.p[i]=a.p[i]+b.p[i]+x;
        x=c.p[i]/Mod;
        c.p[i]%=Mod;
    }//将a和b各位数相加并赋给c，最后得到c=a+b
    if(x>0)
        c.p[++c.len]=x;
    return c;
}

HP operator + (const HP &a,const int &b){//重载加号，大数加整数
    HP c;
    c.len=a.len;
    //因为在该程序中使用大数加整数时不存在大数为负数的情况，所以在大数加整数时不用考虑正负
    int x = b;
    for(int i=1;i<=c.len;++i) {
        c.p[i]=a.p[i]+x;
        x=c.p[i]/Mod;
        c.p[i]%=Mod;
    }//得到c=a+b
    while(x>0){
        c.p[++c.len]=x%Mod;
        x/=Mod;
    }
    return c;
}

HP operator * (const HP &a,const int &b) {//重载乘号，大数乘整数
    HP c;
    c.len=a.len;
    c.b=a.b;//因为该程序中大数乘整数时整数定为整数，所以相乘的结果的正负与大数的正负一致
    int x = 0;
    for(int i=1;i<=c.len; ++i) {
        c.p[i]=a.p[i]*b+x;
        x=c.p[i]/Mod;
        c.p[i]%=Mod;
    }//将大数的每位数与整数相乘并赋给c，得到c=a*b
    while(x>0){
        c.p[++c.len]=x%Mod;
        x/=Mod;
    }
    return c;
}

HP operator *(const HP &a,const HP &b){//重载乘号，大数乘大数
    if(b.len==0) return b;//若b==0则a*b=0
    if(b.len==1){
        HP aa=a;
        if(a.b!=b.b) aa.b=-1;
        return aa*b.p[1];
    }//若b为个位数，则返回大数乘整数
    HP c;
    c.len=b.len-1;
    for(int i=c.len;i>0;--i){
        c.p[i]=b.p[i+1];
    }//c=b/10
    HP aa=a;
    if(a.b==b.b){
        aa.b=1;
    }//a,b同号则答案为正，a,b异号则答案为负
    else aa.b=-1;
    //由于aa的正负已经为答案的正负，所以后续计算除aa外其他数应均为正号
    return aa*c*10+aa*b.p[1];
}

HP operator - (const HP &a,const int &b){//重载减号，大数减整数
    HP c;
    c.len=a.len;
    //因为在该程序中使用大数减整数时不存在大数为负数或相减后的结果为负数的情况，所以在大数减整数时不用考虑正负
    for(int i=a.len;i>0;--i){
        c.p[i]=a.p[i];
    }//将a的值赋给c
    if(c.p[1]>=b){
        c.p[1]-=b;
    }//若c的个位数大于等于b则直接即可，反之则需向前一位借位
    else{
        c.p[1]=c.p[1]+10-b;
        for(int i=2;i<=c.len;++i){
            if(c.p[i]==0){
                --c.p[i];
            }
            else{
                --c.p[i];
                if(i==c.len&&c.p[i]==0){
                    --c.len;
                }
                break;
            }
        }
    }//得到c=a-b
    return c;
}

HP operator - (const HP &aa,const HP &bb) {//重载减号，大数减大数
    int flag=1;//记录结果的正负
    if(bb.b==-1){
        HP c=bb;
        c.b=1;
        return aa+c;
    }//若被减数为负，c=bb,则返回aa+c
    if(aa.b==-1){
        HP c=aa;
        c.b=1;
        c=c+bb;
        c.b=-1;
        return c;
    }//若减数为负，c=-aa，则aa-bb=-c-bb=-(c+bb)
    HP a=aa;
    HP b=bb;
    if(b>a){
        a=bb;
        b=aa;
        flag=-1;
    }//若被减数大于减数，则a-b=-(b-a)
    HP c=a;
    c.b=flag;
    int x=0;
    for(int i=1;i<=a.len;++i) {
        if(i<=b.len){
            x+=b.p[i];
        }
        if(c.p[i]>=x){
            c.p[i]-=x;
            x=0;
        }
        else{
            c.p[i]+=10;
            c.p[i]-=x;
            x=1;
        }
    }//得到c=a-b
    while(c.len>0&&c.p[c.len]==0) --c.len;
    return c;
}

HP operator % (const HP &a,const HP &b){//重载%，大数对大数取模
    HP c;
    c.len=a.len;
    for(int i=a.len;i>0;--i){
        c.p[i]=a.p[i];
    }//将a的值赋给c
    while(c>b){
        int t=c.len-b.len;
        if(t>0){//如果c和b有位数差则采用3.2描述的算法，反之则直接相减
            HP g;
            g.len=t;
            g.p[t]=1;//令g=pow(10,t-1);
            g=g*b;
            while(c>g){
                c=c-g;
                //因为该运算是取模所以不必y统计循环次数
            }
        }
        else c=c-b;
    }
    if(a.b!=b.b) c.b=-1;//若a,b异号则结果为负
    return c;
}

HP operator / (const HP &a,const HP &b){//重载除号，大数除以大数
    HP c;
    c.len = a.len;
    HP d;//统计总循环次数
    for(int i=a.len;i>0;--i){
        c.p[i]=a.p[i];
    }//将a的值赋给c
    while(c>b){
        int t=c.len-b.len;
        if(t>0){//如果c和b有位数差则采用3.2描述的算法，反之则直接相减
            HP g,gg;
            g.len=t;
            g.p[t]=1;//令g=pow(10,t-1)
            gg=g*b;
            int k=0;//统计加倍后的循环次数
            while(c>gg){
                c=c-gg;
                ++k;
            }
            d=d+g*k;//总循环次数应加上 加倍后的循环次数*倍数
        }
        else{
            c=c-b;
            d=d+1;//循环次数加一
        }
    }
    if(a.b!=b.b) d.b=-1;//若a,b异号则结果为负
    return d;
}

HP exgcd(HP a,HP b,HP &x,HP &y){//扩展欧几里得算法
    if(b.len==0)
    {
        x.len=1;
        x.p[1]=1;
        y.len=0;
        return a;  //到达递归边界开始向上一层返回
    }
    HP r=exgcd(b,a%b,x,y);
    HP temp=y;
    y=x-(a/b)*y;
    x=temp;
    return r;   //得到a,b的最大公因数
}

HP power(HP a,int b){//BR算法的快速幂运算
    HP c;
    c.len=1;
    c.p[c.len]=1;
    while(b>0){
        if(b%2==1){
            c=(c%n)*(a%n)%n;
        }
        a=(a%n)*(a%n)%n;
        b/=2;
    }
    return c;
}

HP power_dfs(HP a,HP b){//基于BR算法的改进
    if(b.len==1){
        return power(a%n,b.p[1]);
    }
    HP c;
    c.len=b.len-1;
    for(int i=c.len;i>0;--i){
        c.p[i]=b.p[i+1];
    }//c=b/10
    return (power(power_dfs(a%n,c)%n,10)%n)*(power(a%n,b.p[1])%n)%n;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout<<"\n请输入大素数p: ";
    cin>>pp;
    cout<<"\n请输入大素数q: ";
    cin>>qq;
    for(int i=(int)pp.length();i>0;--i){
        p.p[i]=pp[(int)pp.length()-i]-'0';
    }//将大素数p由字符串类型转化为自定义的高精度类型
    p.len=(int)pp.length();
    for(int i=(int)qq.length();i>0;--i){
        q.p[i]=qq[(int)qq.length()-i]-'0';
    }//将大素数q由字符串类型转化为高精度类型
    q.len=(int)qq.length();
    n=p*q;
    phin=(p-1)*(q-1);
    while(1){
        cout<<"\n请输入与φ(n)互素的整数e: ";
        cin>>ee;
        for(int i=(int)ee.length();i>0;--i){
            e.p[i]=ee[(int)ee.length()-i]-'0';
        }//将e由字符串类型转化为高精度类型
        e.len=(int)ee.length();
        HP y;
        HP o=exgcd(e,phin,d,y);//对e和phin进行扩欧运算，返回的o为最大公因数，得到的d为e的逆元
        if(o.len==1&&o.p[1]==1){
            cout<<"\n e符合要求！\n计算得出 d = ";
            d=(d%phin+phin)%phin;
            d.print();
            break;
        }
        cout<<"\n e不符合要求！";
    }
    cout<<"\n请输入明文：";
    cin>>str_m;
    for(int i=(int)str_m.length();i>0;--i){
        M.p[i]=str_m[(int)str_m.length()-i]-'0';
    }//明文M由字符串类型转化为高精度类型
    M.len=(int)str_m.length();
    C=power_dfs(M,e)%n;//对明文进行加密运算
    cout<<"\n加密后的密文为：";
    C.print();
    m=power_dfs(C,d)%n;//对密文进行解密运算
    cout<<"\n解密后的明文为：";
    m.print();
    return 0;
}
