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


typedef struct Node {  // 이중 연결 리스트를 만들기위해 왼쪽 링크 오른쪽 링크를 만든다.
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
int initialize(headNode** h); // 값을 바꿀때는 더블포인터로 매개변수를 받는다.

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
	headNode* headnode=NULL; //헤드노드를 초기화 해준다.
    printf("[----- [SIWON JOO] [2018038045] -----]");

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
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) // 노드를 초기화 해주고 노드의 메모리를 할당해주는 함수.
 {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h); // 할당된 메모리를 해제해주면서 초기화한다.

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode)); // 헤드노드 size 만큼 메모리를 할당한다.
	(*h)->first = NULL; //first 를 NULL값으로 초기화해준다.
	return 1;
}

int freeList(headNode* h) // 함수가 종료될때 연결되어있는 메모리를 해제하고 노드 전체 메모리를 해제해주는 함수
{
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; // 헤드노드의 값을 가진 리스트 노드 n 을 만든다.

	listNode* prev = NULL; // prev 라는 노드구조체를 만들어 NULL 값으로 초기화 시킨다.
	while(p != NULL) { // p 는 곧 h 와 같으므로 p값이 빌때까지 연결된 link 를 끊어준다.
		prev = p; // prev 에 p 주소를 담고
		p = p->rlink; // p 는 다음 노드로 옮긴다.
		free(prev); // prev 의 메모리가 해제가 되면 처음 노드의 link 가 끊기고 반복하면서 다음 노드로 이동하면서 메모리를 해제시킨다.
	}
	free(h); // 연결된 메모리를 전부 할당 해제했으면 헤드노드의 메모리를 할당 해제한다.
	return 0;
}


