#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* 
 * \brief define permettant de reconnaitre le contexte en cours 
 */
#define CTX_MAGIC 0xCAFEBABE

/* 
 * \enum ctx_state_e
 * enumération des états que peut prendre une fonction 
 */
enum ctx_state_e {CTX_INIT, CTX_EXQ, CTX_END};

/* \typedef 
 * représente une fonction qui retourne un void 
 */
typedef void (func_t) (void*);

/* \struct 
 * représente un contexte 
 */
struct ctx_s {
	void * ctx_esp;
	void * ctx_ebp;
	unsigned int ctx_state;
	func_t * ctx_f;
	void * ctx_arg;
	void * ctx_stack;
	unsigned ctx_magic;
};

/**
 *
 */
struct ctx_current_s {
  struct ctx_s * current;
  void * esp_initial;
  void * ebp_initial;
};

/* \brief 
 * fonction permettant l'initiation d'un contexte 
 * \param[in] ctx 		context à initialiser
 * \param[in] stack_size 	taille du contexte à initialiser
 * \param[in] f			fonctione exécuter sur la pile
 * \param[in] arg		arguement de la fonctione lancé par le contexte
 */
int init_ctx(struct ctx_s * ctx, int stack_size, func_t f, void * arg);

/* fonction permettant d'échanger des contextes */
void switch_to_ctx (struct ctx_s * ctx);
