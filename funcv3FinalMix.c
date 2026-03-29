/*********************************************************************************************************  
This is to certify that this project is our own work, based on our personal efforts in studying and applying the concepts learned. We have 
constructed the functions and their respective algorithms and corresponding code by ourselves. The program was run, tested, and 
debugged by our own efforts. We further certify that we have not copied in part or whole or otherwise plagiarized the work of other 
students and/or persons, nor did we employ the use of AI in any part of the deliverable. 
                                                                                                    
                                                                                Maullon, Edriel Lexine A., DLSU ID# 12512079
                                                                                Tolentino, Johann Haree G., DLSU ID# 12506494  
*********************************************************************************************************/ 

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "recipev2.h"
#include "stringDef.h"

void ListRecipeTitles(recipeType recipies[], int nCount);
void DisplayRecipe(recipeType recipe);
void ScanRecipies(recipeType recipies[], int nCount);
void getIngredientCalories(recipeType *r, foodCalorieType f[], int nFoodItems);

/**
 * @brief scanString is a function that allows the scanning of strings with spaces.
 * 
 * @param string[] the address where the string will be stored.
 * @param n dictates the size of the character array- done so with sizeof().
 */
void scanString(char string[], int n)
{
    int i;
    char ch;

    i = 0;
    do
    {
        scanf("%c", &ch);
        if (ch != '\n')
        {
            string[i] = ch;
            i++;
        }

    } while (i < n && ch != '\n');

    string[i] = '\0';
}
/**
 * @brief DisplayActions is a function that shows a variety of choices that will be
 * displayed depending on the number it gets as input.
 * 
 * @param nSelect The input number that determines which choices will be
       displayed on screen. The inputs are already pre-determined within
       the program.
 */
void DisplayActions(int nSelect)
{
    switch (nSelect)
    {
    case 0: // Main Menu Actions
        printf("|-------  Welcome to the Main Menu!  -------|\n\n");

        printf("Pick your action: \n");
        printf("[1] Configure Recipes\n");
        printf("[2] View Recipies\n");
        printf("[3] Close Program\n");
        printf("\n");
        break;

    case 1: // Update Recipe Actions
        printf("|---------  Configure Recipes Menu  --------|\n\n\n\n");

        printf("Pick your action: \n");
        printf("[1] Add Food-Calorie Info\n");
        printf("[2] Delete Food-Calorie Info\n");
        printf("[3] View Food-Calorie Info\n");
        printf("[4] Save Calorie Info to Text File\n");
        printf("[5] Load Calorie Info from Text File\n");
        printf("[6] Add a Recipe\n");
        printf("[7] Delete a Recipe\n");

        printf("\n[0] Return to Main Menu\n");
        printf("[X] Next Page\n");
        printf("\n");

        break;
    case 2:
        printf("|-----------  View Recipes Menu  -----------|\n\n\n\n");

        printf("Pick your action: \n");
        printf("[1] Import Recipes from Text File\n");
        printf("[2] Recipe List\n");
        printf("[3] Scan Recipes\n");
        printf("[4] Search by Title\n");
        printf("[5] Search by Ingredient\n");
        printf("[6] Generate Shopping List\n");
        printf("[7] Show me what's good\n");
        printf("[8] Return to Main Menu\n");
        printf("\n");

        break;
    case 3:
        printf("|----------  Modify Recipes Menu  ----------|\n\n\n\n");

        printf("Pick your action: \n");
        printf("[1] Add Ingredient\n");
        printf("[2] Delete Ingredient\n");
        printf("[3] Add Step\n");
        printf("[4] Delete Step\n");
        printf("[5] End Modifications\n\n");

        break;
    case 4:
        printf("|---------  Configure Recipes Menu  --------|\n\n\n\n");

        printf("Pick your action: \n");
        printf("[1] Modify a Recipe\n");
        printf("[2] List Recipe Titles\n");
        printf("[3] Scan Recipes One By One\n");
        printf("[4] Search by Ingredient\n");
        printf("[5] Search by Title\n");
        printf("[6] Import Recipes from Text File\n");
        printf("[7] Export Recipes to Text File\n");

        printf("\n[0] Return to Main Menu\n");
        printf("[X] Previous Page\n");
        printf("\n");
        break;
    default:
        break;
    }
}

/**
 * @brief PasswordCheck asks the user to input a username and password to access the Recipe Box.
 * The function will return 1 if the username and password are inputted correctly.
 * 
 * @return int 1 if the username and password are correct- in this case, the user typed in
               "admin" and "ad1234" as the username and password respectively;
               0 if the username and password are incorrect
 */
int PasswordCheck()
{
    str15 sNameInput;
    str15 sPassInput;

    int nCheck;

    printf("\n");

    printf("Please Input a valid name and password\n");

    printf("\n");

    printf("Name: ");
    scanf(" %s", sNameInput);

    printf("Password: ");
    scanf(" %s", sPassInput);

    if (strcmp(sNameInput, "admin") == 0 && strcmp(sPassInput, "ad1234") == 0)
    {
        nCheck = 1;
    }
    else
    {
        nCheck = 0;
    }

    return nCheck;
}

/**
 * @brief AddIngredient asks the user to input the name of a food item, how much of it there
 * is- both the quantity and unit specified, and how much calories it contains.
 * 
 * @param a The foodCalorieType struct that contains the adress of the food item's name,
       the quantity and unit, and the number of calories.
 */
void AddIngredient(foodCalorieType *a)
{
    // Name of Ingredient
    printf("Ingredient: ");
    scanString(a->sIngredient, (int)sizeof(a->sIngredient));

    // Quantity of Ingredient
    printf("Quantity: ");
    scanf(" %f", &a->fQuantity);
    getchar();

    // Unit of ingredient
    printf("Unit: ");
    scanString(a->sUnit, (int)sizeof(a->sUnit));

    printf("Calories: ");
    scanf(" %f", &a->fCalories);
}

