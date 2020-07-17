#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct _node {
	char name[20];			//이름
	char phonenum[13];		//전화번호
	char email[40];			//이메일 주소
	struct _node* next;	//다음 노드의 주소를 담아놀 포인터
}NODE;

//void start();					//파일안 내용을 불러오는 함수
void plus(NODE *);				//node추가.
void del(NODE *,NODE *);					//node 삭제.
NODE *find_plus(NODE*, NODE *);		//plus함수 내 함수. 중복여부 확인.
NODE* find_del(NODE*, NODE*);		//del함수 내 함수. 삭제하려는 노드의 이전노드 탐색용.
void formal(NODE *);					//node 내 data 변경.
//void end();						//파일에 값 저장.

int main()
{
	int input = 0;;										//명령어 입력
	NODE* hnode = (NODE*)malloc(sizeof(NODE));		//머리 노드 생성. 데이터 X
	hnode->next = NULL;

	printf("PIMS에 오신것을 환영합니다.\n 고객님의 개인정보를 보관합니다.\n ");
	printf("1 : 새로운 사람을 등록하거나 등록된 사람의 정보를 수정 및 삭제할 수 있습니다.\n");
	printf("2 : 이름을 한 글자 이상 입력하면 그 결과를 출력합니다\n");
	printf("3 : 개인정보들을 저장하고 프로그램을 종료합니다.\n");
	while (1) {
		printf("\n 명령어를 입력해주세요! >> ");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			plus(hnode);
			break;
		case 2:
			//find();
			break;
		case 3:
			//end();
			return 0;
			break;
		default:
			printf("잘못된 명령어 입니다\n");
			break;
		}
	}
	return 0;
}

void plus(NODE * target)		//node 추가
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	NODE *temp = (NODE*)malloc(sizeof(NODE));

	printf("이름을 입력해주세요 >> ");
	scanf("%s", temp->name);
	printf("전화번호을 입력해주세요 (-빼고)>> ");
	scanf("%s", temp->phonenum);
	
	NODE * found = find_plus(temp,target);			//중복여부를 파악하기 위해 탐색 함수 출력.
	if (found == NULL)		//이름과 전화번호가 같은 값이 없을 때 = 새로운 노드 추가하는 경우
	{
		printf("이메일주소를 입력해주세요 >> ");
		scanf("%s", temp->email);
		newNode->next = target->next;
		strcpy(newNode->name,temp->name);
		strcpy(newNode->phonenum ,temp->phonenum);
		strcpy(newNode->email, temp->email);
		target->next = newNode;
		printf("등록되었습니다!\n >> ");
	}
	else
	{
		int n;
		printf("이미 등록되어 있는 분이십니다.\n 수정을 원하시면 1, 삭제를 원하시면 2, 아무 작업도 하지 않으신다면 0을 입력해주세요 >> ");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			formal(found);
			break;
		case 2:
			del(found,target);
			break;
		default:
			break;
		}
	}

}
NODE *find_plus(NODE *data,NODE * node)		//탐색-중복의 경우 찾기
{
	if (node == NULL) {			//아무노드도 없는 경우
		return NULL;
	}
	NODE* tmp = node->next;	
	for (; tmp != NULL; tmp = tmp->next) {		//next가 NULL에 도달할 때까지 탐색.
		if (!strcmp(tmp->name ,data->name) && !strcmp(tmp->phonenum ,data->phonenum)) {			//만약 이름과 전화번호가 같은경우
			return tmp;
		}
	}
	return NULL;					//탐색하지 못한 경우
}
NODE* find_del(NODE* data, NODE* node)			//삭제하려는 노드의 이전노드를 찾기위한 탐색.
{
	if (node == NULL) {
		return NULL;
	}
	NODE* tmp = node->next;
	for (; tmp != NULL; tmp = tmp->next) {
		if (tmp->next == data) {							//next에 삭제하려는 노드의 주소가 담겨있는 노드 = 이전노드
			return tmp;
		}
	}
	return NULL;
}
void formal(NODE* data)									//값 수정.
{
	printf("이름 : ");
	scanf("%s", data->name);
	printf("전화번호 : ");
	scanf("%s", data->phonenum);
	printf("이메일 : ");
	scanf("%s", data->email);
}
void del(NODE* del,NODE *target)
{
	NODE *del_f =find_del(del, target);		//삭제하려는 노드의 이전노드 탐색
	printf("p\n");
	del_f->next = del->next;								//next = 가르키는 노드의 변경. 이전노드에 next에 삭제하려는 노드의 next값 넣어줌.
	printf("p\n");
	free(del);
	printf("삭제되었습니다\n");
}