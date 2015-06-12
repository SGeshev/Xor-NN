#include <math.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <vector>
#include <cassert>
#include <cmath>


using namespace std;



double Deriv(double x)
{
	return 1.0 - x*x;
};

double transferFunction(double x)
{
return tanh(x);};

    int input1[]={0,0,1,1};
	double hiddenInput1[4];

    int input2[]={0,1,0,1};
	double hiddenInput2[4];

	double output;
	double targetValue[4]={0,1,1,0};
	double eta = 0.1;
	int epoch = 2000;
	double InputWeight1[]={0,0,0,0};
	double InputWeight2[]={0,0,0,0};
	double InputWeight3[]={0,0,0,0};
	double InputWeight4[]={0,0,0,0};

	double HiddenWeight1[]={0,0,0,0};
	double HiddenWeight2[]={0,0,0,0};

	double deltaWeight1[]={0,0,0,0};
	double deltaWeight2[]={0,0,0,0};
	double deltaWeight3[]={0,0,0,0};
	double deltaWeight4[]={0,0,0,0};
	double HiddenDelta1[]={0,0,0,0};
	double HiddenDelta2[]={0,0,0,0};

	double OUTPUT[]= {0,0,0,0};	

	double DeltaK[]={0,0,0,0};
	double DeltaJ1[] = {0,0,0,0};
	double DeltaJ2[] = {0,0,0,0};

	double bias1[]={1,1,1,1};
	double bias2[]={1,1,1,1};
	double bias3[]={1,1,1,1};
	double deltaBias1[]= {0,0,0,0};
	double deltaBias2[]= {0,0,0,0};
	double deltaBias3[]= {0,0,0,0};





	double randomWeight() 
		{
		double a = rand() / double(RAND_MAX);
	
              return a;
		};

	void GenerateWeight(){
		for(int i=0;i<4;i++){
			InputWeight1[i]=randomWeight();
			InputWeight2[i]=randomWeight();
			InputWeight3[i]=randomWeight();
			InputWeight4[i]=randomWeight();

			HiddenWeight1[i]=randomWeight();
			HiddenWeight2[i]=randomWeight();


		}
	}

	void FeedForward()
	{
		double output1 = 0.0;
		double output2 = 0.0;
		double output3 = 0.0;
		double output4 = 0.0;
		double sum1,sum2;
		for(int i=0; i<4; i++)
		{
			output1=input1[i]*InputWeight1[i];
			output2 = input2[i]*InputWeight2[i];
			output3 = input1[i]*InputWeight3[i];
			output4 = input2[i]*InputWeight4[i];

			sum1 = output1 + output2;
			sum2 = output3 + output4;

			hiddenInput1[i] = transferFunction(sum1 +bias1[i]);
			hiddenInput2[i] = transferFunction(sum2 +bias2[i]);
			
		}
	};
	void FeedForward2()
	{double output1 = 0.0;
	 double output2 =0.0;
	 double SUM;
	 for(int i=0; i<4; i++)
	 {
		 output1=input1[i]*HiddenWeight1[i];
			output2 = input2[i]*HiddenWeight2[i];
			SUM = output1+output2;

			OUTPUT[i]= transferFunction(SUM+bias3[i]);
	 }
	};
	void OutputGradient()
	{
		for(int i=0; i<4; i++)
		{
			DeltaK[i]=OUTPUT[i] * (1-OUTPUT[i]) * (OUTPUT[i]-targetValue[i]);
			deltaBias3[i]=-eta*DeltaK[i];
		}
	};

	double HiddenGradientSUM()
	{
		double sum;
		for(int i=0; i<4; i++)
		sum +=(DeltaK[i]*HiddenWeight1[i])+(DeltaK[i]*HiddenWeight2[i]);
		
			return sum;
	};
	void HiddenGradient()
	{
		for(int i=0; i<4; i++)
		{
			DeltaJ1[i]=hiddenInput1[i]*(1-hiddenInput1[i])*HiddenGradientSUM();
			DeltaJ2[i]=hiddenInput2[i]*(1-hiddenInput2[i])*HiddenGradientSUM();
			deltaBias1[i]=-eta*DeltaJ1[i];
			deltaBias2[i]=-eta*DeltaJ2[i];

		}
	};

	void backProp()
	{
		for(int i =0; i<4;i++){
			deltaWeight1[i]=-eta*(DeltaJ1[i]*input1[i]);
			InputWeight1[i]+=deltaWeight1[i];

	        deltaWeight2[i]=-eta*(DeltaJ2[i]*input2[i]);
			InputWeight2[i]+=deltaWeight2[i];

	        deltaWeight3[i]=-eta*(DeltaJ1[i]*input1[i]);
			InputWeight3[i]+=deltaWeight3[i];

	        deltaWeight4[i]=-eta*(DeltaJ2[i]*input2[i]);
			InputWeight4[i]+=deltaWeight4[i];

	        HiddenDelta1[i]=-eta*(DeltaK[i]*hiddenInput1[i]);
			HiddenWeight1[i]+=HiddenDelta1[i];

	       HiddenDelta2[i]=-eta*(DeltaK[i]*hiddenInput2[i]);
		   HiddenWeight2[i]+=HiddenDelta2[i];

		   bias1[i]+=deltaBias1[i];
		   bias2[i]+=deltaBias2[i];
		   bias3[i]+=deltaBias3[i];
		}

	};


void main()
{   srand(time(0));
	GenerateWeight();

	for(int i = 0;i<epoch;i++){
	FeedForward();
	FeedForward2();
	OutputGradient();
	HiddenGradient();
	backProp();
	}
	cout<<transferFunction(0.32)<<endl;
	for(int i=0;i<4;i++)
	{
	//cout<<"<"<<InputWeight1[i]<<"><"<<InputWeight2[i]<<"><"<<InputWeight3[i]<<"><"<<InputWeight4[i]<<">"<<endl;
	cout<<"<"<<hiddenInput1[i]<<"><"<<hiddenInput2[i]<<">"<<endl<<"OUTPUT                                               "<<OUTPUT[i]<<endl;
	}
	system("Pause");
}