/**
 * @brief foodChartHeaderFooter is a helper function that goes with viewFoodCalorieChart.
 * It prints the header or footer of the chart, depending on the parameter.
 * 
 * @param input The input, which will only either be 1 or 0- that determines
       whether to show the header or the footer.
 */
void foodChartHeaderFooter(int input)
{
    if (input)
    {
        printf("+----------------------+---------+-----------------+---------+\n");
        printf("|      Food Item       |   Qty   |      Units      | Calorie |\n");
        printf("+----------------------+---------+-----------------+---------+\n");
    }
    else if (!input)
    {
        printf("+----------------------+---------+-----------------+---------+\n");
    }
}

/**
 * @brief viewFoodCalorieChart displays the food item, quantity, unit, and number of calories,
 * in that order, for all the food items in the array.
 * 
 * @param f The array of food items to be displayed by the program.
 * @param nFoodItems The number of food items in the array f
 */
void viewFoodCalorieChart(foodCalorieType f[], int nFoodItems)
{
    int i;
    char next;

    if (nFoodItems != 0)
    {
        for (i = 0; i < nFoodItems && (next != 'X' || next != 'x'); i++)
        {
            if (i % 10 == 0)
                foodChartHeaderFooter(1);

            printf("| %-20s | %-7.2f | %-15s | %-7.2f |\n", f[i].sIngredient, f[i].fQuantity,
                f[i].sUnit, f[i].fCalories);

            if ((i + 1) == nFoodItems)
                foodChartHeaderFooter(0);

            if ((i + 1) % 10 == 0)
            {
                foodChartHeaderFooter(0);

                printf("\nNext (N) | Exit (X)\n");
                printf("Input: ");
                scanf(" %c", &next);
                getchar();
            }
        }
    }
    else
        printf("No food item/s to display...\n\n");
    
}

/**
 * @brief searchFoodItem searches for a specified food item name in the array
 * of food items.
 * 
 * @param f The array of food items.
 * @param key The name of the food item to be searched.
 * @param nCount The number of elements in the array of food items.
 * @return int i- the index at which the food item was found;
 *             -1 if the food item isn't found.
 */
int searchFoodItem(foodCalorieType f[], char key[], int nCount)
{
    int i, res = -1;

    for (i = 0; i < nCount; i++)
        if (strcmp(f[i].sIngredient, key) == 0)
            res = i;

    return res;
}

/**
 * @brief AddFoodCalorieInfo adds the information of one food item to an array that contains
 * a list of all the food items.
 * 
 * @param aFoodList The array of food items.
 * @param nCount The number of food items in the array.
 */
void AddFoodCalorieInfo(foodCalorieType aFoodList[], int *nCount)
{
    int i;

    str20 sFoodName;
    int nNameCheck = 0;
    int nInvalid = 0;

    // checks if inputted name is the same from food list arrays
    // redoes everything if detects the same name via nNameCheck is less tham nElements
    do
    {
        // Clear previous checks
        nNameCheck = 0;
        strcpy(sFoodName, ""); // clears sFoodName string of previous inputs

        // Print already exists error message
        if (nInvalid == 1)
        {
            printf("Food Item name already exists in the database!\n");
        }

        printf("Food Item Name: ");
        scanString(sFoodName, (int)sizeof(sFoodName)); // asks for input name

        for (i = 0; i < *nCount; i++)
        {
            // increment nNameCheck 1 per unidentical string
            if (strcmp(sFoodName, aFoodList[i].sIngredient) != 0)
            {
                nNameCheck += 1;
            }
        }

        if (nNameCheck < *nCount)
        {
            nInvalid = 1;
        }

    } while (nNameCheck < *nCount);

    strcpy(aFoodList[*nCount].sIngredient, sFoodName); // copies checked name into sIngredient

    printf("Quantity: ");
    scanf(" %f", &aFoodList[*nCount].fQuantity);

    printf("Unit: ");
    scanf(" %15s", aFoodList[*nCount].sUnit);

    printf("Calories: ");
    scanf(" %f", &aFoodList[*nCount].fCalories);

    (*nCount)++;
}

/**
 * @brief DeleteFoodItem deletes a food item from the array of food items, then move the elements
 * of the array to reflect this change.
 * 
 * @param stFoodItems The array of food items.
 * @param nFoodItems The number of elements in the array of food items.
 */
void DeleteFoodItem(foodCalorieType stFoodItems[], int *nFoodItems)
{
    int i, nIndex;
    str20 foodItemName;

    viewFoodCalorieChart(stFoodItems, *nFoodItems);

    printf("Which food item do you want to delete?: ");
    scanString(foodItemName, (int)sizeof(str20));

    nIndex = searchFoodItem(stFoodItems, foodItemName, *nFoodItems);

    if (nIndex != -1)
    {
        for (i = nIndex; i < *nFoodItems; i++)
            stFoodItems[i] = stFoodItems[i + 1];

        printf("Food Item \"%s\" deleted.\n\n", foodItemName);

        (*nFoodItems)--; // Decrement the actual value
    }
    else
        printf("Food Item not found...\n\n");
}

/**
 * @brief viewSingleFoodItem displays the food item information for one single item.
 * 
 * @param f The food items struct that contains the information of one food item.
 */
void viewSingleFoodItem(foodCalorieType f)
{
    if (strcmp(f.sIngredient, "") != 0)
    {
        foodChartHeaderFooter(0);
        printf("| %-20s | %-7.2f | %-15s | %-7.2f |\n", f.sIngredient, f.fQuantity,
            f.sUnit, f.fCalories);
        foodChartHeaderFooter(0);
    }
    else
        printf("No food item to display...\n\n");
    
}

