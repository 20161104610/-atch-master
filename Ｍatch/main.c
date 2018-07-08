#include <stdio.h>
#include <string.h>

int tnum;

struct Student {
    char name[10];//姓名
    char sex;//性别
    char proname[20];//节目名称
    char prochoo[20];//节目类别
    char classname[10];//班级名称
    char phonenum[20];//电话号码
    int sorce[5];//分数
    double fasorce;//最终得分
};

typedef struct Student ElmtypeS;

typedef struct{
    ElmtypeS elem[30];
    int last;
}SeqlistS;

struct Teacher{
    char name[10];//姓名
    char sex[5];//性别
    char phonenum[20];//电话号码
};

typedef struct Teacher ElmtypeT;

typedef struct{
    ElmtypeT elem[5];
    int lastT;
}SeqlistT;



int menu(){//菜单栏
    int m=0;
    printf("|  ------------------------------------  |\n");
    printf("|               节目记分系统❤️             |\n");
    printf("|  ------------------------------------  |\n");
    printf("|              ✨1----节目信息            |\n");
    printf("|              ✨2----录入裁判信息         |\n");
    printf("|              ✨3----录入得分            |\n");
    printf("|              ✨4----节目排名            |\n");
    printf("|              ✨5----裁判信息            |\n");
    printf("|              ✨0----退出系统            |\n");
    printf("|  ------------------------------------  |\n");
    printf("输入数字以进行操作：\n");
    scanf("%d",&m);
    return m;
}

void save(SeqlistT *L,int n){//保存
    FILE *fw;
    int i;
    fw=fopen("//Users//h20161104610//Desktop//teachers.csv","w");
    for(i=0;i<n;i++){
        fprintf(fw,"%s %s %s\n",L->elem[i].name,L->elem[i].sex,L->elem[i].phonenum);
    }
    fclose(fw);
}

void loads(SeqlistS *L){//读取数据
    FILE *fr;
    fr=fopen("//Users//h20161104610//Desktop//workers.csv","r+");
    if(fr == NULL){
        printf("读取文件失败!\n");
    }
    else{
        int i,j;
        L->last=0;
        char name[10];
        char sex;
        char pname[20];
        char pchoo[20];
        char cname[10];
        char pnum[20];
        while(fscanf(fr,"%d %s %c %s %s %s %s\n",&j,name,&sex,pname,pchoo,cname,pnum)!=EOF){
            i=j-1;
            strcpy(L->elem[i].name,name);
            L->elem[i].sex=sex;
            strcpy(L->elem[i].proname,pname);
            strcpy(L->elem[i].prochoo,pchoo);
            strcpy(L->elem[i].classname,cname);
            strcpy(L->elem[i].phonenum,pnum);
            L->last++;
        }
        printf("文件读取成功!\n");
        fclose(fr);
    }
}

void teachers(SeqlistT *L){//录入裁判信息
    int i;
    int n;
    FILE *fw=fopen("//User//h20161104610//Desktop//teachers.csv", "w");
    printf("请输入裁判数量:\n");
    scanf("%d",&n);
    tnum=n;
    L->lastT=n;
    for(i=0;i<n;i++){
        printf("请输入第%d个裁判的姓名：\n",i+1);
        scanf("%s",L->elem[i].name);
        printf("请输入第%d个裁判的性别：\n",i+1);
        scanf("%s",L->elem[i].sex);
        printf("请输入第%d个裁判的电话号码：\n",i+1);
        scanf("%s",L->elem[i].phonenum);
    }
    fclose(fw);
    save(L,n);
}

void input(SeqlistS *L,int n){
    int i,j,k,h,z=0;
    float fs=0;
    for(i=0;i<30;i++){
        printf("请输入给第%d小组的评分:\n",i+1);
        for(k=0;k<n;k++){
            printf("第%d位评委评分:\n",k+1);
            scanf("%d",&L->elem[i].sorce[k]);
        }
        
        for(k=0;k<n;k++){
            for(h=0;h<n-k;k++){
                if(L->elem[i].sorce[k]>=L->elem[i].sorce[k+1]){
                    z=L->elem[i].sorce[k];
                    L->elem[i].sorce[k]=L->elem[i].sorce[k+1];
                    L->elem[i].sorce[k+1]=z;
                }
            }
            
        }
        if(n>2){
            for(k=1;k<n-1;k++){
                fs=fs+L->elem[i].sorce[k];
            }
            fs=fs/(n-2);
            L->elem[i].fasorce=fs;
            printf("第%d小组的最终得分为:\n",i+1);
            printf("%.2f\n",fs);
        }
        else{
            for(k=0;k<n;k++){
                fs=fs+L->elem[i].sorce[k];
            }
            fs=fs/n;
            L->elem[i].fasorce=fs;
            printf("第%d小组的最终得分为:\n",i+1);
            printf("%.2f\n",fs);
        }
        
        printf("|  ------------------------------------  |\n");
        printf("|              是否继续进行评分❤️           |\n");
        printf("|  ------------------------------------  |\n");
        printf("|               ✨是------(1)            |\n");
        printf("|               ✨否------(0)            |\n");
        printf("|  ------------------------------------  |\n");
        scanf("%d",&j);
        if(j==0){
            break;
        }
    }
    
}

