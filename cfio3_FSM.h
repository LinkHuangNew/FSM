#ifndef _CFIO3_FSM_H
#define _CFIO3_FSM_H

#ifdef __cplusplus
extern "C"{
#endif

typedef unsigned char SM_State;
//typedef void(*Procedure)(void *);//函数指针,这儿没用
//状态情况不宜太多。
enum client_SM_states{ 
    c_SM_init,
    c_SM_work,
    c_SM_wait,
    c_SM_finish,
    c_SM_error
}; //计算进程状态

enum master_SM_states{ 
    m_SM_init,
    m_SM_wait,
    m_SM_work,
    m_SM_finish,
    m_SM_error
}; //消息进程状态

enum server_SM_states{ 
    s_SM_init,
    s_SM_wait,
	s_SM_handle_msg,
	s_SM_write_data,
    s_SM_finish,
    s_SM_error
}; //IO进程状态

typedef struct _SM_AVR
{
    int rank;
    int procs_type;
    SM_State state;
    char message[256];
}SM_VAR;  //状态机参数封装


SM_VAR* SM_init(int rank,int type,char *message);
void SM_finilize(SM_VAR* var);
SM_State SM_get_state(SM_VAR* var);

/**************************client**********************************/
void client_SM_init2work(SM_VAR* var);
void client_SM_work2wait(SM_VAR* var);
void client_SM_work2finish(SM_VAR* var);
void client_SM_wait2work(SM_VAR* var);
void client_SM_anyone2error(SM_VAR* var);
void client_SM_error2init(SM_VAR* var);

/****************************master**********************************/
void master_SM_init2wait(SM_VAR* var);
void master_SM_wait2work(SM_VAR* var);
void master_SM_work2wait(SM_VAR* var);
void master_SM_work2finish(SM_VAR* var);
void master_SM_anyone2error(SM_VAR* var);
void master_SM_error2init(SM_VAR* var);

/****************************server**********************************/
void server_SM_init2wait(SM_VAR* var);
void server_SM_wait2handle(SM_VAR* var);
void server_SM_handle2wait(SM_VAR* var);
void server_SM_handle2write(SM_VAR* var);
void server_SM_write2wait(SM_VAR* var);
void server_SM_write2finish(SM_VAR* var);
void server_SM_anyone2error(SM_VAR* var);
void server_SM_error2init(SM_VAR* var);


typedef void(*Procedure)(SM_VAR *);//函数指针,这儿没用

//下述的状态转换表适用于单纯的循环状态机，所以没啥用。调用太过于简单却增加了限制。
Procedure client_SM_steps[] = {//计算进程状态转换函数表。
    client_SM_init2work,
	client_SM_work2wait,
	client_SM_work2finish,
    client_SM_wait2work,
	client_SM_anyone2error,
    client_SM_error2init
};

Procedure master_SM_steps[] = {//消息进程状态转换函数表。
    master_SM_init2wait,
	master_SM_wait2work,
	master_SM_work2wait,
    master_SM_work2finish,
	master_SM_anyone2error,
    master_SM_error2init
};

Procedure server_SM_steps[] = {//IO进程状态转换函数表。
    server_SM_init2wait,
	server_SM_wait2handle,
	server_SM_handle2wait,
    server_SM_handle2write,
	server_SM_write2wait,
	server_SM_write2finish,
	server_SM_anyone2error,
    server_SM_error2init
};

#ifdef __cplusplus
}
#endif

#endif