void printList(headNode* h) { // 노드의 list 를 출력하는 함수.
	int i = 0; // 인덱스를 표현하기 위해 정수형 변수 선언
	listNode* p; // 노드를 출력하기위해 리스트 노드 구조체 p 를 선언함

	printf("\n---PRINT\n");

	if(h == NULL) { // 헤드노드가 비어있다면 결국 아무런 값도 입력받지 않은 상태이므로 오류 메세지 출력
		printf("Nothing to print....\n");
		return; // 함수를 빠져나간다.
	}

	p = h->first; // p의 헤드노드의 값을 가져온다.

	while(p != NULL) { // 노드가 NULL 값이 될때까지 즉 마지막 노드까지 반복한다.
		printf("[ [%d]=%d ] ", i, p->key); // // 인덱스 값과 해당 인덱스의 노드 값 을 출력한다.
		p = p->rlink; // 노드를 오른쪽 즉 다음 노드로 옮긴다. 
		i++; // 인덱스 값 증가
	}
	printf("  items = %d\n", i); // 총 노드의 수 출력
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) { // 노드의 끝에 새로운 노드를 삽입하는 함수이다.

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드를 만들어 메모리를 할당한다.
	node->key = key; // 입력받은 키 값을 새로운 노드 키에 넣어준다.
	node->rlink = NULL; // 새로운 노드의 오른쪽 링크를 초기화해준다.
	node->llink = NULL; // 새로운 노드의 왼쪽 링크를 초기화해준다.

	if (h->first == NULL) // 헤드노드가 비어있다면
	{
		h->first = node; // 새로 만든 노드를 헤드노드로 바꿔준다.
		return 0; 
	}

	listNode* n = h->first; // 헤드노드의 값을 가진 리스트 노드 n 을 만든다.
	while(n->rlink != NULL) { // 노드를 한칸씩 옮기면서 NULL값 즉 n이 노드의 끝까지 갈때까지 반복한다.
		n = n->rlink; // 노드를 다음노드로 옮긴다. 
	}
	n->rlink = node; // 새로운 노드를 원래 있던 마지막 노드의 rlink 와 연결한다.
	node->llink = n; // 새로운 노드의 llink 를 원래의 마지막 노드와 연결한다.
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) { 

	if (h->first == NULL) // 헤드노드가 비어있다면 오류메세지 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; // 헤드노드의 값을 가진 리스트 노드 n 을 만든다.
	listNode* trail = NULL; // 이전노드의 주소를 갖게하기위한 구조체 trail 을 선언하고 NULL 값으로 초기화해준다.

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) { // n의 rlink 가 비어있다면 다음 노드가 없고 first node == last node이다. 
		h->first = NULL; // 바로 헤드 노드를 NULL값으로 초기화 해준다.
		free(n); //  n의 메모리를 할당 해제한다.
		return 0; // 함수를 빠져나온다.
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) { // 다음노드가 비어있을때까지 반복한다. 즉 마지막 노드까지 반복한다는 뜻
		trail = n; // 다음 노드로 옮길것이기 때문에 이전노드의 데이터를 trail 의 저장해준다. 
		n = n->rlink; // 다음노드로 옮긴다
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL; 
	free(n); // 구조체n의 메모리 할당을 해제해준다.

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 처음 위치에 삽입할 새로운 노드 구조체를 만들고 메모리를 할당해준다.
	node->key = key; // 입력받은 키 값을 노드의 키값에 넣어준다.
	node->rlink = node->llink = NULL; // 새로만든 노드의 오른쪽 왼쪽 링크를 NULL 값으로 초기화해준다.

	if(h->first == NULL) // 헤드 노드가 비어있다면 
	{ 
		h->first = node; // 새로운 노드를 헤드노드로 바꿔준다.
		return 1; 
	}

	node->rlink = h->first; // 헤드노드를 새로 삽입할 노드의 rlink로 바꿔준다.
	node->llink = NULL; // 리스트 처음에 삽입했기 떄문에 llink는 NULL 값으로 초기화 해준다.

	listNode *p = h->first;// 헤드노드의 값을 가진 리스트 노드 n 을 만든다.
	p->llink = node; // 헤드 노드가 위에서 바꼈기 떄문에 p의 llink가 노드를 가르키면서 이중연결 리스트 형태로 바꿔준다. 
	h->first = node; // 새로 삽입한 노드를 헤드 노드로 바꿔준다.

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) { // 첫번째 노드 삭제하는 함수

	if (h->first == NULL) // 헤드노드가 비어있다면 오류메세지 출력.
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; // 헤드노드의 값을 가진 리스트 노드 n 을 만든다.
	h->first = n->rlink; // 다음 칸에 노드를 헤드노드로 바꿔준다.

	free(n); // 이전의 헤드노드의 메모리 할당을 해제해준다.

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {  

	if(h->first == NULL) { // 헤드노드가 비어있다면 오류메세지 출력한다.
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; // // 헤드노드의 값을 가진 리스트 노드 n 을 만든다. (실제로는 구조체 선언이 먼저고 h->first 대입은 그 다음에 일어난다.)
	listNode *trail = NULL; // 이전 노드를 가르키는 trail 구조체를 선언한 후 NULL값으로 초기화 해준다.
	listNode *middle = NULL; // 중간 노드를 가르키는 middle 구조체를 선언한 후 NULL 값으로 초기화 해준다.

	while(n != NULL){ // 노드가 빌때 까지 즉 마지막 노드에 도달할때까지 반복한다.
		trail = middle; // 
		middle = n; // n의 데이터를 middle에 넣어준다
		n = n->rlink; // 다음 노드로 한칸 이동한다.
		middle->rlink = trail; // middle 의 오른쪽 링크는 원래 다음 노드를 가르켜야하는데 역순으로 바꿔주어야 하기 떄문에 반대로 이전 노드인 trail을 가르킨다. 
		middle->llink = n; //llink 는 이전노드가 아닌 다음 노드를 가르킨다.
	}

	h->first = middle; // 노드를 끝까지 돌면 middle 이 마지막 노드를 가르키는데 역순이기때문에 마지막이 헤드노드가 되어서 헤드노드를 middle로 바꿔준다.

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 삽입할 노드를 새로 만들어 메모리를 할당해준다.
	node->key = key; // 입력받은 키값을 새로 만든 노드의 키 값에 넣어준다.
	node->llink = node->rlink = NULL; // 노드의 왼쪽 오른쪽 링크를 NULL 값으로 초기화 시킨다.

	if (h->first == NULL) // 만약 헤드노드가 비어있다면
	{
		h->first = node; // 헤드노드에 새로삽입할 노드를 넣어준다.
		return 0;
	}

	listNode* n = h->first; // 헤드노드의 값을 가진 리스트 노드 n 을 만든다.

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { // n 이 NULL 값일떄까지 반복한다.
		if(n->key >= key) {  // 입력받은 key 값이 노드에 있는 key 값보다 작거나 같을때
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { 
				insertFirst(h, key); // 키값을 가진 노드를 첫노드 앞쪽에 삽입한다.
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; // 삽입할 노드의 오른쪽 링크에 n 을 대입한다.
				node->llink = n->llink; // 삽입할 노드의 왼쪽 링크에 n 의 왼쪽링크를 넣는다.
				n->llink->rlink = node; // n의 왼쪽링크의 오른쪽 링크 에 node 를 넣는다.
			}
			return 0;
		}

		n = n->rlink; // n 을 다음 칸으로 이동한다.
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) // 헤드노드가 비어있다면 오류 메세지 출력
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first; // 헤드노드의 값을 가진 리스트 노드 n 을 만든다.

	while(n != NULL) {  // n 이 NULL 값일떄까지 반복한다.
		if(n->key == key) { // 입력받은 key 값이 노드에 있는 key 값보다 작거나 같을때
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); // 첫번째 노드 삭제하는 함수 호출
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h); // 마지막 노드 삭제하는 함수 호출
			} else { /* 중간인 경우 */
			// 삭제해야 하기때문에 n 의 오른쪽 링크와 왼쪽 링크를 끊어준다.
				n->llink->rlink = n->rlink;
 				n->rlink->llink = n->llink; 
				free(n); // n의 메모리를 할당 해제한다.
			}
			return 1; 
		}

		n = n->rlink; // 노드를 오른쪽으로 한칸 이동한다.
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


