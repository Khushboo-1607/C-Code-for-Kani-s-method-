#include<bits/stdc++.h>
using namespace std;

vector<float> modifyC(int n,vector<float>&rf,vector<float>fnew){
    vector<float>C;
    for(int i=0;i<2*(n+1);i++){
        C.push_back(0);
    }
    bool flag;
    float a1;
    int iter=0;
    while(iter<5){
        
        for(int i=0;i<2*(n+1);i++){
            flag=true;
            a1=C[i];
            C[i]=rf[i]*(fnew[i]+C[i+1]+C[i-1]);
            
            if(a1-C[i]>0.01 || a1-C[i]<-0.01){
                flag=false;
            }
        }
        iter++;
        if(flag==true){
            break;
        }
    }
    return C;
}

int main(){
    vector<float> v;
    float L;
    
    cout<<"Please input the total length (in m) of the beam to be analyzed : ";
    cin>>L;
    cout<<" \n";
    float ls;
    cout<<"For the left end, please input the support type among the following supports (Enter the number denoting the support) \n 1. pin\n 2. roller\n 3. fixed\n ";
    cin>>ls;
    float rs;
    cout<<"\nFor the right end, please input the support type among the following supports (Enter the number denoting the support) \n 1. pin\n 2. roller\n 3. fixed\n ";
    cin>>rs;
    int n;
    cout<<"\nPlease input the number of internal roller supports " ;
    cin>>n;
    
    float d[n+1];
    cout<<" Enter the supports distance starting from the left side ";
    for(int i=0;i<n+1;i++){
        cin>>d[i];
    }
    for(int i=0;i<n+1;i++){
        cout<<d[i];
    }
    int count=0;
    float f[2*(n+1)];
    float t,p,a;
    for(int i=0;i<2*(n+1);i=+2){
        if(count>n){
            break;
        }
        
        cout<<"for section "<<count+1<<" enter 0 for no load, 1 for concentrated load, 2 for UDL ";
        float x;
        if(i==0){
            cin>>x;
        }
        cin>>t;
        
        
            if(t==0){
                f[i]=0;
                f[i+1]=0;
            }
             if(t==1){
                
                cout<<"Enter the magnitude of load ";
                cin>>p;
                cout<<"Enter the distance of load ";
                cin>>a;
                int b=d[count]-a;
                f[i]=-p*b*a*a/(d[count]*d[count]);
                f[i+1]=+p*b*a*a/(d[count]*d[count]);
                v.push_back(f[i]);
                v.push_back(f[i+1]);
            }
            if(t==2){
                cout<<"Enter the magnitude of load ";
                cin>>p;
                f[i]=-p*d[count]*d[count]/12;
                f[i+1]=+(p*d[count]*d[count])/12;
                cout<<d[count];
                cout<<f[i]<<" "<<f[i+1]<<endl;
                v.push_back(f[i]);
                v.push_back(f[i+1]);
            }
        
           
      //  else if(count==n && (rs==1 || rs==2)){
        //     if(t==0){
        //         f[i]=0;
        //         f[i+1]=0;
        //     }
           
        //     if(t==2){
        //         cout<<"Enter the magnitude of load ";
        //         cin>>p;
        //         f[i]=-p*d[count]*d[count]/8;
        //         f[i+1]=0;
        //     }
        // }
        // else if(count>n){
        //     break;
        // }
        // else{
        //         if(t==0){
        //                 f[i]=1;
        //                 f[i+1]=0;
        //         }
            
        //         if(t==1){
                
        //         cout<<"Enter the magnitude of load ";
        //         cin>>p;
        //         cout<<"Enter the distance of load ";
        //         cin>>a;
        //         int b=d[count]-a;
        //         f[i]=p*b*a*a/(d[count]*d[count]);
        //         f[i+1]=-p*b*a*a/(d[count]*d[count]);
        //         v.push_back(f[i]);
        //         v.push_back(f[i+1]);
        //     }
        //     if(t==2){
        //         cout<<"Enter the magnitude of load ";
        //         cin>>p;
        //         f[i]=p*d[count]*d[count]/12;
        //         f[i+1]=-(p*d[count]*d[count])/12;
        //         cout<<d[count];
        //         cout<<f[i]<<" "<<f[i+1]<<endl;
        //         v.push_back(f[i]);
        //         v.push_back(f[i+1]);
        //     }
        //}
        
        count++;
    
    }
    // for(int i=0;i<2*(n+1);i++){
    //     cout<<f[i]<<" ";
    // }
     for(float ele:v){
        cout<<ele<<" ";
    }

    vector<float>I;
    cout<<" enter the material property (I) the beam sections in succession ";
    float y;
    for(int i=0;i<n+1;i++){
        cin>>y;
        I.push_back(y);
    }
    //calculating stiffness of each section
    vector<float>k;
    for(int i=0;i<n+1;i++){
        k.push_back(4*I[i]/d[i]);
    }
    //calculating rotation factors
    vector<float>rf;
    vector<float>den;
    vector<float>num;
    
    int m=n+1;
    if(ls==3){
        rf.push_back(0);
    }
    for(int i=0;i<=m;i+=1){
        den.push_back(k[i]+k[i+1]);
        den.push_back(k[i]+k[i+1]);
    }
    num.push_back(k[0]);
    for(int i=1;i<=m-1;i+=1){
        num.push_back(k[i]);
        num.push_back(k[i]);
    }
    num.push_back(k[m]);
    for(int i=0;i<=m;i++){
        rf.push_back(-0.5*num[i]/den[i]);
    }

    
    if(rs==1 || rs==2){
        rf.push_back(-0.5);
    }
     for(float ele:rf){
        cout<<ele<<" ";
    }
    int s=rf.size();
    // adding fixed end moments
    vector<float>fnew;
    fnew.push_back(v[0]);
    for(int i=1;i<2*(n+1)-1;i+=2){
        fnew.push_back(v[i]+v[i+1]);
        fnew.push_back(v[i]+v[i+1]);
    }
    fnew.push_back(v[2*(n+1)-1]);
    cout<<endl;
     for(float ele:fnew){
        cout<<ele<<" ";
    }
    // Iterating to get final rotation contributions
    vector<float>C=modifyC(n,rf,fnew);
    
    
    for(float ele:C){
        cout<<endl<<ele<<" ";
    }
    int w;
    vector<float>M;
    for(int i=0;i<(n+1);i++){
        w=f[i]+2*C[i]+C[i+1];
        M.push_back(w);
        w=f[i+1]+2*C[i+1]+C[i];
        M.push_back(w);
    }
    //M.push_back(f[0]+2*)
    for(float ele:M){
        cout<<"The final moments from left to right are"<<" "<<ele<<" ";
    }
    return 0;
}