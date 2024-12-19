#include<bits/stdc++.h>
using namespace std;

class base
{
public:
    string s;
    int n,p,r1,r2,score=0,penalty=0,n_0=0,n_1=0,point=0 ,bonus=0,final_score=0;
    void input()
    {
        cin >> n >> p >> s >> r1 ;
    }
    int calc_point()
    {
        for(int i = 0 ; i < n ;i++)
        {
            if(s[i]=='1')
            {
                point+=5; n_1++;
            }else
            {
                point-=2; n_0++;
            }
        }
        return point;
    }
    string monster_s;
    void take_input()
    {
        cin >> monster_s;
    }
    void penalty_count()
    {
        n_0+=penalty;
        n_1-=penalty;
    }

    void resort()
    {
        for(int i = 0 ; i < n ;i++)
        {
            if(monster_s[i]-'0' > 5)
            {
                if(n_0 > 0)
                   {s[i]='0'; n_0--;}
                else
                   {s[i]='1';n_1--;}
            }else
            {
                if(n_1 > 0)
                   {s[i]='1';n_1--;}
                else
                   {s[i]='0'; n_0--;}
            }
        }
    }
    void print()
    {
        cout<<"Round 1 Completed with energy string "<<s<<endl;
        cout<<"Killed "<<score<<" Monster "<<endl;
        cout<<"Penalty "<<penalty<<endl;
        cout<<"Score "<<score<<endl << endl;
    }
    bool  check()
    {
        if(p <= score)
            return true;
        else
            return false;
    }
};

class round1 : public base
{
    public:
        int m ,a,temp,col=0 ;
     void play()
    {
        for(int i = 0 ; i < n ;i++)
        {
            if(s[i]=='1')
            {
                if(monster_s[i]-'0' <= 5 )
                {
                    score++; bonus++;
                }else
                {
                    if(bonus > 0)
                    {
                        score++; bonus--;
                    }else
                    {
                        penalty++;
                    }
                }
            }else
            {
                if(bonus > 0)
                    {
                        score++; bonus--;
                    }else
                    {
                        penalty++;
                    }
            }
        }
        n_0+=penalty;
        n_1-=penalty;
    }

};

class round2 : public base
{
    public:
    round2(){}
    round2(round1 &b)
    {
        score=b.score; n=b.n;
        r1=b.r1; r2=b.r2;
        penalty=b.penalty;
        s=b.s;
    }
    int f =0;
    void play()
    {
        cout<<"Energy string for the second round is "<<s<<endl<<endl;
        for(int i=0 ; i < n ;i++)
        {
            if(s[i]=='1' && monster_s[i]-'0' <=5)
            {
                score++;
            }else
            {
                cout<<"Could not kill the "<<i+1<<"th monster"<<endl;
                cout<<"Fix the given puzzle"<<endl;
                int m,a,col=1,ro=1,ro1,col1,k,x,y,arr[50][50] ,temp;
                cin >> m ;
                temp=m;
                map<int , int>mp;

                for(int i = 1 ; i <=m*m ;i++)
                {
                    cin >> a;
                    mp[a]++;
                }

                for(auto it : mp)
                {
                    x=it.first;y=it.second;
                    if(it.second >=m)
                    {
                        mp.erase(it.first);
                        if(y-m > 0)
                        mp.insert({x,y-m});
                        it.second=it.second-m;
                        f=1;
                        for(int i =0 ; i < m ;i++)
                            arr[i][i]=it.first;
                            break;
                    }
                }
                if(f==0)
                {
                    cout<<"Could not solve the Puzzle"<<endl;
                    cout<<"GAME OVER"<<endl<<endl;
                    return;
                }else
                {

                    for(int i = m-1 ; i >=1;i--)
                    {

                        for(int j = 1 ; j <=2;j++)
                        {
                        f=0;
                           for(auto it : mp)
                           {
                               if(it.second >=i)
                               {
                                  x=it.first;y=it.second;
                                  f=1;
                                  mp.erase(it.first);
                                  mp.insert({x,y-i});
                                  break;
                                }
                          }
                          if(f==1)
                          {
                             if(j==1)
                             {
                                for( k=col,ro1=0 ; k < temp;k++,ro1++)
                                {
                                   arr[ro1][k]=x;
                                }
                             col++;
                             }else
                             {
                                 for( k=ro,col1=0 ; k < temp;k++,col1++)
                                 {
                                   arr[k][col1]=x;
                                  }
                              ro++;
                             }
                        }else
                        {
                            cout<<"Could not solve the Puzzle"<<endl;
                            cout<<"GAME OVER"<<endl<<endl;
                            return;
                        }
                        }
                    }
                }

                cout<<"Fixed The Puzzle "<<endl<<endl;
                score++;
                for(int i=0;i < m;i++)
                {
                    for(int j=0; j < m ;j++)
                    {
                        cout<<arr[i][j]<<' ';
                    }
                    cout<<endl;
                }
                f=0;
            }
        }
        cout<<"Completed Mission"<<endl<<endl;
    }

};
int main()
{
    round1 obj1[3];
        cout<<"Starting The Game"<<endl;
    for(int i = 1 ; i <=2 ;i++)
    {

      if(i==1)
        cout<<"TAKE INPUT FOR THE FIRST ROUND OF THE FIRST PERSON"<<endl;
      else
        cout<<"TAKE INPUT FOR THE FIRST ROUND OF THE SECOND PERSON"<<endl;
      obj1[i].input();
      if(obj1[i].calc_point() >= obj1[i].r1)
      {
        cout<<"Entered The First Round"<<endl;
        obj1[i].take_input();
        obj1[i].resort();
        obj1[i].play();
        obj1[i].print();
        if(obj1[i].check())
        {
          cout<<"Entered The Second Round"<<endl;
          cout<<"TAKE INPUT FOR THE SECOND ROUND"<<endl;
          round2  obj2(obj1[i]);
          obj2.take_input();
          obj2.calc_point();
          obj2.penalty_count();
          obj2.resort();
          obj2.play();
          obj1[i].score=obj2.score;
        }else{
          cout<<"Could not qualify in the second round"<<endl;
        }
      }else
      {
         if(i==1)
            cout<<"Mission Impossible for the first person"<<endl;
         else
            cout<<"Mission Impossible for the second person"<<endl;
      }

    }
    cout<<"Score of the first player is "<<obj1[1].score*100 / obj1[1].n <<endl;
    cout<<"Score of the second player is "<<obj1[2].score*100 / obj1[2].n<<endl<<endl;
    if( (obj1[1].score*100 / obj1[1].n == obj1[2].score*100 / obj1[2].n ))
        cout<<"Match Draw";
    else if(obj1[1].score*100/obj1[1].n > obj1[2].score*100 / obj1[2].n)
        cout<<"First Player Won The Match";
    else
        cout<<"Second Player Won The Match";
}
