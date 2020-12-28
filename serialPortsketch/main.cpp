#include<iostream>
#include<string>
#include<stdlib.h>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include"SerialPort.h"

using namespace std;

char output[MAX_DATA_LENGTH];
char incomingData[MAX_DATA_LENGTH];

// change the name of the port with the port name of your computer
// must remember that the backslashes are essential so do not remove them
char *port = "\\\\.\\COM12";

//connection for the databse
MYSQL* connectionVariable()
{
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"192.168.1.28","admin","admin","project_rfid_temperature",0,NULL,0);

    return conn;
}

//saving the datails with the database
string saving(string output)
{
    MYSQL* conn;
    //checking for mysql connection
    conn = connectionVariable();
    //check for connection
    if(conn)
    {
        //declaration
        int queryString = 0;
        stringstream treams;


        for(int i=0;i<1;i++)
        {
            //inserting the data
            treams<<"INSERT INTO users_temperature(names,temperature) VALUES('"<<output[63]<<output[64]<<output[65]<<output[66]<<output[67]<<output[68]<<output[69]<<"','"<<output[56]<<output[57]<<output[58]<<output[59]<<output[60]<<output[61]<<"')";


            string query = treams.str();
            const char* q = query.c_str();
            queryString = mysql_query(conn,q);

            //checking for success
            if(queryString == 0)
            {
                cout<<"Saving process successful..."<<endl;
            }
            else
            {
                cout<<"The saving process has failed!...."<<endl;
            }
        }
    }
    else
    {
        cout<<"poor database connection"<<endl;
    }
}

int main(){
	SerialPort arduino(port);
	if(arduino.isConnected()){
		cout<<"Connection made"<<endl<<endl;
	}
	else{
		cout<<"Error in port name"<<endl<<endl;
	}
	while(arduino.isConnected()){
		cout<<"Enter your command: "<<endl;
		string data;
		cin>>data;

		char *charArray = new char[data.size() + 1];
		copy(data.begin(), data.end(), charArray);
		charArray[data.size()] = '\n';

		arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
		arduino.readSerialPort(output, MAX_DATA_LENGTH);

		cout<<">> "<<output<<endl;

		//saving output to the database
		saving(output);

		delete [] charArray;
	}
	return 0;
}
