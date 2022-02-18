#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>
#include<cmath>
#include<algorithm>
#define maxn 70010
using namespace std;
typedef long long ll;
string gx="1000000000000111";
string f="1111111111111111";//初态
int key[maxn];
int newk[1000];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //cout<<"p\n";
    int n=0;
    key[0]=f[0]-'0';
    //生成密钥
    while(++n<70000){
        //cout<<f[0];
        int x=0;
        for(int i=15;i>=0;--i){
            int k=(gx[i]-'0')*(f[i]-'0');
            if(i>0) f[i]=f[i-1];
            x+=k;
        }
        f[0]=x%2+'0';
        key[n]=x%2;
    }
    //验证密钥是否正确
    int flag=0;
    for(int i=16;i<70000;++i){
        int x=0;
        for(int k=0;k<16;++k){
            x+=(key[i-k-1]*(gx[k]-'0'));
        }
        if(key[i]!=x%2){
            cout<<"\nWrong answer! "<<i<<endl;
            flag=1;
            return 0;
        }
    }
    if(flag==0){
        cout<<"\nRight!\n";
    }
    //打印前100比特
    for(int i=0;i<100;++i){
        cout<<key[i];
    }
    cout<<endl;
    //计算周期
    for(int i=1;i<70000;++i){
        int flag=0;
        //cout<<key[i-1];
        for(int j=i;j<70000;++j){
            if(key[j]!=key[j-i]){
                flag=1;
                break;
            }
        }
        if(flag==0) {
            cout<<"\nThe period of this key is "<<i<<".\n";
            int m=2;
            m=pow(2,16)-1;
            cout<<"The maximum period is "<<m<<".\n";
            break;
        }
    }
    
    for(int i=0;i<1000;++i){
        newk[i]=key[i+100];
    }
    for(int i=4;i<1000;++i){
        //cout<<"I"<<i<<' ';
        int newgx[i];
        for(ll k=1;k<pow((ll)2,i);++k){
            flag=0;
            ll k1=k;
            //cout<<endl;
            for(int j=0;j<i;++j){
                newgx[j]=k1%2;
                k1/=2;
                //cout<<newgx[j];
            }
            for(int j=i;j<1000;++j){
                int x=0;
                for(int d=0;d<i;++d){
                    x+=newgx[d]*newk[j-d-1];
                }
                if(newk[j]!=x%2){
                    flag=1;
                    break;
                }
            }
            if(flag==0){
                cout<<"g(x) = 1";
                for(int j=0;j<i;++j){
                    cout<<newgx[j];
                }
                cout<<endl;
                break;
            }
        }
        if(flag==0) break;
    }
    return 0;
}
