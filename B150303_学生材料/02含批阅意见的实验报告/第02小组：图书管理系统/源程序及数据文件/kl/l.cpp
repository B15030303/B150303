#include"iostream.h"
#include"string.h"
#include"fstream.h"
#include<windows.h>
//#include<stdlib.h>
#include <iomanip.h>
#include"book.h"
#include"reader.h"

/*****************************心形图形***************************/
int n=9;
void draw(int n)
{
int i,j;
for (i=1-(n>>1);i<=n;i++)
if (i>=0)
{
for (j=0;j<i;j++) cout<<"  ";
for (j=1;j<=2*(n-i)+1;j++) cout<<" *";
cout<<"\n";
}
else
{
for (j=i;j<0;j++) cout<<"  ";
for (j=1;j<=n+2*i+1;j++)  cout<<" *";
for (j=1;j<=-1-2*i;j++) cout<<"  ";
for (j=1;j<=n+2*i+1;j++) cout<<" *";
cout<<"\n";
}
}

/*********************顶层菜单函数****************************/
void menu( )        
{
	cout<<"\n\n\n\n";
cout << "\t********************欢迎使用图书管理系统********************" << endl;
		cout << "\t  --------------------------------------------------------  " << endl;
		cout << "\t |                 【(1)     借  书    】                 |" << endl;
		cout << "\t |                 【(2)     还  书    】                 |" << endl;
		cout << "\t |                 【(3)    图书维护   】                 |" << endl;
		cout << "\t |                 【(4)    读者维护   】                 |" << endl;
		cout << "\t |                 【(0)    退出系统   】                 |" << endl;
		cout << "\t  --------------------------------------------------------  " << endl;
	

		cout << "\t******************请选择数字键选择相应的服务****************" << endl;


}
/**************************密码***********************/
void order()/*指令操作模块*/
{
    char passwd[]="B150303";/*设置密码*/
    char str[7];
    int i=0;
	
    cout<<"请输入密码（#号键结束）:\n";
	
    while( (str[i]=cin.get() ) !='#')/*逐字符读入，'#'作为结束标志*/
    {
       if(str[i]!='\n')
        { 
           cout<<"*";
           i++;
         }
     }
     str[i]='\0';/*增加字符串结束标志*/
     if(strcmp(str,passwd)==0)
     {
        cout<<"\n登陆成功！\n";
        
      }
      else
      {
         cout<<"\n密码错误,请重新输入：\n";
         order();
       }
 }
/*************************主函数*******************************/
int main()
{
    
	system("Color fb");
      draw(n);
   order();
	system ("cls");
		cout << endl ;
		cout << " \t     *   * ";cout << " ***** ";cout << " *     ";cout << " ***** ";cout << " ***** ";cout << " *   * ";cout << " ***** ";cout << "   *       "<<endl;
        cout << " \t     * * * ";cout << " *     ";cout << " *     ";cout << " *     ";cout << " *   * ";cout << " ** ** ";cout << " *     ";cout << "   *       "<<endl;
        cout << " \t     * * * ";cout << " ***** ";cout << " *     ";cout << " *     ";cout << " *   * ";cout << " * * * ";cout << " ***** ";cout << "   *       "<<endl;
        cout << " \t     ** ** ";cout << " *     ";cout << " *     ";cout << " *     ";cout << " *   * ";cout << " *   * ";cout << " *     ";cout << "           "<<endl;
        cout << " \t     *   * ";cout << " ***** ";cout << " ***** ";cout << " ***** ";cout << " ***** ";cout << " *   * ";cout << " ***** ";cout << "   *       "<<endl;
        cout<<endl;
  int choice=1;             
          int bookid;               //定义图书编号
          int readerid;             //定义读者编号          
          RDatabase ReaderDB;       //定义读者库类的对象
          Reader *r;                //定义读者类的对象
          BDatabase BookDB;         //定义图书库类的对象
          Book *b;                  //定义图书类的对象
          while(choice!=0)
          {
			  
                menu( );

    cin>>choice;
	    if(choice>4)  
                  break; 
	    switch(choice)
            {
               case 1:
                       cout<<"\t\t\t★☆★☆★☆借书★☆★☆★☆"<<endl<<"\t\t\t\t读者编号:"<<endl;
                       cin>>readerid;
                       cout<<"\t\t\t\t图书编号: ";
                       cin>>bookid;
                       r=ReaderDB.query(readerid);
                       if(r==NULL)
                       {
                            cout<<"\t\t\t\t不存在该读者，不能借书"<<endl;
                            break;
                       }
                       b=BookDB.query(bookid);
                       if(b==NULL)
                       {
                             cout<<"\t\t\t\t不存在该图书，不能借书"<<endl;
                             break;
                       }
                       if (b->borrowbook()==0)
                       {
                          cout<<"\t\t\t\t该图书已借出，不能借书"<<endl;
                          break;
                       }
                       r->borrowbook(b->getno());
                       break;
                case 2:
                       cout<<"\t\t\t★☆★☆★☆还书★☆★☆★☆"<<endl<<"\t\t\t\t读者编号:"<<endl;
                       cin>>readerid;
                       cout<<"\t\t\t\t图书编号:";
                       cin>>bookid;
                       r=ReaderDB.query(readerid);
                       if(r==NULL)
                       {
                            cout<<"\t\t\t\t不存在该读者，不能还书"<<endl;
                            break;
                       }
                       b=BookDB.query(bookid);
                       if(b==NULL)
                       {
                             cout<<"\t\t\t\t不存在该图书，不能还书"<<endl;
                             break;
                       }
                       b->retbook();
                       r->retbook(b->getno());
                       break;
               case 3:
                       BookDB.bookdata();
                       break;
               case 4:
                       ReaderDB.readerdata();
                       break;
            }
          }
       

	return 0;
}