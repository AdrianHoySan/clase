#include "biblioteca.h"
#include "stdio.h"


void main() {
    dict *dic,*dic2,*dic3,*dic4; // Diccionario
    object key, value; // Almacenes de datos
    object key2,value2,key3,value3; //Almacenes de datos para segunda biblioteca

    // creamos diccionario
    dic = dict_new();
    dic2 = dict_new();
    dic3 = dict_new();
    dic4 = dict_new();

    // insertamos dos elementos
    int_to_obj(1, &key); str_to_obj("Pepe", &value);
    //Vamos a comprobar si comprueba bien cuando añade
    switch (dict_add(dic, key, value))
    {
    case 0:
        printf("Se ha añadido correctamente \n");
        break;
    case 1:
        printf("Esa clave ya existe \n");
        break;
    default:
        printf("Error \n");
        break;
    }
    int_to_obj(1, &key); str_to_obj("Amparo", &value);
    //Este debería darnos el error de esa clave ya existe porque tiene la misma que el anterior
    switch (dict_add(dic, key, value))
    {
    case 0:
        printf("Se ha añadido correctamente \n");
        break;
    case 1:
        printf("Esa clave ya existe \n");
        break;
    default:
        printf("Error \n");
        break;
    }
    int_to_obj(2, &key); str_to_obj("Juan", &value);
    dict_add(dic, key, value);
    int_to_obj(3, &key); str_to_obj("Adrian", &value);
    dict_add(dic, key, value);

    // insertamos los elementos del segundo diccionario
    int_to_obj(1, &key2); str_to_obj("Pepe", &value2);
    dict_add(dic2, key2, value2);
    int_to_obj(3, &key2); str_to_obj("Adrian", &value2);
    dict_add(dic2, key2, value2);
    int_to_obj(2, &key2); str_to_obj("Juan", &value2);
    dict_add(dic2, key2, value2);

    // insertamos los elementos del tercer diccionario
    float_to_obj(10.65, &key3); int_to_obj(4, &value3);
    dict_add(dic3, key3, value3);
    str_to_obj("Julian", &key3); str_to_obj("Juan", &value3);
    dict_add(dic3, key3, value3);
    int_to_obj(3, &key3); str_to_obj("Adrian", &value3);
    dict_add(dic3, key3, value3);
    str_to_obj("Pablo", &key3); str_to_obj("Pedro", &value3);
    dict_add(dic3, key3, value3);

    //Vamos a ver si son iguales los diccionarios
    switch (dict_equals(dic,dic2))
    {
    case 0:
        printf("Son iguales \n");
        break;
    case 1:
        printf("No son iguales \n");
        break;
    case 2:
        printf("No son igual de grandes \n");
        break;
    case 3:
        printf("Hay un diccionario vacío \n");
        break;
    default:
        printf("Ha habido un error \n");
        break;
    }

    //Vamos a comparar dos diccionarios de diferentes tamaños
    switch (dict_equals(dic,dic3))
    {
    case 0:
        printf("Son iguales \n");
        break;
    case 1:
        printf("No son iguales \n");
        break;
    case 2:
        printf("No son igual de grandes \n");
        break;
    case 3:
        printf("Hay un diccionario vacío \n");
        break;
    default:
        printf("Ha habido un error \n");
        break;
    }

    //Vamos a comparar un diccionario con elementos con un vacío
    switch (dict_equals(dic,dic4))
    {
    case 0:
        printf("Son iguales \n");
        break;
    case 1:
        printf("No son iguales \n");
        break;
    case 2:
        printf("No son igual de grandes \n");
        break;
    case 3:
        printf("Hay un diccionario vacío \n");
        break;
    default:
        printf("Ha habido un error \n");
        break;
    }

    // buscamos elemento
    char str[50];
    str_to_obj("Pedro", &key);
    if(dict_search(dic3, key, &value) == 0) {
        obj_to_str(value, str);
        printf("%s \n", str);
    } else {
        printf("No existe esa clave \n");
    }

    // eliminamos un elemento
    if(dict_remove(dic3,key) == 0) {
       printf("Eliminado \n"); 
    } else {
        printf("No existe esa clave \n");
    }

    //iteramos
    int i;
    float f;
    char stri[255];
    dict_node *node;
    node = dict_first(dic3);
    //Iteramos por nuestro diccionario
    while (node != NULL) {
        dict_key(node, &key3); dict_value(node, &value3);
        //Comprobamos el tipo de nuestra clave
        if(node->key.type == 0) {
            obj_to_int(key3, &i);
            printf("%d->", i);
        } else if(node->key.type == 1) {
            obj_to_float(key3, &f);
            printf("%f->", f);
        } else {
            obj_to_str(key3, stri);
            printf("%s->", stri);
        }
        //Comprobamos el tipo de nuestro valor
        if(node->value.type == 0) {
            obj_to_int(value3, &i);
            printf("%d \n", i);
        } else if(node->value.type == 1) {
            obj_to_float(value3, &f);
            printf("%f \n", f);
        } else {
            obj_to_str(value3, str);
            printf("%s \n",str);
        }
        //Pasamos al siguiente elemento
        node = dict_next(dic3, node);
    }
    
    // destruimos el diccionario (libera TODO)
    dict_destroy(dic);
    dict_destroy(dic2);
    dict_destroy(dic3);
    dict_destroy(dic4);
}