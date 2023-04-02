#include<iostream>

struct Node
{
    public:
    char item_;
    struct Node* next;
    Node(char item_)
    {
        this->item_ = item_;
        next = NULL;
    }
};

class linked_list
{  
    Node* head;
public:
    linked_list(){head = NULL;}

    void Reversed()
    {
        Node *curr = head;
        Node *next = NULL;
        Node *prev = NULL;

        while(curr != NULL)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    void Insert(char item_1)
    {
        Node* New = new Node(item_1);
 
        if(head == NULL)
        {
            head = New;
            return;
        }
        else
        {
            Node* last = head;
            while(last->next != NULL)
                last = last->next;
            last->next = New;
            return;
        }
    }
    
    void Print()
    {
        struct Node* New = head;
        while(New != NULL)
        {
            std::cout<<New->item_;
            New = New->next;
        }
    }

};

int main()
{
    linked_list l;
    std::string s;
    std::getline(std::cin,s);
    for(int i=0; i<s.length(); i++)
    {
        l.Insert(s[i]);
    }

    l.Reversed();
    l.Print();

    return 0;
}