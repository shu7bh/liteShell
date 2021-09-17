#include "prompt.h"
#include "input.h"
#include "runCommand.h"
#include "headers.h"

int main()
{
    setPromptVar();
    setInputVar();

    char* token;

    while (1)
    {
        prompt();
        char* inputBuf = input();

        while ((token = strtok_r(inputBuf, ";", &inputBuf)))
            runCommand(token);
    }
}
