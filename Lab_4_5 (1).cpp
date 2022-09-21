#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define allvec(a) a.begin(),a.end()
using namespace std;

class Row{
        public:
        string Author_ID,Book_ID,Author_Name,Book;
        Row(string Author_ID,string Book_ID,string Author_Name,string Book){
                this->Author_ID = Author_ID;
                this->Book_ID = Book_ID;
                this->Author_Name = Author_Name;
                this->Book = Book;
        }
};
bool operator==(const Row &lhs,const Row &rhs){
        return (lhs.Author_ID == rhs.Author_ID and lhs.Book_ID == rhs.Book_ID and lhs.Author_Name == rhs.Author_Name
                        and lhs.Book == rhs.Book);
}
bool operator!=(const Row &lhs,const Row &rhs){
        return !(lhs == rhs);
}
bool operator<(const Row &lhs,const Row &rhs){
        return (lhs.Book_ID < rhs.Book_ID);
}
Row mt = Row("Empty","Empty","Empty","Empty");
int powerMod(int a, int b, int m){
                if(b == 0){
                        return (a%m);
                }
                int ans = powerMod(a,b>>1,m);
                ans *= ans;
                ans %= m;
                if(b&1){
                        ans *= a;
                        ans %= m;
                }
                return ans;
        }
int hashFunction(string s, int mod_1){
        int hashValue = 0;
        int n = s.size();
        for(int i =0 ; i < n; i++){
                hashValue += ((i+1)*powerMod((int)s[i],i+1,mod_1))%mod_1;
                hashValue %= mod_1;
        }
        return hashValue;
}
class Hash_Table{
        vector<Row> Table;
        public:                   
        const int mod_1 = 1000;
        int insert(Row a){
                int val = hashFunction(a.Book_ID,mod_1);
                if(Table[val] == mt)
                        Table[val]  =a;
                else{
                        bool flag = false;
                        for(int i = val; i < 1000; i++){
                                if(Table[val] == mt){
                                        flag = true;
                                        Table[val] = a;
                                        break;
                                }
                        }
                        if(!flag){
                                for(int i = 0; i < val; i++){
                                        if(Table[val] == mt){
                                                flag = true;
                                                Table[val] = a;
                                                break;
                                        }
                                }
                        }
                        if(!flag)
                                return -1;
                }
                return 0;
        }
        public:
        Hash_Table(vector<Row> inputTable){
                for(int i= 0; i < 1000; i++){
                        Table.push_back(mt);
                }
                for(auto t: inputTable){
                        insert(t);
                }
        }
};
class Extendible_Hashing{
        map<string, vector<Row>> Table;
        map<string,int> mp;
        const int MAX_BUCKET_SIZE = 4;
        public:
        int insert(Row a){
                string s = "";
                int val = hashFunction(a.Book_ID,1e5+3);
                function<int(string)> split;
                split = [&](string in)->int{
                        string s1 = "0"+in;
                        string s2 = "1"+in;
                        if(in.size() > 65)
                                return -1;
                        int bit = 1<<((int)in.size());
                        for(auto t : Table[in]){
                                if(hashFunction(t.Book_ID,1e5+3)&bit){
                                        Table[s2].pb(t);
                                }else{
                                        Table[s1].pb(t);
                                }
                        }
                        if(bit&val){
                                if(Table[s2].size() == MAX_BUCKET_SIZE){
                                        if(split(s2) == -1)
                                                return -1;
                                        Table[in].clear();
                                        mp[in] = true;
                                        return 0;
                                }
                                Table[s2].pb(a);
                        }else{
                                if(Table[s1].size() == MAX_BUCKET_SIZE){
                                        if(split(s1) == -1)
                                                return -1;
                                        Table[in].clear();
                                        mp[in] = true;
                                        return 0;
                                }
                                Table[s1].pb(a);
                        }
                        Table[in].clear();
                        mp[in] = true;
                        return 0;
                };
                for(int i = 1; 1<<i <= val; i++){
                        if(i&val){
                                s = "1"+s;
                        }else{
                                s = "0"+s;
                        }
                        if(!mp[s]){
                                if(Table[s].size() == MAX_BUCKET_SIZE){
                                        return split(s);
                                }
                                Table[s].pb(a);
                                return 0;
                        }
                }
                return -1;
        }
};
class Extendible_Hashing_Set{
        map<string, set<Row>> Table;
        map<string,int> mp;
        const int MAX_BUCKET_SIZE = 4;
        public:
        int insert(Row a){
                string s = "";
                int val = hashFunction(a.Book_ID,1e5+3);
                function<int(string)> split;
                split = [&](string in)->int{
                        string s1 = "0"+in;
                        string s2 = "1"+in;
                        if(in.size() > 65)
                                return -1;
                        int bit = 1<<((int)in.size());
                        for(auto t : Table[in]){
                                if(hashFunction(t.Book_ID,1e5+3)&bit){
                                        Table[s2].insert(t);
                                }else{
                                        Table[s1].insert(t);
                                }
                        }
                        if(bit&val){
                                if(Table[s2].size() == MAX_BUCKET_SIZE){
                                        if(split(s2) == -1)
                                                return -1;
                                        Table[in].clear();
                                        mp[in] = true;
                                        return 0;
                                }
                                Table[s2].insert(a);
                        }else{
                                if(Table[s1].size() == MAX_BUCKET_SIZE){
                                        if(split(s1) == -1)
                                                return -1;
                                        Table[in].clear();
                                        mp[in] = true;
                                        return 0;
                                }
                                Table[s1].insert(a);
                        }
                        Table[in].clear();
                        mp[in] = true;
                        return 0;
                };
                for(int i = 1; 1<<i <= val; i++){
                        if(i&val){
                                s = "1"+s;
                        }else{
                                s = "0"+s;
                        }
                        if(!mp[s]){
                                if(Table[s].size() == MAX_BUCKET_SIZE){
                                        return split(s);
                                }
                                Table[s].insert(a);
                                return 0;
                        }
                }
                return -1;
        }
};


class Distributed_Hashing{
        map<string, vector<Row>> Table;
        int MAX_BUCKET_SIZE, MAX_TABLE_SIZE;
        public:
        void insert(Row a){
                string s = "";
                int val = hashFunction(a.Book_ID,1e5+3);
                for(int i = 1; 1<<i <= val; i++){
                        if(i&val){
                                s = "1"+s;
                        }else{
                                s = "0"+s;
                        }
                }
                string ss=s.substr(0,MAX_TABLE_SIZE);
                if(Table[ss].size() == MAX_BUCKET_SIZE){
                        cout<<"Bucket "<<s<<" is full"<<endl;
                }
                else{
                        Table[ss].pb(a);
                }
        }   
        void find(string s,int val){
                for(auto t : Table[s]){
                        int x=hashFunction(t.Book_ID,1e5+3);
                        if(x == val){
                                cout<<"Found"<<endl;
                                cout<<t.Book_ID<<" "<<t.Book<<" "<<t.Author_Name<<endl;
                                return;
                        }
                        
                }
        }
        Distributed_Hashing(int MAX_BUCKET_SIZE, int MAX_TABLE_SIZE){
                this->MAX_BUCKET_SIZE = MAX_BUCKET_SIZE;
                this->MAX_TABLE_SIZE = MAX_TABLE_SIZE;
        }
};

int32_t main(){
        cout<<1<<endl;
}
