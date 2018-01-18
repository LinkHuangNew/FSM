#include <stdio.h>



/**************************SM**********************************/
SM_VAR* SM_init(int rank,int type,char *message){
	SM_VAR *var = new SM_VAR;
	var->rank = rank;
	var->procs_type = type;
	if(0 == type){
		var->state = c_SM_init;
	}else if(1 == type){
		var->state = m_SM_init;
	}else{
		var->state = s_SM_init;
	}	
	return var;
}

void SM_finilize(SM_VAR* var){
	delete var;
}

SM_State SM_get_state(SM_VAR* var){
	return var->state;
}

/**************************client**********************************/
void client_SM_init2work(SM_VAR* var){
	if(c_SM_init == var->state){
		var->state = c_SM_work;
	}else{
		client_SM_anyone2error(var);
	}
}

void client_SM_work2wait(SM_VAR* var){
	if(c_SM_work == var->state){
		var->state = c_SM_wait;
	}else{
		client_SM_anyone2error(var);
	}
}

void client_SM_work2finish(SM_VAR* var){
	if(c_SM_work == var->state){
		var->state = c_SM_finish;
	}else{
		client_SM_anyone2error(var);
	}
}

void client_SM_wait2work(SM_VAR* var){
	if(c_SM_wait == var->state){
		var->state = c_SM_work;
	}else{
		client_SM_anyone2error(var);
	}
}

void client_SM_anyone2error(SM_VAR* var){
	printf("client SM error! CS:%d\n",var->state);
	var->state = c_SM_error;
}

void client_SM_error2init(SM_VAR* var){
	if(c_SM_error == var->state){
		var->state = c_SM_init;
	}else{
		client_SM_anyone2error(var);
	}
}


/****************************master**********************************/
void master_SM_init2wait(SM_VAR* var){
	if(m_SM_init == var->state){
		var->state = m_SM_wait;
	}else{
		master_SM_anyone2error(var);
	}
}

void master_SM_wait2work(SM_VAR* var){
	if(m_SM_wait == var->state){
		var->state = m_SM_work;
	}else{
		master_SM_anyone2error(var);
	}
}

void master_SM_work2wait(SM_VAR* var){
	if(m_SM_work == var->state){
		var->state = m_SM_wait;
	}else{
		master_SM_anyone2error(var);
	}
}

void master_SM_work2finish(SM_VAR* var){
	if(m_SM_work == var->state){
		var->state = m_SM_finish;
	}else{
		master_SM_anyone2error(var);
	}
}

void master_SM_anyone2error(SM_VAR* var){
	printf("master SM error! CS:%d\n",var->state);
	var->state = m_SM_error;
}

void master_SM_error2init(SM_VAR* var){
	if(m_SM_error == var->state){
		var->state = m_SM_init;
	}else{
		master_SM_anyone2error(var);
	}
}

/****************************server**********************************/
void server_SM_init2wait(SM_VAR* var){
	if(s_SM_init == var->state){
		var->state = s_SM_wait;
	}else{
		server_SM_anyone2error(var);
	}
}

void server_SM_wait2handle(SM_VAR* var){
	if(s_SM_wait == var->state){
		var->state = s_SM_handle_msg;
	}else{
		server_SM_anyone2error(var);
	}
}

void server_SM_handle2wait(SM_VAR* var){
	if(s_SM_handle_msg == var->state){
		var->state = s_SM_wait;
	}else{
		server_SM_anyone2error(var);
	}
}

void server_SM_handle2write(SM_VAR* var){
	if(s_SM_handle_msg == var->state){
		var->state = s_SM_write_data;
	}else{
		server_SM_anyone2error(var);
	}
}

void server_SM_write2wait(SM_VAR* var){
	if(s_SM_write_data == var->state){
		var->state = s_SM_wait;
	}else{
		server_SM_anyone2error(var);
	}
}

void server_SM_write2finish(SM_VAR* var){
	if(s_SM_write_data == var->state){
		var->state = s_SM_finish;
	}else{
		server_SM_anyone2error(var);
	}
}

void server_SM_anyone2error(SM_VAR* var){
	printf("server SM error! CS:%d\n",var->state);
	var->state = s_SM_error;
}

void server_SM_error2init(SM_VAR* var){
	if(s_SM_error == var->state){
		var->state = s_SM_init;
	}else{
		server_SM_anyone2error(var);
	}
}

