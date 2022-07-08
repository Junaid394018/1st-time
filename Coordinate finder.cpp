#include<iostream>
#include<math.h>
using namespace std;
long double opbearing(long double a, long double b, long double c, long double d); long double X, x1,y,Y, Q; //globle variable
long double Bbearing(long double a);
long double condnorth(long double a, double b, long double c);
long double nextb(long double a, long double b);
int dms(long double a);
long double berror(long double a, long double b); 
long double condeast(long double a, double b, long double c);
double Linmis(float a, float b); 


int main()
{  cout<<"Note : \nThis programme need coordinate of starting two point of traverse, lenght of traverse legs and internal angles to find out the coordinate of remaining points of traverse\n\n"; 
   int va, no=1, qn=1, j=0; long double x,y; double sum;  char c, cd, p;
    cout<<"Enter the number of points of traverse :"; cin>>va;  
	int yu=2*va, Q=va; 
   double length[va];  sum=0; 
   for(int i=0; i<va ;++i){ sum=sum+length[i];}
    
	cout<<"Enter length of base line A to B = "; cin>>length[0]; c='B'; cd='C';
   for(int i=1; i<va; ++i,++c, ++cd)
      {if(i==va-1) {cd='A';} {if(i==25) { cd=cd+6;}}{if(c=='[') {c='a';}}
	  cout<<"Enter the length from "<<c<<" to "<<cd<<" : "; cin>>length[i];}

long double   bearings[yu], db[va] ;   long double inangle[va];
long double x_aixes[va],  y_aixes[va];   X=x_aixes[0]; Y=y_aixes[0];

cout<<"Enter the Easting of  point A E1 = "; cin>>x_aixes[0]; cout<<"Enter the Norting of point A N1 = "; cin>>y_aixes[0];
cout<<"Enter the Easting of point B E2 = "; cin>>x_aixes[1]; cout<<"Enter the Norting of point B N2 = "; cin>>y_aixes[1];  
 p='A'; for(int  i=0,  on=0; i<va; ++i, on++, ++p, ++no) 
   {{if(p=='['){ p='a';  }}
    cout<<"Enter the internal angle of point "<<p<<" 0"<<no<<" = "; cin>>inangle[on]; }
   
   //Calaculatin starting
   
   bearings[0]=opbearing(x_aixes[1],x_aixes[0],y_aixes[1],y_aixes[0]);
   db[0]=Bbearing(bearings[0]);    // db[] store back bearing
  
   for(int i=va-1,we=1; i>j; ++j, ++qn, we++ )
   {   
      bearings[qn]=nextb(db[j],inangle[we]); db[we]=Bbearing(bearings[we]);}
	  
	  bearings[qn-1]=nextb(db[j-1],inangle[va-1]);
  
  // Displying
  cout<<"----------------RESULTS-------------------------------------RESULTS---------------------\n\n";
  cout<<"Point       Forward Bearings                      Point       Backward Bearings\n\n";
   c='A'; cd='B'; for(int ip=0;  ip<va; ip++, c++, cd++)
       {if(bearings[ip]>360) 
          bearings[ip]=bearings[ip]-360; if(ip==va-1)	{ cd='A'; } 
  cout<<""<<c<<cd<<"          "<<dms(bearings[ip])<<"\t<---------------> ";cout<<cd<<c<<"          "<<dms(db[ip])<<"\n"<<endl; } 
  long double sp=berror(bearings[0],(Bbearing(bearings[yu-1])+inangle[0])); float  ed=sp/va;
  cout<<"\nError in Bearing : "<<dms(sp); cout<<"\nError per station : "<<dms(ed);
  

  cout<<"\n\nPoint       Corrected  Bearings                     \n\n";  

  long double CB[va], eed=ed; c='A'; cd='B'; for(int ip=0, ao=1;  ip<va; ip++, c++, cd++,++ao)
       {if(bearings[ip]>360) 
          bearings[ip]=bearings[ip]-360;
		if(ip==va-1)	{ cd='A'; } 
		 ed=ed+eed;
		if(ed>=60){ bearings[ip]=bearings[ip]+1/60;    }
		 CB[ip]= bearings[ip]+ed;     
        cout<<""<<c<<cd<<"          "<<dms(CB[ip])<<"\t "<<"\n\n";} 
		
		
  cout<<"\n\nCoordinate "<<endl;cout<<"Point     Cordinate East                 Cordinate North"<<endl;
  cout<<"A         "<<x_aixes[0]<<"\t                 "<<y_aixes[0]<<endl; cout<<"\nB         "<<x_aixes[1]<<"\t                         "<<y_aixes[1]<<endl<<endl;
   c='C';     
   for(int  i=1, j=2; i<=va-1; ++i, ++j, c++)
	    {x_aixes[j]=condeast(x_aixes[i],length[i],CB[i]);  y_aixes[j]=condnorth(y_aixes[i],length[i],CB[i]); x1=x_aixes[j]; y=y_aixes[j];
    if(i==va-1){  cout<<"\n\nCalculted coordinate of A\nEasting : "<<x_aixes[j]<<"\nNorting : "<<y_aixes[j];    }
 else
  cout<<c<<"         "<<x_aixes[j]<<"\t                 "<<y_aixes[j]<<endl<<endl; 
  }  float cb=berror(X,x1), cc=berror(Y,y); 
 cout<<"\nError in cordinates\nError in Easting : "<<cb<<"\tError per station : "<<cb/(va-1)<<endl<<"\nError in Northing : "<<cc<<"\tError per station : "<<cc/(va-1)<<endl;
 double qp=Linmis(cb,cc),  pq=sum/qp; 	
 cout<<"\nLinear misclosure :  e = "<<qp; cout<<"\n\nFractional Linear Misclosure : F.L.M = "<<pq; 
 if(pq>500 && pq<5000){ cout<<"\n\nType : Low accuracy\nPurpose\n       Control for drainage schemes and earthwork//Small-scale  mapping";}
 else if(pq>5000 && pq<50000){cout<<"\n\nType : General\nPurpose\n        General engineering work incliding site surveys and setting out of struvture and roadwork or adding secondary control to primary control networks"; }
 else if(pq>50000){cout<<"\n\nType : Geodetic\nPurpose\n         Provision of very accurate reference points for engineering surveys or primary control points "<<endl; }
 

  return 0;}
  
  
  
  
  //Functions 
