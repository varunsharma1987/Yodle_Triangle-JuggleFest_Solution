/**

    Problem Name: 2 - Juggle Fest (Yodle)
    Contributer: Varun Sharma
    Date: December, 21 2015
*/

#include<bits/stdc++.h>

using namespace std;


#define pb push_back
#define pii pair<int,int>
#define MP make_pair
#define xx first
#define yy second



struct Circuit{
    int H,E,P;
    Circuit(){}
    Circuit(int h,int e,int p){
        H=h,E=e,P=p;
    }
};

struct Juggler{
    int H,E,P;
    vector<int>V;
    Juggler(){}
    Juggler(int h,int e,int p,vector<int>v){
        H=h,E=e,P=p;
        for(int i=0;i<v.size();i++) V.pb(v[i]);
    }
};

vector<Circuit>circuitList;
vector<Juggler>jugglerList;
string s;

int dotProduct(int cc,int jj){      /// Measure performance of circuit juggler pair
    Circuit c=circuitList[cc];
    Juggler j=jugglerList[jj];
    return c.H*j.H+c.E*j.E+c.P*j.P;
}

int getVal(string s,int st){        /// Split integer from string
    int len=s.length();
    int ret=0;
    for(int i=st;i<len;i++) ret=ret*10+(s[i]-'0');
    return ret;
}

void parseCircuit(){                /// Parse circuits information
    stringstream ss(s);
    string w; ss>>w; ss>>w;
    ss>>w; int h=getVal(w,2);
    ss>>w; int e=getVal(w,2);
    ss>>w; int p=getVal(w,2);
    circuitList.pb(Circuit(h,e,p));
}

priority_queue<pii>assignedJuggler[2005];
vector<int>unassignedJuggler;
vector<int>noPreference;
int ID[120005];

void parseJuggler(){            /// Parse Juggler information
    stringstream ss(s);
    string w; ss>>w;
    ss>>w; int id=getVal(w,1);
    ss>>w; int h=getVal(w,2);
    ss>>w; int e=getVal(w,2);
    ss>>w; int p=getVal(w,2);
    ss>>w; for(int i=0;i<w.length();i++) if(w[i]==',') w[i]=' ';
    stringstream tt(w);
    string ww;
    vector<int>v;
    while(tt>>ww){
        int idd=getVal(ww,1);
        v.pb(idd);
    }
    Juggler J=Juggler(h,e,p,v);
    jugglerList.pb(J);
}

int main(){
    freopen("juggleFest.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n=2000,m=12000;
    for(int i=0;i<n;i++){
        getline(cin,s);
        parseCircuit();
    }
    getchar();
    for(int i=0;i<m;i++){
        getline(cin,s);
        parseJuggler();
        unassignedJuggler.pb(i);                    /// i'th Juggler isn't assigned a circuit
    }
    int id=0,mxSize=m/n;
    int sz=unassignedJuggler.size();
    while(id<unassignedJuggler.size()){             /// Try to assign each Juggler to a circuit
        int now=unassignedJuggler[id];
        if(ID[now]==jugglerList[now].V.size()){     /// Juggler who are not assigned to any of his preference circuit is listed into a new list
            noPreference.pb(now);
            id++;
            continue;
        }
        int nextPrefer=jugglerList[now].V[ID[now]++];   /// Get the next preference circuit of current Juggler
        int curSkill=dotProduct(nextPrefer,now);
        if(assignedJuggler[nextPrefer].size()>=mxSize){ /// Check if the current circuit is full or not
            pii top=assignedJuggler[nextPrefer].top();
            int prevSkill=-top.xx;
            if(curSkill>prevSkill){                     /// Compare the current Juggler's skill to worst Jugglers's skill
                assignedJuggler[nextPrefer].pop();
                assignedJuggler[nextPrefer].push(MP(-curSkill,-now));
                unassignedJuggler.pb(-top.yy);
                id++;
            }
        }
        else{
            assignedJuggler[nextPrefer].push(MP(-curSkill,-now));
            id++;
        }
    }
    id=0;
    int circuitID=0;
    while(id<noPreference.size()){              /// Juggler who were not assigned to any of his preference circuit is assigned to any circuit which is not full
        int now=noPreference[id++];
        while(assignedJuggler[circuitID].size()>=mxSize) circuitID++;
        assignedJuggler[circuitID].push(MP(-dotProduct(circuitID,now),-now));
    }

    for(int i=0;i<n;i++){
        cout<<"C"<<i;
        while(!assignedJuggler[i].empty()){
            int id=-assignedJuggler[i].top().yy; assignedJuggler[i].pop();
            cout<<" J"<<id;
            for(int k=0;k<jugglerList[id].V.size();k++){
                int cc=jugglerList[id].V[k];
                cout<<" C"<<cc<<":"<<dotProduct(cc,id);
            }
            if(!assignedJuggler[i].empty()) cout<<",";
        }
        cout<<endl;
    }
    return 0;
}
