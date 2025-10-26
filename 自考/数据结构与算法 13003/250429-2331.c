// typedef struct DListNode {
//     int val;
//     struct DListNode *prev, *next;
// } DListNode;
// DListNode* createNode(int value); // 创建一个新的双链表节点
// DListNode* f29(DListNode* list1, DListNode* list2) {
//     DListNode dummy = {0, NULL, NULL};
//     DListNode* tail = &dummy;
//     while (list1 && list2) {
//         // if (______ (1) ______) {
//         // (1) 比较两个链表当前节点值，值小的节点先接入结果链表
//         if (list1->val < list2->val) {
//             tail->next = list1; list1->prev = tail; list1 = list1->next;
//         } else {
//             tail->next = list2; list2->prev = tail; list2 = list2->next;
//         }
//         // ______ (2) ______;
//         // (2) 尾指针后移，指向新接入的节点
//         tail = tail->next;
//     }
//     // if (list1) { tail->next = list1; ______ (3) ______; }
//     // (3) 连接剩余 list1 节点的前驱指针到当前尾节点
//     if (list1) {  tail->next = list1; list1->prev = tail;}
//     if (list2) { tail->next = list2; list2->prev = tail; }
//     return dummy.next;
// }


#include <stdio.h>
#include <stdlib.h>

typedef struct DListNode {
    int val;
    struct DListNode *prev, *next;
} DListNode;

// 创建一个新的双链表节点
DListNode* createNode(int value) {
    DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
    newNode->val = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

DListNode* f29(DListNode* list1, DListNode* list2) {
    DListNode dummy = {0, NULL, NULL};
    DListNode* tail = &dummy;
    while (list1 && list2) {
        // if (______ (1) ______) {
        // (1) 比较两个链表当前节点值，值小的节点先接入结果链表
        if (list1->val < list2->val) {
            tail->next = list1; list1->prev = tail; list1 = list1->next;
        } else {
            tail->next = list2; list2->prev = tail; list2 = list2->next;
        }
        // ______ (2) ______;
        // (2) 尾指针后移，指向新接入的节点
        tail = tail->next;
    }
    // if (list1) { tail->next = list1; ______ (3) ______; }
    // (3) 连接剩余 list1 节点的前驱指针到当前尾节点
    if (list1) {  tail->next = list1; list1->prev = tail;}
    if (list2) { tail->next = list2; list2->prev = tail; }
    return dummy.next;
}

// 打印双向链表
void printList(DListNode* head) {
    DListNode* current = head;
    printf("Forward: ");
    while (current != NULL) {
        printf("%d ", current->val);
        if (current->next == NULL) break;
        current = current->next;
    }
    printf("\n");
}

// 创建一个测试链表
DListNode* createTestList(int values[], int size) {
    if (size == 0) return NULL;
    
    DListNode* head = createNode(values[0]);
    DListNode* current = head;
    
    for (int i = 1; i < size; i++) {
        DListNode* newNode = createNode(values[i]);
        current->next = newNode;
        newNode->prev = current;
        current = newNode;
    }
    
    return head;
}

// 测试函数
int main() {
    // 创建第一个有序链表: 1 -> 3 -> 5 -> 7
    int values1[] = {1, 3, 5, 7};
    DListNode* list1 = createTestList(values1, 4);
    printf("List 1: ");
    printList(list1);
    
    // 创建第二个有序链表: 2 -> 4 -> 6 -> 8
    int values2[] = {2, 4, 6, 8};
    DListNode* list2 = createTestList(values2, 4);
    printf("List 2: ");
    printList(list2);
    
    // 合并两个链表
    DListNode* merged = f29(list1, list2);
    printf("Merged list: ");
    printList(merged);
    
    // 创建另一个测试用例: [1, 5, 6] 和 [2, 3, 4]
    int values3[] = {1, 5, 6};
    DListNode* list3 = createTestList(values3, 3);
    printf("\nList 3: ");
    printList(list3);
    
    int values4[] = {2, 3, 4};
    DListNode* list4 = createTestList(values4, 3);
    printf("List 4: ");
    printList(list4);
    
    // 合并两个链表
    DListNode* merged2 = f29(list3, list4);
    printf("Merged list 2: ");
    printList(merged2);
    
    return 0;
}