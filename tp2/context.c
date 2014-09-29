#include "context.h"

static struct ctx_s *current_ctx = (struct ctx_s*)0;
void* initial_esp;
void* initial_ebp;

int init_ctx(struct ctx_s *ctx, int stack_size, func_t f, void* args){

  ctx->ctx_stack = malloc(stack_size);
  if(ctx->ctx_stack == NULL){
    perror("Erreur d'allocution pour la stack\n");
    return 0;
  }

  ctx->ctx_esp = ctx->ctx_ebp = ((char*)ctx->ctx_stack) +stack_size - 4;

  ctx->ctx_f = f;
  ctx->ctx_arg = args;
  ctx->ctx_state = CTX_INIT;
  ctx->ctx_magic = CTX_MAGIC;

  return 1;
}

void switch_to_ctx(struct ctx_s *ctx){
  
  static int first_call = 1;

  if(first_call){
    first_call = 0;
    asm("movl %%esp, %0"
	: "=r" (initial_esp)
	: );
    asm("movl %%ebp, %0"
	: "=r" (initial_ebp)
	: );
  }
  

  if(current_ctx){
    assert(ctx->ctx_magic == CTX_MAGIC);
    asm("movl %%esp, %0"
	: "=r" (current_ctx->ctx_esp)
	: );
    asm("movl %%ebp, %0"
	: "=r" (current_ctx->ctx_ebp)
	: );
  }

  current_ctx = ctx;
  asm("movl %0, %%esp"
      : 
      :"r" (ctx->ctx_esp));
  asm("movl %0, %%ebp"
      :
      :"r" (ctx->ctx_ebp));
  
  if(current_ctx->ctx_state == CTX_INIT){
    	current_ctx->ctx_state = CTX_EXQ;
    	current_ctx->ctx_f(current_ctx->ctx_arg);
    	current_ctx->ctx_state = CTX_END;
    
	first_call = 1;
	current_ctx = (struct ctx_s*)0;
	asm("movl %0, %%esp"
	    : 
	    :"r" (initial_esp));
	asm("movl %0, %%ebp"
	    :
	    :"r" (initial_ebp));
  }

}
