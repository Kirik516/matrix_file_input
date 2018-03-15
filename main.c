#include <stdio.h>
#include <stdlib.h>

#define List(_type)                                                         \
typedef struct _ListNode_ ## _type                                          \
{                                                                           \
    _type data;                                                             \
    struct _ListNode_ ## _type  *pnext;                                     \
} ListNode_ ## _type;                                                       \
                                                                            \
typedef struct _List_ ## _type                                              \
{                                                                           \
    ListNode_ ## _type *begin;                                              \
    ListNode_ ## _type *last;                                               \
    ListNode_ ## _type *end;                                                \
    void (*push_back)(struct _List_ ## _type *, _type*);                    \
} List_ ## _type;                                                           \
                                                                            \
void _push_back_ ## _type (struct _List_ ## _type *list, _type *i)          \
{                                                                           \
    ListNode_ ## _type *newNode =                                           \
    (ListNode_ ## _type *) malloc(sizeof(ListNode_ ## _type));              \
    newNode->data = *i;                                                     \
    newNode->pnext = newNode + sizeof(ListNode_ ## _type);                  \
                                                                            \
    list->end = newNode->pnext;                                             \
    if (list->begin == NULL)                                                \
    {                                                                       \
        list->begin = newNode;                                              \
        list->last = newNode;                                               \
        return;                                                             \
    }                                                                       \
    list->last->pnext = newNode;                                            \
    list->last = newNode;                                                   \
}                                                                           \

#define MAKE_LIST(_plist, _list_type) _plist->push_back =                   \
                        _push_back_ ## _list_type;                          \
                        _plist->last = _plist->begin = NULL;                \

int main()
{
    FILE *f;

    char fname[1000];
    scanf("%1000s", fname);

    if (fname[sizeof(fname) - 1] != '\0')
    {
        printf("File name to long\n");
        return 1;
    }

    f = fopen("dat.txt", "r");

    if (f == NULL)
    {
        printf("No such file or directory\n");
        return 1;
    }

    int tmp;
    fpos_t p;
    List_int *list = (List_int*) malloc(sizeof(List_int));
    MAKE_LIST(list, int);
    List_List_int matr;
    List_List_int *pmatr = &matr;
    MAKE_LIST(pmatr, List_int);
    while (!feof(f))
    {
        fgetpos(f, &p);
        if (fgetc(f) == '\n')
        {
            matr.push_back(&matr, list);
            free(list);
            list = (List_int*) malloc(sizeof(List_int));
            MAKE_LIST(list, int);
            continue;
        }
        fsetpos(f, &p);
        fscanf(f, "%d", &tmp);
        list->push_back(list, &tmp);
    }
    fclose(f);

    ListNode_List_int *inList = matr.begin;
    ListNode_int *cln;
    while (inList != matr.end)
    {
        cln = inList->data.begin;
        while (cln != inList->data.end)
        {
            printf("%d ", cln->data);
            cln = cln->pnext;
        }
        printf("\n");
        inList = inList->pnext;
    }

    return 0;
}