/**
 * @brief DeleteIngredient deletes an ingredient from a recipe. It will then move all
 * the elements of the ingredients array to reflect this change.
 * 
 * @param recipe The struct containing the information of one recipe.
 */
void DeleteIngredient(recipeType *recipe)
{
    int i, j;
    str20 sIngredientToDelete;

    // Ask which ingredient to delete
    printf("What ingredient to delete: ");
    scanString(sIngredientToDelete, (int)sizeof(sIngredientToDelete));

    // Locate Ingredient
    for (i = 0; i < recipe->nIngredientCount; i++)
    {
        if (strcmp(recipe->stIngredients[i].sIngredient, sIngredientToDelete) == 0)
        {
            // Deelete Ingredient then shift remaining upwards
            for (j = i; j < recipe->nIngredientCount; j++)
            {
                recipe->stIngredients[j] = recipe->stIngredients[j + 1];
            }

            recipe->nIngredientCount -= 1;
        }
    }

    // End function message
    printf("Ingredient Deleted.");
}

/**
 * @brief SearchByRecipeTitle searches the array of recipes to find a recipe with the
 * same specified string input for the recipe name.
 * 
 * @param recipies The array containing all the recipes.
 * @param sRecipeInput The recipe name to be searched for in the array.
 * @param nCount The number of elements in the array.
 * @return int index of the recipe with the inputted name;
 *             -1 if the recipe isn't found.
 */
int SearchRecipeByTitle(recipeType recipies[], char sRecipeInput[], int nCount)
{
    int i, res = -1;
    int nCheck = 0;

    for (i = 0; i < nCount; i++)
        if (strcmp(recipies[i].sRecipeName, sRecipeInput) == 0 && nCheck == 0)
        {
            nCheck++; // Guarantees that there is indeed only one
            res = i;
        }

    return res;
}

/**
 * @brief AddStep adds an instruction to the recipe.
 * 
 * @param recipe The struct containing the information of the recipe.
 */
void AddStep(recipeType *recipe)
{
    str70 sStepToAdd;

    printf("Step to add: ");
    scanString(sStepToAdd, (int)sizeof(sStepToAdd));

    strcpy(recipe->aInstruct[recipe->nInstructCount + 1], sStepToAdd);
    recipe->nInstructCount += 1;
}

/**
 * @brief DeleteStep deletes an instruction from the recipe, and moves the array
 * of steps to reflect this change.
 * 
 * @param recipe The struct containing the information of the recipe.
 */
void DeleteStep(recipeType *recipe)
{
    int i;
    int nStep = 0;

    printf("Input number of what step to delete: ");
    scanf(" %d", &nStep);

    nStep -= 1;

    for (i = nStep; i < recipe->nInstructCount; i++)
    {
        strcpy(recipe->aInstruct[nStep], recipe->aInstruct[nStep + 1]);
    }

    recipe->nInstructCount -= 1;
}

/**
 * @brief getIngredientCalories calculates for the caloric value of the ingredients
 * in a recipe, searching through the food items array to find a match.
 * 
 * @param r The recipe to be modified.
 * @param f The array of food items.
 * @param nFoodItems The number of elements in the array of food items.
 */
void getIngredientCalories(recipeType *r, foodCalorieType f[], int nFoodItems)
{
    int i, nIndex;

    for (i=0; i<r->nIngredientCount; i++)
    {
        nIndex = searchFoodItem(f, r->stIngredients[i].sIngredient, nFoodItems);

        if (nIndex != -1) //Under the assumption that the food item and ingredient have the same unit
            r->stIngredients[i].fCalories = 
            (f[nIndex].fCalories / f[nIndex].fQuantity) * r->stIngredients[i].fQuantity;
        else 
            r->stIngredients[i].fCalories = 0; //Assume 0 calories if not found
    }
}

/**
 * CalculateCalories computes the total amount of calories of a recipe.
 * This is done through adding all nCalories in stIngredients to its own int declaration
 *
 * @param recipe - The recipe struct used for calorie calculation
 */
void CalculateCalories(recipeType *recipe)
{
    int i;

    recipe->fCalories = 0;

    for (i = 0; i < recipe->nIngredientCount; i++)
    {
        recipe->fCalories += recipe->stIngredients[i].fCalories;
    }
}

/**
 * @brief AddRecipe enables the user to add a recipe into the recipe array.
 * It adds the new recipe into the next vacant slot in the array.
 *
 *
 * @param recipes The Recipe Array Reference
 * @param nCount The number of recipes currently in the recipe array
 * @param f The array of food items
 * @param nFoodItems The number of elements in the array of food items
 */
