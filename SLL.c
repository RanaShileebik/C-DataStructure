#include <stdio.h>
#include <stdlib.h>

// تعريف هيكل (struct) يمثل العقدة في القائمة المرتبطة
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
    newNode->next = NULL;  // تعيين المؤشر إلى NULL لأنها عقدة جديدة
    return newNode;
}

// دالة لإضافة عقدة في بداية القائمة
void addAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data); // إنشاء عقدة جديدة
    newNode->next = *head; // جعل العقدة الجديدة تشير إلى الرأس الحالي
    *head = newNode;       // تحديث الرأس للإشارة إلى العقدة الجديدة
}

// دالة لإضافة عقدة في نهاية القائمة
void addAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data); // إنشاء عقدة جديدة
    if (*head == NULL) { // إذا كانت القائمة فارغة
        *head = newNode; // اجعل العقدة الجديدة هي الرأس
        return;
    }
    struct Node* temp = *head; // متغير مؤقت للتنقل في القائمة
    while (temp->next != NULL) { // البحث عن العقدة الأخيرة
        temp = temp->next;
    }
    temp->next = newNode; // ربط العقدة الجديدة بالنهاية
}

// دالة لحذف عقدة بناءً على قيمة معينة
void deleteNode(struct Node** head, int key) {
    struct Node* temp = *head, *prev = NULL;

    // إذا كانت العقدة الأولى تحتوي على القيمة المطلوبة
    if (temp != NULL && temp->data == key) {
        *head = temp->next; // تحديث الرأس للإشارة إلى العقدة التالية
        free(temp);         // تحرير الذاكرة
        return;
    }

    // البحث عن العقدة التي تحتوي على القيمة
    while (temp != NULL && temp->data != key) {
        prev = temp;       // تخزين العقدة السابقة
        temp = temp->next; // الانتقال إلى العقدة التالية
    }

    // إذا لم يتم العثور على القيمة
    if (temp == NULL) {
        printf("القيمة %d غير موجودة في القائمة.\n", key);
        return;
    }

    // حذف العقدة عن طريق تعديل مؤشر العقدة السابقة
    prev->next = temp->next;
    free(temp); // تحرير الذاكرة
}

// دالة لعرض عناصر القائمة
void displayList(struct Node* head) {
    if (head == NULL) { // إذا كانت القائمة فارغة
        printf("القائمة فارغة.\n");
        return;
    }
    struct Node* temp = head; // متغير للتنقل في القائمة
    printf("عناصر القائمة: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data); // طباعة البيانات
        temp = temp->next; // الانتقال إلى العقدة التالية
    }
    printf("NULL\n"); // نهاية القائمة
}

// دالة للبحث عن قيمة داخل القائمة
int searchNode(struct Node* head, int key) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == key) // إذا تم العثور على القيمة
            return 1;          // القيمة موجودة
        temp = temp->next;     // الانتقال إلى العقدة التالية
    }
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
