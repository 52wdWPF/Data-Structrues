#include<iostream>
#include<cstdlib>

#define MALLOC(a, n, type) {\
    if(!((a)=(type)malloc(n))) {\
        std::cout<<"It malloc fail"<<std::endl;\
        exit(EXIT_FAILURE);\
    }\
}
#define COMPARE(a, b) a>b?1:b==a?0:-1

struct polyPointer{
    float coef;
    float expon;
    polyPointer *next;
};

void M_poly(polyPointer *&a){
    polyPointer *temp, *p;
    int flag=0;
    float t_coef, t_expon;
    std::cout<<"请输入系数和指数, 系数和指数同时为0时结束输入"<<std::endl;
    std::cin>>t_coef>>t_expon;
    while(t_expon || t_coef){
        if(!t_expon) {std::cin>>t_coef>>t_expon; continue;}
        MALLOC(temp, sizeof(polyPointer), polyPointer *);
        temp->coef=t_coef;
        temp->expon=t_expon;
        if(!flag) {a=temp;flag=1;}
        else {
            p->next=temp;
        }
        p=temp;
        std::cin>>t_coef>>t_expon;
    }
    p->next=NULL;
}

void attach(float cofficient, int exponent, polyPointer *&ptr){
    if(!cofficient) return;
    polyPointer *temp;
    MALLOC(temp, sizeof(polyPointer), polyPointer *);
    temp->coef=cofficient;
    temp->expon=exponent;
    ptr->next=temp;
    ptr=temp;
}

polyPointer *padd(polyPointer *a, polyPointer *b){
    polyPointer *c, *rear, *temp;                        //其中rear为尾节点
    MALLOC(rear, sizeof(polyPointer), polyPointer *);
    c=rear;
    while(a && b)
        switch (COMPARE(a->expon, b->expon)){
            case -1:
                attach(b->coef, b->expon, rear);
                b=b->next;
                break;
            case 0:
                attach(b->coef+a->coef, b->expon, rear);
                b=b->next;
                a=a->next;
                break;
            case 1:
                attach(a->coef, a->expon, rear);
                a=a->next;
        }
    if(!a)
        while(b){
            attach(b->coef, b->expon, rear);
            b=b->next;
        }
    if(!b)
        while(a){
            attach(a->coef, a->expon, rear);
            a=a->next;
        }
    rear->next=NULL;                            //尾指针置空
    temp=c;
    c=c->next;
    free(temp);
    return c;
}

void PrintPoly(polyPointer *a){
    while(a){
        if(a->coef!=1){
            std::cout<<a->coef;
        }
        std::cout<<'x'<<a->expon;
        a=a->next;
        if(a) std::cout<<'+';
    }
}

int main(){
    polyPointer *a_p, *b_p, *c_p;
    M_poly(a_p);
    M_poly(b_p);
    c_p=padd(a_p, b_p);
    PrintPoly(a_p);
    std::cout<<'+';
    PrintPoly(b_p);
    std::cout<<'=';
    PrintPoly(c_p);
    std::cout<<std::endl;
    //当然还要释放空间free...
    return 0;
}
