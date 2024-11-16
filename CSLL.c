#include <stdio.h>
#include <stdlib.h>

// تعريف هيكل (struct) يمثل العقدة في القائمة الدائرية
struct Node {
    int data;               // البيانات التي تحملها العقدة
    struct Node* next;      // مؤشر يشير إلى العقدة التالية
};

// دالة لإنشاء عقدة جديدة
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) { // التأكد من تخصيص الذاكرة
        printf("فشل في تخصيص الذاكرة\n");
        exit(1); // إنهاء البرنامج في حالة حدوث خطأ
    }
    newNode->data = data;  // تعيين البيانات
    newNode->next = newNode; // الإشارة إلى نفسها لأنها عقدة وحيدة حالياً
    return newNode;
}

// دالة لإضافة عقدة في بداية القائمة الدائرية
void addAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data); // إنشاء عقدة جديدة

    if (*head == NULL) { // إذا كانت القائمة فارغة
        *head = newNode; // العقدة الجديدة تصبح الرأس
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) { // البحث عن العقدة الأخيرة
            temp = temp->next;
        }
        temp->next = newNode;  // تحديث العقدة الأخيرة للإشارة إلى العقدة الجديدة
        newNode->next = *head; // ربط العقدة الجديدة بالرأس الحالي
        *head = newNode;       // تحديث الرأس للإشارة إلى العقدة الجديدة
    }
}

// دالة لإضافة عقدة في نهاية القائمة الدائرية
void addAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data); // إنشاء عقدة جديدة

    if (*head == NULL) { // إذا كانت القائمة فارغة
        *head = newNode; // العقدة الجديدة تصبح الرأس
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) { // البحث عن العقدة الأخيرة
            temp = temp->next;
        }
        temp->next = newNode;  // ربط العقدة الأخيرة بالعقدة الجديدة
        newNode->next = *head; // ربط العقدة الجديدة بالرأس
    }
}

// دالة لحذف عقدة بناءً على قيمة معينة
void deleteNode(struct Node** head, int key) {
    if (*head == NULL) { // إذا كانت القائمة فارغة
        printf("القائمة فارغة، لا يمكن الحذف.\n");
        return;
    }

    struct Node *current = *head, *prev = NULL;

    // إذا كانت العقدة المراد حذفها هي الرأس
    if ((*head)->data == key) {
        // إذا كانت القائمة تحتوي على عقدة واحدة
        if ((*head)->next == *head) {
            free(*head);
            *head = NULL;
            return;
        }

        // البحث عن العقدة الأخيرة لتحديثها
        struct Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = (*head)->next; // تحديث العقدة الأخيرة للإشارة إلى العقدة الثانية
        struct Node* toDelete = *head;
        *head = (*head)->next;     // تحديث الرأس
        free(toDelete);            // تحرير الذاكرة
        return;
    }

    // البحث عن العقدة المراد حذفها
    do {
        prev = current;
        current = current->next;
    } while (current != *head && current->data != key);

    if (current->data != key) {
        printf("القيمة %d غير موجودة في القائمة.\n", key);
        return;
    }

    // حذف العقدة
    prev->next = current->next;
    free(current);
}

// دالة لعرض عناصر القائمة
void displayList(struct Node* head) {
    if (head == NULL) { // إذا كانت القائمة فارغة
        printf("القائمة فارغة.\n");
        return;
    }
    struct Node* temp = head;
    printf("عناصر القائمة: ");
    do {
        printf("%d -> ", temp->data); // طباعة البيانات
        temp = temp->next; // الانتقال إلى العقدة التالية
    } while (temp != head);
    printf("(الرأس)\n"); // الإشارة إلى أن القائمة دائرية
}

// دالة للبحث عن قيمة داخل القائمة
int searchNode(struct Node* head, int key) {
    if (head == NULL) { // إذا كانت القائمة فارغة
        return 0;
    }

    struct Node* temp = head;
    do {
        if (temp->data == key) { // إذا تم العثور على القيمة
            return 1;
        }
        temp = temp->next; // الانتقال إلى العقدة التالية
    } while (temp != head);

    return 0; // القيمة غير موجودة
}

int main() {
    struct Node* head = NULL; // إنشاء قائمة فارغة

    // إضافة عقد إلى القائمة
    addAtBeginning(&head, 10); // إضافة 10 في البداية
    addAtEnd(&head, 20);       // إضافة 20 في النهاية
    addAtEnd(&head, 30);       // إضافة 30 في النهاية
    addAtBeginning(&head, 5);  // إضافة 5 في البداية

    // عرض القائمة
    displayList(head);

    // البحث عن قيمة
    int searchKey = 20;
    if (searchNode(head, searchKey))
        printf("القيمة %d موجودة في القائمة.\n", searchKey);
    else
        printf("القيمة %d غير موجودة في القائمة.\n", searchKey);

    // حذف عقدة
    int deleteKey = 10;
    printf("حذف القيمة %d...\n", deleteKey);
    deleteNode(&head, deleteKey);
    displayList(head);

    return 0;
}
