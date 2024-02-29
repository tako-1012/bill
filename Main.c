#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCT 1000
#define MAX_BILL 100

void AddBill();
void ShowBill();
void ShowMenu();
void ShowHelp();
void DeleteBill();
int Caluculation();


//商品一覧用の構造体
struct Product
{
    char name[100];
    int price;
};

//伝票用の構造体
struct Bill
{
    char name[100];
    char drink[3];
    int num;
};

struct Product product[100];
struct Bill bill[100];

//商品の数
int AddCount = 0;

//伝票の商品の数
int BillCount = 0;

int main()
{

    // ファイルポインタを宣言
    FILE *file = fopen("Menu.csv", "r");

    //エラー処理
    if (file == NULL)
    {
        perror("ファイルを開けません");
        return 1;
    }

    char name[100];
    int price;

    for (; fscanf(file, "%[^,],%d\n", name, &price) != EOF;)
    {
        strcpy(product[AddCount].name, name);
        product[AddCount].price = price;
        AddCount++;
    }

    // ファイルを閉じる
    fclose(file);

    char input[100];

    //コマンド一覧を表示
    ShowHelp();

    while (1)
    {
        printf("コマンドを入力してください(終了はexitコマンドを見たいときはhelp): ");
        scanf("%s", input);

        if (strcmp(input, "exit") == 0)
        {
            printf("終了します\n");
            break;
        }
        else if (strcmp(input, "add") == 0)
        {
            AddBill();
        }
        else if (strcmp(input, "bill") == 0)
        {
            ShowBill();
        }
        else if (strcmp(input, "menu") == 0)
        {
            ShowMenu();
        }
        else if (strcmp(input, "help") == 0)
        {
            ShowHelp();
        }
        else if (strcmp(input, "delete") == 0)
        {
            DeleteBill();
        }
        else if (strcmp(input, "calu") == 0)
        {
            printf("合計金額は%d円です\n", Caluculation());
        }
        else
        {
            printf("コマンドが間違っています\n");
        }
    }

    return 0;
}

//伝票に商品を追加する
void AddBill()
{
    char name[100];
    char drink[3];
    int con = 0;
    printf("商品を入力してください: ");
    scanf("%s", name);

    for (int i = 0; i < AddCount; i++)
    {
        if (strcmp(product[i].name, name) == 0)
            con = 1;
    }

    if (con == 0)
    {
        printf("商品がありません\n");
        return;
    }

    if (BillCount < MAX_BILL)
    {
        strcpy(bill[BillCount].name, name);
        BillCount++;
    }
    else
    {
        printf("商品を追加できません\n");
    }
    printf("飲み方を入力してください(ストレートならS,ロックならR,ハイボールならHB,トワイスアップならT): ");
    scanf("%s", drink);
    while (strcmp(drink, "S") != 0 && strcmp(drink, "R") != 0 && strcmp(drink, "HB") != 0 && strcmp(drink, "T") != 0)
    {
        printf("飲み方が間違っています\n");
        printf("飲み方を入力してください(ストレートならS,ロックならR,ハイボールならHB,トワイスアップならT): ");
        scanf("%s", drink);
    }
    strcpy(bill[BillCount].drink, drink);

    printf("数量を入力してください: ");
    scanf("%d", &bill[BillCount].num);

    printf("お酒の名前: %s 飲み方: %s 数量: %dを追加しました。\n", name, drink, bill[BillCount].num);
}

//伝票を表示する
void ShowBill()
{
    if (BillCount == 0)
    {
        printf("商品がありません\n");
        return;
    }
    else
    {
        for (int i = 0; i < BillCount; i++)
        {
            printf("商品名: %s 飲み方: %s\n", bill[i].name, bill[i].drink);
        }
    }
}

//商品一覧を表示する
void ShowMenu()
{
    if (AddCount == 0)
    {
        printf("商品がありません\n");
        return;
    }
    else
    {
        for (int i = 0; i < AddCount; i++)
        {
            printf("商品名: %s 金額: %d\n", product[i].name, product[i].price);
        }
    }
}

//コマンド一覧を表示する
void ShowHelp()
{
    printf("伝票の追加: add\n伝票の削除: delete\nメニューの表示: menu\n現在の伝票の表示: bill\n現在のお会計の一覧と金額表示: calu\nコマンドを入力してください(終了はexit): ");
}

//伝票の商品を削除する
void DeleteBill()
{
    char name[100];
    char drink[3];
    printf("商品名を入力してください: ");
    scanf("%s", name);
    printf("飲み方を入力してください: ");
    scanf("%s", drink);
    for (int i = 0; i < BillCount; i++)
    {
        if (strcmp(bill[i].name, name) == 0 && strcmp(bill[i].drink, drink) == 0)
        {
            for (int j = i; j < BillCount; j++)
            {
                strcpy(bill[j].name, bill[j + 1].name);
                strcpy(bill[j].drink, bill[j + 1].drink);
            }
            BillCount--;
            printf("商品名: %s 飲み方: %sを削除しました\n", name, drink);
            return;
        }
    }
    printf("商品がありません\n");
}

//合計金額を計算する
int Caluculation(){
    int sum = 0;
    for (int i = 0; i < BillCount; i++)
    {
       sum += bill[i].num * product[i].price;
    }
    return sum;
}