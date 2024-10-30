/**
 * @file biblioteca.c
 * @author Adrián Hoyos Sánchez
 * @brief 
 * @version 1
 * @date 2024-10-30
 * 
 */
#include "biblioteca.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief 
 * Método que convierte un int en un object
 * @param src este es el int que vamos a convertir
 * @param dst este el object donde vamos a guardar el dato
 */
void int_to_obj(int src, object *dst) {
    dst->type = 0;
    sprintf(dst->data,"%i",src);
}

/**
 * @brief 
 * Método que transforma un object en una variable de tipo int
 * @param src este el object que vamos a transformar
 * @param dst este es la variable donde lo vamos a depositar
 */
void obj_to_int(object src, int *dst) {
    if(src.type == 0) {
        *dst = atoi(src.data);
    }
}

/**
 * @brief 
 * Método que transforma un float a un object
 * @param src este es el float que vamos a transformar
 * @param dst este es el object donde vamos a almacenar el dato
 */
void float_to_obj(float src, object *dst){
    dst->type = 1;
    sprintf(dst->data,"%f",src);
}

/**
 * @brief 
 * Métood que transforma un object a un float
 * @param src este es el object que vamos a transformar
 * @param dst este es el float donde almacenamos el dato
 */
void obj_to_float(object src, float *dst) {
    if(src.type == 1) {
        *dst = atof(src.data);
    }
}

/**
 * @brief 
 * Método que transforma un String a un object
 * @param src este es el string que vamos a transformar
 * @param dst este es el object donde lo vamos a almacenar
 */
void str_to_obj(char *src, object *dst) {
    dst->type = 2;
    sprintf(dst->data,"%s",src);
}

/**
 * @brief 
 * Método que transforma un object en un String
 * @param src este es el object que vamos a transformar
 * @param dst este es el string donde lo vamos a almacenar
 */
void obj_to_str(object src, char *dst) {
    if(src.type == 2) {
        sprintf(dst,"%s",src.data);
    }
}

/**
 * @brief 
 * Método que crea un diccionario
 * @return dict* devolvemos la dirección de memoria del diccionario recién creado
 */
dict *dict_new() {
    dict *diccionario = malloc(sizeof(dict));
    diccionario->first = NULL;
    diccionario->len = 0;

    return diccionario;
}

/**
 * @brief 
 * Método que destruye un diccionario con todos sus componentes
 * @param dic este el diccionario que queremos destruir
 */
void dict_destroy(dict *dic) {
    dict_node *nodoAux = dict_first(dic);
    dict_node *siguiente;
        
    while (nodoAux != NULL)
    {
        siguiente = dict_next(dic, nodoAux);
        free(nodoAux);
        nodoAux = siguiente;
    }

    free(dic);
}

/**
 * @brief 
 * Método que indica si una clave está en un diccionario
 * @param dic el diccionario donde queremos comprobar si existe la clave
 * @param key la clave que queremos comprobar si existe
 * @return int devuelve 0 si la hemos encontrado o 1 si no la hemos encontrado
 */
int existe(dict *dic, object key) {
    int encontrado = 1;
    dict_node *nodoAux = dict_first(dic);

    if(nodoAux != NULL) {
        do
        {
            if(strcmp(nodoAux->key.data,key.data) == 0) {
                encontrado = 0;
                break;
            }
            nodoAux = dict_next(dic, nodoAux);
        } while (nodoAux != NULL);
    }

    return encontrado; 
}

/**
 * @brief 
 * Método que añade una entrada al diccionario
 * @param dic el diccionario donde queremos añadir la entrada
 * @param key la clave que queremos que tenga esa entrada
 * @param value el valor que queremos que tenga esa entrada
 * @return int si devuelve 0 es que se ha añadido correctamente, 1 es que la clave ya existe
 */
int dict_add(dict *dic, object key, object value) {
    dict_node *nodo = malloc(sizeof(dict_node));
    int anadido = 0;
    sprintf(nodo->key.data,"%s",key.data);
    nodo->key.type = key.type;
    sprintf(nodo->value.data,"%s",value.data);
    nodo->value.type = value.type;

    nodo->next = NULL;
    dict_node *nodoAux = dict_first(dic);

    if(anadido == 0) {
        //comprobamos si ya existe esa clave
        if(existe(dic, key) != 0) {
            //recorremos el diccionario para añadir al final el nuevo nodo
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
                nodoAux = dict_next(dic, nodoAux);
            } while (nodoAux != NULL);
        } else {
            anadido = 1;
        }
    }

    return anadido;
}

/**
 * @brief 
 * Método que busca una clave en el diccionario y le asigna su valor deseado
 * @param dic el diccionario donde queremos buscar la llave
 * @param key la llave que queremos buscar en el diccionario
 * @param dst el objecto donde retornaremos el valor de esa clave
 * @return int devuelve 0 si encuentra la clave y 1 si no la encuentra
 */