void shows(SeqlistS *L){
    int i,j;
    j=L->last;
    if(j>=0){
        printf("| 姓名 | 性别 | 节目名称 | 节目类别 | 班级 | 电话号码 |\n");
        for(i=0;i<=L->last;i++){
            printf("|   %s   |   %c   |   %s   |   %s   |   %s   |   %s   |\n",L->elem[i].name,L->elem[i].sex,L->elem[i].proname,L->elem[i].prochoo,L->elem[i].classname,L->elem[i].phonenum);
        }
    }
    else{
        printf("      ---------没有可以显示的信息!\n");
    }
    
}

void showsort(SeqlistS *L){
    int i,j;
    j=L->last;
    if(j>=0){
        printf("| 姓名 | 性别 | 节目名称 | 节目类别 | 班级 | 电话号码 |  得分  |\n");
        for(i=0;i<=L->last;i++){
            printf("|   %s   |   %c   |   %s   |   %s   |   %s   |   %s   |  %.2lf  |\n",L->elem[i].name,L->elem[i].sex,L->elem[i].proname,L->elem[i].prochoo,L->elem[i].classname,L->elem[i].phonenum,L->elem[i].fasorce);
        }
    }
    else{
        printf("      ---------没有可以显示的信息!\n");
    }
    
}


void showt(SeqlistT *L){
    int i,j;
    j=L->lastT;
    if(j>=0){
        printf("| 姓名 | 性别 | 电话号码 |\n");
        for(i=0;i<tnum;i++)
        {
            printf("|%-6s|%-6s|%-6s|\n",L->elem[i].name,L->elem[i].sex,L->elem[i].phonenum);
        }
    }
    else{
        printf("      ---------没有可以显示的信息!\n");
    }
    
}

void sort(SeqlistS *L){//排序
    int i,j;
    int s=0;
    printf("开始排序:\n");
    for(i=0;i<30;i++){
        for(j=0;j<30-i;j++){
                if(L->elem[j].fasorce<L->elem[j+1].fasorce){
                   s=L->elem[j].fasorce;
                   L->elem[j].fasorce=L->elem[j+1].fasorce;
                   L->elem[j+1].fasorce=s;
                }
        }
    }
}


void display(int h,SeqlistS *ls,SeqlistT *lt){
            switch(h){
                case 1://节目信息 从文件中读取✅
                    loads(ls);
                    shows(ls);
                    break;
                case 2://裁判信息 开始录入✅
                    teachers(lt);
                    break;
                case 3://录入得分并计算最终得分✅
                    input(ls,tnum);
                    break;
                case 4://排序 节目得分排序✅
                    sort(ls);
                    showsort(ls);
                    break;
                case 5://显示裁判信息✅
                    showt(lt);
                    break;
                case 0://退出系统✅
                    break;
                default:
                    printf("输入类型错误!\n");
            }}

int main(){
    SeqlistS ls;
    SeqlistT lt;
    ls.last=-1;
    lt.lastT=-1;
    int h=0;
    int m;
    
    while(1){
        h=menu();
        if(h==0){
            return 0;
        }
        else{
            display(h,&ls,&lt);
            //disinput(&ls,&lt);
            printf("|  ------------------------------------  |\n");
            printf("|                回到主菜单？❤️            |\n");
            printf("|  ------------------------------------  |\n");
            printf("|               ✨是------(1)            |\n");
            printf("|               ✨否------(0)            |\n");
            printf("|  ------------------------------------  |\n");
            scanf("%d",&m);
            if(m==1){
                h=menu();
                display(h,&ls,&lt);
            }
            else if(m==0){
                return 0;
            }
            else{
                printf("输入类型错误!\n");
            }
        }
    }
    return 0;
}
