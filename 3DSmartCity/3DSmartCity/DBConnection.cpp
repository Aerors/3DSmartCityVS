#include "StdAfx.h"
#include "DBConnection.h"


DBConnection::DBConnection(void)
{
}

DBConnection::~DBConnection(void)
{
}

bool DBConnection::ConnectToDB(PGconn *&conn,char *pghost,char *pgport,char *dbname,char *user,char *pwd)
{
	char * pgoptions, *pgtty;
	pgoptions=NULL;
	pgtty=NULL;

	conn=PQsetdbLogin(pghost,pgport,pgoptions,pgtty,dbname,user,pwd);	
	if (PQstatus(conn)==CONNECTION_BAD)
	{
		std::cout<<"Connection db "<<dbname<<" failed!"<<std::endl;
		std::cout<<PQerrorMessage(conn)<<std::endl;
		return false;
	} 
	else
	{
		std::cout<<"Connection db "<<dbname<<" sucess!"<<std::endl;
		return true;
	}
}

bool DBConnection::ConnectToDB(char *pghost,char *pgport,char *dbname,char *user,char *pwd)
{
	char * pgoptions, *pgtty;
	pgoptions=NULL;
	pgtty=NULL;

	conn=PQsetdbLogin(pghost,pgport,pgoptions,pgtty,dbname,user,pwd);	
	if (PQstatus(conn)==CONNECTION_BAD)
	{
		std::cout<<"Connection db "<<dbname<<" failed!"<<std::endl;
		std::cout<<PQerrorMessage(conn)<<std::endl;
		return false;
	} 
	else
	{
		std::cout<<"Connection db "<<dbname<<" sucess!"<<std::endl;
		return true;
	}
}



PGresult * DBConnection::ExecSQL(PGconn * conn,const char *sql, int * row_num)
{
	PGresult *res=NULL;
	if (conn==NULL)
	{
		std::cout<<"connection is null"<<std::endl;
		return NULL;
	} 
	else
	{
		PQsetClientEncoding(conn,"gbk");
		res=PQexec(const_cast<PGconn *>(conn),sql);	
		*row_num=PQntuples(res);
	}
	return res;
}

PGresult * DBConnection::ExecSQL(const char *sql)
{
	PGresult *res=NULL;
	if (conn==NULL)
	{
		std::cout<<"connection is null"<<std::endl;
		return NULL;
	} 
	else
	{
		PQsetClientEncoding(conn,"gbk");
		res=PQexec(conn,sql);
	}
	return res;
}

void DBConnection::ParseResult(PGresult* res,vector<PipePoint>& pts)
{
	// 输出记录： 记录数和所有字段
	/*（2）元组数函数
		extern int PQntuples(const PGresult *res)
		返回值：查询集中记录数
		*/
    int tuple_num=PQntuples(res);

	/*
	（3）字段数函数
		extern int PQnfields(const PGresult *res)
		返回值：每条记录中列数（字段数）；
		res：查询集指针；
	*/
	int i,j,k;
    int field_num=PQnfields(res);
	vector<PipePoint>::iterator itor;
	pts.clear();
	pts.resize(2*tuple_num);
	for(i=0,itor=pts.begin(),k=0;i<tuple_num;++i,itor+=2,k+=2)
    {
		PipePoint lle[2];
		char *ptf,*elef,*ptt,*elet;
        for(j=0;j<field_num;++j)
			/*
			（4）取值函数
				extern char *PQgetvalue(const PGresult *res, int tup_num, int field_num);
				返回值：查询集中每个位置的值；
				res：查询集指针；
				tup_num：行号，从0开始；
				field_num：列号，从0开始；
			*/
            /*cout<<PQgetvalue(res,i,j)<<" ";*/
		{
			char* s = PQgetvalue(res,i,j);
			if(j==1)
			{	ptf = s;
			}
			else if(j==2)
			{elef = s;
			}
			else if(j==3)
			{ptt = s;
			}
			else if(j==4)
			{elet = s;
			}
			
		}
		lle[0] = PipePoint(ptf,elef);
		lle[1] = PipePoint(ptt,elet);
	
		pts[k] = lle[0];
		pts[k+1] = lle[1];
		
    }
}