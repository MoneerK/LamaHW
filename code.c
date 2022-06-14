/*
    Libraries
    ==========================================
    include any libraries you use here
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


/*
    Constants
    ==========================================
    The below are constants you will need in this program. You can use them anywhere in your code.
        e.g., printf("%.2lf", SHOP_LOCATION_X) will print 4.50
    Constants are like variables but cannot be modified after the program starts.
    Do not change their values!
*/

// (x, y) values for the location of the store
const double SHOP_LOCATION_X = 4.5;
const double SHOP_LOCATION_Y = 3.8;
// the name of the file that contains all the products
const char FILE_NAME[] =  "products.txt" ;
// SKUs of products that have 15% discount
const int DISCOUNTED[7] = { 27638, 72646, 39044, 50948, 52363, 37462, 38511 };


/*
    Function prototypes
    ==========================================
    Check the function definitions below for more
    information about each function

    Note 1: Do NOT modify the names, return types, or arguments of these functions.
    Note 2: You are allowed to create additional functions if you need to.
*/

int mainMenu();
double findNearestShop();
void listProductsCheaperThan(double price);
int addProduct(int sku, double price);
void processPurchase(int numOfItems, int itemSkus[]);
void drawPrices(int numOfProducts, int productSkus[]);

/* Helper functions */
double manhattanDistance(double x1, double y1, double x2, double y2);
double euclideanDistance(double x1, double y1, double x2, double y2);
int isOnDiscount(int sku);
double discountedPrice(double price);
double getPriceBySku(int sku);
int doublesAreEqual(double x, double y);


/*
    The main function
    ==========================================
    No need to implement this, we already implemented it for you!
    It calls the mainMenu function and keeps calling it until it returns 1.
    When it does, it exits the program.
*/
int main() {
    int shouldExit;
    do {
        shouldExit = mainMenu();
    } while (shouldExit != 1);
    printf("Thanks for using this program!\n");
    return 0;
}


/*
    Function definitions
    ==========================================
    Note 1: Do NOT modify the names, return types, or arguments of these functions.
    Note 2: You are allowed to create additional functions if you need to, but you HAVE TO
    implement all of these functions.
*/



/*
    Displays the main menu of the program and processes the user's choice.
    RETURNS 1 to main if the user chooses to Exit, otherwise RETURNS 0.
    
    The main menu contains the following functionalities:
    1 -> Find nearest shop
    2 -> List products cheaper than some price
    3 -> Adds a new product to the store
        If the product was added successfully, PRINT "Product added successfully." inside
        the mainMenu function otherwise PRINT "The added product is not unique."
    4 -> Serves a customer to process their purchase
    5 -> Draws an image that shows the prices of some products
    6 -> Exits the program

    If the user enters any other number, PRINT "Invalid Choice" and RETURN 0.
*/
int mainMenu() {
    int option;
    do{ 
        printf("Welcome! Please choose one of the following options [1-6]:\n\
        1. Find Nearest shop\n\
        2. List product cheaper than a price\n\
        3. Add a new product to the store\n\
        4. Process a Purchase\n\
        5. Draw a figure of the prices\n\
        6. Exit\n");
        if (scanf("%d", &option) != 1){
            printf("Input is not an integer, please try again.");
            break;
        } else if ((option <1) && (option>6)){
            printf("The number is not within the accepted range, please try again.");
            continue;
        }
    } 
    while ((option <1) || (option >6));

    switch (option)
    {
    case 1:
        /* Find Nearest shop\n\ */
        char strDist[15];
        int distType;
        double nearShop;
        printf("Enter the distance measure you would like to use:\n");
        printf("Type 'euclidean' for Euclidean Distance\n");
        printf("Type 'manhattan' for Manhattan Distance\n");
        scanf("%s",strDist);
        if (strcmp(strDist, "euclidean")) distType = 2;
        else if (strcmp(strDist, "manhattan")) distType = 1;
        else distType = 0;
        if (distType != 0){
            nearShop = findNearestShop(distType);
            printf("NearestShop is: %f m\n",nearShop);
        } else {
            printf("Wrong distance type\n");
        }
        break;
    case 2:
       
        double price;
        printf("what is the price:");
        scanf("%lf", &price);
        printf("products cheaper than the price:%lf are:\n",price);
        listProductsCheaperThan(price);
        break;
    case 3:
        int addSku = 12345;
        double addPrice = 5.55;
        printf("What is the SKU of the product to be added?");
        scanf("%d",&addSku);
        printf("What is the price of the new product?");
        scanf("%lf", &addPrice);

        if (addProduct(addSku,addPrice)== 0){
            //fail
            printf("SKU(%d) is already added\n",addSku);

        } else {
            //success
            printf("SKU(%d) is added successfully\n",addSku);
        }
    
        break;
    case 4:
    
        // printf("%d\n",isOnDiscount(509448));
        printf("%lf\n",getPriceBySku(374612));

        break;
    case 5:
   
        break;
    case 6:
   
        break;

    
    default:
        printf("Error value:%d:", option);
        break;
    }
    
    //  printf("%d\n",myNum);
    return 1;
}


