#include <string.h>
#include <stdlib.h>
#include "Command.h"
#include "SelectState.h"

void field_state_handler(Command_t *cmd, size_t arg_idx) {
    cmd->cmd_args.sel_args.fields = NULL;
    cmd->cmd_args.sel_args.fields_len = 0;
    cmd->cmd_args.sel_args.limit = -1;
    cmd->cmd_args.sel_args.offset = -1;
    
    cmd->whe_args.whe_args.fields = NULL;
    cmd->whe_args.whe_args.fields_len = 0;
    cmd->whe_args.whe_args.op_type1 = 0;
    cmd->whe_args.whe_args.op_type2 = 0;
    cmd->whe_args.whe_args.string_comp1 = NULL;
    cmd->whe_args.whe_args.num_comp1 = 0;
    cmd->whe_args.whe_args.string_comp2 = NULL;
    cmd->whe_args.whe_args.num_comp2 = 0;
    cmd->whe_args.whe_args.op_num = 0;
	
	cmd->agge_args.agge_args.fields = NULL;
    cmd->agge_args.agge_args.agge_type = none;
	
    while(arg_idx < cmd->args_len) {
        if (!strncmp(cmd->args[arg_idx], "*", 1)) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "id", 2)) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "name", 4)) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "email", 5)) {
            add_select_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "age", 3)) {
            add_select_field(cmd, cmd->args[arg_idx]);
		} else if (!strncmp(cmd->args[arg_idx], "avg", 3)) {
            aggregate_state_handler(cmd, arg_idx);
        } else if (!strncmp(cmd->args[arg_idx], "count", 5)) {
            aggregate_state_handler(cmd, arg_idx);
        } else if (!strncmp(cmd->args[arg_idx], "sum", 3)) {
            aggregate_state_handler(cmd, arg_idx);
        } else if (!strncmp(cmd->args[arg_idx], "from", 4)) {
            table_state_handler(cmd, arg_idx+1);
            return;
        } else {
            cmd->type = UNRECOG_CMD;
            return;
        }
        arg_idx += 1;
    }
    cmd->type = UNRECOG_CMD;
    return;
}

void update_state_handler(Command_t *cmd, size_t arg_idx) {
	cmd->cmd_args.sel_args.fields = NULL;
    cmd->cmd_args.sel_args.fields_len = 0;
    cmd->cmd_args.sel_args.limit = -1;
    cmd->cmd_args.sel_args.offset = -1;

    cmd->upd_args.upd_args.fields = NULL;
	cmd->upd_args.upd_args.str = NULL;
	cmd->upd_args.upd_args.num = 0;
	
    cmd->whe_args.whe_args.fields = NULL;
    cmd->whe_args.whe_args.fields_len = 0;
    cmd->whe_args.whe_args.op_type1 = 0;
    cmd->whe_args.whe_args.op_type2 = 0;
    cmd->whe_args.whe_args.string_comp1 = NULL;
    cmd->whe_args.whe_args.num_comp1 = 0;
    cmd->whe_args.whe_args.string_comp2 = NULL;
    cmd->whe_args.whe_args.num_comp2 = 0;
    cmd->whe_args.whe_args.op_num = 0;
	
	//keep using the select function
	while(arg_idx < cmd->args_len) {
        if (!strncmp(cmd->args[arg_idx], "*", 1)) {
            add_update_field(cmd, cmd->args[arg_idx]);
        } else if (!strncmp(cmd->args[arg_idx], "id", 2)) {
            add_update_field(cmd, "id");
        } else if (!strncmp(cmd->args[arg_idx], "name", 4)) {
            add_update_field(cmd, "name");
        } else if (!strncmp(cmd->args[arg_idx], "email", 5)) {
            add_update_field(cmd, "email");
        } else if (!strncmp(cmd->args[arg_idx], "age", 3)) {
            add_update_field(cmd, "age");
        } else if (!strncmp(cmd->args[arg_idx], "table", 5)) {
            ;
        } else if (!strncmp(cmd->args[arg_idx], "set", 3)) {
            ;
        } else if (!strncmp(cmd->args[arg_idx], "=", 1)) {
            arg_idx++;
			if(!strncmp(cmd->upd_args.upd_args.fields,"id",2) || !strncmp(cmd->upd_args.upd_args.fields,"age",3)){
				cmd->upd_args.upd_args.num = atoi(cmd->args[arg_idx]);
			} else if(!strncmp(cmd->upd_args.upd_args.fields,"name",4) || !strncmp(cmd->upd_args.upd_args.fields,"email",5)){
				cmd->upd_args.upd_args.str = strdup(cmd->args[arg_idx]);
			}
        } else if (!strncmp(cmd->args[arg_idx], "where", 5)) {
            where_state_handler(cmd, arg_idx+1);
            return;
        } else {
            cmd->type = UNRECOG_CMD;
            return;
        }
        arg_idx += 1;
    }
	if(arg_idx == cmd->args_len)
		return;
    cmd->type = UNRECOG_CMD;
    return;
}

