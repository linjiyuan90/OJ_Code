/*
 * Bidhan Roy
 * University of Dhaka
 */

#include "iostream"
#include "vector"
#include "set"
#include "map"

using namespace std;

#define foreach(i,n) for(__typeof((n).begin())i =(n).begin();i!=(n).end();i++)
#define sgn(x,y) ((x)+eps<(y)?-1:((x)>eps+(y)?1:0))
#define rep(i,n) for(__typeof(n) i=0; i<(n); i++)
#define mem(x,val) memset((x),(val),sizeof(x));
#define rite(x) freopen(x,"w",stdout);
#define read(x) freopen(x,"r",stdin);
#define all(x) x.begin(),x.end()
#define sz(x) ((int)x.size())
#define sqr(x) ((x)*(x))
#define pb push_back
#define mp make_pair
#define clr clear()
#define inf (1<<30)
#define ins insert
#define xx first
#define yy second
#define eps 1e-9

typedef long long i64;
typedef unsigned long long ui64;
typedef string st;
typedef vector<int> vi;
typedef vector<st> vs;
typedef map<int,int> mii;
typedef map<st,int> msi;
typedef set<int> si;
typedef set<st> ss;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

#define mx 100010
#define mod 1000000009

i64 ncdp[28][28];
i64 ncr(i64 n, i64 r){
    if(r>n) return 0;
    if(n==r) return 1;
    if(r==0) return 1;
    if(r==1) return n % mod;
    if(ncdp[n][r]==-1) ncdp[n][r] = ( ncr(n-1,r-1) + ncr(n-1,r) ) % mod;
    return ncdp[n][r];
}

i64 dp[mx][27];

void gen(){
    /// Calculating F(N,K)
    for(int L=1; L<=100000; L++){
        for(int k=1; k<=26; k++){
            if(L==1) dp[L][k]=k;
            else {
                i64 &now=dp[L][k];
                now=dp[L-1][k];
                now*=k;
                now%=mod;
                if(L%2==0){
                    now-=dp[L/2][k];
                    now%=mod;
                    if(now<0) now+=mod;
                }
            }
        }
    }

    /// Calculating G(N,K)
    for(int k=1; k<=26; k++){
        i64 now =1;
        for(int L=1; L<=100000; L++){
            now *= k;
            now %= mod;
            dp[L][k] = now - dp[L][k];
            if( dp[L][k] < 0 ) dp[L][k] += mod;
        }
    }

    /// Calculating P(N,K)
    for(int k=1; k<=26; k++){
        for(int L=1; L<=100000; L++){
            for(int j=k; j>=1; j--){
                dp[L][k] -= ( ncr(k,j-1) * dp[L][j-1] )%mod;
                if( dp[L][k] < 0 ) dp[L][k] += mod;
            }
        }
    }

}

int main(){
    mem(ncdp,-1);
    gen();
    ios_base::sync_with_stdio(0);
    int n,k,test;
    cin>>test;
    while( test-- ) {
        cin >>n >> k;
        cout<< (dp[n][k] * ncr(26,k) )%mod <<endl;
    }
    return 0;
}
