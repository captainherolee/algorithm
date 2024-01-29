#include <stdio.h>
#include <malloc.h>


#define NULL (0)

typedef struct ListNode {
    int data;
    struct ListNode* prev;
    struct ListNode* next;
};

ListNode* list_create(int data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));

    node->prev = NULL;
    node->next = NULL;

    node->data = data;

    return node;
}

ListNode* list_insert(ListNode* head, LinstNode* newNode) {
    ListNode* next = head->next;
    head->next = newNode;
    newNode->next = next;
    newNode->prev = head;
    if (next != NULL) {
        next->prev = newNode;
    }

    return newNode;
}

int list_erase(ListNode* head, int data)
{
	ListNode* it = head->next;
	int ret = 0;

	while (it != NULL)
	{
		if (it->data == data)
		{
			ListNode* prev = it->prev;
			ListNode* next = it->next;
			ListNode* tmp = it;
			it = it->next;

			prev->next = next;
			if (next != NULL)
			{
				next->prev = prev;
			}
			
			free(tmp);
			ret++;
		}
		else
		{
			it = it->next;
		}
	}

	return ret;
}

int main(int argc, char* argv[])
{
	int T, N;
	setbuf(stdout, NULL);

	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		scanf("%d", &N);

		ListNode* head = list_create(NULL);
		printf("#%d", test_case);
		for (int i = 0; i < N; i++)
		{
			int mode, data;
			scanf("%d%d", &mode, &data);

			if (mode == 1)
			{
				ListNode* node = list_create(data);

				list_insert(head, node);
			}
			else if (mode == 2)
			{
				printf(" %d", list_erase(head, data));
			}
		}

		while (head != NULL)
		{
			ListNode* tmp = head;
			head = head->next;
			free(tmp);
		}
		printf("\n");
	}
	return 0;
}