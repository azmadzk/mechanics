#include<stdio.h>
#include<stdlib.h>
#include<chrono>
#include<thread>
#include<cmath>
#include<iostream>
#include<windows.h>
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

int dimensions = 30;				//dimensions

float polrad(float coorx,float coory){		//cartesian to polar conversion
	float r;				//returns the radius of given x and y coordinates
	r=sqrt((coorx*coorx)+(coory*coory));
	return r;
}

float poltheta(float coorx,float coory){	//cartesian to polar conversion
	float theta;				//returns the angle of given x and y coordinates in radians
	theta=tan(coory/coorx);
	return theta;
}

float recx(float radius,float theta){		//polar to cartesian conversion
	float coorx;				//returns the x coordinate of given r and angle coordinates
	coorx=radius*cos(theta)+dimensions/2;
	return coorx;
}

float recy(float radius,float theta){		//polar to cartesian conversion
	float coory;				//returns the y coordinate of given r and angle coordinates
	coory=radius*sin(theta)+dimensions/2;
	return coory;
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int main(){
	ShowConsoleCursor(false);
	int n,i,j;
	float r,theta,e,coorx,coory,dt,dtheta,h,miu,arg;
	dt=0.4;								//time jump (a large, coarse approximation of dt)
	e=0.6;								//orbital eccentricity
	h=10;								//specific angular momentum
	miu=20;								//standard gravitational parameter
	theta=0;							//initial true anomaly in radians
	arg=20;								//argument of periapsis in radians
	r=pow(h,2)/miu/(1+e*cos(theta));	//initial two-body distance of given initial true anomaly and orbital eccentricity
	
	for(n=1;n>0;n++){
		cout<<"distance: "<<r<<" true anomaly: "<<theta<<endl;
		
		coorx=ceil(recx(r,theta+arg)-0.5);	//polar to cartesian conversion
		coory=ceil(recy(r,theta+arg)-0.5);
		
		for(i=dimensions;i>=0;i--){
			cout<<"  ";
			for(j=0;j<=dimensions;j++){
				if(i==coory&&j==coorx){cout<<"o";}else		
				if(i==dimensions/2&&j==dimensions/2){cout<<"O";}else			
				{cout<<" ";}
				cout<<" ";
			}
		cout<<endl;
		}
		sleep_for(nanoseconds(10000000));	//delay between frames
		system("cls");				//reset console
		dtheta=dt*h/pow(r,2);			//calculates dtheta
		theta=theta+dtheta;			//calculates new true anomaly
		r=pow(h,2)/miu/(1+e*cos(theta));	//calculates two-body distance of a given true anomaly

	}
}
