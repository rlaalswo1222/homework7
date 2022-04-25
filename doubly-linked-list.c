/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("[----- [김민재] [2021041070] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode); // 연결리스트 생성
			break;
		case 'p': case 'P':
			printList(headnode); // 노드 출력 
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); // 노드 입력
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); // 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); // 노드 맨뒤에 추가 
			break;
		case 'e': case 'E':
			deleteLast(headnode); //노드 맨뒤 삭제 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); // 노드 맨앞 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode); // 노드 맨앞 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); // 노드 역순
			break;
		case 'q': case 'Q':
			freeList(headnode); // 노드 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 그외
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) { //주소를 저장하는 포인터의 주소를 받기 위해서이다. 때문에 initialize에서 head를 수정하려면 이중포인터가 필요.
// 나머지는 head를 수정하지 않으므로 이중포인터로 넘기지 않아도 무방

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode)); //헤드노드를 생성
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) { //노드의 마지막까지 이동
		prev = p; // 이전 노드
		p = p->rlink; //다음노드로 이동
		free(prev); // 이전노드 삭제
	}
	free(h); //헤드노드 삭제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //노드가 없다면
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; 

	while(p != NULL) { // 노드의 마지막까지 이동
		printf("[ [%d]=%d ] ", i, p->key); //노드 출력
		p = p->rlink; // 다음 노드로 이동
		i++; 
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 삽입할 노드 생성
	node->key = key; // 노드의 값을 입력값으로 설정
	node->rlink = NULL; // 다음노드 링크 null
	node->llink = NULL; // 이전노드 링크 null

	if (h->first == NULL) // 노드가 비어있다면
	{
		h->first = node; // 첫자리에 노드를 삽입
		return 0;
	}

	listNode* n = h->first; 
	while(n->rlink != NULL) { // 노드의 마지막으로 이동
		n = n->rlink; // 다음 노드로 이동
	}
	n->rlink = node; // 마지막 노드의 다음 노드 링크는, 삽입할 노드를 가리킴
	node->llink = n; // 삽입할 노드의 이전 노드 링크는, 삽입하기 전 마지막이였던 노드를 가리킴
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //노드가 없다면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {
		h->first = NULL; // 헤드가 가리키는 곳 NULL
		free(n); // n을 삭제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {
		trail = n; // trail를 이전노드로 설정
		n = n->rlink; // 다음 노드로 이동
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL; //마지막 노드의 이전 노드의 다음노드를 가리키는 곳 NULL
	free(n); // 마지막 노드 삭제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //삽입할 노드 생성 
	node->key = key; // 노드의 값을 입력값으로 설정
	node->rlink = node->llink = NULL; // 노드의 이전,다음 노드 링크 null

	if(h->first == NULL) // 노드가 없다면
	{
		h->first = node; // 첫번째에 삽입
		return 1;
	}

	node->rlink = h->first; //삽입할 노드의 다음노드를 현재 헤드 노드로 지정
	node->llink = NULL; // 삽입할 노드가 맨 앞이므로 이전노드는 null

	listNode *p = h->first;
	p->llink = node; // 현재 헤드노드의 이전 노드를, 삽입할 노드로 지정
	h->first = node; // 첫번째에 삽입
 
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) // 노드가 없다면
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; 
	h->first = n->rlink; // 헤드의 다음 노드 주소를 삭제할 노드의 다음 주소로 저장

	free(n); // 노드 삭제 

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //노드가 없다면
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;
	//n이 현재, middle이 그뒤, tail이 그뒤를 가르키면서 값을 가지고 있게된다.
	while(n != NULL){
		trail = middle; //trail은 middle을 가리킴
		middle = n; // middle은 n을 가리킴 
		n = n->rlink; //다음노드로 이동
		middle->rlink = trail; //middle의 다음노드는 trail, 이전노드는 n을 가리킴
		middle->llink = n;
	}
	//끝나면 노드를 가리키는 방향이 역순으로 가리키게 됌
	h->first = middle; // 다 바뀌었으면 n은 Null이므로 그 다음 노드인 middle이 헤드노드가 된다.

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //삽입할 노드 생성
	node->key = key; // 노드의 값을 입력값으로 설정
	node->llink = node->rlink = NULL; //이전,다음 노드 null

	if (h->first == NULL) // 노드가 비어있다면
	{
		h->first = node; // 첫자리에 노드 삽입
		return 0;
	}

	listNode* n = h->first;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) { // 삽입될 값이 현재 노드의 값보다 작거나 같다면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { 
				insertFirst(h, key); // 첫자리에 노드 삽입
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //삽입할 노드의 다음 노드 링크는, '삽입됐을 시 자신의 뒤에 놓이게 될 노드'를 가리킴
				node->llink = n->llink; //삽입할 노드의 이전 노드 링크는, '삽입됐을 시 자신의 뒤에 놓이게 될 노드'를 가리킴
				n->llink->rlink = node; // '삽입됐을 시 자신의 앞에 놓이게 될 노드'의 다음 노드 링크는, 삽입될 노드를 가리킴
				
			} 
			return 0;
		}

		n = n->rlink;// 다음노드로 이동
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //노드가 비어있으면
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; // 삭제할 노드의 앞에 있는 노드의 다음 노드 링크는, 삭제할 노드의 뒤에 있는 노드를 가리킴
				n->rlink->llink = n->llink; // 삭제할 노드의 뒤에 있는 노드의 이전 노드 링크는, 삭제할 노드의 앞에 있는 노드를 가리킴
				free(n); // 앞,뒤 노드가 삭제할 노드를 건너뛰어 가리키므로 삭제 가능
			}
			return 1;
		}

		n = n->rlink; //다음노드로 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


