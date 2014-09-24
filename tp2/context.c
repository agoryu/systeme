#include "context.h"

static struct ctx_current_s *current_ctx = (struct ctx_current_s*)0;

int init_ctx(struct ctx_s *ctx, int stack_size, func_t f, void* args){

  ctx->ctx_stack = malloc(stack_size);
  if(ctx->ctx_stack == NULL){
    perror("Erreur d'allocution pour la stack\n");
    return -1;
  }

  ctx->ctx_esp = ctx->ctx_ebp = ((char*)ctx->ctx_stack) +stack_size - 4;

  ctx->ctx_f = f;
  ctx->ctx_arg = args;
  ctx->ctx_state = CTX_INIT;
  ctx->ctx_magic = CTX_MAGIC;

  return 0;
}

void switch_to_ctx(struct ctx_s *ctx){
  if(current_ctx){
    assert(ctx->ctx_magic == CTX_MAGIC);
    asm("movl %%esp, %0"
	: "=r" (current_ctx->current->ctx_esp)
	: );
    asm("movl %%ebp, %0"
	: "=r" (current_ctx->current->ctx_ebp)
	: );
  } else {	
    asm("movl %%esp, %0"
	: "=r" (current_ctx->esp_initial)
	: );
    asm("movl %%ebp, %0"
	: "=r" (current_ctx->ebp_initial)
	: );
  }
  current_ctx->current = ctx;
  asm("movl %0, %%esp"
      : 
      :"r" (ctx->ctx_esp));
  asm("movl %0, %%ebp"
      :
      :"r" (ctx->ctx_ebp));
  
  if(current_ctx->current->ctx_state == CTX_INIT){
    	current_ctx->current->ctx_state = CTX_EXQ;
    	current_ctx->current->ctx_f(current_ctx->current->ctx_arg);
    	current_ctx->current->ctx_state = CTX_END;
    
	while(1){}
  }

}
