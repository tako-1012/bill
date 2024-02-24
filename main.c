#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void processArguments(int argc, char *argv[]);
void PrintHelp();
void ShowProduct();
void AddProduct(char *name, char *price);
void AddProductGet();
void DeleteProduct();

struct Product
{
    char name[100];
    int price;
};

struct Product prudct[100];
int count = 0;
char input[100], vinput[100];

int main(int argc, char *argv[])
{
    while (1)
    {
        // 引数がない場合は繰り返し入力を受け付ける
        if (argc == 1)
        {
            printf("コマンドを入力してください （商品はproduct計算はcalculation終了exitは終了): ");
            scanf("%s", input);
            if (strcmp(input, "product") == 0)
            {
                while (strcmp(vinput, "exit") != 0)
                {
                    printf("コマンドを入力してください （exitで終了helpでヘルプを表示): ");
                    scanf("%s", vinput);

                    if (strcmp(vinput, "exit") == 0)
                    {
                        printf("終了します。\n");
                    }
                    else if (strcmp(vinput, "help") == 0)
                    {
                        PrintHelp();
                    }
                    else if (strcmp(vinput, "list") == 0)
                    {
                        ShowProduct();
                    }
                    else if (strcmp(vinput, "add") == 0)
                    {
                        AddProductGet();
                    }
                    else if (strcmp(vinput, "delete") == 0)
                    {
                        DeleteProduct();
                    }
                    else
                    {
                        printf("コマンドが間違っています1\n");
                    }
                }
            }
        }
        return 0;
    }
}

    // ヘルプの表示
    void PrintHelp()
    {
        printf("商品の追加: add 商品名 金額\n商品の削除: delete 商品名\n商品の一覧表示: list\n");
    }

    void Product()
    {
        
    }

    // 商品情報の入力
    void AddProductGet()
    {
        char name[100];
        char price[100];
        printf("商品名を入力してください: ");
        scanf("%s", name);
        printf("金額を入力してください: ");
        scanf("%s", price);
        AddProduct(name, price);
    }

    // 商品の追加の処理
    void AddProduct(char *name, char *price)
    {
        for (int i = 0; i < count; i++)
        {
            if (strcmp(prudct[i].name, name) == 0)
            {
                printf("商品がすでに存在します\n");
                return;
            }
        }
        if (count < 100)
        {
            strcpy(prudct[count].name, name);
            prudct[count].price = atoi(price);
            ;
            count++;
            printf("商品名: %s 金額: %s\n", name, price);
        }
        else
        {
            printf("商品を追加できません\n");
        }
    }

    // 表示する
    void ShowProduct()
    {
        if (count == 0)
        {
            printf("商品がありません\n");
            return;
        }
        else
        {
            for (int i = 0; i < count; i++)
            {
                printf("商品名: %s 金額: %d\n", prudct[i].name, prudct[i].price);
            }
        }
    }

    // 商品の削除
    void DeleteProduct()
    {
        printf("削除する商品名を入力してください: ");
        char name[100];
        scanf("%s", name);
        for (int i = 0; i < count; i++)
        {
            if (strcmp(prudct[i].name, name) == 0)
            {
                for (int j = i; j < count; j++)
                {
                    prudct[j] = prudct[j + 1];
                }
                count--;
                printf("%sを削除しました\n", name);
                return;
            }
        }
        printf("商品が見つかりませんでした\n");
        return;
    }
