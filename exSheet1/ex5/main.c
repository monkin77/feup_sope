#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    //alineaA(argc, argv, envp);

    alineaB(argc, argv, envp);

    return 0;
}

void alineaA(int argc, char *argv[], char *envp[])
{
    printf("Command line arguments: \n");
    for (int i = 0; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }
    printf("\n");

    printf("Shell's environment variables: \n");
    for (int i = 0; (envp[i]) != NULL; i++)
    {
        printf("%s \n", envp[i]);
    }
    printf("\n");
}

void alineaB(int argc, char *argv[], char *envp[])          // Since this is done in C I have to iterate all chars. A simple solution would be to use C++
{
    *argv[0] = " ";     // changed the first character of the first argument (main) in order to not match any env. variable
    char *currString;
    char* envOnArgs[argc];
    int currIdx = 0;
    for (int i = 0; envp[i] != NULL; i++)       // iterate all the env. variables
    {
        for (int a = 0; a < argc; a++)      // iterate all the cmd args
        {
            //printf("Pair: %s %s \n", envp[i], argv[a]);
            for (int c = 0; c < sizeof(envp[i]) / sizeof(char); c++)        // iterate all the chars on the environment variable
            {
                if(envp[i][c] == '='){      // if the chars from the env. variable are equal to the argument until they reached the '=' (key value) than save
                    envOnArgs[currIdx] = envp[i];
                    currIdx += 1;
                }
                if (envp[i][c] == argv[a][c]){
                    /*
                    if(c == ((sizeof(envp[i]) / sizeof(char))- 1) ){
                        envOnArgs[currIdx] = envp[i];
                        currIdx += 1;
                    }*/
                    continue;
                }
                else{
                    break;
                }
            }
        }
    }
    printf("Environment variables on cmd args: \n");
    for(int idx = 0; envOnArgs[idx] != NULL; idx++){
        printf("%s \n", envOnArgs[idx]);
    }
}