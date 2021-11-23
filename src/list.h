#ifndef list_h
#define list_h

#define Node_new(T)\
	typedef struct T##_Node{\
		T data;\
		struct T##_Node* next;\
		struct T##_Node* prev;\
	}T##_Node_t;

#define List_new(T)\
	typedef struct T##_List{\
		T##_Node_t* head;\
		T##_Node_t* tail;\
		size_t size;\
	}T##_List_t;

#define List_init(T)\
	T##_List_t T##_List_init(){\
		T##_List_t list;\
		list.head = NULL;\
		list.tail = NULL;\
		list.size = 0;\
		return list;\
	}
	
#define List_push(T)\
	void T##_List_push(T##_List_t* list, T data){\
		if(list->head == NULL){\
			list->head = (T##_Node_t*)calloc(1,sizeof(T##_Node_t));\
			list->head->data = data;\
			list->head->next = NULL;\
			list->head->prev = NULL;\
			list->tail = list->head;\
			list->size = 1;\
			return;\
		}\
		else{\
			list->tail->next = (T##_Node_t*)calloc(1, sizeof(T##_Node_t));\
			list->tail->next->data = data;\
			list->tail->next->next = NULL;\
			T##_Node_t* tmp = list->tail;\
			list->tail = list->tail->next;\
			list->tail->prev = tmp;\
		}\
	}

#define List_pop_last(T)\
	T T##_List_pop_last(T##_List_t* list){\
		T data = {NULL};\
		if(list->head == NULL) return data;\
		if(list->tail == list->head){\
			data = list->head->data;\
			T##_Node_t* tmp = list->head;\
			list->head = NULL;\
			list->tail = NULL;\
			free(tmp);\
			return data;\
		}\
		else{\
			data = list->tail->data;\
			T##_Node_t* tmp = list->tail;\
			list->tail = list->tail->prev;\
			list->tail->next = NULL;\
			free(tmp);\
			return data;\
		}\
	}

#define List_pop_first(T)\
	T T##_List_pop_first(T##_List_t* list){\
		T data = {NULL};\
		if(list->head == NULL) return data;\
		if(list->head == list->tail){\
			data = list->head->data;\
			T##_Node_t* tmp = list->head;\
			list->head = NULL;\
			list->tail = NULL;\
			free(tmp);\
			return data;\
		}\
		else{\
			data = list->head->data;\
			T##_Node_t* tmp = list->head;\
			list->head = list->head->next;\
			list->head->prev = NULL;\
			free(tmp);\
			return data;\
		}\
	}

#define List_remove(T)\
	void T##_List_remove(T##_List_t* list, int index){\
		if(list->head == NULL) return;\
		if(list->size < index) return;\
		int count = 0;\
		T##_Node_t* current = list->head;\
		while(count < index){\
			current = current->next;\
		}\
		T##_Node_t* tmp = current->prev;\
		tmp->next = current->next;\
		free(current);\
	}

#define List_top(T)\
	T T##_List_top(T##_List_t* list){\
		T data = {NULL};\
		if(list->head == NULL) return data;\
		data = list->tail->data;\
		return data;\
	}

#define List_bottom(T)\
	T T##_List_bottom(T##_List_t* list){\
		T data = {NULL};\
		if(list->head == NULL) return data;\
		data = list->head->data;\
		return data;\
	}

#define List_destroy(T)\
	void T##_List_destroy(T##_List_t* list){\
		if(list->head == NULL) return;\
		T##_Node_t* tmp;\
		while(list->head != NULL){\
			tmp = list->head;\
			list->head = list->head->next;\
			free(tmp);\
		}\
		list->head = NULL;\
		list->tail = NULL;\
	}

#define LIST_FUNCTIONS(T)\
	List_init(T) List_push(T) List_pop_last(T)\
	List_pop_first(T) List_top(T) List_bottom(T) List_destroy(T)

#define LIST_HEADER(T)\
	Node_new(T) List_new(T)\
	T##_List_t T##_List_init();\
	void T##_List_push(T##_List_t* list, T data);\
	T T##_List_pop_last(T##_List_t* list);\
	T T##_List_pop_first(T##_List_t* list);\
	T T##_List_remove(T##_List_t* list);\
	T T##_List_top(T##_List_t* list);\
	T T##_List_bottom(T##_List_t* list);\
	void T##_List_destroy(T##_List_t* list);

#endif