void delete_state_handler(Command_t *cmd, size_t arg_idx) {
	
    cmd->whe_args.whe_args.fields = NULL;
    cmd->whe_args.whe_args.fields_len = 0;
    cmd->whe_args.whe_args.op_type1 = 0;
    cmd->whe_args.whe_args.op_type2 = 0;
    cmd->whe_args.whe_args.string_comp1 = NULL;
    cmd->whe_args.whe_args.num_comp1 = 0;
    cmd->whe_args.whe_args.string_comp2 = NULL;
    cmd->whe_args.whe_args.num_comp2 = 0;
    cmd->whe_args.whe_args.op_num = 0;
	
	//keep using the select function
	while(arg_idx < cmd->args_len) {
        if (!strncmp(cmd->args[arg_idx], "table", 5)) {
            ;
        } else if (!strncmp(cmd->args[arg_idx], "from", 3)) {
            ;
        } else if (!strncmp(cmd->args[arg_idx], "where", 5)) {
            where_state_handler(cmd, arg_idx+1);
            return;
        } else {
            cmd->type = UNRECOG_CMD;
            return;
        }
        arg_idx += 1;
    }
	if(arg_idx == cmd->args_len)
		return;
    cmd->type = UNRECOG_CMD;
    return;
}

void aggregate_state_handler(Command_t *cmd, size_t arg_idx){
	if (arg_idx < cmd->args_len){
		if(!strncmp(cmd->args[arg_idx], "sum", 3))
			cmd->agge_args.agge_args.agge_type = sum;
		else if(!strncmp(cmd->args[arg_idx], "count", 5))
			cmd->agge_args.agge_args.agge_type = count;
		else if(!strncmp(cmd->args[arg_idx], "avg", 3))
			cmd->agge_args.agge_args.agge_type = avg;
		
		char *pch;
		pch = strstr(cmd->args[arg_idx] , "(");
		if(!strncmp(pch+1, "id", 2)){
			add_agge_field(cmd,"id");
		}
		else if(!strncmp(pch+1, "name", 4)){
			add_agge_field(cmd,"name");
		}
		else if(!strncmp(pch+1,"email", 5)){
			add_agge_field(cmd,"email");
		}
		else if(!strncmp(pch+1, "age", 3)){
			add_agge_field(cmd,"age");
		}
		arg_idx++;
		if (arg_idx == cmd->args_len) {
            return;
        } else if(!strncmp(cmd->args[arg_idx],"table",5)){
			table_state_handler(cmd,arg_idx+1);
			return;
		} else if(!strncmp(cmd->args[arg_idx],"where",5)){
			where_state_handler(cmd,arg_idx+1);
			return;
		} else if (!strncmp(cmd->args[arg_idx], "offset", 6)) {
            offset_state_handler(cmd, arg_idx+1);
            return;
        } else if (!strncmp(cmd->args[arg_idx], "limit", 5)) {
            limit_state_handler(cmd, arg_idx+1);
            return;
        }
	}
}
void table_state_handler(Command_t *cmd, size_t arg_idx) {
    if (arg_idx < cmd->args_len
            && !strncmp(cmd->args[arg_idx], "table", 5)) {

        arg_idx++;
        if (arg_idx == cmd->args_len) {
            return;
        } else if(!strncmp(cmd->args[arg_idx],"where",5)){
	    where_state_handler(cmd,arg_idx+1);
	    return;
	} else if (!strncmp(cmd->args[arg_idx], "offset", 6)) {
            offset_state_handler(cmd, arg_idx+1);
            return;
        } else if (!strncmp(cmd->args[arg_idx], "limit", 5)) {
            limit_state_handler(cmd, arg_idx+1);
            return;
        }
    }
    cmd->type = UNRECOG_CMD;
    return;
}
void where_state_handler(Command_t *cmd,size_t arg_idx){
    if (arg_idx < cmd->args_len){
	add_where_field(cmd,cmd->args[arg_idx]);
	if ( !strncmp(cmd->args[arg_idx],"id",2) || !strncmp(cmd->args[arg_idx],"age",3) ){
	     arg_idx++;
         if(!strncmp(cmd->args[arg_idx],"=",1)){
	          cmd->whe_args.whe_args.op_type1 = equalto;
	     } else if(!strncmp(cmd->args[arg_idx],"!=",2)){
	          cmd->whe_args.whe_args.op_type1 = notEqualto;
		 } else if(!strncmp(cmd->args[arg_idx],">=",2)){
	          cmd->whe_args.whe_args.op_type1 = greaterOrEqualto;
	     } else if(!strncmp(cmd->args[arg_idx],"<=",2)){
	          cmd->whe_args.whe_args.op_type1 = lessOrEqualto; 
	     } else if(!strncmp(cmd->args[arg_idx],">",1)){
	          cmd->whe_args.whe_args.op_type1 = greater;
	     } else if(!strncmp(cmd->args[arg_idx],"<",1)){
	          cmd->whe_args.whe_args.op_type1 = less;
	     } 
	     arg_idx++;
	     cmd->whe_args.whe_args.num_comp1 = atoi(cmd->args[arg_idx]);
	} else if ( !strncmp(cmd->args[arg_idx],"name",4) || !strncmp(cmd->args[arg_idx],"email",5) ){
	     arg_idx++;
             if(!strncmp(cmd->args[arg_idx],"=",1)){
	          cmd->whe_args.whe_args.op_type1 = stringEqualto;
	     } else if(!strncmp(cmd->args[arg_idx],"!=",2)){
		  cmd->whe_args.whe_args.op_type1 = stringNotEqualto;
	     }
	     arg_idx++;
	     cmd->whe_args.whe_args.string_comp1 = strdup(cmd->args[arg_idx]) ;
	}
	arg_idx++;
	if(arg_idx < cmd->args_len){
	     if(!strncmp(cmd->args[arg_idx],"and",3)){
	     	cmd->whe_args.whe_args.op_num = andOp;
	     } else if(!strncmp(cmd->args[arg_idx],"or",2)){
	     	cmd->whe_args.whe_args.op_num = orOp;
	     } else if(!strncmp(cmd->args[arg_idx],"offset",6)){
	        offset_state_handler(cmd,arg_idx+1);
			return;
	     } else if(!strncmp(cmd->args[arg_idx],"limit",5)){
	     	limit_state_handler(cmd,arg_idx+1);
			return;
	     }
	     arg_idx++;
	     if(cmd->whe_args.whe_args.op_num==andOp || cmd->whe_args.whe_args.op_num==orOp){
	     	add_where_field(cmd,cmd->args[arg_idx]);
		if ( !strncmp(cmd->args[arg_idx],"id",2) || !strncmp(cmd->args[arg_idx],"age",3) ){
	     		arg_idx++;
             	if(!strncmp(cmd->args[arg_idx],"=",1)){
	          	cmd->whe_args.whe_args.op_type2 = equalto;
	     	} else if(!strncmp(cmd->args[arg_idx],"!=",2)){
	          	cmd->whe_args.whe_args.op_type2 = notEqualto;
	     	} else if(!strncmp(cmd->args[arg_idx],">=",2)){
	          	cmd->whe_args.whe_args.op_type2 = greaterOrEqualto;
	     	} else if(!strncmp(cmd->args[arg_idx],"<=",2)){
	          	cmd->whe_args.whe_args.op_type2 = lessOrEqualto;
	     	} else if(!strncmp(cmd->args[arg_idx],">",1)){
	        	cmd->whe_args.whe_args.op_type2 = greater;
	     	} else if(!strncmp(cmd->args[arg_idx],"<",1)){
	          	cmd->whe_args.whe_args.op_type2 = less;
	     	} 
	     	arg_idx++;
	     	cmd->whe_args.whe_args.num_comp2 = atoi(cmd->args[arg_idx]);
	     } else if ( !strncmp(cmd->args[arg_idx],"name",4) || !strncmp(cmd->args[arg_idx],"email",5) ){
	     	arg_idx++;
             	if(!strncmp(cmd->args[arg_idx],"=",1)){
	          cmd->whe_args.whe_args.op_type2 = stringEqualto;
	     	} else if(!strncmp(cmd->args[arg_idx],"!=",2)){
		  cmd->whe_args.whe_args.op_type2 = stringNotEqualto;
	     	}
	     	arg_idx++;
	     	cmd->whe_args.whe_args.string_comp2 = strdup(cmd->args[arg_idx]) ;
		 }
	    }
	 }
	 arg_idx++;
	 if(arg_idx < cmd->args_len){
		 if(!strncmp(cmd->args[arg_idx],"offset",6)){
	        offset_state_handler(cmd,arg_idx+1);
			return;
	     } else if(!strncmp(cmd->args[arg_idx],"limit",5)){
	     	limit_state_handler(cmd,arg_idx+1);
			return;
	     }
	 }
    }
    cmd->type = UNRECOG_CMD;
    return;
}
void offset_state_handler(Command_t *cmd, size_t arg_idx) {
    if (arg_idx < cmd->args_len) {
        cmd->cmd_args.sel_args.offset = atoi(cmd->args[arg_idx]);

        arg_idx++;

        if (arg_idx == cmd->args_len) {
            return;
        } else if (arg_idx < cmd->args_len
                && !strncmp(cmd->args[arg_idx], "limit", 5)) {

            limit_state_handler(cmd, arg_idx+1);
            return;
        }
    }
    cmd->type = UNRECOG_CMD;
    return;
}

void limit_state_handler(Command_t *cmd, size_t arg_idx) {
    if (arg_idx < cmd->args_len) {
        cmd->cmd_args.sel_args.limit = atoi(cmd->args[arg_idx]);

        arg_idx++;

        if (arg_idx == cmd->args_len) {
            return;
        }
    }
    cmd->type = UNRECOG_CMD;
    return;
}