long double opbearing(long double a, long double b, long double c, long double d)     //functions for opening bearing
{long double b12=atan((a-b)/(c-d)); 
   if(c-d==0) b12=90;
 else if(c-d!=0)   
	b12=b12*180/3.142857; 
 if((a-b)<0 && (c-d)>=0)         // 4th quadrant
    {if(b12<0)
        b12=360+b12;
     else if(b12>=0)
	    b12=360-b12;}
else if((a-b)<0 && (c-d)<0)        // 3rd quadrant	
       {if(b12<0)
           b12=180-b12;
        else if(b12>=0)
		   b12=180+b12;}   
else if((a-b)>=0 && (c-d)<0)      // 2nd quadrant		 
       { if(b12<0)
            b12=180+b12;
         else if(b12>=0)
		    b12=180-b12;}
			return b12;} 
long double Bbearing(long double a)    //function for backbearing
{ long double d;
if(a==180)  d=360; 
else if(a>180)  d=a-180; 
 else if(a<180)  d=a+180;      return d; }
 long double nextb(long double a, long double b)       //function for next bearing
 { long double d; d=a+b; return d;}  
int dms(long double a)     //DMS Converter
 {long double d, c; int b; 
	b=a;    cout<<b<<"* ";	c=(a-b)*60;
	if(!(c==0))
    {a=c;  b=a;  cout<<b<<"' "; c=(a-b)*60;}
	if(!(c==0))
      {a=c; d=a;  cout<<d<<"\"";  c=(a-b)*60;} return 0;}
long double berror(long double a, long double b)    //bearing error
{long double e=a-b; return e;}
 long double condeast(long double a, double b, long double c)    //Coordinate finder East
 {long double e, z=(c*3.142857)/180;
         e=(a+b*sin(z));
         return e;
 
}
 long double condnorth(long double a, double b, long double c)    //Coordinate finder  North
  {
  	long double n, z=(c*3.142857)/180;
  	n=a+b*cos(z);
  	return n;
  }
  double Linmis(float a, float b)                             //linear misclosure
  {
  	double lm=sqrt(a*a+b*b);
  	return lm;
  }
   
		  




  