/*
    Helps the store find the nearest shop to restock from.
    Asks the user to enter a word to decide which distance measure to use.
        'euclidean' -> Euclidean Distance
        'manhattan' -> Manhattan Distance
        Anything else -> PRINT an error message and ask for the word again.
    Then asks the user to enter the number of shops nearby.
    For each shop, it asks the user to enter the coordinates x y of that shop.
    
    It RETURNS the distance of the closest shop to the store. Remember that the store
    is at location (SHOP_LOCATION_X, SHOP_LOCATION_Y) that are as constants defined above
*/
double findNearestShop(int distType) {
        int nearestShopIndex = 0, numShops = 0;
        double dblShopCordX,dblShopCordY, nearShop;
        printf("Enter number of shops:\n");
        scanf("%d", &numShops);
        double arrShopXCoord[numShops];
        double arrShopYCoord[numShops];
        double arrDistance[numShops];
        for (int i=0; i< numShops; i++){
            printf("Enter X Coordination for shop#%d:\n", i);
            scanf("%lf", &arrShopXCoord[i]);
            printf("Enter Y Coordination for shop#%d:\n", i);
            scanf("%lf", &arrShopYCoord[i]);
            if (distType == 1) arrDistance[i] = euclideanDistance (SHOP_LOCATION_X, SHOP_LOCATION_Y, arrShopXCoord[i],arrShopYCoord[i]);
            else  arrDistance[i] = manhattanDistance(SHOP_LOCATION_X, SHOP_LOCATION_Y, arrShopXCoord[i],arrShopYCoord[i]);
        }
        double minDis = arrDistance[0];
        for (int i=1; i< numShops; i++){
            if(arrDistance[i] < minDis){
                minDis = arrDistance[i];
                nearestShopIndex = i;
            }     
        }
        printf("Near Shop number : %d\n", nearestShopIndex);
        return minDis;
}


/*
    PRINTS the SKUs and prices of all products that
    are cheaper than the passed price

    Takes into account the discounted products in the DISCOUNTED constant array.
*/
void listProductsCheaperThan(double price) {
    FILE *fp = fopen(FILE_NAME, "r");
    if(fp == NULL) {
        perror("Unable to open file");
        exit(1);
    }
    else printf("File open\n");

    char block[128];
    fgets(block, sizeof(block), fp);
    int items  = atoi(block); 
    int productSKU[items];
    double productPrice[items];  
    char *ptr;
    // printf("items:%d\n", items);
    for (int i= 0 ; i<items;i++){
        if (fgets(block,sizeof(block), fp) !=NULL)
        {
            char * token = strtok(block, " ");
            // printf("%s\n",token);
                while( token != NULL ) {
                    // printf( "%s:", token ); //printing each token
                    productPrice[i] = strtod(strtok(NULL, " "),&ptr);
                    // printf( "%lf\t", productPrice[i] );
                    productSKU[i] = atoi(token);
                    // printf( "%d\n", productSKU[i] );
                    break;
                }
        }
    }
    for(int i=0; i < items; i++)
    {
        
            if (isOnDiscount(productSKU[i]) == 1)
            {
                double dblDiscountedPrice = discountedPrice(getPriceBySku(productSKU[i]));
                if( dblDiscountedPrice< price)
                {
                    printf( "%d\t", productSKU[i] );
                    printf( "%lf\n", dblDiscountedPrice );
                }
            }else if (productPrice[i] < price)
            {
                printf( "%d\t", productSKU[i] );
                printf( "%lf\n", productPrice[i] );
            }
    }
    // if (price == -1.0) printf("SKU not found\n"); 
    fclose(fp);
    return;
}


/*
    Adds the product to the list of products in the file IF the SKU is unique.
    It also updates the number of products at the top of the file.

    If the product is added succesfully, RETURNS 1, otherwise RETURNS 0
*/
int addProduct(int sku, double price) {
    if (getPriceBySku(sku)==-1){
        #define MAX 256
        char nItems[10];
        FILE *fptr1, *fptr2;
        int lno = 0, linectr = 0;
        char str[MAX];        
        char temp[] = "temp.txt";
        char skuPrice[20];
        fptr1 = fopen(FILE_NAME, "r");
        if (!fptr1) 
        {
            printf("Unable to open the input file!!\n");
            return 0;
        }
        fptr2 = fopen(temp, "w");
        if (!fptr2) 
        {
            printf("Unable to open a temporary file to write!!\n");
            fclose(fptr1);
            return 0;
        }
        fseek(fptr1,0,SEEK_SET);
        fscanf(fptr1, "%[^\n]", nItems);
        sprintf( nItems,"%d\n",atoi(nItems)+1);
        fseek(fptr1,0,SEEK_SET);
        strcpy(str, "\0");
        while (!feof(fptr1)) 
        {
            fgets(str, MAX, fptr1);
                if (lno == 0 )
                {
                    fprintf(fptr2, "%s", nItems);
                    lno++;
                } 
                else  
                {
                    fprintf(fptr2, "%s", str);
                } 

                linectr++;
        }
        sprintf( skuPrice,"\n%d %.2lf",sku,price);
        fprintf(fptr2, "%s", skuPrice);
        fclose(fptr1);
        fclose(fptr2);
        remove(FILE_NAME);
        rename(temp, FILE_NAME);
        return 1;
    }

    return 0;
}