void AddRecipe(recipeType recipes[], int *nCount, foodCalorieType f[], int nFoodItems)
{
    int nChoice = 0;
    int nIngredient = 0;
    int nStep = 0;
    int nServingSize = 0;

    int nIngredientExit = 0;
    int nStepExit = 0;

    str20 sTempName;

    recipeType recipeToAdd;

    // Initialization of integers in struct
    recipeToAdd.nIngredientCount = 0;
    recipeToAdd.nInstructCount = 0;
    recipeToAdd.nServingSize = 0;

    if (*nCount < maxSize)
    {
        // Recipe name
        do
        {
            // Recode this to include array check
            strcpy(sTempName, "");

            printf("Name of Recipe: ");
            scanString(sTempName, (int)sizeof(sTempName));
        } while (sTempName[0] == '\0');
        strcpy(recipeToAdd.sRecipeName, sTempName);

        // Dish Class
        do
        {
            printf("\n[1] Starter\n");
            printf("[2] Main\n");
            printf("[3] Dessert\n");
            printf("Choose classification: ");
            scanf(" %d", &nChoice);
            getchar();

            switch (nChoice)
            {
            case 1:
                strcpy(recipeToAdd.sDishClass, "Starter");
                break;
            case 2:
                strcpy(recipeToAdd.sDishClass, "Main");
                break;
            case 3:
                strcpy(recipeToAdd.sDishClass, "Dessert");
                break;

            default:
                printf("Invalid input.");
                break;
            }

        } while (nChoice < 1 || nChoice > 3);

        // Ingredients
        do
        {
            nChoice = 0;

            printf("Add Ingredient?");
            printf("\n[1] Yes");
            printf("\n[2] No");
            printf("\nInput: ");
            scanf(" %d", &nChoice);
            getchar();

            switch (nChoice)
            {
            case 1:
                AddIngredient(&recipeToAdd.stIngredients[nIngredient]);
                nIngredient += 1; // Increments once finish input
                recipeToAdd.nIngredientCount += 1;
                break;
            case 2:
                nIngredientExit += 1;
                break;

            default:
                printf("Invalid Input");
                break;
            }

        } while (nIngredientExit == 0);

        getIngredientCalories(&recipes[*nCount], f, nFoodItems);
        CalculateCalories(&recipeToAdd);

        // Instructions
        do
        {
            nChoice = 0;

            printf("Add Step?");
            printf("\n[1] Yes");
            printf("\n[2] No");
            printf("\nInput: ");
            scanf(" %d", &nChoice);
            getchar();

            switch (nChoice)
            {
            case 1:
                AddStep(&recipeToAdd);
                nStep += 1; // Increments once finish input
                recipeToAdd.nInstructCount += 1;
                break;
            case 2:
                nStepExit++;
                break;

            default:
                printf("Invalid Input");
                break;
            }
        } while (nStepExit == 0);

        // Serving Size
        printf("Serving Size: ");
        scanf(" %d", &nServingSize);
        getchar();

        recipeToAdd.nServingSize = nServingSize;

        recipes[*nCount] = recipeToAdd;
        *nCount += 1;
    }
    else
    {
        printf("RecipeArrayFull: Maximum amount of recipes reached.\n");
    }
}

/**
 * @brief DeleteRecipe deletes a recipe from the repository, and moves all
 * the elements of the repository to reflect this change.
 * 
 * @param stRecipes The array of recipes.
 * @param nRecipes The number of elements in the array of recipes.
 */
void DeleteRecipe(recipeType stRecipes[], int *nRecipes)
{
    int i, nIndex;
    str20 recipeName;

    ListRecipeTitles(stRecipes, *nRecipes);

    printf("Which recipe do you want to delete?: ");
    scanString(recipeName, (int)sizeof(str20));

    nIndex = SearchRecipeByTitle(stRecipes, recipeName, *nRecipes);

    if (nIndex != -1)
    {
        for (i = nIndex; i < *nRecipes; i++)
            stRecipes[i] = stRecipes[i + 1];

        printf("Recipe \"%s\" deleted.\n\n", recipeName);

        (*nRecipes)--; // Decrement the actual value
    }
    else
        printf("Recipe not found...\n\n");
}

/**
 * @brief ModifyRecipe asks which recipe should the user modify.
 * After modification, the function then saves the modified recipe back into the recipe array
 *
 * @param recipes - The Recipe Array
 * @param nCount - Number of recipes in the array
 */
void ModifyRecipe(recipeType recipes[], int nCount)
{
    int i;
    int nExit = 0;
    int nRecipe;
    char action;

    str20 sRecipeInput;
    recipeType recipeToModify;

    if (nCount != 0)
    {
        do
        {
            // Introduce the menu
            printf("+------------------------------------------------------+\n");
            printf("|                 MODIFY RECIPE MENU                   |\n");
            printf("+------------------------------------------------------+\n");

            // Display list of Recipes
            ListRecipeTitles(recipes, nCount);

            // Ask which recipe to input
            printf("What Recipe will you modify?\n");
            printf("Recipe: ");
            scanString(sRecipeInput, (int)sizeof(sRecipeInput));

            // set recipeToModify
            for (i = 0; i < nCount; i++)
            {
                if (strcmp(recipes[i].sRecipeName, sRecipeInput) == 0)
                {
                    recipeToModify = recipes[i];
                    nRecipe = i;
                }
            }

            // Display Recipe
            DisplayRecipe(recipeToModify);

            // Ask which modification to do
            DisplayActions(3);

            printf("Your Action: ");
            scanf(" %c", &action);

            do
            {
                switch (action)
                {
                case '1':
                    // Add Ingredient
                    AddIngredient(&recipeToModify.stIngredients[recipeToModify.nIngredientCount + 1]);
                    CalculateCalories(&recipeToModify);
                    break;
                case '2':
                    DeleteIngredient(&recipeToModify);
                    CalculateCalories(&recipeToModify);
                    break;
                case '3':
                    AddStep(&recipeToModify);
                    break;
                case '4':
                    DeleteStep(&recipeToModify);
                    break;
                case '5':
                    // End ModifyRecipe();
                    recipes[nRecipe] = recipeToModify;
                    nExit = 1;
                    break;

                default:
                    printf("Invalid Action...\n");
                    break;
                }

                // Apply Changes
                recipes[nRecipe] = recipeToModify;

            } while (action >= '1' && action <= '5');

        } while (nExit == 0);
    }
    else
    {
        printf("RecipeArrayNull: No recipes present. Please make one first.\n");
    }
}

/**
 * @brief ListRecipeTitles lists all the names of the recipes in alphabetical order.
 * 
 * @param recipies The array of recipes.
 * @param nCount The number of elements in the aray of recipes.
 */
