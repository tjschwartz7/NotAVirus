#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

/*************/
/*The Amazing*/
/*Not A Virus*/
/*************/


//Don't ever run this program.
//Its a bad idea.

DWORD WINAPI BadIdea(LPVOID lpParam);
void ErrorHandler(LPCTSTR lpszFunction);

//Consider moving some bytes to the heap hahahaha
int main()
{
    //If you manage to crash this program because you reached the end of the array...
    //Congratulations. You must be running this on a supercomputer.
    DWORD*   dwThreadIdArray = new DWORD(10000);
    HANDLE  hThreadArray[10000];
    int iter = 0;

    //The ride never ends
    while(true)
    {

        if (iter >= 10000)
        {
            std::cout << "Congratulations. You did it. Hooray. Your reward is..." << std::endl;
            break;
        }
        //Start the fire
        hThreadArray[iter] = CreateThread(
            NULL,                   // default security attributes
            0,                      // use default stack size  
            BadIdea,       // thread function name
            NULL,                   // argument to thread function 
            0,                      // use default creation flags 
            &*dwThreadIdArray);     // returns the thread identifier 


        // Check the return value for success.
        // If CreateThread fails, terminate execution. 
        // This will automatically clean up threads and memory. 
        if (hThreadArray[iter] == NULL)
        {
            ErrorHandler(TEXT("LOL"));
            //You thought
            //ExitProcess(3);
        }

        //Next thread :)
        iter++;
    } // End of main thread creation loop.

    //There's no thread joining code 
    //because I have no intention of resolving these threads.

    return 0;
}


//There was never any intention of this function returning
DWORD WINAPI BadIdea(LPVOID lpParam)
{
    //Each thread allocates 100^3 DOUBLES from the heap...
    //At this rate, you might need a bit more memory...
    double* arr = new double(100*100*100);
    while (true)
    {
        //This is a sufficiently inefficient way to do this
        for (int i = 0; i < 100; i++)
        {
            //This loop only exists to make the program run more than it needs to
            for (int j = 0; j < 100; j++)
            {
                //This loop exists
                for (int k = 0; k < 100; k++)
                {
                    //Yucky
                    //Takes advantage of locality to ensure that no two doubles accessed are adjacent to each other in memory.
                    //This makes the program take longer because now the program has to perform another cache access each time instead of storing anything
                    //of value in its cache >:)
                    arr[i * k + k] = j * i * .0111122233344 * 1.51212424256575 * 2.7512354124324*12.12345678912345678;
                    arr[i * k + k] = sqrt(arr[i * k + k]);
                }
            }
        }
    }

    //This is a good PC benchmark;
    //Can it reach this return statement
    //before the singularity happens?
    return 0; 
}


/*What errors?*/
void ErrorHandler(LPCTSTR lpszFunction)
{
    // Retrieve the system error message for the last-error code.

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    // Display the error message.

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    // Free error-handling buffer allocations.

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}