/*
    Accepts the number of items the customer is buying, and an array of SKUs
    of those items the customer is buying.
    It prints all the purchase details on the screen, and writes them into a file
    called "receipt.txt" along with the total cost of the whole purchase.
    Takes into account the discounted products in the DISCOUNTED constant array.
    If any provided SKU is not in the list of products, PRINT an error message as follows and continue:
        "SKU 58312 is not available! Ignoring!"
    
    E.g., the file "receipt.txt" will look like this after this function ends:
    
    Customer purchased 3 items:
    - 45763 2 5.00
    - 31402 3 3.60
    - 68178 1 19.50
    ===============
    Total: 28.10

*/
void processPurchase(int numOfItems, int itemSkus[]) {
    return;
}


/*
    Draws a picture that shows the prices of the passed product SKUs.
    Each product will be represented by a black bar that has width 30, and
    the length of the bar will be equal to ceil(price of product) x 10.
    Separate bars from each other by 20 white pixels.

    The picture should be 500 pixels of height, and 30 x numOfProducts + 20 x numOfProducts + 1

    If any provided SKU is not in the list of products, PRINT an error message as follows and continue:
        "SKU 58312 is not available! Ignoring!"
*/
void drawPrices(int numOfProducts, int productSkus[]) {
    return;
}


/*
    RETURNS the Manhattan Distance between 2 points (x1, y1) and (x2, y2)
*/
double manhattanDistance(double x1, double y1, double x2, double y2) {
    printf("manhattanDistance ditance %lf: %lf\n", x2, y2);
    int dist = abs(y2-y1)+ abs(x2-x1);
    return (double)dist;
}


/*
    RETURNS the Euclidean Distance between 2 points (x1, y1) and (x2, y2)
*/
double euclideanDistance(double x1, double y1, double x2, double y2) {
    printf("euclideanDistance ditance %lf: %lf\n", x2, y2);
    return sqrt(pow((y2-y1),2)+pow((x2-x1),2));
}


/*
    RETURNS 1 if the passed SKU is on discount, otherwise RETURNS 0
*/
int isOnDiscount(int sku) {
    for (int i =0; i< sizeof(DISCOUNTED); i++){
        if (sku == DISCOUNTED[i]) return 1;
    }   
    return 0;
}


/*
    RETURNS the price after a 15% sale.
*/
double discountedPrice(double price) {
    return (price *0.85);
}


/*
    RETURNS the price of the given SKU, or -1 if the SKU does not exist in the list of products

    Takes into account the discounted products in the DISCOUNTED constant array.
*/
double getPriceBySku(int sku) {
    
    FILE *fp = fopen(FILE_NAME, "r");
    if(fp == NULL) {
        perror("Unable to open file");
        exit(1);
    }
    // else printf("File open\n");

    char block[128];
    fgets(block, sizeof(block), fp);
    int items  = atoi(block); 
    double price = -1.0;   
    char *ptr;
    // printf("items:%d\n", items);
    for (int i= 0 ; i<items;i++){
        if (fgets(block,sizeof(block), fp) !=NULL)
        {
            char * token = strtok(block, " ");
            if (sku == atoi(token)){
                while( token != NULL ) {
                    // printf( "%s:", token ); //printing each token
                    token = strtok(NULL, " ");
                    // printf( "%s\n", token );
                    price = strtod(token,&ptr);
                    break;
                }
            }
        }
    }
    // if (price == -1.0) printf("SKU not found\n"); 
    fclose(fp);
    return price;
}


/*
    You do not need to implement this function, it is already implemented for you.

    Use this function when you want to compare 2 double values for equality.
    Doubles can have precision problems, so doing x == y sometimes gives the
    wrong answer. This functions considers the minor errors that may happen when
    comparing doubles.

    Example of usage:
    
    if (doublesAreEqual(num1, num2) == 1) {
        // do something
    }

    The function will RETURN 1 if the 2 variables are equal, otherwise it will
    RETURN 0.
*/
int doublesAreEqual(double x, double y) {
    return fabs(x - y) < 1.0e-8;
}
