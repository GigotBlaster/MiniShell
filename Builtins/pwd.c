#include "../minishell.h"

//PDW : Print Working Directory

int main() 
{
    char cwd[SIZE_PATH]; // cwd = current_working_directory
    
	if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd); 
    else 
	{
        perror("getcwd() error");
        return 1;
    }
    return 0;
}

//return : "/mnt/nfs/homes/npetitpi/Documents/Stud/GigotGit/MiniShell/Builtins"