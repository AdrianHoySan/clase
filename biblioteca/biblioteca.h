typedef struct {int type; char data[255];} object;
typedef struct st_dict_node {object key; object value; struct st_dict_node *next;} dict_node;
typedef struct {dict_node *first; int len;} dict;

void int_to_obj(int src, object *dst);
void float_to_obj(float src, object *dst);
void str_to_obj(char *src, object *dst);

void obj_to_int(object src,int *dst);
void obj_to_float(object src, float *dst);
void obj_to_str(object src, char *dst);

dict *dict_new();
void dict_destroy(dict *dic);

dict_node *dict_first(dict *dic);
dict_node *dict_next(dict *dic, dict_node *current);

int dict_add(dict *dic, object key, object value);
int dict_search(dict *dic, object key, object *dst);
int dict_remove(dict *dic, object key);

void dict_key(dict_node *pair, object *dst);
void dict_value(dict_node *pair, object *dst);

int dict_lens(dict *dic);
int dict_equals(dict *dic1, dict *dic2);