void ListRecipeTitles(recipeType recipies[], int nCount)
{
    int i, j;
    int min;
    str20 tempString;

    str20 aRecipeNames[maxSize]; // string array for recipe names

    if (nCount != 0)
    {
        // Copy all recipe names into aRecipeNames
        for (i = 0; i < nCount; i++)
        {
            strcpy(aRecipeNames[i], recipies[i].sRecipeName);
        }

        // Sort aRecipeNames based on alphabetical order
        for (i = 0; i < nCount - 1; i++)
        {
            min = i;
            for (j = i + 1; j < nCount; j++)
            {
                if (strcmp(aRecipeNames[j], aRecipeNames[min]) < 0)
                {
                    min = j;
                }
            }

            if (min != i)
            {
                strcpy(tempString, aRecipeNames[i]);
                strcpy(aRecipeNames[i], aRecipeNames[min]);
                strcpy(aRecipeNames[min], tempString);
            }
        }

        printf("\n\n\n");
        // display sorted aRecipesList in CMD
        for (i = 0; i < nCount; i++)
        {
            printf("Recipe No. %d: %20s\n", i + 1, aRecipeNames[i]);
        }

        printf("\n\n");
    }
    else
        printf("No recipes to display...\n\n");
}

/**
 * @brief DisplayRecipe displays all the information of one recipe.
 * 
 * @param recipe The struct containing the information of the recipe.
 */
void DisplayRecipe(recipeType recipe)
{
    int i;

    if (strcmp(recipe.sRecipeName, "") !=0)
    {
        // Recipe and dish class
        printf("|----------- Recipe -----------|\n");
        printf("\n%s", recipe.sRecipeName);
        printf("\n%s",recipe.sDishClass);
        printf("\nCalorie Count: %-.2f", recipe.fCalories);

        printf("\n|------- Dish Class ---------|\n");
        printf("\n%s\n", recipe.sDishClass);

        printf("\n|------- Ingredients --------|\n");
        // Ingredients
        for (i = 0; i < recipe.nIngredientCount; i++)
        {
            printf("%.2f %s %s\n",
                recipe.stIngredients[i].fQuantity,
                recipe.stIngredients[i].sUnit,
                recipe.stIngredients[i].sIngredient);
        }

        printf("\n|--------- Process ----------|\n");
        // Steps
        for (i = 0; i < recipe.nInstructCount; i++)
        {
            printf("%s\n", recipe.aInstruct[i]);
        }

        printf("\n|--------- Serving ----------|\n");
        // Serving Size
        printf("Good for %d servings\n", recipe.nServingSize);
    }
    else
        printf("No recipe to print!\n\n");
    
}

/**
 * @brief ScanRecipeByIngredient searches the array of recipes that contain a specified
 * ingredient, and then displays all the recipes that use that said ingredient.
 * 
 * @param recipies The array of recipes.
 * @param nCount The number of elements in the array of recipes.
 */
void ScanRecipeByIngredient(recipeType recipies[], int nCount)
{
    int i, j;
    int nMatchedCount = 0;

    str20 sIngredient;
    recipeType matchedRecipies[maxSize];

    // Ask user to input recipe name to display
    printf("What ingredient are we looking for in a recipe?\n");
    printf("Recipe: ");
    scanString(sIngredient, (int)sizeof(sIngredient));

    // Compile All Matched Recipies into matchedRecipies
    for (i = 0; i < nCount; i++)
    {
        for (j = 0; j < recipies[i].nIngredientCount; j++)
        {
            if (strcmp(sIngredient, recipies[i].stIngredients[j].sIngredient) == 0)
            {
                matchedRecipies[nMatchedCount] = recipies[i];
                nMatchedCount += 1;
            }
        }
    }

    // Display All Recipies one by one
    ScanRecipies(matchedRecipies, nMatchedCount);

    // Uncomment Display Recipe Function once implemented
    // Add all recipies with matching ingredients into array

    //DisplayRecipe();
}

/**
 * @brief ScanRecipes displays the recipes in the array one by one. The user is allowed
 * to scroll through the next or previous recipes.
 * 
 * @param recipies 
 * @param nCount 
 */
void ScanRecipies(recipeType recipies[], int nCount)
{
    int i;
    char action;

    int nExit = 0;

    i = 0;
    while ((i < nCount || nExit != 0) && nCount != 0)
    {
        DisplayRecipe(recipies[i]);

        // Scanf input for action
        strcpy(&action, "");
        printf("(1) Next, (2) Previous, (0) Exit: ");
        scanf(" %c%*[^\n]", &action);

        if (action == '1')
            i++;
        else if (action == '2' && i != 0)
            i--;
        else if (action == '0')
        {
            // Return to View Recipies Menu
            nExit = 1;
        }
        else
            printf("Invalid Input");

    } 

    if (nCount == 0)
        printf("No recipes to display...\n\n");
}

/**
 * @brief DisplayIngredient display the information of the ingredient, as well
 * as calculating the quantity of each ingredient based on the number of servings.
 * 
 * @param ingredient The ingredient to be displayed.
 * @param nMultiplier The multiplier to be applied to the quantity of calories.
 */
void DisplayIngredient(foodCalorieType ingredient, int nMultiplier)
{
    float fcal = ingredient.fQuantity * nMultiplier;
    printf("- %.2f %s %s\n", fcal, ingredient.sUnit, ingredient.sIngredient);
}

/**
 * @brief GenerateShoppingList generates a shopping list of the ingredients included in a recipe.
 * The total units of each ingredient is based on how many people are being served.
 *
 * @param recipes
 * @param nCount
 */
