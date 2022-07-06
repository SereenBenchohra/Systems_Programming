Node *new_node(int data)
{
    Node *n;
    n = (Node *)malloc(sizeof(Node));
    if(!n)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    n->data = data;
    n->next = NULL;
    return n; 


}


void printList(Node *list, int size)
{
    Node *temp;
    int i;
    for (i = 0; i < size; i++)
        printf("%d\n", temp->data);
    
}

void freeList(Node* head)
{
   Node  *tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}

int main()
{
    Node *node1, *node2, *node3, *node4, *list;
    node1 = new_node(4);
    node2 = new_node(7);
    node3 = new_node(23);
    node4 = new_node(1);

    node1->next = node2;
    node3->next = node4;

    list = merge_lists(node1, node2);
    printList(list);

    freeList(list);

    return 0; 
}