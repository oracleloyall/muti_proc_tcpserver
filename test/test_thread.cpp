#include<pthread.h>
#include<string.h>
#include"analysis.hpp"
class mutex_t
{
public:
    mutex_t();
    ~mutex_t();
    bool lock();
    bool time_lock(int us_);
    bool unlock();
    bool try_lock();

    pthread_mutex_t& get_mutex() {return m_mutex;}

private:
    pthread_mutex_t              m_mutex;
};

mutex_t::mutex_t()
{
    pthread_mutex_init(&m_mutex, NULL);
}

mutex_t::~mutex_t()
{
    pthread_mutex_destroy(&m_mutex);
}

bool mutex_t::lock()
{
    if (pthread_mutex_lock(&m_mutex))
    {
        return false;
    }
    return true;
}

bool mutex_t::time_lock(int us_)
{
    timespec ts = {us_/(1000000), us_*(1000)};
    if (pthread_mutex_timedlock(&m_mutex, &ts))
    {
        return false;
    }
    return true;
}

bool mutex_t::unlock()
{
    if (pthread_mutex_unlock(&m_mutex))
    {
        return false;
    }
    return true;
}

bool mutex_t::try_lock()
{
    if (pthread_mutex_trylock(&m_mutex))
    {
        return false;
    }
    return true;
}
mutex_t mtex;
void funtest()
{
	char buff[200];
	strncpy(buff,"test for pthread",30);
	char temp[200];
	strncpy(temp,"test for pthread",30);
    memcpy(temp,buff,200);
}
void *thread_func(void *)
{
	int i=0;
	Analysisi::TestTimeAnalysis sis(10);
	while(i++<100000){
		mtex.lock();
		funtest();
		mtex.unlock();
	}
}
void *t(void *)
{

}
#define MUTI

int main(void)
{
	{
			  Analysisi::TestTimeAnalysis sis(5);
			  pthread_t ntid;
			  pthread_create(&ntid, NULL, thread_func,NULL);
			//  pthread_join(ntid, NULL);
	}
	//simple thread
	{
#ifdef MUTI
	mutex_t mtex;
	Analysisi::TestTimeAnalysis sis(10);
	for(int i=0;i<400000;i++)
	{
		mtex.lock();
		funtest();
		mtex.unlock();
	}
#endif
	}

	{
#ifdef MUTI
		  pthread_t ntid1;
		  pthread_t ntid2;
		  pthread_t ntid3;
		  pthread_t ntid4;
		  pthread_create(&ntid1, NULL, thread_func,NULL);
		  pthread_create(&ntid2, NULL, thread_func,NULL);
		  pthread_create(&ntid3, NULL, thread_func,NULL);
		  pthread_create(&ntid4, NULL, thread_func,NULL);
		  pthread_join(ntid1, NULL);
		  pthread_join(ntid2, NULL);
		  pthread_join(ntid3, NULL);
		  pthread_join(ntid4, NULL);
#endif
	}

	return 0;
}
