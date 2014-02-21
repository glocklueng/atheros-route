#include "common.h"
#include "phone_control.h"
#include "phone_action.h"
#include "phone_audio.h"
#include "dtmf_data.h"
#include "si32178.h"

int pcm_ret = 0;
int dtmf_ret = 0;
int total_dtmf_ret = 0;
unsigned char dtmf_buf[6000]={0};	

//计算校验
unsigned char sumxor(const  char  *arr, int len)
{
	int i=0;
	unsigned char sum = 0;
	for(i=0; i<len; i++)
	{
		sum ^= arr[i];
	}

	return sum;
}

int senddtmf(char dtmf)
{
	int tmp;
	if(total_dtmf_ret <= 0)
	{
		//ioctl(phone_audio.phone_audio_pcmfd,SET_WRITE_TYPE,0);
	}

	dtmf_ret = GenerateCodePcmData(&dtmf,1,dtmf_buf,Big_Endian);
	total_dtmf_ret += dtmf_ret;
	
	tmp = AUDIO_STREAM_BUFFER_SIZE-phone_audio.input_stream_wp;
	if(tmp < dtmf_ret)
	{
		memcpy(&input_stream_buffer[phone_audio.input_stream_wp],dtmf_buf,tmp);
		phone_audio.input_stream_wp = 0;
		memcpy(&input_stream_buffer[phone_audio.input_stream_wp],dtmf_buf+tmp,dtmf_ret-tmp);
		phone_audio.input_stream_wp +=(dtmf_ret-tmp);
	}
	else
	{
		memcpy(&input_stream_buffer[phone_audio.input_stream_wp],dtmf_buf,dtmf_ret);
		phone_audio.input_stream_wp += dtmf_ret;
	}

}

int onhook()
{
	if(!set_onhook())
	{
		phone_audio.start_recv = 1;
		PRINT("onhook success\n");
	}
}

int offhook()
{
	if(!set_offhook())
	{
		PRINT("offhook success\n");
	}
}

//拨号
int dialup(char *num,int num_len)
{
	//ioctl(phone_audio.phone_audio_pcmfd,SET_WRITE_TYPE,1);

	if(num_len>40)
		num_len = 40;
	phone_audio.input_stream_rp = 0;
	phone_audio.input_stream_wp = 0;

	pcm_ret = GenerateCodePcmData(num,num_len,&input_stream_buffer[phone_audio.input_stream_wp],Big_Endian);
	PRINT("ret = %d\n",pcm_ret);
	phone_audio.input_stream_wp += pcm_ret;
	if(phone_audio.input_stream_wp >= AUDIO_STREAM_BUFFER_SIZE)
		phone_audio.input_stream_wp = 0;
		
	return 0;
}
