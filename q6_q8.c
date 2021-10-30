#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef enum
{
    ATOM,
    LIST
} eltype;
typedef char atom;
struct _listnode;
typedef struct
{
    eltype type;
    union
    {
        atom a;
        struct _listnode *l;
    };
} element;
typedef struct _listnode
{
    element el;
    struct _listnode *next;
} * list;
const element NIL = {.type = LIST, .l = NULL};

//i. element aasel(atom a); atom as element, that returns an element whose content is set to atom a.
element aasel(atom a)
{
    element resultElement;
    resultElement.type = ATOM;
    resultElement.a = a;
    return resultElement;
}

//ii. element lasel(list l); list as element, that returns an element whose content is set to the list, pointed by l.
element lasel(list l)
{
    element resultElement;
    resultElement.type = LIST;
    resultElement.l = l;
    return resultElement;
}

//iii. element car(element e); that returns the head of the list, represented by e; returns NIL, if e is not a list.
element car(element e)
{
    if (e.type != LIST)
    {
        return NIL;
    }
    else
    {
        return e.l->el;
    }
}
//iv. list cdr(element e); that returns tail of the list, represented by e. The tail of a list with one or zero element is NIL. The tail of an element that is not a list is also NIL.
list cdr(element e)
{
    if (e.type != LIST || e.l == NULL)
    {
        return NULL;
    }
    return e.l->next;
}
//v. list cddr(element e); that returns the cdr of the cdr of the list, represented by e.
list cddr(element e)
{
    return (e.l->next)->next;
}
//vi. list cons(element e, list l); that creates a new list whose car and cdr are the element e and the list l.
list cons(element e, list l)
{
    list consList = (list)malloc(sizeof(struct _listnode));
    consList->el = e;
    consList->next = l;
    return consList;
}

//vii. list append(list l1, list l2); that creates a new list whose elements are shallow copies of elements in l1 and l2, appended.
list append(list l1, list l2)
{
    if (l1 == NULL)
    {
        return l2;
    }
    else if (l2 == NULL)
    {
        return l1;
    }
    else
    {
        list appendedList = l1;
        struct _listnode *traversal = appendedList;
        while (traversal->next != NULL)
        {
            traversal = traversal->next;
        }
        traversal->next = l2;
        return appendedList;
    }
}
//viii. void lfreer(list l); that frees all the memory previously allocated by the whole list (including all its elements and its inner lists)
void lfreer(list l)
{
    list traversal = l;

    while (traversal != NULL)
    {
        if (traversal->el.type == LIST)
        {
            lfreer(traversal->el.l);
        }

        list temp = traversal->next;
        free(traversal); //freee truct list node (void *)
        traversal = temp;
    }
}
//ix. void print(element e); that prints the content of the element e.

bool firstBraket = true;

void print(element e)
{

    if (e.type == ATOM)
    {
        printf(" %c ", e.a);
    }
    else if (e.type == LIST)
    {
        if (firstBraket == true && e.l != NULL)
        {
            printf("(");
            firstBraket = false;
        }
        if (e.l == NULL)
        {
            printf("NIL");
        }

        else
        {
            if (e.l->next != NULL)
            {
                if (e.l->el.type == LIST)
                {
                    printf("(");
                }

                print(e.l->el);
                print(lasel(e.l->next));
            }
            else
            {
                print(e.l->el);
                printf(")");
            }
        }
    }
}

int main()
{
    //Q7 test the codes
    /*
    *creating our elememts and lists and print 
    */
    element a = aasel('a');
    element b = aasel('b');
    element c = aasel('c');
    element d = aasel('d');
    element e = aasel('e');
    //create the list
    list finalList = cons(a, cons(lasel(cons(b, cons(c, NULL))), cons(d, cons(e, NULL))));

    //Q8 print the list
    print(lasel(finalList));
    firstBraket = true;
    printf("\n");
    print(car(lasel(finalList)));
    printf("\n");
    print(lasel(cdr(lasel(finalList))));
    firstBraket = true;

    printf("\n");
    print((car(car(lasel(finalList)))));

    lfreer(finalList);
    printf("\n");
    // print((car(car(lasel(finalList)))));

    return 0;
}