void GenerateShoppingList(recipeType recipes[], int nCount)
{
    int i;
    int nServing;
    int nCheck = 0;
    str20 sRecipeName;

    recipeType stRecipeToDisplay;

    // Display all Recipes
    ListRecipeTitles(recipes, nCount);

    getchar();

    // Ask which recipe to display ingredients
    printf("Choose Recipe to make shopping list: ");
    scanString(sRecipeName, (int)sizeof(sRecipeName));

    // Ask how many people are being served
    printf("How many people are being served?: ");
    scanf(" %d", &nServing);

    for (i = 0; i < nCount; i++)
    {
        if (strcmp(recipes[i].sRecipeName, sRecipeName) == 0 && nCheck == 0)
        {
            stRecipeToDisplay = recipes[i];
            nCheck += 1;
        }
    }

    // Display ingredients needed
    for (i = 0; i < stRecipeToDisplay.nIngredientCount; i++)
    {
        DisplayIngredient(stRecipeToDisplay.stIngredients[i], nServing);
    }
}

/**
 * SelectRandomRecipe outputs a random recipe within an array of recipes with a specific dish class.
 *
 * @param recipes - Recipe array needed for randomization
 * @param nCount - The number of recipes
 * @param sTag - Dish class Tag used to filter recipes
 *
 * @return recipeType - A random recipe with the Dish Class of sTag
 */
recipeType SelectRandomRecipe(recipeType recipes[], int nCount, char sTag[])
{
    int i;
    int nRandom;
    int nFlagged = 0;

    recipeType rtRecipe;
    recipeType arrRecipes[maxSize];

    // Put all recipes tagged "sTag" into array
    for (i = 0; i < nCount; i++)
    {
        if (strcmp(recipes[i].sDishClass, sTag) == 0)
        {
            arrRecipes[nFlagged] = recipes[i];
            nFlagged += 1;
        }
    }

    // Randomly Select Recipe
    nRandom = (rand() % (nFlagged - 0 + 1) + 0);
    rtRecipe = arrRecipes[nRandom];

    return rtRecipe;
}

/**
 * SelectRandomFoodItem outputs a foodCalorieType Food Item
 * within an array of foodCalorieType less than or equal to
 * a set amount of calories
 *
 * @param foodItems - Array of Food Items
 * @param nCount - Number of Food Items
 * @param nCaloriesLeft - Set amount of calories
 *
 * @return foodCalorieType - The random foodCalorieType
 */
foodCalorieType SelectRandomFoodItem(foodCalorieType foodItems[], int nCount, float nCaloriesLeft)
{
    int i;
    int nRandom;
    int nFlagged = 0;

    foodCalorieType foodItem;
    foodCalorieType stFoodItems[maxSize];

    for (i = 0; i < nCount; i++)
    {
        if (foodItems[i].fCalories <= nCaloriesLeft)
        {
            stFoodItems[nFlagged] = foodItems[i];
            nFlagged += 1;
        }
    }

    // Randomly Select Recipe
    nRandom = (rand() % (nFlagged - 0 + 1) + 0);
    foodItem = stFoodItems[nRandom];

    return foodItem;
}

/**
 * RecipeContainsCheck checks if the recipe array contains one recipe with a specific dish class tag.
 *
 * @param recipes - Recipe array needed for randomization
 * @param nCount - The number of recipes
 * @param sTag - Dish class Tag used to filter recipes
 *
 * @return int - 1 if a recipe exists with a dish class of tag sTag, 0 if not.
 */
int RecipeContainsCheck(recipeType recipes[], int nCount, char sTag[])
{
    int i;
    int nFlagged = 0;

    //recipeType rtRecipe;
    //recipeType arrRecipes[maxSize];

    // Put all recipes tagged "sTag" into array
    for (i = 0; i < nCount; i++)
    {
        if (strcmp(recipes[i].sDishClass, sTag) == 0)
        {
            //arrRecipes[nFlagged] = recipes[i];
            nFlagged += 1;
        }
    }

    if (nFlagged == 0)
        return 0;
    else
        return 1;
}

/**
 * @brief FoodItemContainsCheck checks if the food item array contains a food item below or
 * equal to the target number of calories.
 * 
 * @param recipes The array of recipes.
 * @param nCount The number of elements in the array of recipes.
 * @param fCalNeeded The target amount of calories.
 * @return int 0 if there are no food items below or equal to the calorie target;
 *             1 if there is at least 1 food item below or equal to the calorie target.
 */
int FoodItemContainsCheck(foodCalorieType recipes[], int nCount, float fCalNeeded)
{
    int i;
    int nFlagged = 0;

    // Tag all Food Items equal or below fCalNeeded
    for (i = 0; i < nCount; i++)
    {
        if (recipes[i].fCalories <= fCalNeeded)
        {
            nFlagged += 1;
        }
    }

    if (nFlagged == 0)
        return 0;
    else
        return 1;
}

/**
 * @brief Recommendation provides the necessary recipes and food item either at or below a specified calorie range.
 * All chosen recipes and food items are randomized. Every recommendation is unique
 *
 * @param recipes - The Recipe Array Reference
 * @param nRecipeCount - Number of recipes currently in the array
 * @param foodList - The Food Items Array Reference
 * @param nFoodCount - Number of food items currently in the array
 */
