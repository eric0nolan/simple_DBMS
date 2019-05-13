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
	     } else if(!strncmp(cmd->args[arg_idx],">",1)){
	          cmd->whe_args.whe_args.op_type1 = greater;
	     } else if(!strncmp(cmd->args[arg_idx],"<",1)){
	          cmd->whe_args.whe_args.op_type1 = less;
	     } else if(!strncmp(cmd->args[arg_idx],">=",2)){
	          cmd->whe_args.whe_args.op_type1 = greaterOrEqualto;
	     } else if(!strncmp(cmd->args[arg_idx],"<=",2)){
	          cmd->whe_args.whe_args.op_type1 = lessOrEqualto;
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
	     	} else if(!strncmp(cmd->args[arg_idx],">",1)){
	        	cmd->whe_args.whe_args.op_type2 = greater;
	     	} else if(!strncmp(cmd->args[arg_idx],"<",1)){
	          	cmd->whe_args.whe_args.op_type2 = less;
	     	} else if(!strncmp(cmd->args[arg_idx],">=",2)){
	          	cmd->whe_args.whe_args.op_type2 = greaterOrEqualto;
	     	} else if(!strncmp(cmd->args[arg_idx],"<=",2)){
	          	cmd->whe_args.whe_args.op_type2 = lessOrEqualto;
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
