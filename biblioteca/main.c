#include "biblioteca.h"
#include "stdio.h"


void main() {
    dict *dic,*dic2; // Diccionario
    object key, value; // Almacenes de datos
    object key2,value2; //Almacenes de datos para segunda biblioteca

    // creamos diccionario
    dic = dict_new();
    dic2 = dict_new();

    // insertamos dos elementos
    int_to_obj(1, &key); str_to_obj("Pepe", &value);
    dict_add(dic, key, value);
    int_to_obj(2, &key); str_to_obj("Juan", &value);
    dict_add(dic, key, value);
    int_to_obj(3, &key); str_to_obj("Adrian", &value);
    dict_add(dic, key, value);

    // insertamos los elementos del segundo diccionario
    int_to_obj(1, &key2); str_to_obj("Pepe", &value2);
    dict_add(dic2, key2, value2);
    int_to_obj(2, &key2); str_to_obj("Juan", &value2);
    dict_add(dic2, key2, value2);
    int_to_obj(3, &key2); str_to_obj("Adrian", &value2);
    dict_add(dic2, key2, value2);

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
    default:
        printf("Ha habido un error \n");
        break;
    }

    // // buscamos elemento
    // char str[50];
    // int_to_obj(122, &key);
    // if(dict_search(dic, key, &value) == 0) {
    //     obj_to_str(value, str);
    //     printf("%s \n", str);
    // } else {
    //     printf("No existe esa clave \n");
    // }

    // //eliminamos un elemento
    // if(dict_remove(dic,key) == 0) {
    //    printf("Eliminado \n"); 
    // } else {
    //     printf("No hay esa clave \n");
    // }

    // //iteramos
    // int i;
    // dict_node *node;
    // node = dict_first(dic);
    // while (node != NULL) {
    //     dict_key(node, &key); dict_value(node, &value);
    //     obj_to_int(key, &i); obj_to_str(value, str);
    //     printf("%d->%s \n", i, str);

    //     node = node->next;
    // }
    
    // destruimos el diccionario (libera TODO)
    dict_destroy(dic);
    dict_destroy(dic2);
}