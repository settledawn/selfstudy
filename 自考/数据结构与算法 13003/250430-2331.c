#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 20
typedef char VertexType;

// 边表结点
typedef struct node {
    int adjvex;           // 顶点的序号
    struct node *next;    // 指向下一条边的指针
} EdgeNode;

// 顶点表结点
typedef struct vnode {
    VertexType vertex;    // 顶点域
    EdgeNode *link;       // 边表头指针
} VNode, Adjlist[MaxVertexNum];

// 定义为图类型
typedef Adjlist ALGraph;

// 循环队列定义
#define MaxSize 20
typedef struct {
    int data[MaxSize];
    int front, rear;
} CirQueue;

// 初始化队列
void InitQueue(CirQueue *Q) {
    Q->front = Q->rear = 0;
}

// 判断队列是否为空
int QueueEmpty(CirQueue *Q) {
    return (Q->front == Q->rear);
}

// 入队操作
void EnQueue(CirQueue *Q, int x) {
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % MaxSize;
}

// 出队操作
int DeQueue(CirQueue *Q) {
    int temp = Q->data[Q->front];
    Q->front = (Q->front + 1) % MaxSize;
    return temp;
}

// 创建图的邻接表
void createGraph(ALGraph G, int n, int edges[][2], int edgeCount) {
    // 初始化顶点表
    for (int i = 1; i <= n; i++) {
        G[i].vertex = 'A' + i - 1;
        G[i].link = NULL;
    }
    
    // 添加边
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        
        // 添加边 u -> v
        EdgeNode *node1 = (EdgeNode*)malloc(sizeof(EdgeNode));
        node1->adjvex = v;
        node1->next = G[u].link;
        G[u].link = node1;
        
        // 添加边 v -> u (无向图)
        EdgeNode *node2 = (EdgeNode*)malloc(sizeof(EdgeNode));
        node2->adjvex = u;
        node2->next = G[v].link;
        G[v].link = node2;
    }
}

void bfs(ALGraph G, int n) {
    CirQueue Q;  // 定义循环队列 Q，用于 BFS 的层序遍历控制
    int j, k;    // 定义整型变量 j、k，用于顶点下标等操作
    InitQueue(&Q);  // 初始化队列 Q
    EdgeNode *p; int visited[20] = {0};  // p 是邻接表边节点指针，visited 数组标记顶点是否访问
    printf("v1->"); visited[1] = 1;  // 访问顶点 v1，标记为已访问并输出
    EnQueue(&Q, 1);  // 顶点 1 入队
    while (!QueueEmpty(&Q)) {  // 队列非空时持续遍历
        k = DeQueue(&Q); p = G[k].link;  // 取出队列顶点 k，p 指向 k 的邻接边节点
        while (p != NULL) {  // 遍历顶点 k 的所有邻接顶点
            j = p->adjvex;  // 获取邻接顶点下标 j
            if (!visited[j]) {  // 若顶点 j 未访问
                printf("v%d->", j); visited[j] = 1; EnQueue(&Q, j);  // 访问、标记、入队
            }
            p = p->next;  // 指向下一个邻接边节点
        }
    }
    printf("end\n");
}

// 测试函数
int main() {
    ALGraph G;
    int n = 6; // 6个顶点
    
    // 定义边: (1,2), (1,3), (2,4), (2,5), (3,6)
    int edges[][2] = {{1,2}, {1,3}, {2,4}, {2,5}, {3,6}};
    int edgeCount = 5;
    
    // 创建图
    createGraph(G, n, edges, edgeCount);
    
    // 执行BFS遍历
    printf("BFS遍历结果: ");
    bfs(G, n);
    
    return 0;
}