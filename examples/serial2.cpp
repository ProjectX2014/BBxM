#include <iostream>
#include <fstream>

#include <fcntl.h>

using namespace std;


#include "includes.h"
#include "sources.h"


int main()
{
	cout<<endl;
	
	
	
	int fd1;

	int fd2;

	char * buff = new char[2];

	int wr,rd,nbytes,tries;	
	
	
	fcntl(fd1, F_SETFL, O_NONBLOCK);
	
	fd1=open("/dev/ttyACM0", O_RDWR | O_NONBLOCK);
	
	
	
	
	if (fd1 == -1 )
	{
		cout<<"Error connnecting";
	}
	else
	{
		fcntl(fd1, F_SETFL,0);
		
		
		
		wr=write(fd1,"\r\nch2.gettemp\r\n",15);
		
		
		
		wr=write(fd1,"\r\nrels.get\r\n",12);
		
		
		//read a bunch of lines
		for(int i=0;i<10;i++)
		{
			
			//read a single line:
			
			string data="";
			
			rd=0;
			int bytes=0;
			do
			{
				bytes= read(fd1,buff,1);
				
				if(buff[0]=='\r')
				{
					read(fd1,buff,1);//read the following char which should be \n
					break;
				}
				else
				{			
					data.append(1,buff[0]);  
				}
			}while(bytes>0);
			
			
			
			cout<<endl<<"buff: "<<data<<endl;
		}
		
		
		
	
	
	}
	
	
	close(fd1);
	
	
	

	cout<<endl;
	return 0;
}