void Recommendation(recipeType recipes[], int nRecipeCount, foodCalorieType foodList[], int nFoodCount)
{
    float fCalories = 0;
    float fCalTarget;

    int nCheck = 0;
    int nNextRecipe = 0;
    int nFound = 0;
    int nFoodItemCheck = 0;
    int i;
    char action;

    recipeType stMain;
    recipeType stStarter;
    recipeType stDessert;
    foodCalorieType stFoodItem;

    int actionCheck[4] = {0, 0, 0, 0};

    printf("Target Calorie Limit: ");
    scanf(" %f", &fCalTarget);

    srand(time(NULL));

    for (i=0; i<nRecipeCount; i++)
        getIngredientCalories(&recipes[i], foodList, nFoodCount);

    // Search through recipies with tag Main
    // Randomly Select a Main Recipe
    if (RecipeContainsCheck(recipes, nRecipeCount, "Main") != 0)
    {
        stMain = SelectRandomRecipe(recipes, nRecipeCount, "Main");
        fCalories += stMain.fCalories;

        actionCheck[nCheck] = 1;

        //nMainCheck = 1;
        nCheck += 1;
    }

    // If nCalTarget is not reached
    // Search through recipies with tag Starter
    if (fCalories < fCalTarget)
    {
        nFound = 1;
        if (RecipeContainsCheck(recipes, nRecipeCount, "Starter") != 0)
        {
            stStarter = SelectRandomRecipe(recipes, nRecipeCount, "Starter");
            fCalories += stStarter.fCalories;

            actionCheck[nCheck] = 2;

            //nStarterCheck = 1;
            nCheck += 1;
        }

        // If nCalTarget is not reached
        // Search through recipies with tag Dessert
        if (fCalories < fCalTarget)
        {
            if (RecipeContainsCheck(recipes, nRecipeCount, "Dessert") != 0)
            {
                stDessert = SelectRandomRecipe(recipes, nRecipeCount, "Dessert");
                fCalories += stDessert.fCalories;

                actionCheck[nCheck] = 3;

                //nDessertCheck = 1;
                nCheck += 1;
            }

            // If still not enough
            // food calories bruv
            if (fCalories < fCalTarget)
            {
                if (FoodItemContainsCheck(foodList, nFoodCount, fCalTarget - fCalories) != 0)
                {
                    stFoodItem = SelectRandomFoodItem(
                        foodList,
                        nFoodCount, fCalTarget - fCalories);
                    fCalories += stFoodItem.fCalories;

                    actionCheck[nCheck] = 4;

                    nCheck += 1;
                }
            }
        }
    }

    // THEN display istg
    while (nNextRecipe < nCheck)
    {
        printf("Type 1 to display recipes: ");
        scanf(" %c", &action);

        if (action == '1')
        {
            switch (actionCheck[nNextRecipe])
            {
            case 1:
                DisplayRecipe(stMain);
                break;
            case 2:
                DisplayRecipe(stStarter);
                break;
            case 3:
                DisplayRecipe(stDessert);
                break;
            case 4:
                viewSingleFoodItem(stFoodItem);
                break;

            default:
                break;
            }

            nNextRecipe += 1;
        }
        else
        {
            printf("Invalid Input.");
        }

    }

    if (nFound != 1 && nFoodItemCheck != 1)
        printf("Recipe not found\n\n");
}

/**
 * @brief SaveCalorieInfo exports all the foodItem information onto a text file.
 * 
 * @param foodInfo The array of food items.
 * @param n The number of elements in the array of food items.
 */
void SaveCalorieInfo(foodCalorieType foodInfo[], int n)
{
    int i;
    str20 sFilename;
    FILE *ptr;

    // Ask user to open which file
    printf("Enter filename\n");
    printf("Include the .txt file extension: ");
    scanString(sFilename, (int)sizeof(sFilename));

    ptr = fopen(sFilename, "w");

    if (ptr)
    {
        for (i = 0; i < n; i++)
        {
            fprintf(ptr, "%s\n", foodInfo[i].sIngredient);
            fprintf(ptr, "%.2f %s %.2f\n",
                    foodInfo[i].fQuantity,
                    foodInfo[i].sUnit,
                    foodInfo[i].fCalories);

            fprintf(ptr, "\n");
        }
        fclose(ptr);
    }
    else
        printf("File not found...\n\n");
}

/**
 * @brief fScanString is a variation of the scanString function, made specifically
 * to scan strings with spaces within text files.
 * 
 * @param ptr The file pointer.
 * @param string The address where the string will be stored.
 * @return int 1 if the string is successfully scanned.
 *             0 if the string isn't scanned successfully; the file has reached the end.
 */
int fscanString(FILE *ptr, char string[])
{
    char ch;
    int i = 0;
    int x;
    while ((x = fscanf(ptr, "%c", &ch)) == 1 && ch != EOF && ch != '\n')
    {
        string[i] = ch;
        i++;
    }
    string[i] = '\0';

    if (x == 1) // if (ch != EOF)
        return 1;
    else
        return 0;
}

/**
 * @brief LoadCalorieInfo loads the food calorie information from a text file, and stores
 * it as elements of the array of food items.
 * 
 * @param foodInfo The array of food items.
 * @param nCount The number of elements in the array of food items.
 */
void LoadCalorieInfo(foodCalorieType foodInfo[], int *nCount)
{
    // Ask user to open which file
    int x, nIndex, nChoice;
    str20 sFilename;
    foodCalorieType foodItemTemp;
    FILE *ptr;

    // Ask user to open which file
    printf("Enter filename\n");
    printf("Include the .txt file extension: ");
    scanString(sFilename, (int)sizeof(sFilename));

    ptr = fopen(sFilename, "r");

    // Checks if file exists
    if (ptr)
    {
        // Scans Line by Line as per SaveCalorieInfo has been formatted
        // If info is found, prompt user to either skip or read the file into current foodInfo database
        do
        {
            x = fscanString(ptr, foodItemTemp.sIngredient);

            if (x)
            {
                nIndex = searchFoodItem(foodInfo, foodItemTemp.sIngredient, *nCount);
                fscanf(ptr, "%f %s %f ", &foodItemTemp.fQuantity, foodItemTemp.sUnit, &foodItemTemp.fCalories);

                viewSingleFoodItem(foodItemTemp);

                printf("\n\n\n\n");

                if (nIndex != -1)
                {
                    printf("Overwrite food item?\n");
                    printf("\"%s\"\n", foodItemTemp.sIngredient);
                    printf("Yes (1) | No (2): ");
                }
                else
                    printf("Read (1) or skip (2) food item?: ");
                scanf("%d", &nChoice);

                switch (nChoice)
                {
                case 1:
                    // read the file
                    if (nIndex != -1) // If the food item exists in the box; overwritting
                        foodInfo[nIndex] = foodItemTemp;
                    else if (nIndex == -1 && *nCount < maxSize) // Adds the contents read into the end of the foodInfo array using nCount;
                    {
                        foodInfo[*nCount] = foodItemTemp;
                        (*nCount)++; // because CS counting
                    }
                    else if (*nCount >= maxSize)
                        printf("Error: Array is full!\n");
                    break;
                case 2:
                    printf("Food Item \"%s\" skipped...\n\n\n", foodItemTemp.sIngredient);
                    break;
                default:
                    printf("Invalid input...\n\n\n");
                    break;
                }
                // As variable name states, dump the extra \n
            }
        } while (x);

        fclose(ptr);
    } // Loops until EOF is found
    else
        printf("File not found...\n\n");
}

