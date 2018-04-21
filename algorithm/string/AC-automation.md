# AC 自动机
## 引入

## 模板
```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#define MAXN 1000200
namespace AC_Automation {
    struct Node {
        Node *next[26];
        Node *fail;
        int cnt;
        void Init() {
            for(int i=0; i<26; i++)
                next[i]=NULL;
            cnt=0;
            fail=NULL;
        }
    }*root;
    inline void Insert(char s[]){
        Node *p=root;//从root节点开始
        int len=strlen(s);
        for(int i=0,id;i<len;i++){
            id=s[i]-'a';
            if(p->next[id]==NULL){
                p->next[id]=new Node;
                p->next[id]->Init();
            }
            p=p->next[id];
        } 
        p->cnt++;//单词结束 Fix单词重复 
    }
    inline void Getfail(){
        std::queue<Node *> q;
        Node *u,*v,*p;
        p=root;
        q.push(p);
        while(!q.empty()){
            u=q.front();q.pop();
            for(int id=0;id<26;id++){
                v=u->next[id];
                if(v!=NULL){
                    if(u==root) v->fail=root;//词头失效
                    else{
                        p=u->fail;
                        while(p!=NULL){//匹配最大后缀 
                            if(p->next[id]!=NULL){
                                v->fail=p->next[id];
                                break;
                            }
                            p=p->fail;//更小的后缀
                        }
                        if(p==NULL) v->fail=root;//找不到后缀指向root 
                    } 
                    q.push(v);
                }
            }
        }
    }
    inline int Query(char s[]){
        int len=strlen(s),cnt=0,id;
        Node *p,*temp;
        p=root;
        for(int i=0;i<len;i++){
            id=s[i]-'a';
            while(p->next[id]==NULL&&p!=root) p=p->fail;
            p=p->next[id];
            if(p==NULL) p=root;
            temp=p;
            while(temp!=root){
                if(temp->cnt>=0) cnt+=temp->cnt,temp->cnt=-1;//>=0是为了继续匹配 
                else break;
                temp=temp->fail;
            } 
        }
        return cnt;
    } 
}
using namespace AC_Automation;
int n;
int main() {
    int T;
    char s[MAXN+10];
    scanf("%d",&T);
    while(T--){
        root=new Node;
        root->Init();
        root->fail=NULL;
        scanf("%d\n",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",s);
            Insert(s);
        }
        Getfail();
        scanf("%s",s);
        printf("%d\n",Query(s));
    }
    return 0;
}
```