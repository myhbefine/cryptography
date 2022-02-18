#include<stdio.h>
#include<iostream>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<list>
#include<queue>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<fstream>
#define maxn 4
#define mod 998244353
using namespace std;
typedef long long ll;
int t,n;
int sum[maxn+1]={0};
char s;
map<string,int> m[maxn+1];
char le[maxn-1];

struct letter2{
    double lv;
    string c;
    bool operator < (const letter2& rhs) const{
        return lv>rhs.lv;
    }
}let[maxn+1][26*26*26*26];

int leti[maxn+1]={0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //cout<<"P\n";
    t=1;//cin>>t;
    while(t--){
        ifstream in;
        string filename="/Users/macbook/Documents/lll2/lll2/数据.txt";
        in.open(filename);
        cin.unsetf(ios::skipws);
        while(!in.eof()){
            in.get(s);
            if(s>='A'&&s<='Z'){
                s='a'+s-'A';
            }
            string str;
            if((s>='a'&&s<='z')||(s>='A'&&s<='Z')){
                str=str+s;
                sum[1]++;
                m[1][str]++;
                if(m[1][str]==1){
                    let[1][leti[1]++].c=str;
                }
                for(int i=0;i<maxn-1;i++){
                    if(le[i]>='a'&&le[i]<='z'){
                        str=le[i]+str;
                        sum[i+2]++;
                        m[i+2][str]++;
                        if(m[i+2][str]==1){
                            let[i+2][leti[i+2]++].c=str;
                        }
                    }
                    else break;
                }
            }
            for(int i=maxn-2;i>0;i--){
                le[i]=le[i-1];
            }
            le[0]=s;
        }
        for(int i=1;i<=maxn;i++){
            cout<<endl<<i<<"个字母的统计结果："<<endl;
            for(int j=0;j<leti[i];j++){
                let[i][j].lv=(double)m[i][let[i][j].c]/sum[i];
            }
            sort(let[i],let[i]+leti[i]);
            for(int j=0;j<10;j++){
                cout<<"字母"<<let[i][j].c<<"的频率为："<<let[i][j].lv<<endl;
            }
        }
        in.close();
        
    }
    return 0;
}

/////运行结果：
/*
 
 
 1个字母的统计结果：
 字母e的频率为：0.127249
 字母t的频率为：0.0857491
 字母a的频率为：0.0797476
 字母o的频率为：0.0769998
 字母i的频率为：0.0712196
 字母n的频率为：0.0693903
 字母s的频率为：0.0638196
 字母r的频率为：0.0602715
 字母h的频率为：0.0590867
 字母d的频率为：0.0474726
 
 2个字母的统计结果：
 字母he的频率为：0.0344231
 字母th的频率为：0.0321558
 字母in的频率为：0.0227873
 字母an的频率为：0.0227478
 字母er的频率为：0.0223313
 字母re的频率为：0.0192494
 字母nd的频率为：0.0172828
 字母ed的频率为：0.0162649
 字母ou的频率为：0.0161167
 字母en的频率为：0.0137972
 
 3个字母的统计结果：
 字母the的频率为：0.0280507
 字母and的频率为：0.018373
 字母ing的频率为：0.0123867
 字母her的频率为：0.00908747
 字母you的频率为：0.0086493
 字母hat的频率为：0.00622638
 字母ere的频率为：0.00610633
 字母was的频率为：0.00600229
 字母ent的频率为：0.00565216
 字母for的频率为：0.00542607
 
 4个字母的统计结果：
 字母that的频率为：0.00628798
 字母with的频率为：0.00614315
 字母ther的频率为：0.00569056
 字母ould的频率为：0.00505694
 字母tion的频率为：0.00464659
 字母here的频率为：0.00380779
 字母have的频率为：0.00370218
 字母ight的频率为：0.00335218
 字母ough的频率为：0.00315606
 字母thin的频率为：0.00314399
 
 */
