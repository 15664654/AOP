#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "aop.h"
#include "Zend/zend_operators.h"


ZEND_DECLARE_MODULE_GLOBALS(aop)




static void php_aop_init_globals(zend_aop_globals *aop_globals)
{
}

static zend_function_entry aop_functions[] =
{
    ZEND_FE(aop_add_around, NULL)
    ZEND_FE(aop_add_before, NULL)
    ZEND_FE(aop_add_after, NULL)
    ZEND_FE(aop_add_final, NULL)
    ZEND_FE(aop_add_exception, NULL)
    {NULL, NULL, NULL}
};




zend_module_entry aop_module_entry =
{
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_AOP_EXTNAME,
    aop_functions,
    PHP_MINIT(aop),
    PHP_MSHUTDOWN(aop),
    PHP_RINIT(aop),
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_AOP_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_AOP
ZEND_GET_MODULE(aop)
#endif

static zend_class_entry* aop_class_entry;

zend_object_handlers aopTriggeredJoinpoint_object_handlers;

void aop_free_storage(void *object TSRMLS_DC)
{
    aopTriggeredJoinpoint_object *obj = (aopTriggeredJoinpoint_object *)object;
    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);
    efree(obj);
}




zend_object_value aop_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zval *tmp;
    zend_object_value retval;

    aopTriggeredJoinpoint_object *obj = (aopTriggeredJoinpoint_object *)emalloc(sizeof(aopTriggeredJoinpoint_object));
    memset(obj, 0, sizeof(aopTriggeredJoinpoint_object));
    obj->std.ce = type;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);

    retval.handle = zend_objects_store_put(obj, NULL,
                                           aop_free_storage, NULL TSRMLS_CC);
    retval.handlers = &aopTriggeredJoinpoint_object_handlers;

    return retval;
}

PHP_METHOD(aopTriggeredJoinpoint, getArguments);
PHP_METHOD(aopTriggeredJoinpoint, setArguments);
PHP_METHOD(aopTriggeredJoinpoint, getKindOfAdvice);
PHP_METHOD(aopTriggeredJoinpoint, getReturnedValue);
PHP_METHOD(aopTriggeredJoinpoint, setReturnedValue);
PHP_METHOD(aopTriggeredJoinpoint, getException);
PHP_METHOD(aopTriggeredJoinpoint, setException);
PHP_METHOD(aopTriggeredJoinpoint, getPointcut);
PHP_METHOD(aopTriggeredJoinpoint, getTriggeringObject);
PHP_METHOD(aopTriggeredJoinpoint, getTriggeringClassName);
PHP_METHOD(aopTriggeredJoinpoint, getTriggeringMethod);
PHP_METHOD(aopTriggeredJoinpoint, process);


ZEND_BEGIN_ARG_INFO(arginfo_aop_noargs, 0)
ZEND_END_ARG_INFO()


static const zend_function_entry aop_methods[] = {
    PHP_ME(aopTriggeredJoinpoint, getArguments,arginfo_aop_noargs, 0)
    PHP_ME(aopTriggeredJoinpoint, setArguments,arginfo_aop_noargs, 0)
    PHP_ME(aopTriggeredJoinpoint, getKindOfAdvice,arginfo_aop_noargs, 0)
    PHP_ME(aopTriggeredJoinpoint, getReturnedValue,arginfo_aop_noargs, 0)
    PHP_ME(aopTriggeredJoinpoint, setReturnedValue,arginfo_aop_noargs, 0)
    PHP_ME(aopTriggeredJoinpoint, getException,arginfo_aop_noargs, 0)
    PHP_ME(aopTriggeredJoinpoint, setException,arginfo_aop_noargs, 0)
    PHP_ME(aopTriggeredJoinpoint, getPointcut,arginfo_aop_noargs, 0)
    PHP_ME(aopTriggeredJoinpoint, getTriggeringObject,arginfo_aop_noargs, 0)
    PHP_ME(aopTriggeredJoinpoint, getTriggeringClassName,arginfo_aop_noargs, 0)
    PHP_ME(aopTriggeredJoinpoint, getTriggeringMethod,arginfo_aop_noargs, 0)
    PHP_ME(aopTriggeredJoinpoint, process,arginfo_aop_noargs, 0)
    {
        NULL, NULL, NULL
    }
};



