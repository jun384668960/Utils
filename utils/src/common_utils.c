#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/vfs.h>
#include <sys/sysinfo.h>
#include <sys/time.h>
#include <sys/types.h>
#include <dirent.h>

#include "common_utils.h"

#ifdef __cplusplus
extern "C"{
#endif

int exec_cmd(const char *cmd)   
{   
    FILE *fp = NULL;
    if((fp = popen(cmd, "r")) == NULL)
    {
        printf("Fail to popen\n");
        return -1;
    }
    pclose(fp);
	
	return 0;
} 

int exec_cmd_chstr_exist(char* cmd, char* str)
{
	if(NULL == str || NULL == cmd)
	{
		return -1;
	}
			
    FILE *fp = NULL;
    char buf[256]= {0};

    if((fp = popen(cmd, "r")) == NULL)
    {
        printf("Fail to popen\n");
        return -1;
    }
    
    while(fgets(buf, sizeof(buf), fp) != NULL)
    {
		if(strstr(buf, str))
		{
		    pclose(fp);
			return 0;
		}
    }
    pclose(fp);

    return -1;
}

unsigned long long get_system_tf_freeKb(char* dir)
{
	int ret;
	if(dir == NULL) return 0;
	
	struct statfs diskInfo;
	ret = statfs(dir, &diskInfo);
	if(ret == 0)
	{
		unsigned long long totalBlocks = diskInfo.f_bsize;
		unsigned long long freeDisk = diskInfo.f_bfree*totalBlocks;
		return freeDisk/1024LL;
	}
	
	return 0;
}

unsigned long get_system_mem_freeKb()
{
	int error;  
  	struct sysinfo s_info;  
	
	error = sysinfo(&s_info);  
	if(error == 0)
	{
		return s_info.freeram/1024L;
	}
	return 0;
}

int64_t get_tick_count()
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	return (int64_t)now.tv_sec * 1000000 + now.tv_nsec / 1000;
}

void  get_file_pure_name(char* full_name,char * dest)
{
	char*  mn_first = full_name;
	char*  mn_last  = full_name + strlen( full_name );
	if ( strrchr( full_name, '\\' ) != NULL )
		mn_first = strrchr( full_name, '\\' ) + 1;
	else if ( strrchr( full_name, '/' ) != NULL )
		mn_first = strrchr( full_name, '/' ) + 1;
//	if ( strrchr( full_name, '.' ) != NULL )
//		mn_last = strrchr( full_name, '.' );
	if ( mn_last < mn_first )
		mn_last = full_name + strlen( full_name );
	
	memmove(dest ,mn_first,(mn_last-mn_first));
}

void select_delay_ms(int nMillisecond)
{
	struct	 timeval   mTimeOut;	 //定时的时间 
	mTimeOut.tv_sec   =   nMillisecond/1000; 
	mTimeOut.tv_usec   =   (nMillisecond%1000)*1000; 
	
	select(0,	NULL,	NULL,	NULL,	&mTimeOut);
}

int is_file_exist(const char* file_path)
{
	if(file_path == NULL)
		return -1;
	if(access(file_path, F_OK) == 0)
		return 0;
	
	return -1;
}

int is_dir_exist(const char* dir_path)
{
	if(dir_path == NULL)
		return -1;
	if(opendir(dir_path) == NULL)
		return -1;
	
	return 0;
}

int int2hex2str(char *pValue,int lValue,int lCharLen)
{
    char tmp[10];
    memset(tmp,0,sizeof(tmp));
    sprintf(tmp,"%%0%dx",lCharLen);
    return sprintf(pValue,tmp,lValue);
}

int int2str(char *pValue,int lValue,int lCharLen)
{
    char tmp[10];
    memset(tmp,0,sizeof(tmp));
    sprintf(tmp,"%%0%dd",lCharLen);
    return sprintf(pValue,tmp,lValue);
}

char* strrev(char* s)  
{  
    /* h指向s的头部 */  
    char* h = s;      
    char* t = s;  
    char ch;  
  
    /* t指向s的尾部 */  
    while(*t++){};  
    t--;    /* 与t++抵消 */  
    t--;    /* 回跳过结束符'\0' */  
  
    /* 当h和t未重合时，交换它们所指向的字符 */  
    while(h < t)  
    {  
        ch = *h;  
        *h++ = *t;    /* h向尾部移动 */  
        *t-- = ch;    /* t向头部移动 */  
    }  
  
    return(s);  
}

int random_range(int min, int max)
{
	int pos, dis;
	
	srand((int)time(NULL));
	if(min == max)
	{
		return max;
	}
	else if(max > min)
	{
		pos = min;
		dis = max - min + 1;
		return rand() % dis + pos;
	}
	else
	{
		pos = max;
		dis = min - max + 1;
		return rand() % dis + pos;
	}
}

#ifdef __cplusplus
}
#endif


