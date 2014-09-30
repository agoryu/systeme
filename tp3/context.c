#include "context.h"

static struct ctx_s *current_ctx = (struct ctx_s*)0;
static struct ctx_s *ctx_ring = (struct ctx_s*)0;
void* initial_esp;
void* initial_ebp;
static int first_call = 1;

/**
 * \brief Fonction permettant l'initiation d'un contexte 
 * \param[in] ctx 			contexte à initialiser
 * \param[in] stack_size 	taille du contexte à initialiser
 * \param[in] f				fonctione exécuter sur la pile
 * \param[in] arg			arguement de la fonctione lancé par le contexte
 * \return					0 en cas d'erreur et 1 sinon
 */
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

/**
 * \brief Fonction permettant d'échanger des contextes
 * \param[in] ctx 		context qui sera actif
 */
void switch_to_ctx(struct ctx_s *ctx){

  /* si ctx est null on retourne au main */
  if (!ctx) {
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

  if(ctx -> state == CTX_END) {
    if(ring == ctx)
      ring = current_ctx;

    current_ctx->next = ctx->next;
    free(ctx->ctx_stack);
    free(ctx);
    yield();
  }

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
  
    start_ctx();
  }

  void start_ctx() {
    if(current_ctx->ctx_state == CTX_INIT){
      current_ctx->ctx_state = CTX_EXQ;
      current_ctx->ctx_f(current_ctx->ctx_arg);
      current_ctx->ctx_state = CTX_END;
    
      /* retour au main */
      if(ctx->next == ctx) {
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
  }

  int create_ctx(const int stack_size, const func_t, const void* arg) {
  
    struct ctx_s new_ctx;
    new_ctx = malloc(sizeof (struct ctx_s));
  
    if(new_ctx == NULL)
      return 0;

    /* premier passage dans le create */
    if (ctx_ring != NULL) {
      new_ctx -> next = ctx_ring -> next;
      ctx_ring -> next = new_ctx;
      /* tous les autres passages */
    } else {
      ctx_ring = new_ctx;
      new_ctx -> next = new_ctx;
    }

    return init_ctx(new_ctx, stack_size, f, arg);
  }

  void yield() {
    if(current_ctx)
      switch_to(current_ctx->next);
    /* premiet passage */
    else
      switch_to(ctx_ring);
  }

