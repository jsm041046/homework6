/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

typedef struct Node { //��� ����ü ����
	int key;
	struct Node* link;
} listNode;

typedef struct Head { //����� �� ���κ��� ����Ű�� ��� ����
	struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h); //���� ����Ʈ�� �� �պκ��� �ʱ�ȭ
int freeList(headNode* h); //���� ����Ʈ�� �޸� �Ҵ��� ����

int insertFirst(headNode* h, int key); //���� ����Ʈ�� ù��°�� key�� ������
int insertNode(headNode* h, int key); //���� ����Ʈ�� �߰��� key�� ������
int insertLast(headNode* h, int key); //���� ����Ʈ�� �� �ڿ� key�� ������

int deleteFirst(headNode* h); //���� ����Ʈ�� ù��° ���Ҹ� ������
int deleteNode(headNode* h, int key); //���� ����Ʈ�� key���Ҹ� ������
int deleteLast(headNode* h); //���� ����Ʈ�� �������� ��ġ�� ���Ҹ� ������
int invertList(headNode* h); //���� ����Ʈ�� ������ ������ �ٲ�

void printList(headNode* h); //���� ����Ʈ�� ���

int main()
{
	char command; //����� ���� ���ں��� ����
	int key; //�ӽ÷� ���Ұ��� ������ ����
	headNode* headnode=NULL; //���� ����Ʈ�� �� ���� ����ų ����
    printf("[----- 2021041046 ������ -----]\n"); //�й�, �̸� ���
	do{ //�ݺ���
		printf("----------------------------------------------------------------\n"); //�ȳ�
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //��ɾ� �Է� ����

		switch(command) { //�Էµ� ��ɾ ���� �б�
		case 'z': case 'Z':
			headnode = initialize(headnode); //���� ����Ʈ �ʱ�ȭ
			break;
		case 'p': case 'P':
			printList(headnode); //���� ����Ʈ ���
			break;
		case 'i': case 'I':
			printf("Your Key = "); 
			scanf("%d", &key); //���Ұ� �Է�
			insertNode(headnode, key);//���� ����Ʈ �߰��� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); //���Ұ� �Է�
			deleteNode(headnode, key); //���� ����Ʈ���� ���ϴ� ���� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); //���Ұ� �Է�
			insertLast(headnode, key); //���� ����Ʈ�� �������� ���� �Է�
			break;
		case 'e': case 'E':
			deleteLast(headnode); //���� ����Ʈ�� �������� ���� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); //���Ұ� �Է�
			insertFirst(headnode, key); //���� ����Ʈ�� ù��°�� ���� ����
			break;
		case 't': case 'T':
			deleteFirst(headnode); //���� ����Ʈ�� ù��°�� ���� ����
			break;
		case 'r': case 'R':
			invertList(headnode); //���� ����Ʈ�� ������ ������ ��ȯ
			break;
		case 'q': case 'Q':
			freeList(headnode); //���� ����Ʈ�� �޸� �Ҵ� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //�Է¿� Q ���� ������ ������ ��������

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;

    //�ӽ÷� prev�����͸� ���� �� �ΰ��� �����͸� �̿��� p�� ���� ��ũ�� �����ϰ� prev�� ������ ������ �޸𸮸� �����ϴ� ���� p�� ���� ����Ű�� ���� �� ���� �ݺ���
	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
    //������ ���ԵǴ� ���Ҹ� ����
	free(h);
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
    //�ӽ÷� ���� �ִ� node���� ���� �� �Ҵ��ϰ�, ���Ұ��� ������
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
    //�Ҵ�� ��带 ����� ��ũ�� �����ϰ�, ����� ��ũ�� �ش� ��忡 ������
	node->link = h->first;
	h->first = node;

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
    //�ӽ÷� ���� �ִ� node���� ���� �� �Ҵ��ϰ�, ���Ұ��� ������
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
    //���� ���� ������ ����Ű�� p�����ͺ����� ����, NULL�� ����Ű�� prev�����ͺ��� ����
    listNode* p = h->first;
    listNode* prev = NULL;
    while (p != NULL && p->key <= node->key) //p�� NULL�� �����ų� p�� ���Ұ��� node���� Ŀ�� �� ���� �ݺ�
    {
        prev = p;
        p = p->link; //prev���� p�� ���ϰ� �ϰ�, p�� ���� ��ġ�� �̵���Ŵ
    } 
    if(prev != NULL) //��ġ�� �� ���� �ƴ� ���
    {
        //������ ��ġ�� ���� �߰�
        node->link = prev->link;
        prev->link = node;
    } else {
        node->link = h->first;
        h->first = node;
    }
    

	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
    //�ӽ÷� ���� �ִ� node���� ���� �� �Ҵ��ϰ�, ���Ұ��� ������
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
    //���� ���� ������ ����Ű�� p�����ͺ����� ����
    listNode* p = h->first;
    listNode* prev = NULL;
    while (p != NULL) //p�� NULL�� ���� �� ���� �ݺ�
    {
        prev = p;
        p = p->link; //prev���� p�� ���ϰ� �ϰ�, p�� ���� ��ġ�� �̵���Ŵ
    } 
    if(prev != NULL) //��ġ�� �� ���� �ƴ� ���
    {
        //������ ��ġ�� ���� �߰�
        node->link = prev->link;
        prev->link = node;
    } else {
        node->link = h->first;
        h->first = node;
    }

	return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
    //�ӽ� ������ p����
    listNode* p = h->first;
    if(h->first != NULL) //���� ����Ʈ�� ��尡 ������ ���(��尡 �ִ� = ���� ����Ʈ�� ���� �����Ѵ�)
    {
        h->first = h->first->link; //�� �� ���Ҹ� ���� ���ҷ� ����
        free(p); //������ �� �� ���Ҵ� �Ҵ� ����
    }
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
    //���� ���� ������ ����Ű�� p�����ͺ����� ����, NULL�� ����Ű�� prev�����ͺ��� ����
    listNode* p = h->first;
    listNode* prev = NULL;
    while (p != NULL && p->key != key) //p�� NULL�� �����ų� p�� ���Ұ��� key�� ������ �� ���� �ݺ�
    {
        prev = p;
        p = p->link; //prev���� p�� ���ϰ� �ϰ�, p�� ���� ��ġ�� �̵���Ŵ
    } 
    if(p ==  NULL)
    {
        printf("List don't have that element!\n"); //�ش� ���Ұ� ������ �ȳ�
        return -1; //������ ���� ����
    }
    if(prev != NULL) //���� ���Ұ� ���� ���
    //���� ������ ��ũ�� ���� ���ҷ� �ΰ�����
        prev->link = p->link;
    else
        h->first = p->link; //ù��° ��ũ�� ���� ���ҷ� �ΰ�����
    free(p); //���� p�� �޸� �Ҵ� ����
	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
    //���� ���� ������ ����Ű�� p�����ͺ����� ����, NULL�� ����Ű�� prev�����ͺ��� ����
    listNode* p = h->first;
    listNode* prev = NULL;
    while (p->link != NULL) //p�� ���� ���Ұ� NULL�� ���� �� ���� �ݺ�
    {
        prev = p;
        p = p->link; //prev���� p�� ���ϰ� �ϰ�, p�� ���� ��ġ�� �̵���Ŵ
    } 
    if(p != NULL) //���� p�� ������ ���
    {
        prev->link = NULL; //������ ������ ��ũ�� ����
        free(p); //���� p�� �޸� �Ҵ� ����
    }
	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
    //���� ���� ������ ����Ű�� p�����ͺ����� ����, NULL�� ����Ű�� prev�����ͺ��� ����
    listNode* p = h->first;
    listNode* prev = NULL;
    listNode* temp;
    while (p != NULL) //p�� NULL�� ���� �� ���� �ݺ�
    {
        temp = p->link; //p�� ��ũ�� �ӽ� ����
        p->link = prev; //p�� ��ũ�� �ݴ�������� ����
        prev = p;
        p = temp; //prev���� p�� ���ϰ� �ϰ�, p�� ���� ��ġ�� �̵���Ŵ
    } 
    h->first = prev; //������ �� ���� �� ������ ������
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

