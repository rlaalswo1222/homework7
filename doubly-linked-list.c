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
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         lab3�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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
	printf("[----- [�����] [2021041070] -----]\n");
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
			initialize(&headnode); // ���Ḯ��Ʈ ����
			break;
		case 'p': case 'P':
			printList(headnode); // ��� ��� 
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); // ��� �Է�
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); // ��� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); // ��� �ǵڿ� �߰� 
			break;
		case 'e': case 'E':
			deleteLast(headnode); //��� �ǵ� ���� 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); // ��� �Ǿ� ����
			break;
		case 't': case 'T':
			deleteFirst(headnode); // ��� �Ǿ� ����
			break;
		case 'r': case 'R':
			invertList(headnode); // ��� ����
			break;
		case 'q': case 'Q':
			freeList(headnode); // ��� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // �׿�
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) { //�ּҸ� �����ϴ� �������� �ּҸ� �ޱ� ���ؼ��̴�. ������ initialize���� head�� �����Ϸ��� ���������Ͱ� �ʿ�.
// �������� head�� �������� �����Ƿ� ���������ͷ� �ѱ��� �ʾƵ� ����

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode)); //����带 ����
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) { //����� ���������� �̵�
		prev = p; // ���� ���
		p = p->rlink; //�������� �̵�
		free(prev); // ������� ����
	}
	free(h); //����� ����
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //��尡 ���ٸ�
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; 

	while(p != NULL) { // ����� ���������� �̵�
		printf("[ [%d]=%d ] ", i, p->key); //��� ���
		p = p->rlink; // ���� ���� �̵�
		i++; 
	}

	printf("  items = %d\n", i);
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // ������ ��� ����
	node->key = key; // ����� ���� �Է°����� ����
	node->rlink = NULL; // ������� ��ũ null
	node->llink = NULL; // ������� ��ũ null

	if (h->first == NULL) // ��尡 ����ִٸ�
	{
		h->first = node; // ù�ڸ��� ��带 ����
		return 0;
	}

	listNode* n = h->first; 
	while(n->rlink != NULL) { // ����� ���������� �̵�
		n = n->rlink; // ���� ���� �̵�
	}
	n->rlink = node; // ������ ����� ���� ��� ��ũ��, ������ ��带 ����Ŵ
	node->llink = n; // ������ ����� ���� ��� ��ũ��, �����ϱ� �� �������̿��� ��带 ����Ŵ
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //��尡 ���ٸ�
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->rlink == NULL) {
		h->first = NULL; // ��尡 ����Ű�� �� NULL
		free(n); // n�� ����
		return 0;
	}

	/* ������ ������ �̵� */
	while(n->rlink != NULL) {
		trail = n; // trail�� �������� ����
		n = n->rlink; // ���� ���� �̵�
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->rlink = NULL; //������ ����� ���� ����� ������带 ����Ű�� �� NULL
	free(n); // ������ ��� ����

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //������ ��� ���� 
	node->key = key; // ����� ���� �Է°����� ����
	node->rlink = node->llink = NULL; // ����� ����,���� ��� ��ũ null

	if(h->first == NULL) // ��尡 ���ٸ�
	{
		h->first = node; // ù��°�� ����
		return 1;
	}

	node->rlink = h->first; //������ ����� ������带 ���� ��� ���� ����
	node->llink = NULL; // ������ ��尡 �� ���̹Ƿ� �������� null

	listNode *p = h->first;
	p->llink = node; // ���� ������� ���� ��带, ������ ���� ����
	h->first = node; // ù��°�� ����
 
	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) // ��尡 ���ٸ�
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; 
	h->first = n->rlink; // ����� ���� ��� �ּҸ� ������ ����� ���� �ּҷ� ����

	free(n); // ��� ���� 

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //��尡 ���ٸ�
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;
	//n�� ����, middle�� �׵�, tail�� �׵ڸ� ����Ű�鼭 ���� ������ �ְԵȴ�.
	while(n != NULL){
		trail = middle; //trail�� middle�� ����Ŵ
		middle = n; // middle�� n�� ����Ŵ 
		n = n->rlink; //�������� �̵�
		middle->rlink = trail; //middle�� �������� trail, �������� n�� ����Ŵ
		middle->llink = n;
	}
	//������ ��带 ����Ű�� ������ �������� ����Ű�� ��
	h->first = middle; // �� �ٲ������ n�� Null�̹Ƿ� �� ���� ����� middle�� ����尡 �ȴ�.

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //������ ��� ����
	node->key = key; // ����� ���� �Է°����� ����
	node->llink = node->rlink = NULL; //����,���� ��� null

	if (h->first == NULL) // ��尡 ����ִٸ�
	{
		h->first = node; // ù�ڸ��� ��� ����
		return 0;
	}

	listNode* n = h->first;

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key >= key) { // ���Ե� ���� ���� ����� ������ �۰ų� ���ٸ�
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) { 
				insertFirst(h, key); // ù�ڸ��� ��� ����
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n; //������ ����� ���� ��� ��ũ��, '���Ե��� �� �ڽ��� �ڿ� ���̰� �� ���'�� ����Ŵ
				node->llink = n->llink; //������ ����� ���� ��� ��ũ��, '���Ե��� �� �ڽ��� �ڿ� ���̰� �� ���'�� ����Ŵ
				n->llink->rlink = node; // '���Ե��� �� �ڽ��� �տ� ���̰� �� ���'�� ���� ��� ��ũ��, ���Ե� ��带 ����Ŵ
				
			} 
			return 0;
		}

		n = n->rlink;// �������� �̵�
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //��尡 ���������
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);
			} else if (n->rlink == NULL){ /* ������ ����� ��� */
				deleteLast(h);
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink; // ������ ����� �տ� �ִ� ����� ���� ��� ��ũ��, ������ ����� �ڿ� �ִ� ��带 ����Ŵ
				n->rlink->llink = n->llink; // ������ ����� �ڿ� �ִ� ����� ���� ��� ��ũ��, ������ ����� �տ� �ִ� ��带 ����Ŵ
				free(n); // ��,�� ��尡 ������ ��带 �ǳʶپ� ����Ű�Ƿ� ���� ����
			}
			return 1;
		}

		n = n->rlink; //�������� �̵�
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