PHP_MSHUTDOWN_FUNCTION(aop)
{
    return SUCCESS;
}

PHP_RINIT_FUNCTION(aop)
{
    aop_g(count_pcs)=0;
    aop_g(overloaded)=0;
    return SUCCESS;
}

PHP_MINIT_FUNCTION(aop)
{
    ZEND_INIT_MODULE_GLOBALS(aop, php_aop_init_globals,NULL);
    //Using if with array
    REGISTER_LONG_CONSTANT("AOP_PRIVATE", ZEND_ACC_PRIVATE, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("AOP_PUBLIC", ZEND_ACC_PUBLIC, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("AOP_PROTECTED", ZEND_ACC_PROTECTED, CONST_CS | CONST_PERSISTENT);

    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "aopTriggeredJoinpoint", aop_methods);
    aop_class_entry = zend_register_internal_class(&ce TSRMLS_CC);

    aop_class_entry->create_object = aop_create_handler;
    memcpy(&aopTriggeredJoinpoint_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    aopTriggeredJoinpoint_object_handlers.clone_obj = NULL;


//    _zend_execute = zend_execute;
//    zend_execute  = aop_execute;
    return SUCCESS;
}
PHP_METHOD(aopTriggeredJoinpoint, getArguments){}
PHP_METHOD(aopTriggeredJoinpoint, setArguments){}
PHP_METHOD(aopTriggeredJoinpoint, getKindOfAdvice){}
PHP_METHOD(aopTriggeredJoinpoint, getReturnedValue){}
PHP_METHOD(aopTriggeredJoinpoint, setReturnedValue){}
PHP_METHOD(aopTriggeredJoinpoint, getException){}
PHP_METHOD(aopTriggeredJoinpoint, setException){}
PHP_METHOD(aopTriggeredJoinpoint, getPointcut){}
PHP_METHOD(aopTriggeredJoinpoint, getTriggeringObject){}
PHP_METHOD(aopTriggeredJoinpoint, getTriggeringClassName){}
PHP_METHOD(aopTriggeredJoinpoint, getTriggeringMethod){}
PHP_METHOD(aopTriggeredJoinpoint, process){}



void add_pointcut (zval *callback, zval *selector,int type TSRMLS_DC) {
    aop_g(count_pcs)++;
    if (aop_g(count_pcs)==1) {
        aop_g(pcs) = emalloc(sizeof(pointcut));
    } else {
        aop_g(pcs) = erealloc(aop_g(pcs),aop_g(count_pcs)*sizeof(pointcut));
    }
    int count=aop_g(count_pcs)-1;
    aop_g(pcs)[count].selector = Z_STRVAL_P(selector);
    Z_ADDREF_P(callback);
    aop_g(pcs[count]).advice_callback = callback;
    aop_g(pcs[count]).kind_of_advice = type;
    parse_pointcut(&aop_g(pcs[count]));
}

void parse_pointcut (pointcut *pc) {
    pc->method = NULL;
    pc->class_name = NULL;
    pc->scope = NULL;
    pc->static_state = 2;
    char *strval;
    strval = estrdup (pc->selector);
    php_strtolower(strval, strlen(strval));
    pc->class_name = get_class_part(strval);
    pc->scope = get_scope(strval);
    pc->static_state = is_static(strval);
    if (pc->class_name!=NULL) {
        pc->method = get_method_part(strval);
        pc->num_ns = get_ns(pc->class_name, &(pc->ns));
        if (pc->num_ns>0) {
            pc->class_name = get_class_part_with_ns(pc->class_name);
        }
    } else {
        pc->method = estrdup(strval);
        pc->num_ns = get_ns(pc->method, &(pc->ns));
        if (pc->num_ns>0) {
            pc->method = get_class_part_with_ns(pc->method);
        }
    }
}


ZEND_FUNCTION(aop_add_around)
{
    zval *callback;
    zval *selector;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &selector, &callback) == FAILURE) {
        zend_error(E_ERROR, "Bad params");
        return;
    }
    add_pointcut(callback, selector,1 TSRMLS_CC);
}

