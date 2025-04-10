
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    const char number[] = "123.456"; 
    int c, n, d;

    //if both conversions from c-string to integers can take place
    if(characteristic(number, c) && mantissa(number, n, d))
    {
        //do some math with c, n, and d
        cout<<"c: "<<c<<endl;
        cout<<"n: "<<n<<endl;
        cout<<"d: "<<d<<endl;
    }
    else //at least one of the conversions failed
    {
        //handle the error on input
        cout<<"Error on input"<<endl;
    }

    //room for 9 characters plus the null terminating character
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;

    //initialize the values
    c1 = 1;
    n1 = 1;
    d1 = 2;

    c2 = 2;
    n2 = 2;
    d2 = 3; 

    //if the c-string can hold at least the characteristic
    if(add(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on add"<<endl;
    }

    if(divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }

    return 0;
} 
//--
bool characteristic(const char numString[], int& c)
{
    int placeCounter = 0;
    bool foundDecimal = false;
    bool isNeg = false;
    int firstNonWhitespaceCounter = 0;
    int terminatorFinder = 0;
    while (true)
    {
        if (numString[terminatorFinder] == '\0')
            break;
        terminatorFinder++;
    }
    for (int negativeFinder = 0; negativeFinder < terminatorFinder; negativeFinder++)
    {
        if (numString[negativeFinder] == '-')
            isNeg = true;
        else if (numString[negativeFinder] != ' ')
        {
            firstNonWhitespaceCounter = negativeFinder;
            break;
        }
    }
    int blah = sizeof(numString);
    int blah2 = terminatorFinder;
    int cleansedNumStringSize = 0;
    char* cleansedNumString;
    if (firstNonWhitespaceCounter != 0)
    {
        cleansedNumString = new char[terminatorFinder - firstNonWhitespaceCounter];
        int cleansedNumStringIterator = 0;
        for (int whitespaceIterator = firstNonWhitespaceCounter; whitespaceIterator < terminatorFinder; whitespaceIterator++)
        {
            cleansedNumString[cleansedNumStringIterator] = numString[whitespaceIterator];
            cleansedNumStringSize++;
            cleansedNumStringIterator++;
        }
    }
    else
    {
        cleansedNumString = new char[terminatorFinder];
        for (int numStringIterator = 0; numStringIterator < terminatorFinder; numStringIterator++)
        {
            cleansedNumString[numStringIterator] = numString[numStringIterator];
        }
        cleansedNumStringSize = terminatorFinder;
    }
    for (int decFinder = 0; decFinder < cleansedNumStringSize; decFinder++)
    {
        if (cleansedNumString[decFinder] == '.')
        {
            placeCounter = decFinder;
            foundDecimal = true;
            break;
        }
    }
    if (foundDecimal == false)
    {
        placeCounter = cleansedNumStringSize - 1;
    }
    char* slicedCopy = new char[placeCounter];
    int characteristic = 0;
    for (int intTransposer = 0; intTransposer < placeCounter; intTransposer++)
    {
        slicedCopy[intTransposer] = cleansedNumString[intTransposer];
    }
    int powerMultiplier = 1;
    for (int charToIntIterator = placeCounter - 1; charToIntIterator >= 0; charToIntIterator--)
    {
        characteristic = characteristic + (slicedCopy[charToIntIterator] - '0') * powerMultiplier;
        powerMultiplier *= 10;
    }
    if (isNeg)
        characteristic *= -1;
    c = characteristic;
    return true;
}
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    int placeCounter = 0;
    bool foundDecimal = false;
    int terminatorFinder = 0;
    while (true)
    {
        if (numString[terminatorFinder] == '\0')
            break;
        terminatorFinder++;
    }
    int numStringLength = terminatorFinder;
    for (int decFinder = 0; decFinder < numStringLength; decFinder++)
    {
        if (numString[decFinder] == '.')
        {
            placeCounter = decFinder;
            foundDecimal = true;
            break;
        }
    }
    placeCounter++;
    if (foundDecimal == false)
    {
        placeCounter = numStringLength - 1;
    }
    char* slicedCopy = new char[numStringLength - placeCounter];
    int mantissa = 0;
    int denomSize = 0;
    int slicedCopyIterator = 0;
    for (int intTransposer = placeCounter; intTransposer < numStringLength; intTransposer++)
    {
        if (numString[intTransposer] == ' ')
        {
            numStringLength = intTransposer;
            break;
        }
        slicedCopy[slicedCopyIterator] = numString[intTransposer];
        slicedCopyIterator++;
        denomSize++;
    }
    int powerMultiplier = 1;
    for (int charToIntIterator = (numStringLength - placeCounter) - 1; charToIntIterator >= 0; charToIntIterator--)
    {
        mantissa = mantissa + (slicedCopy[charToIntIterator] - '0') * powerMultiplier;
        powerMultiplier *= 10;
    }
    denominator = 1;
    for (int denomIterator = 0; denomIterator < denomSize; denomIterator++)
    {
        denominator *= 10;
    }
    numerator = mantissa;
    return true;
}

//--
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to add the two numbers
    //hard coded return value to make the main() work
    result[0] = '4';
    result[1] = '.';
    result[2] = '1';
    result[3] = '6';
    result[4] = '6';
    result[5] = '6';
    result[6] = '6';
    result[7] = '6';
    result[8] = '6';
    result[9] = '\0';

    return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to subtract the two numbers
    return true;
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to multiply the two numbers
    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to divide the two numbers
    //hard coded return value to make the main() work
    result[0] = '0';
    result[1] = '.';
    result[2] = '5';
    result[3] = '6';
    result[4] = '2';
    result[5] = '5';
    result[6] = '\0';
    
    return true;
}
