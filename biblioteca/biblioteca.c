#include "biblioteca.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void int_to_obj(int src, object *dst) {
    dst->type = 0;
    sprintf(dst->data,"%i",src);
}

void obj_to_int(object src, int *dst) {
    if(src.type == 0) {
        *dst = atoi(src.data);
    }
}

void float_to_obj(float src, object *dst){
    dst->type = 1;
    sprintf(dst->data,"%f",src);
}

void obj_to_float(object src, float *dst) {
    if(src.type == 1) {
        *dst = atof(src.data);
    }
}

void str_to_obj(char *src, object *dst) {
    dst->type = 2;
    sprintf(dst->data,"%s",src);
}

void obj_to_str(object src, char *dst) {
    if(src.type == 2) {
        sprintf(dst,"%s",src.data);
    }
}

dict *dict_new() {
    dict *diccionario = malloc(sizeof(dict));
    diccionario->first = NULL;
    diccionario->len = 0;

    return diccionario;
}

void dict_destroy(dict *dic) {
    dict_node *nodoAux = dict_first(dic);
    dict_node *siguiente;
        
    while (nodoAux != NULL)
    {
        siguiente = nodoAux->next;
        free(nodoAux);
        nodoAux = siguiente;
    }

    free(dic);



}

int dict_add(dict *dic, object key, object value) {
    dict_node *nodo = malloc(sizeof(dict_node));
    sprintf(nodo->key.data,"%s",key.data);
    sprintf(nodo->value.data,"%s",value.data);
    nodo->next = NULL;
    dict_node *nodoAux = dict_first(dic);
    do
    {
        if(nodoAux == NULL) {
            dic->first = nodo;
            dic->len++;
            break;
        } else if(nodoAux->next == NULL) {
            nodoAux->next = nodo;
            dic->len++;
            break;
        }
        nodoAux = nodoAux->next;
    } while (nodoAux != NULL);
    
    return 0;
}

int dict_search(dict *dic, object key, object *dst) {
    dict_node *nodoAux = dict_first(dic);
    int boo = 1;

    if(nodoAux != NULL) {
        do
        {
            if(strcmp(nodoAux->key.data,key.data) == 0) {
                boo = 0;
                sprintf(dst->data,"%s",nodoAux->value.data);
                break;
            }
            nodoAux = nodoAux->next;
        } while (nodoAux != NULL);
    } 


    return boo;
    
}

int dict_remove(dict *dic, object key) {
    dict_node *nodoAux = dict_first(dic);
    dict_node *siguiente;
    int boo = 1;
    if(strcmp(nodoAux->key.data,key.data) == 0) {
        dic->first = nodoAux->next;
        free(nodoAux);
        boo = 0;
    } else {
        do
        {
            if(strcmp(nodoAux->next->key.data,key.data) == 0) {
                if(nodoAux->next->next != NULL) {
                    siguiente = nodoAux->next->next;
                    free(nodoAux->next);
                    nodoAux->next = siguiente;
                    boo = 0;
                    break;
                } else {
                    free(nodoAux->next);
                    nodoAux->next = NULL;
                    boo = 0;
                    break;
                }
            }
            nodoAux = nodoAux->next;
        } while (nodoAux->next != NULL);
    }


    return boo;
}

dict_node *dict_first(dict *dic) {
    return dic->first;
}

dict_node *dict_next(dict *dic, dict_node *current) {
    dict_node *next;

    if(current != NULL) {
        if(current->next != NULL) {
            next = current->next;
        } else {
            next = NULL;
        }
    } else {
        next = NULL;
    }

    return next;
}

void dict_key(dict_node *pair, object *dst) {
    sprintf(dst->data,"%s",pair->key.data);
}

void dict_value(dict_node *pair, object *dst) {
    sprintf(dst->data,"%s",pair->value.data);
}

int dic_len(dict *dic) {
    return dic->len;
}

int dict_equals(dict *dic1, dict *dic2) {
    dict_node *comparacionPrimero = dict_first(dic1);
    dict_node *comparacionSegundo = dict_first(dic2);
    dict_node *siguienteSegundo;
    int comprobacion = 0;
    int iguales = 0;

    if(comparacionPrimero != NULL && comparacionSegundo != NULL) {
        if(dic_len(dic1) == dic_len(dic2)) {
            while(comparacionPrimero != NULL) {
                siguienteSegundo = comparacionSegundo;
                while(siguienteSegundo != NULL && iguales == 0) {
                    if(strcmp(comparacionPrimero->key.data,siguienteSegundo->key.data) == 0) {
                        iguales = 1;
                    } else {
                        siguienteSegundo = siguienteSegundo->next;
                    }
                }
                if(iguales == 0) {
                    comprobacion = 1;
                    break;
                }
                comparacionPrimero = comparacionPrimero->next;
            }
        } else {
            comprobacion = 2;
        }
    } else {
        comprobacion = 3;
    }

    return comprobacion;
}