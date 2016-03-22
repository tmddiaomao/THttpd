#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "sql_connect.h" //sql_connect.h

const std::string _remote_ip = "127.0.0.1";
const std::string _remote_user = "root";
const std::string _remote_passwd = "";
const std::string _remote_db = "student_dd";

int main()
{
	int content_length = -1;
	char method[1024];
	char query_string[1024];
	char post_data[4096];
	memset(method,'\0',sizeof(method));
	memset(query_string,'\0',sizeof(query_string));
	memset(post_data,'\0',sizeof(post_data));
	strcpy(method,getenv("REQUEST_METHOD"));
	std::cout<<"<html>"<<std::endl;
	std::cout<<"<head>show student</head>"<<std::endl;
	std::cout<<"<body>"<<std::endl;
	if( strcasecmp("POST",method) == 0){
                content_length = atoi(getenv("CONTENT_LENGTH"));
                int i = 0;
                for(;i < content_length;i++){
                        read(0,&post_data[i],1);
                }
                post_data[i]='\0';
         //       write(2, post_data, sizeof(post_data));
	}
//	printf("%s\n",post_data);
	int i = 0;
	while(post_data[i]!='\0'){
		if(post_data[i] == '&' || post_data[i] == '='){
 			post_data[i]=' ';
		}
		i++;
	}
//	printf("post_data:%s\n",post_data);	
	char name[64];
	char age[64];
	char school[64];
	char hobby[64];
	memset(name,'\0',sizeof(name));
	memset(age,'\0',sizeof(age));
	memset(hobby,'\0',sizeof(hobby));
	memset(school,'\0',sizeof(school));
	sscanf(post_data,"%*s %s %*s %s %*s %s %*s %s",name,age,school,hobby);
//	printf("post_data:%s\n",post_data);	
	//std::string insert_data = "'name',age,'school','hobby'";
	std::string insert_data;
	insert_data+="'";
	insert_data+=name;
	insert_data+="',";
	insert_data+=age;
	insert_data+=",'";
	insert_data+=school;
	insert_data+="',";
	insert_data+="'";
	insert_data+=hobby;
	insert_data+="'";
	const std::string _host = _remote_ip;
	const std::string _user = _remote_user;
	const std::string _passwd = _remote_passwd;
	const std::string _db = _remote_db;
	sql_connecter conn(_host,_user,_passwd,_db);
	conn.begin_connect();
	conn.insert_sql(insert_data);
	
	std::string _sql_data[1024][5];
        std::string header[5];
        int curr_row = -1;
	
	conn.select_sql(header,_sql_data,curr_row);
        std::cout<<"<table border=\"1\">"<<std::endl;
        std::cout<<"<tr>"<<std::endl;
	
       for(int i = 0;i<5;i++){
               std::cout<<"<th>"<<header[i]<<"</th>"<<std::endl;
       }
       std::cout<<"</tr>"<<std::endl;//std::cout<<"</tr>"<<std::cout
       for(int i = 0;i<curr_row;i++){
               std::cout<<"<tr>"<<std::endl;
               for(int j=0;j<5;j++){
                       std::cout<<"<td>"<<_sql_data[i][j]<<"</td>"<<std::endl;
               }
               std::cout<<"</tr>"<<std::endl;
       }
        std::cout<<"</table>";
        std::cout<<"</body>"<<std::endl;
        std::cout<<"</html>"<<std::endl;
}
