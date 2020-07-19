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

FILE* fp;										//파일 포인터

void start(NODE *);							//파일안 내용을 불러오는 함수
void start_setnode(char *,NODE *);				//파일 안 내용을 node에 불러오는 함수.	
void plus(NODE *);							//node추가.
void del(NODE *,NODE *);					//node 삭제.
NODE *find_plus(NODE*, NODE *);		//plus함수 내 함수. 중복여부 확인.
NODE* find_del(NODE*, NODE*);		//del함수 내 함수. 삭제하려는 노드의 이전노드 탐색용.
void formal(NODE *);						//node 내 data 변경.
void find(NODE *);							//node 탐색. 이름 입력받음.
NODE * find_find(char*, NODE*);		//find함수 내 함수. 이름을 가지고 노드 탐색.
void end(NODE *);									//파일에 값 저장.

void start(NODE * target)
{
	fp = fopen("C:/Users/user/Desktop/database/database.txt", "rt");		//파일 쓰기/읽기 모드로 열기
	if (fp == NULL) {
		printf("ERROR\n");
		return ;
	}
	while (1) {
		char buf[256];														//문자열(한 사람의 개인정보)를 받아올 공간
		fgets(buf, sizeof(buf), fp);									//정보를 buf에 넣음.
		if (feof(fp))	break;											//만약 문자열에 끝에 도달 했다면 break
		if (!strcmp(buf, "\n"))	continue;							//\n자체를 문자열로 인식하는 버그때문에 예외 처리
		start_setnode(buf,target);									//함수 호출
	}
	fclose(fp);
}

void start_setnode(char * buf,NODE* node)
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));			//새로운 노드 생성
	
	char* ptr = strtok(buf, " ");										//공백을 기준으로 문자열 분리.
	
	newNode->next = node->next;									//새로운 노드의 다음 주소값을 현 노드의 다음 주소값으로 바꿈 = 노드 삽입
	strcpy(newNode->name, ptr);										//문자열(이름) 복사
	ptr = strtok(NULL, " ");											
	strcpy(newNode->phonenum, ptr);
	ptr = strtok(NULL, " ");
	strcpy(newNode->email, ptr);
	ptr = strtok(NULL, " ");
	node->next = newNode;												//전 노드의 next에 새로운 노드의 주소값 삽입
}

void end(NODE* node)
{
	fp = fopen("C:/Users/user/Desktop/database/database.txt", "w");		//파일 쓰기 모드로 열기
	NODE* target = node->next;																//현재 노드의 다음 노드 주소값 저장.
	NODE* temp = target;																		//다음노드 주소값 백업
	while (target != NULL) {
		temp = temp->next;																		//다음 노드의 next로 이동
		fprintf(fp, "%s ", target->name);													//이름,전화번호, 이메일을 파일에 기록
		fprintf(fp, "%s ", target->phonenum);
		fprintf(fp, "%s\n", target->email);
		free(target);																				//메모리 할당 해제
		target = temp;																			//다음 노드로 이동
	}
	fclose(fp);
}
int main()
{
	int input = 0;;													//명령어 입력
	NODE* hnode = (NODE*)malloc(sizeof(NODE));		//머리 노드 생성. 데이터 X
	hnode->next = NULL;
	start(hnode);

	printf("PIMS에 오신것을 환영합니다.\n 고객님의 개인정보를 보관합니다.\n");
	printf("1 : 새로운 사람을 등록하거나 등록된 사람의 정보를 수정 및 삭제할 수 있습니다.\n");
	printf("2 : 이름을 입력하면 그 결과를 출력합니다\n");
	printf("3 : 개인정보들을 저장하고 프로그램을 종료합니다.\n");
	while (1) {
		printf("\n명령어를 입력해주세요! >> ");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			plus(hnode);
			break;
		case 2:
			find(hnode);
			break;
		case 3:
			end(hnode);
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
		printf("등록되었습니다!\n");
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
	NODE* tmp = node;										//hnode부터 시작
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
	del_f->next = del->next;						//next = 가르키는 노드의 변경. 이전노드에 next에 삭제하려는 노드의 next값 넣어줌.
	free(del);											//노드 삭제!
	printf("삭제되었습니다\n");
}

void find(NODE* target)
{
	char name[10];
	printf("이름을 입력해수세요 >> ");
	scanf("%s", name);
	NODE * found = find_find(name, target);		//입력받은 이름으로 노드 탐색
	if (found == NULL) {									//노드 혹은 입력받은 이름이 노드에 없을 때
		printf("그런 이름이 없습니다!\n");
	}
	else {
		printf("이름 : %s\n전화번호 : %s\n이메일 : %s\n", found->name, found->phonenum, found->email);
	}
}
NODE * find_find(char* str, NODE* node)
{
	if (node == NULL) {			//아무노드도 없는 경우
		return NULL;
	}
	NODE* tmp = node->next;
	for (; tmp != NULL; tmp = tmp->next) {		//next가 NULL에 도달할 때까지 탐색.
		if (!strcmp(tmp->name,str)) {			//만약 이름이 같은경우
			return tmp;
		}
	}
	return NULL;
}