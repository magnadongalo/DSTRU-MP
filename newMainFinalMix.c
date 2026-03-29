#include "funcv3.c"

int main()
{
    // Action inputs
    char action;
    int nExit = 0;
    int nUpdateMenu = 0;
    int nAccessMenu = 0;
    int nCheckVerified;
    int nNextPage = 0;

    str20 sRecipeInput;

    recipeType stRecipes[maxSize];
    foodCalorieType stFoodList[maxSize];

    int nRecipes = 0;
    int nFoodItems = 0;
    int nRes;

    srand(time(NULL));

    do
    {
        // Starts in the Main Menu
        // Display options
        DisplayActions(0);

        // clear char action
        strcpy(&action, "");

        printf("Your Action: ");
        scanf(" %c%*[^\n]", &action); // safeguard to only detect first char if multiple are inputted

        switch (action)
        {
        case '1': // Configure Recipes
            nCheckVerified = PasswordCheck(); // use fucntion to verify access

            if (nCheckVerified == 1) // access granted for configuration
            {
                printf("\nVerified!!!\n");

                // Keep value at 0 to prevent Update Menu loop from ending
                nUpdateMenu = 0;

                do
                {
                    if (!nNextPage)
                        DisplayActions(1);
                    else if (nNextPage)
                        DisplayActions(4);

                    printf("Your Action: ");
                    scanf(" %c", &action);
                    getchar();

                    switch (action)
                    {
                    case '1': // Add Food-Calorie/List Recipe Titles
                        if (!nNextPage)
                            AddFoodCalorieInfo(stFoodList, &nFoodItems);
                        else if (nNextPage)
                            ModifyRecipe(stRecipes, nRecipes);
                        break;
                    case '2': // View Food-Calorie ChartS/Scan Recipes
                        if (!nNextPage)
                            DeleteFoodItem(stFoodList, &nFoodItems);
                        else if (nNextPage)
                            ListRecipeTitles(stRecipes, nRecipes);
                        break;
                    case '3': // Save Calorie Info/Scan By Ingredient
                        if (!nNextPage)
                            viewFoodCalorieChart(stFoodList, nFoodItems);
                        else if (nNextPage)
                            ScanRecipies(stRecipes, nRecipes);
                        break;
                    case '4': // Load Calorie Info/Search By Title
                        if (!nNextPage)
                            SaveCalorieInfo(stFoodList, nFoodItems);
                        else if (nNextPage)
                            ScanRecipeByIngredient(stRecipes, nRecipes);
                        break;
                    case '5': // Add Recipe/Import Recipes
                        if (!nNextPage)
                            LoadCalorieInfo(stFoodList, &nFoodItems);
                        else if (nNextPage)
                        {
                            ListRecipeTitles(stRecipes, nRecipes);

                            // Ask user to input recipe name to display
                            printf("What Recipe will you view?\n");
                            printf("Recipe: ");
                            scanString(sRecipeInput, (int)sizeof(sRecipeInput));

                            nRes = SearchRecipeByTitle(stRecipes, sRecipeInput, nRecipes);

                            DisplayRecipe(stRecipes[nRes]);
                        }
                        break;
                    case '6': // Delete Recipe/Export Recipes
                        if (!nNextPage)
                            AddRecipe(stRecipes, &nRecipes, stFoodList, nFoodItems);
                        else if (nNextPage)
                            ImportRecipes(stRecipes, &nRecipes, stFoodList, nFoodItems);
                        break;
                    case '7': //Scan Recipes
                        if (!nNextPage)
                            DeleteRecipe(stRecipes, &nRecipes);
                        else if (nNextPage)
                            ExportRecipes(stRecipes, nRecipes);
                        break;
                    case '0':
                        printf("Returning to Main Menu...\n");
                        nUpdateMenu = 1;
                        break;
                    case 'X':
                    case 'x':
                        if (!nNextPage)
                            nNextPage++;
                        else if (nNextPage)
                            nNextPage--;
                        break;
                    default:
                        break;
                    }

                } while (nUpdateMenu != 1);
            }
            else // access denied
            {
                printf("\nInvalid username or password!\n");
                printf("Returning to menu...\n\n");

                // this returns to menu
            }

            break;

        case '2': // View a recipe
            // Keep value at 0 to prevent Update Menu loop from ending
            nAccessMenu = 0;

            do
            {
                DisplayActions(2);
                printf("Your Action: ");
                scanf(" %c", &action);

                switch (action)
                {
                case '1':
                    ImportRecipes(stRecipes, &nRecipes, stFoodList, nFoodItems);
                    break;
                case '2': // ListAllRecipes();
                    ListRecipeTitles(stRecipes, nRecipes);
                    break;
                case '3':
                    ScanRecipies(stRecipes, nRecipes);
                    break;
                case '4': // SearchRecipeByTitle();
                    if (nRecipes != 0)
                    {
                        ListRecipeTitles(stRecipes, nRecipes);

                        // Ask user to input recipe name to display
                        printf("What Recipe will you view?\n");
                        printf("Recipe: ");
                        scanString(sRecipeInput, (int)sizeof(sRecipeInput));

                        nRes = SearchRecipeByTitle(stRecipes, sRecipeInput, nRecipes);

                        DisplayRecipe(stRecipes[nRes]);
                    }
                    else 
                        printf("No recipes to display...\n\n");
                break;
                case '5': // SearchRecipeByIngredient();
                    ScanRecipeByIngredient(stRecipes, nRecipes);
                    break;
                case '6': // GenerateShoppingList();
                    GenerateShoppingList(stRecipes, nRecipes);
                    break;
                case '7': // Recommendation();
                    Recommendation(stRecipes, nRecipes, stFoodList, nFoodItems);
                    break;
                case '8': // Returns to main menu
                    printf("Returning to Main Menu...\n");
                    nAccessMenu = 1;
                    break;

                default:
                    break;
                }

            } while (nAccessMenu != 1);

            break;
        case '3': // Exit the program

            printf("You have chosen [3] Close Program");
            printf("\nThank you, and have a nice day!");

            nExit = 1;
            break;
        default:
            printf("Invalid action!\n\n");
            break;
        }
    } while (nExit == 0); // stop do-while loop if nExit is specified

    return 0;
}