int dict_search(dict *dic, object key, object *dst) {
    dict_node *nodoAux = dict_first(dic);
    int boo = 1;
    //comprobamos si el nodo esta vacío
    if(nodoAux != NULL) {
        //recorremos el diccionario hasta que encontremos la clave o no este en este
        do
        {
            if(strcmp(nodoAux->key.data,key.data) == 0) {
                boo = 0;
                sprintf(dst->data,"%s",nodoAux->value.data);
                break;
            }
            nodoAux = dict_next(dic, nodoAux);
        } while (nodoAux != NULL);
    } 


    return boo;
    
}

/**
 * @brief 
 * Método que elimina una clave con su valor del diccionario
 * @param dic diccionario del cual queremos remover el valor marcado por la clave
 * @param key la clave de la pareja que queremos eliminar
 * @return int devuelve 0 si ha podido eliminarla y 1 si no se encuentra en el diccionario
 */
int dict_remove(dict *dic, object key) {
    dict_node *nodoAux = dict_first(dic);
    dict_node *siguiente;
    int boo = 1;
    //comprobamos si el que queremos remover es la primera clave
    if(strcmp(nodoAux->key.data,key.data) == 0) {
        dic->first = nodoAux->next;
        free(nodoAux);
        boo = 0;
        dic->len --;
    } else {
        //Recorremos todo el diccionario en busca de la clave que queremos eliminar
        do
        {
            if(strcmp(nodoAux->next->key.data,key.data) == 0) {
                if(nodoAux->next->next != NULL) {
                    siguiente = nodoAux->next->next;
                    free(nodoAux->next);
                    nodoAux->next = siguiente;
                    dic->len --;
                    boo = 0;
                    break;
                } else {
                    free(nodoAux->next);
                    nodoAux->next = NULL;
                    dic->len --;
                    boo = 0;
                    break;
                }
            }
            nodoAux = dict_next(dic,nodoAux);
        } while (nodoAux->next != NULL);
    }


    return boo;
}

/**
 * @brief 
 * Método que devuelve el primer elemento del diccionario
 * @param dic del diccionario del cual queremos recuperar el primer elemento
 * @return dict_node* devuelve el primer nodo del diccionario
 */
dict_node *dict_first(dict *dic) {
    return dic->first;
}

/**
 * @brief 
 * Método que devuelve el siguiente nodo del que se le pasa por parámetro
 * @param dic el diccionario en el cual se encuentra el nodo que queremos recuperar el siguiente
 * @param current el nodo actual del cual queremos recuperar el siguiente
 * @return dict_node* devuelve el nodo siguiente al actual
 */
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

/**
 * @brief 
 * Método que devuelve una llave de una par clave,valor
 * @param pair el nodo del cual queremos saber la clave
 * @param dst el object donde vamos a almacenar dicha llave
 */
void dict_key(dict_node *pair, object *dst) {
    dst->type = pair->key.type;
    sprintf(dst->data,"%s",pair->key.data);
}

/**
 * @brief 
 * Método que devuelve el valor de un para clave,valor
 * @param pair el nodo del cual queremos saber el valor
 * @param dst el object donde vamos a almacenar dicho valor
 */
void dict_value(dict_node *pair, object *dst) {
    dst->type = pair->value.type;
    sprintf(dst->data,"%s",pair->value.data);
}

/**
 * @brief 
 * Método que devuelve el tamaño de un diccionario
 * @param dic el diccionario del cual queremos saber el tamaño
 * @return int devuelve el tamaño del diccionario
 */
int dic_len(dict *dic) {
    return dic->len;
}

/**
 * @brief 
 * Método que comprueba si dos diccionarios son iguales
 * @param dic1 el primer diccionario a comparar
 * @param dic2 el segundo que queremos comparar
 * @return int devuelve 0 si son iguales, 1 si no lo son, 2 si son de diferentes tamaños, 3 si uno de los dos esta vacío
 */
int dict_equals(dict *dic1, dict *dic2) {
    dict_node *comparacionPrimero = dict_first(dic1);
    dict_node *comparacionSegundo = dict_first(dic2);
    dict_node *siguienteSegundo;
    int comprobacion = 0;
    int iguales = 0;

    //Comprobamos si los diccionarios están vacíos
    if(comparacionPrimero != NULL && comparacionSegundo != NULL) {
        //Comprueban si tienen el mismo tamaño
        if(dic_len(dic1) == dic_len(dic2)) {
            //Recorre el primer diccionario
            while(comparacionPrimero != NULL) {
                siguienteSegundo = comparacionSegundo;
                //Recorre el segundo diccionario o hasta que encuentra una igualdad
                while(siguienteSegundo != NULL && iguales == 0) {
                    if(strcmp(comparacionPrimero->key.data,siguienteSegundo->key.data) == 0 && strcmp(comparacionPrimero->value.data,siguienteSegundo->value.data) == 0) {
                        iguales = 1;
                    } else {
                        siguienteSegundo = dict_next(dic2, siguienteSegundo);
                    }
                }
                if(iguales == 0) {
                    comprobacion = 1;
                    break;
                }
                comparacionPrimero = dict_next(dic1, comparacionPrimero);
                iguales = 0;
            }
        } else {
            comprobacion = 2;
        }
    } else {
        comprobacion = 3;
    }

    return comprobacion;
}

