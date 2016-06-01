#include"iostream.h"
#include"string.h"
#include"fstream.h"
#include<windows.h>
//#include<stdlib.h>
#include <iomanip.h>
/************************定义读者类***********************************/

       class Reader 
       {
	    private:
	        int tag;             //删除标记   1：已删   0：末删
	        int no;              //读者编号  
		    char name[15];       //读者姓名
		    int borbook[Maxbor]; //所借图书
           
         public:
           Reader(){}
           char *getname()        //获取姓名
              {return name;}
           int gettag()           //获取删除标记
              {return tag;}
           int getno()            //获取读者编号
              {return no;}
		 
           void setname(char na[]) //设置姓名
              {
                 strcpy(name,na);
              }

           void delbook()          //设置删除标记
              {tag=1;}
           void addreader(int n,char *na)      //增加读者
              {
                tag=0;
                no=n; 
                strcpy(name,na);
                for(int i=0;i<Maxbor;i++)
                  borbook[i]=0;
               }

            void borrowbook(int bookid)             //借书操作
               {
                 for(int i=0;i<Maxbor;i++)
                   {
                     if(borbook[i]==0)
                       {
                          borbook[i]=bookid;
						  cout<<"\t\t\t\t借书成功"<<endl; 
                          return ;
                       }
                    }
                }
             int retbook(int bookid)             //还书操作
                {
                   for(int i=0;i<Maxbor;i++)
                     {
                       if(borbook[i]==bookid)
                         {
                           borbook[i]=0;
						   cout<<"\t\t\t\t还书成功"<<endl;
                           return 0;
                          }
					  
                      }
                      cout<<"\t\t\t\t还书失败"<<endl;
                      return 0; 
                 }
              void disp()             //输出读者信息
                 {
                   cout<<setw(30)<<no<<setw(15)<<name<<"              借书编号：[";
                   for(int i=0;i<Maxbor;i++)
                         if(borbook[i]!=0)
                            cout<<borbook[i] ;
                    cout<<"]"<<endl;
				
                  }
       }; 
/*************************定义读者库类**********************************************/
 
       class RDatabase
       {
         private:
           int top;                 //读者记录指针
           Reader read[Maxr];       //读者记录
         public:
           RDatabase()
           {
              Reader s;             //建立读者类的对象s
              top=-1;               
              fstream file("reader.txt",ios::in);        //构造函数，将reader.txt读到read[]中
              while(1)
              {
                   file.read((char *)&s,sizeof(s));
                   if(!file)
                     break;
                   top++;
                   read[top]=s;
               }
               file.close();
            }
            void clear()               //删除所有读者信息
            {
               top=-1;
            }
            int addreader(int n,char *na)        //添加读者时先查找是否存在
            {
                Reader *p=query(n);
                if (p==NULL)
                {
                    top++;
                    read[top].addreader(n,na);
                    return 1;
                 }
                 return 0;
            }
            Reader *query(int readerid)       //按编号查找
            {
                for(int i=0;i<=top;i++)
                  if(read[i].getno()==readerid&&read[i].gettag()==0)
					  return &read[i];
                return NULL;
            }
            void disp()                  //输出所有信息
            {

               for(int i=0;i<=top;i++)
				 
                 read[i].disp();
            }
            void readerdata();          //读者维护 
            ~RDatabase()                //析构函数，将read[]写入reader.txt文件
            {
               fstream file("reader.txt",ios::out);
               for(int i=0;i<=top;i++)
                    if(read[i].gettag()==0)
                        file.write((char *)&read[i],sizeof(read[i]));
               file.close();
            }
       };
       void RDatabase::readerdata()       //读者库维护
       {
           int choice=1;
           char rname[20];
           int readerid;
           Reader *r;
           while(choice!=0)
           {
             cout<<"\t\t\t★☆★☆★☆读者维护★☆★☆★☆"<<endl<<"\t\t\t\t1：新增"<<endl<<"\t\t\t\t2：更改"<<endl<<"\t\t\t\t3：删除"<<endl<<"\t\t\t\t4：查找"<<endl<<"\t\t\t\t5：显示"<<endl<<"\t\t\t\t6：全删"<<endl<<"\t\t\t\t0：退出=>"<<endl;
             cin>>choice;
             switch(choice)
             {
                case 1:
                        cout<<"\t\t\t\t输入读者编号:";
                        cin>>readerid;
                        cout<<"\t\t\t\t输入读者姓名:";
                        cin>>rname;
                        addreader(readerid,rname);
                        break;
                case 2:
                        cout<<"\t\t\t\t输入读者编号:";
                        cin>>readerid;
                        r=query(readerid);
                        if(r==NULL)
                        {
                             cout<<"\t\t\t\t该读者不存在"<<endl;
                             break;
                        }
                        cout<<"\t\t\t\t输入新的姓名:";
                        cin>>rname;
                        r->setname(rname);
                        break;
                case 3:
                        cout<<"\t\t\t\t输入读者编号:";
                        cin>>readerid;
                        r=query(readerid);
                        if (r=NULL)
                        {
                           cout<<"\t\t\t\t该读者不存在:"<<endl;
                           break;
                        }
                        r->delbook();
                        break;
                case 4:
                        cout<<"\t\t\t\t输入读者编号:";
                        cin>>readerid;
                        r=query(readerid);
                        if(r==NULL)
                        {
                            cout<<"\t\t\t\t该读者不存在:"<<endl;
                            break;
                        }
						else
						{
						cout<<"\t\t\t读者编号         读者姓名"<<endl;
                        r->disp();
						}
                        break;
                case 5:
                        cout<<"\t\t\t读者编号         读者姓名"<<endl;
                        disp(); 
                        break;
                case 6:
                        clear();
                        break;
             } 
           } 
        }