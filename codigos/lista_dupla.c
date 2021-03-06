#include <stdio.h>
#include <stdlib.h>

typedef struct list{
	int data;
	struct list *next;
	struct list *prev;
} List;

List* create_list(){
	return NULL;
}



List* insert(List *list, int data){
	if (list==NULL){
		List *new_block = (List*) malloc(sizeof(List));
		new_block->data = data;
		new_block->prev = (List*) NULL; //o ponteiro do novo bloco esta apontando para o NULL que estava na lista
		new_block->next = (List*) NULL;
		list = new_block;
	} else {
		List *aux;
		List *new_block = (List*) malloc(sizeof(List));
		new_block->data = data;
		for (aux=list; aux->next!=NULL; aux=aux->next);
		new_block->prev = aux;
		new_block->next = (List*) NULL;
		aux->next = new_block;
	}

	return list;
}

void print_list(List *list){
	List *aux;
	List *aux2;
	for (aux=list; aux!=NULL; aux=aux->next){
		printf(" %d -> ", aux->data);
		aux2=aux;
	}
	printf("\n");
}

void print_list_reverse(List *list){
	List *aux;
	for (aux=aux; aux!=NULL; aux=aux->prev){
		printf(" %d -> ", aux->data);
	}
	printf("\n");
}

//Return 0 if element not exists in list
//Return 1 if element does exist in list
int exists(List* list, int n){
	List *aux;
	for (aux=list; aux->next!=NULL; aux=aux->next){
		if (aux->data == n){
			return 1;
		}
	}
	return 0;
}

List* remove_from_list(List *list, int n){
	List *aux;
	for (aux=list; aux!=NULL; aux=aux->next){
		if (aux->data==n){
			if (aux->prev==NULL){
				aux->next->prev = NULL; //o aux->prev e igual a NULL
				list=aux->next;
				return list;
			} else if (aux->next==NULL){
				aux->prev->next = NULL;
				return list;
			} else {
				aux->prev->next=aux->next;
				aux->next->prev=aux->prev;
				return list;
			}
		}
	}
	return list;
}

List* insert_in_position(List *list, int info, int position){
	List *aux;
	int contador=0;
	for (aux=list; aux->next!=NULL; aux = aux->next){
		contador++;
		if (contador == position){
			printf("DEBUG\n");
			List *new_block = (List*) malloc(sizeof(List));
			if (aux->prev==NULL){
				new_block->prev=NULL;
				new_block->next=aux;
				aux->prev=new_block;
				new_block->data=info;
				list=new_block;
				return list;
			} else {
				new_block->data = info;
				aux->prev->next=new_block;
				new_block->prev=aux->prev;
				aux->prev=new_block;
				new_block->next=aux;
				return list;
			}
		}
	}
	contador++;
	if (position==contador+1){
		list=insert(list, info);
		return list;
	} else if(position>contador+1){
		return NULL;
	}
	return list;
}


List* bubble_sort(List *list){
	List *i, *j;
	int aux;
	for (i=list; i!=NULL; i=i->next){
		for (j=i; j!=NULL; j=j->next){
			if (j->data < i->data){
				aux=i->data;
				i->data=j->data;
				j->data=aux;
			}
		}
	}
	return list;
}


void insertion_sort(List *list){
	List *i, *j;
	for (i=list->next; i!=NULL; i=i->next){
		j=i->prev;
		List *keeper=i;
		while (j!=NULL && i->data < j->data){
			int aux=j->data;
			j->data=i->data;
			i->data=aux;
			i=i->prev;
			j=j->prev;
		}
		i=keeper;
	}

}

List* selection_sort(List *list){
	List *i, *j;
	for (j=list;j->next!=NULL; j=j->next){
		List *menor = j;
		i=j->next;
		while (i!=NULL) {
			if (i->data < menor->data) menor=i;
			i=i->next;
		}
		int x = j->data;
		j->data = menor->data;
		menor->data = x;
	}
	return list;
}

void gc(List *list){
	if (list->next!=NULL){
		gc(list->next);
	}
	free(list);

}

void gc_tco(List *list, List *prox){
	free(list);
	if (prox!=NULL){
		gc(prox, prox->next);
	}
}


int main() {
	List *list = create_list();
	list = insert(list, 5);
	list = insert(list, 4);
	list = insert(list, 3);
	list = insert(list, 2);
	list = insert(list, 1);
	print_list(list);
	selection_sort(list);
	print_list(list);
	gc_tco(list, list->next);
	print_list(list);

	return 0;
}
