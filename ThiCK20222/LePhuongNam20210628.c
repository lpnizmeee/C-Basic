#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "traversal.h"

typedef struct
{
    char name[1000];
    int (*func)();
} MenuItem;

FILE *file = NULL;
FILE *fout = NULL;
tree_t tree = NULL;
char fileout[] = "booking_output.txt";
char filename[] = "booking_orders.txt";
char fileupdate[] = "update.txt";
elmType arr[1000];
int soYeuCau = 0;
int count = 0;
int yeuCauKhongHopLe = 0;

int tinhnang1()
{
    // Mo file che do doc
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Khong mo duoc file %s\n", filename);
        exit(1);
    }
    fscanf(file, "%d", &soYeuCau);
    elmType temp;
    while (fscanf(file, "%s %d %d %s %d-%d-%d %d", temp.maYeuCau, &temp.soNguoi, &temp.soPhong, temp.maKhachSan, &temp.DD, &temp.MM, &temp.YYYY, &temp.kids) != EOF)
    {
        arr[count] = temp;
        count++;
        InsertNode(temp, &tree);
    }
    printf("So yeu cau doc duoc la: %d\n", soYeuCau);
    printf("----------------------------------------------------------------\n");
    // code
    fclose(file);
    return 0;
}

int tinhnang2()
{
    for (int i = 0; i < count; i++)
    {
        if (arr[i].soNguoi <= arr[i].kids)
        {
            yeuCauKhongHopLe += 1;
        }
    }
    printf("So yeu cau khong hop le: %d\n", yeuCauKhongHopLe);
    printf("----------------------------------------------------------------\n");
    return 0;
}

int tinhnang3()
{
    // Tim kiem
    elmType find;
    printf("Nhap ban muon tim: ");
    scanf("%s", find.maYeuCau);
    tree_t result = search(find, tree);
    if (result == NULL)
    {
        printf("Ma yeu cau khong dung %s\n", find.maYeuCau);
    }
    else
    {
        // code
        find = result->element;
        printf("%s %d %d %s %d-%d-%d %d\n", find.maYeuCau, find.soNguoi, find.soPhong, find.maKhachSan, find.DD, find.MM, find.YYYY, find.kids);
    }
    return 0;
}

int tinhnang4()
{
    // cap nhat yeu cau
    printf("Nhap ma yeu cau ban muon cap nhat thong tin: ");
    elmType update;
    scanf("%s", update.maYeuCau);
    getchar();
    tree_t result = search(update, tree);
    if (result == NULL)
    {
        printf("Not found.\n");
    }
    else
    {
        printf("Nhap thong tin ban muon sua doi:\n");
        printf("Ngay thang nam: ");
        scanf("%d-%d-%d", &update.DD, &update.MM, &update.YYYY);
        printf("So nguoi: ");
        scanf("%d", &update.soNguoi);
        printf("So tre em: ");
        scanf("%d", &update.kids);
        if (update.kids >= update.soNguoi)
        {
            printf("Invalid\n");
        }
        else
        {
            result->element.kids = update.kids;
            result->element.soNguoi = update.soNguoi;
            result->element.DD = update.DD;
            result->element.MM = update.MM;
            result->element.YYYY = update.YYYY;
            printf("Updated\n");
        }
    }
    file = fopen(fileupdate, "w");
    if (file == NULL)
    {
        printf("Failed to open\n");
        exit(1);
    }
    f_inorderprint(tree, file);
    fclose(file);
    return 0;
}

int tinhnang5()
{
    // huy yeu cau
    elmType delete;
    printf("Nhap ma yeu cau ban muon huy: ");
    scanf("%s", delete.maYeuCau);
    tree_t result = search(delete, tree);
    if (result == NULL)
    {
        printf("Ma yeu cau khong dung %s\n", delete.maYeuCau);
    }
    else
    {
        printf("Deleted");
        deleteNode(delete, &tree);
        soYeuCau--;
    }
    return 0;
}

int tinhnang6()
{
    fout = fopen(fileout, "w");
    if (fout == NULL)
    {
        printf("Error \n");
        exit(1);
    }
    fprintf(fout, "%d\n", soYeuCau);
    f_inorderprint(tree, fout);
    fclose(fout);
    int count_in = nb_nodes(tree);
    printf("So luong ma yeu cau duoc ghi vao file: %d\n", count_in);
    return 0;
}

int tinhnang7()
{
    // code
    return 0;
}

int thoat()
{
    // Return 1 de doan sau thoat duoc vong lap
    return 1;
}

int main()
{
    elmType *arr = (elmType *)malloc(sizeof(int));
    MenuItem item[] = {{"Doc file log", tinhnang1},
                       {"Kiem tra so luong cac yeu cau khong hop le", tinhnang2},
                       {"Tra cuu theo ma yeu cau", tinhnang3},
                       {"Thay doi yeu cau", tinhnang4},
                       {"Huy yeu cau", tinhnang5},
                       {"Luu danh sach yeu cau ra file", tinhnang6},
                       {"Thong ke khach san duoc yeu thich nhat", tinhnang7},
                       {"Thoat", thoat}};
    int size = sizeof(item) / sizeof(item[0]); // Kich co menu

    for (;;)
    { // Vong lap vo han chay den khi gap thoat thi ket thuc
        printf("\nMenu:\n");
        for (int i = 0; i < size; i++)
        {
            printf("%d. %s\n", i + 1, item[i].name); // In menu
        }
        int luachon;
        printf("\nNhap lua chon: ");
        scanf("%d", &luachon);
        if (luachon < 1 || luachon > size)
        {
            continue; // Neu lua chon khong nam trong kich co thi bo qua
        }
        else if (item[luachon - 1].func())
        {
            // Khi goi den ham thoat thi se thoat vong lap do return 1
            break;
        }
    }
    // Giai phong bo nho cap phat dong
    freeTree(tree);
    free(arr);
}