#include<bits/stdc++.h>
using namespace std;
int m,n,res;
typedef pair<int, int> Point;
int MX=100000;

struct NODE
{
    int cnt;
    bool vis;
    NODE *next[27];
    vector <NODE *> out;
    NODE()
    {
        for(int i = 0; i < 27; i++)
        {
            next[i] = NULL;
        }
        out.clear();
        vis = false;
        cnt=0;
    }

    ~NODE()
    {
        for(int i = 1; i < 27; i++)
            if(next[i] != NULL && next[i] != this)
                delete next[i];
    }
}*root;

void buildtrie(string dictionary[],int n)     {

    root = new NODE();


    for(int i = 0; i < n; i++)
    {
        NODE *p = root;
        for(int j = 0; dictionary[i][j] ; j++)
        {
            char c = dictionary[i][j]- 'a' + 1;
            if(!p->next[c])
                p->next[c] = new NODE();
            p = p->next[c];
        }
    }


    queue <NODE *> q;
    for(int i = 0; i < 27; i++)
    {
        if(!root->next[i])
            root->next[i] = root;
        else
        {
            q.push(root->next[i]);
            root->next[i]->next[0] = root;

        }
    }


    while(!q.empty())
    {
        NODE *u = q.front();
        q.pop();

        for(int i = 1; i < 27; i++)
        {
            if(u->next[i])
            {
                NODE *v = u->next[i];
                NODE *w = u->next[0];
                while( !w->next[i] )
                    w = w->next[0];
                v->next[0] = w = w->next[i];
                w->out.push_back(v);

                q.push(v);
            }
        }
    }
}

void aho_corasick(NODE *p, string word)
{
    for(int i = 0; word[i]; i++)
    {
        char c = word[i]-'a'+1 ;
        while(!p->next[c])
            p = p->next[0];
        p = p->next[c];
        p->cnt++;
    }
}

int dfs( NODE *p )
{
    if(p->vis) return p->cnt;
    for(int i = 0; i < p->out.size(); i++)
        p->cnt += dfs(p->out[i]);
    p->vis = true;
    return p->cnt;
}

string query ;
string  dictionary[507];

int main()
{
    int t, tc, y, z;
    int i, j, k, l, h;
    char ch;
    scanf ("%d", &tc);
    for (t = 1; t <= tc; t++)
    {
        int n;
        scanf("%d",&n);

        cin>>query;

        for (int i=0; i<n; ++i)
        {
            cin>>dictionary[i];
        }

        buildtrie(dictionary, n);

        aho_corasick(root, query);

        printf("Case %d:\n",t);

        for(int i = 0; i < n; i++)
        {
            NODE *p = root;
            for(int j = 0; dictionary[i][j]; j++)
            {
                char c = dictionary[i][j] -'a' +1;
                p = p->next[c];
            }
            printf("%d\n", dfs(p));
        }
        delete root;
    }

    return 0;
}
