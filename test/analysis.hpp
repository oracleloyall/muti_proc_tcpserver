#ifndef ANALYSIS_H_
#define ANALYSIS_H_
/*create 2018
 * author zhaoxi
 * analysis program
 */
#define THREADNUM 10
#include <vector>
#include <list>
#include <map>
#include <pthread.h>
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <iostream>
//#define DEBUG
namespace Analysisi{
#include"pasetime.hpp"
//#include"strtk.hpp"
//#include"ipdbserver.h"
#include"spinlock.hpp"
#include"if.h"
//#include"GeneralHashFunctions.h"
const bool  NetFlag=true;
const bool  FuncFlag=true;
const bool  ErrFlag=true;
struct TimeData{
    int type;//1,2,3,4,5,11,21,31,41,51
	unsigned int end;
};
struct NetAnalysis{
	std::map<unsigned long,TimeData> NTdata;
};
struct FuncAnalysis{
	std::map<unsigned long,TimeData> FTdata;
};
struct Avearge
{
	Avearge():sum(0),AverageTime(0){ }
    void operator()(std::map<unsigned long,TimeData>::value_type & data )
    {
    	++sum;
        if(UNLIKELY(sum==1))
        	AverageTime=(data.second.end+AverageTime)/1;
        else
        	AverageTime=(data.second.end+AverageTime*(sum-1))/sum;
    }
    int sum;
    unsigned int AverageTime;

};
struct ErrShow
{
	ErrShow(){ }
    void operator()(std::map<int,long long>::value_type &data)
    {
#ifdef DEBUG
    	std::cout<<"first "<<data.first<<" ErrorNum:"<<data.second<<"\n";
#endif
    	std::ostringstream Data;
    	Data<<"ErrorCode:"<<data.first<<" ErrorNum:"<<data.second<<"\n";
    	value+=Data.str();
    }
   std::string value;

};
class TimeAnalysis{
public:
	TimeAnalysis()throw():Nindex(0),Findex(0){spinlock_init(&lock);}
	~TimeAnalysis(){spinlock_destroy(&lock);}
	void SaveToFile(const char *file)throw(){
//		string delimiter="\n";
//		std::map<unsigned long,TimeData> Fdata=FTdata;
//		std::map<unsigned long,TimeData> NData=NTdata;
//		strtk::write_to_text_file(file,Fdata,delimiter);
//		strtk::write_to_text_file(file,NData,delimiter);
	}
	std::string ShowAnalysis()
	{
		std::ostringstream Data;
		Avearge avg1= std::for_each(FTdata.begin(), FTdata.end(), Avearge());
		Avearge avg2= std::for_each(NTdata.begin(), NTdata.end(), Avearge());
		Data<<"function analysis sum:"<<avg1.sum<<" avg passtime:"<<avg1.AverageTime;
		Data<<"\t"<<"net interface analysis sum:"<<avg2.sum<<" avg passtime:"<<avg2.AverageTime<<"\n";
		return Data.str();
	}
	void AverageFtPassInfo(){
//		std::for_each(FTdata.begin(), FTdata.end(), [](int &std::pair<unsigned long,TimeData> data){  });
		Avearge avg= std::for_each(FTdata.begin(), FTdata.end(), Avearge());
		std::cout<<"Total Num:"<<avg.sum<<std::endl;
		std::cout<<"Avg PassTime:"<<avg.AverageTime<<std::endl;
	}
	void AverageNtPassInfo(){
	//	std::for_each(NTdata.begin(), NTdata.end(), [](int &std::pair<unsigned long,TimeData> data){  });
		Avearge avg= std::for_each(NTdata.begin(), NTdata.end(), Avearge());
		std::cout<<"Total Num:"<<avg.sum<<std::endl;
		std::cout<<"Avg PassTime:"<<avg.AverageTime<<std::endl;
	}
	inline void FTStart(){FuncPassedtime.Start();}
	inline void FTEnd(int type)
	{
		Fdata.type=type;
		Fdata.end=FuncPassedtime.End();
		FTdata.insert(std::pair<unsigned long,TimeData>(Findex++,Fdata));
	}
	inline void NTStart(){NetPassedtime.Start();}
	inline void NTEnd(int type)
	{
		Ndata.type=type;
		Ndata.end=NetPassedtime.End();
		NTdata.insert(std::pair<unsigned long,TimeData>(Nindex++,Ndata));
		std::cout<<"Use Times"<<Ndata.end<<std::endl;
	}
	unsigned int ThreadId;
private:
	CPassedTime NetPassedtime;
	CPassedTime FuncPassedtime;
	TimeData Fdata;
	TimeData Ndata;
	std::map<unsigned long,TimeData> FTdata;
	std::map<unsigned long,TimeData> NTdata;
	spinlock lock;
	unsigned long Nindex;
	unsigned long Findex;

};
static 	void show(const std::map<int,long long>::value_type &data ){

}
class ErrorAnalysis{
public:
	ErrorAnalysis(){}
	~ErrorAnalysis(){}
	unsigned int ThreadId;
//	typedef std::map<int,long long>::iterator iter;
	void AddNode()
	{
		ErrData.insert(std::pair<int,long long>(20100,0));
		ErrData.insert(std::pair<int,long long>(20102,0));
		ErrData.insert(std::pair<int,long long>(20103,0));
		ErrData.insert(std::pair<int,long long>(20104,0));
		ErrData.insert(std::pair<int,long long>(20105,0));
		ErrData.insert(std::pair<int,long long>(20110,0));
		ErrData.insert(std::pair<int,long long>(20210,0));
		ErrData.insert(std::pair<int,long long>(20200,0));
	}
	void AddData(int ErrorCode){
		++times;
		std::map<int,long long>::iterator iter=ErrData.find(ErrorCode);
		if (LIKELY(iter != ErrData.end())){
		    	++iter->second;
		}
		 else{
#ifdef DEBUG
			std::cout<<ErrorCode<<std::endl;
			std::cout<<"Map size:"<<ErrData.size()<<std::endl;
#endif
		    ErrData.insert(std::pair<int,long long>(ErrorCode,1));

		 }

	}
//	void show(const std::map<int,long long>::value_type &data ){
//
//	}
	std::string ShowAnalysis()
	{
		//for c++11
		//std::for_each(ErrData.begin(), ErrData.end(), std::bind1st(std::mem_fun(&ErrorAnalysis::show)),this);
		//std::for_each(ErrData.begin(), ErrData.end(), &show);
		ErrShow Data=std::for_each(ErrData.begin(), ErrData.end(), ErrShow());
		return Data.value;
	}
private:
	std::map<int,long long> ErrData;
	unsigned long times;
	std::ostringstream Data;

};
TimeAnalysis TAS[THREADNUM];
ErrorAnalysis EAS[THREADNUM];

class TestTimeAnalysis
{
public:
	TestTimeAnalysis(int Type):type(Type){
		unsigned int ThreadId=(unsigned int)pthread_self();
		index=ThreadId%THREADNUM;
		TAS[index].ThreadId=ThreadId;
		TAS[index].FTStart();
	}
	~TestTimeAnalysis(){
		TAS[index].FTEnd(type);
		//TAS[index].AverageFtPassInfo();
		std::string str=TAS[index].ShowAnalysis();
		std::cout<<str<<std::endl;
	}
private:
	int type;
	int index;
};
class TestErrAnalysis
{
public:
	TestErrAnalysis(int type){
		unsigned int ThreadId=(unsigned int)pthread_self();
		index=ThreadId%THREADNUM;
		EAS[index].ThreadId=ThreadId;
		EAS[index].AddData(type);
	}
	~TestErrAnalysis()
	{
		std::cout<<EAS[index].ShowAnalysis();
	}
private:
	int type;
	int index;
};
static void show()
{
	std::cout<<"\n---------------------Err analysis---------------------------"<<std::endl;
	for(int i=0;i<THREADNUM;i++)
	{
		std::cout<<"Thread Id:"<<EAS[i].ThreadId<<"\t";
		std::cout<<EAS[i].ShowAnalysis();
	}
	std::cout<<"\n------------------------------------------------------------"<<std::endl;
	std::cout<<"\n---------------------Tim analysis---------------------------"<<std::endl;
	for(int i=0;i<THREADNUM;i++)
	{
		std::cout<<"Thread Id:"<<TAS[i].ThreadId<<"\t";
		std::cout<<TAS[i].ShowAnalysis();
	}
	std::cout<<"\n------------------------------------------------------------"<<std::endl;

}
}
#endif
