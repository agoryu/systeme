#ifndef CONTEXT_H
#define CONTEXT_H

/**
 * \file context.h
 * \brief Gestionnaire de contexte
 * \author Elliot Vanegue et Gaëtan Deflandre
 * \version 1
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/** 
 * \brief Define permettant de reconnaitre le contexte en cours 
 */
#define CTX_MAGIC 0xCAFEBABE

/** 
 * \enum ctx_state_e
 *  Enumération des états que peut prendre une fonction 
 */
enum ctx_state_e {CTX_INIT, CTX_EXQ, CTX_END};

/** \typedef 
 *   Représente une fonction qui retourne un void 
 */
typedef void (func_t) (void*);

/** \struct 
 *  Représente un contexte 
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

/** \brief Fonction permettant l'initiation d'un contexte 
 * \param[in] ctx 		contexte à initialiser
 * \param[in] stack_size 	taille du contexte à initialiser
 * \param[in] f			fonctione exécuter sur la pile
 * \param[in] arg		arguement de la fonctione lancé par le contexte
 * \return			0 en cas d'erreur et 1 sinon
 */
int init_ctx(struct ctx_s * ctx, int stack_size, func_t f, void * arg);

/** \brief Fonction permettant d'échanger des contextes
  * \param[in] ctx 		context qui sera actif
  */
void switch_to_ctx (struct ctx_s * ctx);

#endif