/**
 * @brief ExportRecipes loads the recipe information to a text file.
 * 
 * @param recipes The array of recipes.
 * @param n The number of elements in the array of recipes.
 */
void ExportRecipes(recipeType recipes[], int n)
{
    int i, j;
    str20 sFilename;
    FILE *ptr;

    // Ask user to open which file
    printf("Enter filename\n");
    printf("Include the .txt file extension: ");
    scanString(sFilename, (int)sizeof(sFilename));

    ptr = fopen(sFilename, "w");

    // Checks if file exists
    if (ptr)
    {
        // The part where you input everything according to the format
        for (i = 0; i < n; i++)
        {
            fprintf(ptr, "%s\n", recipes[i].sRecipeName);
            fprintf(ptr, "%d %s\n", recipes[i].nServingSize, recipes[i].sDishClass);
            fprintf(ptr, "Ingredients %d\n", recipes[i].nIngredientCount);

            for (j = 0; j < recipes[i].nIngredientCount; j++)
                fprintf(ptr, "%.2f %s %s\n", recipes[i].stIngredients[j].fQuantity,
                        recipes[i].stIngredients[j].sUnit, recipes[i].stIngredients[j].sIngredient);

            fprintf(ptr, "Steps %d\n", recipes[i].nInstructCount);

            for (j = 0; j < recipes[i].nInstructCount; j++)
                fprintf(ptr, "%s\n", recipes[i].aInstruct[j]);

            fprintf(ptr, "\n");
        }

        fclose(ptr);
    }
    else
        printf("File not found...\n\n");
}

/**
 * @brief ImportRecipes loads the recipe information from a text file, and stores
 * it as elements of the array of recipes.
 * 
 * @param recipes The array of recipes.
 * @param n The number of elements in the array of recipes.
 * @param f The array of food items.
 * @param nFoodItems The number of elements in the array of food items.
 */
void ImportRecipes(recipeType recipes[], int *n, foodCalorieType f[], int nFoodItems)
{
    int j, x, nIndex, nChoice;
    str20 sFilename, dump;
    recipeType buffer;
    FILE *ptr;
    char cNewlineDump;

    // Ask user to open which file
    printf("Enter filename\n");
    printf("Include the .txt file extension: ");
    scanString(sFilename, (int)sizeof(sFilename));

    ptr = fopen(sFilename, "r");

    // Checks if file exists
    if (ptr)
    {
        // Scans Line by Line as per ExportRecipes has been formatted
        // If info is found, prompt user to either skip or read the file into current foodInfo database

        do
        {
            x = fscanString(ptr, buffer.sRecipeName);

            if (x)
            {
                nIndex = SearchRecipeByTitle(recipes, buffer.sRecipeName, *n);

                fscanf(ptr, "%d %s ", &buffer.nServingSize, buffer.sDishClass);

                fscanf(ptr, "%s %d ", dump, &buffer.nIngredientCount);
                // word "ingredients" goes to dump

                for (j = 0; j < buffer.nIngredientCount; j++)
                {
                    fscanf(ptr, "%f %s ", &buffer.stIngredients[j].fQuantity,
                           buffer.stIngredients[j].sUnit);
                    fscanString(ptr, buffer.stIngredients[j].sIngredient);
                }

                fscanf(ptr, "%s %d ", dump, &buffer.nInstructCount);

                for (j = 0; j < buffer.nInstructCount; j++)
                    fscanString(ptr, buffer.aInstruct[j]);

                fscanf(ptr, "%c", &cNewlineDump); // Get rid of extra \n

                getIngredientCalories(&buffer, f, nFoodItems);
                CalculateCalories(&buffer);

                printf("\n\n\n\n");
                DisplayRecipe(buffer);
                if (nIndex != -1)
                {
                    printf("\n\nOverwrite recipe?\n");
                    printf("Yes (1) | No (2): ");
                }
                else // if (nIndex == 0 || n == 0)
                    printf("\n\nRead (1) or skip (2) recipe?: ");
                scanf("%d", &nChoice);
                getchar();

                switch (nChoice)
                {
                case 1:
                    // read the file
                    if (nIndex != -1) // If the recipe is already in the array
                    {
                        recipes[nIndex] = buffer;
                    }
                    else if (nIndex == -1 && *n < maxSize)
                    // Adds the contents read into the end of the recipeType array using nCount
                    {
                        recipes[*n] = buffer;
                        (*n)++;
                    }
                    break;
                case 2:
                    printf("Recipe \"%s\" skipped...\n\n\n", buffer.sRecipeName);
                    break;
                default:
                    printf("Invalid input...\n\n\n");
                    break;
                }
            }

        } while (x);
        // Loops until EOF is found

        fclose(ptr);
    }
    else
        printf("File not found...\n\n");
}