ZEND_FUNCTION(aop_add_before)
{
    zval *callback;
    zval *selector;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &selector, &callback) == FAILURE) {
        zend_error(E_ERROR, "Bad params");
        return;
    }
    add_pointcut(callback, selector,2 TSRMLS_CC);
}


ZEND_FUNCTION(aop_add_after)
{
    zval *callback;
    zval *selector;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &selector, &callback) == FAILURE) {
        zend_error(E_ERROR, "Bad params");
        return;
    }
    add_pointcut(callback, selector,3 TSRMLS_CC);
}

ZEND_FUNCTION(aop_add_final) {}
ZEND_FUNCTION(aop_add_exception) {}

ZEND_DLEXPORT void aop_execute (zend_op_array *ops TSRMLS_DC) {

    int i,arounded;
    arounded=0;
    joinpoint *jp = get_current_joinpoint ();
    if (jp==NULL || jp->method==NULL || aop_g(overloaded)) {
        _zend_execute(ops TSRMLS_CC);
        return;
    }
    instance_of_pointcut *previous_ipc;
    previous_ipc = NULL;
    zval *object;
    for (i=0;i<aop_g(count_pcs);i++) {
        if (pointcut_match_joinpoint(aop_g(pcs)[i],jp)) {
         //   arounded=1;
/*
            zval *rtr=NULL;
            MAKE_STD_ZVAL(object);
            Z_TYPE_P(object) = IS_OBJECT;
            (object)->value.obj = aop_create_handler(aop_class_entry TSRMLS_CC);
            aopTriggeredJoinpoint_object *obj = (aopTriggeredJoinpoint_object *)zend_object_store_get_object(object TSRMLS_CC);
            obj->args = get_current_args(ops TSRMLS_CC);
            obj->argsOverload = 0;
            zval_copy_ctor(obj->args);
            if (class->class_name!=NULL) {
                obj->funcName = emalloc(strlen(class->class_name)+strlen(class->method)+3);
                snprintf(obj->funcName, strlen(class->class_name)+strlen(class->method)+3, "%s::%s", class->class_name, class->method);
            } else {
                obj->funcName = class->method;
            }
            if (previous_ipc!=NULL) {
                obj->joinpoint = previous_ipc;
            } else {
                obj->op = ops;
                obj->ex = EG(current_execute_data);
                obj->this = EG(This);
                obj->scope = EG(scope);
            }
            previous_ipc = emalloc(sizeof(joinpoint));
            previous_ipc->callback = aop_g(pcs)[i].callback;
            previous_ipc->object = object;
            previous_ipc->pc = aop_g(pcs)[i];
        }
        */
    }
    if (arounded) {
        aop_g(overloaded)=1;
        zval *ret;
        ret = joinpoint_execute(previous_ipc);
        aop_g(overloaded)=0;
        if (!EG(exception)) {
            if (EG(return_value_ptr_ptr)) {
                *EG(return_value_ptr_ptr)=ret;
            }
        }

    } else {
        _zend_execute(ops TSRMLS_CC);
    }
    if (previous_ipc!=NULL) {
        efree(previous_ipc);
    }
*/
}
/*
zval *joinpoint_execute (joinpoint *pc) {
    zval *args[1];
    args[0] = (zval *)&(pc->object);
    zval *zret_ptr=NULL;
    zend_fcall_info fci;
    zend_fcall_info_cache fcic= { 0, NULL, NULL, NULL, NULL };
    TSRMLS_FETCH();
    fci.param_count= 1;
    fci.size= sizeof(fci);
    fci.function_table= EG(function_table);
    fci.function_name= pc->callback;
    fci.symbol_table= NULL;
    fci.retval_ptr_ptr= &zret_ptr;
    fci.params = (zval ***)args;
    fci.object_ptr= NULL;
    fci.no_separation= 0;
    if (zend_call_function(&fci, &fcic TSRMLS_CC) == FAILURE) {
        zend_error(E_ERROR, "Problem in AOP Callback");
    }
    if (pc->pc.type==2) {
        aopTriggeredJoinpoint_object *temp = NULL;
        temp = (aopTriggeredJoinpoint_object *)Z_OBJVAL((zval)(pc->object));
      //  exec (temp, NULL TSRMLS_CC);
    }
    if (!EG(exception)) {
        return zret_ptr;
    }
}

static zval *get_current_args (zend_op_array *ops TSRMLS_DC) {
    void **p;
    int arg_count;
    int i;
    zval *return_value;
    MAKE_STD_ZVAL(return_value);
    array_init(return_value);
    zend_execute_data *ex = EG(current_execute_data);
    if (!ex || !ex->function_state.arguments) {
        zend_error(E_WARNING, "Problem in AOP getArgs");
        return;
    }

    p = ex->function_state.arguments;
    arg_count = (int)(zend_uintptr_t) *p;

    for (i=0; i<arg_count; i++) {
        zval *element;

        ALLOC_ZVAL(element);
        *element = **((zval **) (p-(arg_count-i)));
        zval_copy_ctor(element);
        INIT_PZVAL(element);
        zend_hash_next_index_insert(return_value->value.ht, &element, sizeof(zval *), NULL);
    }
    return return_value;

}

zval *exec(aopTriggeredJoinpoint_object *obj, zval *args TSRMLS_DC) {
    if (args!=NULL) {
        obj->argsOverload=1;
        obj->args = args;
    }
    if (obj->joinpoint==NULL) {
        zend_execute_data *prev_data;
        zval **original_return_value;
        zend_op **original_opline_ptr;
        zend_op_array *prev_op;
        HashTable *calling_symbol_table;
        zval *prev_this;
        zend_class_entry *current_scope;


        //Save previous context
        prev_op = EG(active_op_array);
        prev_data = EG(current_execute_data);
        original_opline_ptr = EG(opline_ptr);
        calling_symbol_table = EG(active_symbol_table);
        current_scope = EG(scope);

        prev_this = EG(This);

        EG(active_op_array) = (zend_op_array *) obj->op;
        EG(current_execute_data) = obj->ex;
        EG(This) = obj->this;
        EG(scope) = obj->scope;
        if (obj->argsOverload) {
            int i,arg_count;
            zend_execute_data *ex = EG(current_execute_data);
            arg_count = (int)(zend_uintptr_t) *(ex->function_state.arguments);
            HashPosition pos;
            i=0;
            zval ** temp=NULL;
            zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(obj->args), &pos);

            while (zend_hash_get_current_data_ex(Z_ARRVAL_P(obj->args), (void **)&temp, &pos)==SUCCESS) {
                i++;
                zend_vm_stack_push_nocheck(*temp TSRMLS_CC);
                zend_hash_move_forward_ex(Z_ARRVAL_P(obj->args), &pos);
            }
            ex->function_state.arguments = zend_vm_stack_top(TSRMLS_C);
            zend_vm_stack_push_nocheck((void*)(zend_uintptr_t)i TSRMLS_CC);
        }

        aop_g(overloaded)=0;
        _zend_execute(EG(active_op_array) TSRMLS_CC);
        aop_g(overloaded)=1;

        //Take previous context
        EG(This) = prev_this;
        EG(opline_ptr) = original_opline_ptr;
        EG(active_op_array) = (zend_op_array *) prev_op;
        EG(current_execute_data) = prev_data;
        EG(active_symbol_table) = calling_symbol_table;
        EG(scope)=current_scope;
        //Only if we do not have exception
        if (!EG(exception)) {
            return (zval *)*EG(return_value_ptr_ptr);
        } else {


        }

    } else {
        zval *exec_return;
        if (obj->argsOverload) {
            aopTriggeredJoinpoint_object *objN = (aopTriggeredJoinpoint_object *)zend_object_store_get_object(obj->joinpoint->object TSRMLS_CC);
            objN->argsOverload=1;
            objN->args = obj->args;
            zval_copy_ctor(objN->args);
        }
        exec_return = joinpoint_execute(obj->joinpoint);

        //Only if we do not have exception
        if (!EG(exception)) {
            return exec_return;
        }
    }

    return NULL;

}

int strcmp_with_joker (char *str_with_jok, char *str) {
    php_strtolower(str, strlen(str));
    if (!strcmp(str_with_jok,"*")) {
        return 1;
    }

    int i;
    int joker=0;
    if (str_with_jok[strlen(str_with_jok)-1]=='*') {
        return !strcmp(estrndup(str_with_jok,strlen(str_with_jok)-2),estrndup(str,strlen(str_with_jok)-2));
    }
    if (str_with_jok[0]=='*') {
        if (strlen(str)>strlen(str_with_jok)-1) {
            return !strcmp(estrdup(str_with_jok+1),estrdup(str+(strlen(str)-(strlen(str_with_jok)-1))));
        } else {
            return 0;
        }
    }
    return !strcmp(str_with_jok,str);
}

int compare_class_struct (class_struct *selector, class_struct *class) {
    if (selector->static_state!=2 && selector->static_state!=class->static_state) {
        return 0;
    }
    if (selector->scope != NULL && !(selector->scope & class->scope)) {
        return 0;
    }
    if (selector->class_name==NULL && !strcmp(selector->method,"*")) {
        return 1;
    }
    if (!strcmp_with_joker(selector->method, class->method)) {
        return 0;
    }
    if (selector->class_name==NULL && class->class_name==NULL) {
        return 1;
    }
    if ((selector->class_name==NULL || class->class_name==NULL) && selector->class_name!=class->class_name) {
        return 0;
    }

        return 0;
}

int compare_namespace (int numns1, char **ns_with_jok, int numns2,  char **ns) {
    if (numns1==0 && numns2>0) {
        return 0;
    }
    if (numns1==0 && numns2==0) {
        return 1;
    }
    if (numns1>numns2) {
        return 0;
    }
    if (numns2>numns1 && strcmp(ns_with_jok[numns1-1],"**")) {
        return 0;
    }
    int i;
    for (i=0;i<numns1;i++) {
        if (!strcmp_with_joker(ns_with_jok[i],ns[i])) {
            return 0;
        }
    }
    return 1;
}
*/
int get_ns(char *class, char ***ns) {
    int nb;
    nb = get_ns_without_class(class,ns);
    if (nb==1) {
        (*ns)=NULL;
    }
    
    return --nb;
}

int get_ns_without_class(char *class, char ***ns) {
    int i;
    int nb = 0;
    int last = 0;
    for (i=0;i<strlen(class);i++) {
        if (class[i]=='\\') {
            nb++;
            if (nb==1) {
                (*ns) = emalloc(sizeof(char *));
            } else {
                (*ns) = erealloc((*ns),nb*sizeof(char *));
            }
            (*ns)[nb-1] = estrndup(class+last,i-last);
            php_strtolower((*ns)[nb-1], strlen((*ns)[nb-1]));
            last = i+1;
        }
    }
    nb++;
    if (nb==1) {
        (*ns) = emalloc(sizeof(char *));
    } else {
        (*ns) = erealloc((*ns),nb*sizeof(char *));
    }
    (*ns)[nb-1] = estrndup(class+last,i-last);
    return nb;

}



int is_static (char *str) {
    int i=0;
    char *partial = NULL;
    int last = 0;
    while (i<strlen(str)) {
        if (str[i]==' ') {
            partial = estrndup(str+last,i-last);
            if (!strcmp(partial, "static")) {
                return 1;
            }
            if (!strcmp(partial, "!static")) {
                return 0;
            }
            last = i+1;
        }
        i++;
    }
    return 2;

}

int explode_scope_by_pipe (char *partial) {
     int i = 0;
     int last = 0;
     int toReturn = NULL;
        while (i<strlen(partial)) {
            if (partial[i]=='|') {
                if (!strcmp(estrndup(partial+last,i-last), "public")) {
                    toReturn = toReturn | ZEND_ACC_PUBLIC;
                }
                if (!strcmp(estrndup(partial+last,i-last), "private")) {
                    toReturn = toReturn | ZEND_ACC_PRIVATE;
                }
                if (!strcmp(estrndup(partial+last,i-last), "protected")) {
                    toReturn = toReturn | ZEND_ACC_PROTECTED;
                }
               last = i+1; 
            }
            i++;
        }
        if (!strcmp(estrdup(partial+last), "public")) {
            toReturn = toReturn | ZEND_ACC_PUBLIC;
        }
        if (!strcmp(estrdup(partial+last), "private")) {
            toReturn = toReturn | ZEND_ACC_PRIVATE;
        }
        if (!strcmp(estrdup(partial+last), "protected")) {
            toReturn = toReturn | ZEND_ACC_PROTECTED;
        }
    return toReturn;
}

int get_scope (char *str) {
    int i=0;
    int toReturn = NULL;
    char *partial = NULL;
    int last = 0;
    while (i<strlen(str)) {
        if (str[i]==' ') {
            partial = estrndup(str,i);
            int temp_return = explode_scope_by_pipe(partial);
            if (temp_return!=NULL) {
                toReturn |= explode_scope_by_pipe(partial);
            }
            last = i;
        }
        i++;
    }
    return toReturn;
}

char* get_class_part (char *str) {
    int i=0;
    int last_space = 0;
    while (i<strlen(str)) {
        if (str[i]==' ') {
            last_space = i+1;
        }
        i++;
    }
    str = str+last_space;
    char *endp;
    char *class_end;
    endp=str+strlen(str);
    class_end = php_memnstr(str, "::", 2, endp);
    if (class_end!=NULL) {
        return estrndup(str, strlen(str)-strlen(class_end));
    }
    
    return NULL;

}

char * get_method_part (char *str) {

    char *endp;
    endp=str+strlen(str);
    return (php_memnstr(str, "::", 2, endp)+2);
}

joinpoint *get_joinpoint_from_ce(zend_class_entry *ce) {

}

joinpoint *get_current_joinpoint() {
    joinpoint *cs = emalloc (sizeof(joinpoint));
    cs->static_state = NULL;
    cs->method=NULL;
    cs->class_name = NULL;
    cs->ce = NULL;

    zend_execute_data *data;
    zend_function      *curr_func;

    data = EG(current_execute_data);

    if (data) {
        curr_func = data->function_state.function;
        if (curr_func->common.function_name==NULL) {
            return NULL;
        }
        cs->method = estrdup (curr_func->common.function_name);
        php_strtolower(cs->method, strlen(cs->method));
        cs->scope = curr_func->common.fn_flags;
        cs->static_state = (curr_func->common.fn_flags & ZEND_ACC_STATIC);
        if (cs->method) {
            if (cs->static_state) {
                cs->ce = curr_func->common.scope;
                cs->class_name = cs->ce->name;
            } else if (data->object) {
                cs->ce = Z_OBJCE(*data->object);
                cs->class_name = estrdup (Z_OBJCE(*data->object)->name);
            }
            if (cs->class_name!=NULL) {
                php_strtolower(cs->class_name, strlen(cs->class_name));
            }
            if (cs->ce!=NULL) {
                cs->num_ns = get_ns(cs->ce->name, &(cs->ns));
                if (cs->num_ns>0) {
                    cs->class_name = get_class_part_with_ns(cs->class_name);
                }

            zend_class_entry *ce = cs->ce;
            char **ns;
            ns = cs->ns;
            int num_ns = cs->num_ns;
            while (ce!=NULL) {
                if (strcmp_with_joker(selector->class_name, get_class_part_with_ns(ce->name)) && compare_namespace(selector->num_ns, selector->ns, num_ns, ns)) {
                    return 1;
                }
                ce = ce->parent;
         if (ce!=NULL) {
    //        num_ns = get_ns(ce->name, &ns);
         }
    }
    zend_uint i;
    for (i=0; i<(class->ce)->num_interfaces; i++) {
        if (strcmp_with_joker(selector->class_name, (class->ce)->interfaces[i]->name)) {
            return 1;
        }
    }
    #if ZEND_MODULE_API_NO >= 20100525
    //Traits
    for (i=0; i<(class->ce)->num_traits; i++) {
        if (strcmp_with_joker(selector->class_name, (class->ce)->traits[i]->name)) {
            return 1;
        }
    }
    #endif




                
            }
        }
    }
    return cs; 
}

char *get_class_part_with_ns(char *class) {
    int i = strlen(class)-1;
    char *toReturn;
    while (i>=0 && class[i]!='\\') {
        i--;
    }
    if (i<0) {
        toReturn = estrdup(class);
    } else {
        toReturn = estrdup(class+i+1);
    }
    php_strtolower (toReturn, strlen(toReturn));
    return toReturn;
}

