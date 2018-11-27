#include <stdio.h>
#include <stdlib.h>
int login(FILE *fp1);
void delivered(FILE *fp2);
void add(FILE *fp2);
void update(FILE *fp2);
void pending(FILE *fp2);
void pass_update();
void display(FILE *fp);

struct Order
{
    int order_id;
    int product_id;
    char product_name[20];
    int qty;
    float price;
    float total_price;
    char cust_name[20];
    int status;
    char stat[20];
};
struct Log
{
    char user_name[20];
    char password[20];
};
int main()
{

    FILE *fp1=fopen("password.txt","a+");
    FILE *fp2=fopen("order.txt","a+");

    if(login(fp1)==1)
    {
        printf("login Success\n");
OP:
        printf("\n****Order Management System****\n");
        int opt;
        printf("1-New Order\n");
        printf("2-Pending Orders\n");
        printf("3-Order History\n");
        printf("4-Update Order\n");
        printf("5-Change User Name & Password\n");
        printf("6-Exit\n");
        printf("Choose the number of action you wish to preform:");
        scanf("%d",&opt);
        switch(opt)
        {
        case 1:
            add(fp2);
            goto OP;
            break;
        case 2:
            pending(fp2);
            goto OP;
            break;
        case 3:
            delivered(fp2);
            goto OP;
            break;
        case 4:
            update(fp2);
            goto OP;
            break;
        case 5:
            pass_update();
            goto OP;
            break;
        case 6:
            exit(0);
        default:
            printf("Select 1-6");
        }
    }
    else
    {
        printf("Wrong User Name or Password\n");
    }

    return 0;
}
int login(FILE *fp1)
{
    struct Log pass;
    char tmpUserName[20],tmpPass[20],ch;
    int login_status;
    int i=0;
    printf("User Name:");
    scanf("%s",&tmpUserName);
    printf("Password:");
    scanf("%s",tmpPass);
    while(fscanf(fp1,"%s\t%s",&pass.user_name,&pass.password)!=EOF)
    {
        if(!strcmp(pass.user_name,tmpUserName)&&!strcmp(pass.password,tmpPass))
        {
            login_status=1;
        }
        else
        {
            login_status=0;
        }
    }
    fclose(fp1);
    return login_status;
}
void delivered(FILE *fp2)
{
    struct Order look;
    fp2 = NULL;
    fclose(fp2);

    fp2=fopen("order.txt","r");

    while(fscanf(fp2,"%d\t\t%s\t\t%d\t\t%s\t\t%f\t\t%d\t%f\t%d",&look.order_id,look.cust_name,&look.product_id,look.product_name,&look.price,&look.qty,&look.total_price,&look.status)!=EOF)
    {
        if(look.status == 1)
        {
            strcpy(look.stat,"Delivered");
            printf("\n%d\t\t%s\t\t%s\t\t%.2f\t\t%s\n",look.order_id,look.cust_name,look.product_name,look.total_price,look.stat);
        }

    }fclose(fp2);
}
void add(FILE *fp2)
{
    struct Order item;
    fp2=fopen("order.txt","a+");
    item.order_id=rec_count(fp2)+1;
    printf("Order ID:%d\n",item.order_id);
    printf("Enter Customer Name:");
    scanf("%s",item.cust_name);
    printf("\nEnter Product ID:");
    scanf("%d",&item.product_id);
    printf("\nEnter Product Name:");
    scanf("%s",item.product_name);
    printf("\nEnter Unit Price:");
    scanf("%f",&item.price);
    printf("\nEnter Quantity:");
    scanf("%d",&item.qty);
    item.total_price=item.qty*item.price;
    printf("\nIf delivered select 1 pending 0:");
    scanf("%d",&item.status);
    if(item.status==0){
        strcpy(item.stat,"Pending");
    }else{
        strcpy(item.stat,"Delivered");
    }
    printf("%d\t\t%s\t\t%d\t\t%s\t\t%.2f\t\t%d\t%.2f\t%s\n",item.order_id,item.cust_name,item.product_id,item.product_name,item.price,item.qty,item.total_price,item.stat);
    fprintf(fp2,"%d\t\t%s\t\t%d\t\t%s\t\t%.2f\t\t%d\t%.2f\t%d\n",item.order_id,item.cust_name,item.product_id,item.product_name,item.price,item.qty,item.total_price,item.status);
    fclose(fp2);
}
void update(FILE *fp2)
{
    display(fp2);
    rewind(fp2);
    int recCount=rec_count(fp2);
    printf("\nRecord:%d",recCount);

    int id;
    printf("Choose Order Id:");
    scanf("%d",&id);
    int pro_id;
    char pro_name[20];
    int qty;
    float u_price;
    float t_price;
    char cu_name[20];
    int status;

    printf("Enter Customer Name:");
    scanf("%s",cu_name);
    printf("\nEnter Product ID:");
    scanf("%d",&pro_id);
    printf("\nEnter Product Name:");
    scanf("%s",pro_name);
    printf("\nEnter Unit Price:");
    scanf("%f",&u_price);
    printf("\nEnter Quantity:");
    scanf("%d",&qty);
    t_price=qty*u_price;
    printf("\nIf delivered select 0 pending 1:");
    scanf("%d",status);




    struct Order otemp;
    struct Order temp[recCount];

    //rewind(fp2);
    fp2 = NULL;
    fclose(fp2);

    fp2=fopen("order.txt","a+");

    int loopCount=0;
    while(fscanf(fp2,"%d\t\t%s\t\t%d\t\t%s\t\t%f\t\t%d\t%f\t%d",&otemp.order_id,otemp.cust_name,&otemp.product_id,otemp.product_name,&otemp.price,&otemp.qty,&otemp.total_price,&otemp.status)!=EOF)
    {

        temp[loopCount].order_id=otemp.order_id;
        strcpy(temp[loopCount].cust_name,otemp.cust_name);
        temp[loopCount].product_id=otemp.product_id;
        strcpy(temp[loopCount].product_name,otemp.product_name);
        temp[loopCount].price=otemp.price;
        temp[loopCount].qty=otemp.qty;
        temp[loopCount].total_price=otemp.total_price;
        temp[loopCount].status=otemp.status;


        if(otemp.order_id == id)
        {
            strcpy(temp[loopCount].cust_name,cu_name);
            temp[loopCount].product_id=pro_id;
            strcpy(temp[loopCount].product_name,pro_name);
            temp[loopCount].price=u_price;
            temp[loopCount].qty=qty;
            temp[loopCount].total_price=t_price;
            temp[loopCount].status=status;
            printf("\n%d\t\t%s\t\t%d\t\t%s\t\t%.2f\t\t%d\t%.2f\t%d",temp[loopCount].order_id,temp[loopCount].cust_name,temp[loopCount].product_id,temp[loopCount].product_name,temp[loopCount].price,temp[loopCount].qty,temp[loopCount].total_price,&temp[loopCount].status);
        }
        loopCount++;
    }
    fileWrite(temp,recCount);

}
int rec_count(FILE *fp2)
{
    fp2 = NULL;
    fclose(fp2);
    fp2 = fopen("order.txt","r");
    int lineCount=0;
    char ch=getc(fp2);
    while(ch!=EOF)
    {
        if(ch=='\n')
        {
            lineCount++;
        }
        ch=getc(fp2);

    }
    return lineCount;
}
void fileWrite(struct Order temp[],int recCount)
{
    FILE *fp4=fopen("order.txt","w");
    int str_loop=0;
    for(str_loop=0; str_loop<recCount; str_loop++)
    {
        fprintf(fp4,"%d\t\t%s\t\t%d\t\t%s\t\t%.2f\t\t%d\t%.2f\t%d\n",temp[str_loop].order_id,temp[str_loop].cust_name,temp[str_loop].product_id,temp[str_loop].product_name,temp[str_loop].price,temp[str_loop].qty,temp[str_loop].total_price,temp[str_loop].status);
    }
    fclose(fp4);
}
void pending(FILE *fp2)
{
    int p=0;
    struct Order look;
    fp2 = NULL;
    fclose(fp2);

    fp2=fopen("order.txt","r");

    while(fscanf(fp2,"%d\t\t%s\t\t%d\t\t%s\t\t%f\t\t%d\t%f\t%d",&look.order_id,look.cust_name,&look.product_id,look.product_name,&look.price,&look.qty,&look.total_price,&look.status)!=EOF)
    {
        if(look.status == 0)
        {p++;
            strcpy(look.stat,"Pending");
            printf("\n%d\t\t%s\t\t%s\t\t%.2f\t\t%s\n",look.order_id,look.cust_name,look.product_name,look.total_price,look.stat);
        }

    }printf("Number of pending orders:%d",p);
}


void pass_update()
{
    char new_User[20],new_Pass[20];
    printf("Enter New User Name:");
    scanf("%s",&new_User);
    printf("\nEnter New Password:");
    scanf("%s",&new_Pass);
    FILE *fp3=fopen("password.txt","w");
    fprintf(fp3,"%s\t%s",new_User,new_Pass);
    fclose(fp3);
}
void display(FILE *fp){
fclose(fp);
fp=fopen("order.txt","r");
char ch=getc(fp);
    while(ch!=EOF)
    {
        printf("%c",ch);
        ch=getc(fp);
    }
    fclose(fp);
}
